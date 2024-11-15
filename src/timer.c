// timer.c
#include "timer.h"

#include "led.h"
#include "matrix.h"
#include "stm32l475xx.h"

void timer_init(int max_us) {
  // Enable clock for TIM2
  RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
  // Clear potential flags in the status register by writing 0
  TIM2->SR = 0;
  // Clear the counter
  TIM2->CNT = 0;
  // Set the timer direction to upcounting mode
  TIM2->CR1 &= ~TIM_CR1_CMS;
  TIM2->CR1 &= ~TIM_CR1_DIR;
  // Set the prescaler to count every microsecond
  // the frequency is f_{CK_PSC} / (PSC[15:0] + 1).
  // Here 80MHz/(79+1) = 1MHz
  TIM2->PSC = 79;

  // Set the auto-reload value to the maximum value
  // so that the timer will overflow every max_us microseconds
  TIM2->ARR = max_us;
  // Enable the interruption started by the timer update event
  TIM2->DIER |= TIM_DIER_UIE;

  // Set higher priority for the USART1 interrupt
  // so that the data transmission will not be interrupted by other interrupts
  NVIC_SetPriority(USART1_IRQn, 1);
  NVIC_SetPriority(TIM2_IRQn, 2);
  // Enable the interruption in the NVIC
  NVIC_EnableIRQ(TIM2_IRQn);

  // Start the timer
  TIM2->CR1 |= TIM_CR1_CEN;
}

extern volatile uint8_t frame[192];
void TIM2_IRQHandler() {
  // Clear the update interrupt flag
  TIM2->SR &= ~TIM_SR_UIF;

  static int row_counter = 0;

  mat_set_row(row_counter, (rgb_color*)(frame + row_counter * 8 * 3));
  row_counter++;
  if (row_counter == 8) {
    row_counter = 0;
  }
}
