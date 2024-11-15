#include "buttons.h"

#include "led.h"
#include "stm32l475xx.h"

void button_init() {
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN_Msk;  // enable GPIOC clock
  GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;   // set to input mode

  SYSCFG->EXTICR[3] |=
      SYSCFG_EXTICR4_EXTI13_PC;  // select PC13 as source of EXTI13 (0010)

  EXTI->IMR1 |= EXTI_IMR1_IM13_Msk;    // enable interrupt on EXTI13
  EXTI->FTSR1 |= EXTI_FTSR1_FT13_Msk;  // enable falling edge trigger on EXTI13

  NVIC_EnableIRQ(EXTI15_10_IRQn);  // enable EXTI line 13
}

void EXTI15_10_IRQHandler() {
  EXTI->PR1 |= EXTI_PR1_PIF13_Msk;  // this bit is cleared by writing a 1

  if (GPIOB->ODR & GPIO_ODR_OD14_Msk) {  // if led green on, alternate
    led_g_off();
  } else {
    led_g_on();
  }
}