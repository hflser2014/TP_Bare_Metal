// led.c
#include "led.h"

#include "stm32l475xx.h"

void led_init() {
  // activate clock by setting bit 1 and 2 of AHB2ENR
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);

  // Set pb14 to output mode
  GPIOB->MODER &= ~GPIO_MODER_MODE14_1;

  // Set pc9 to input mode
  GPIOC->MODER &= ~GPIO_MODER_MODE9;
}

void led_g_on() {
  // Set pb14 to high voltage
  GPIOB->BSRR |= GPIO_BSRR_BS14;
}

void led_g_off() {
  // Reset pb14 to low voltage
  GPIOB->BSRR |= GPIO_BSRR_BR14;
}

void led(enum state s) {
  switch (s) {
    case LED_OFF:
      // Set pc9 to input mode
      GPIOC->MODER &= ~GPIO_MODER_MODE9;
      break;
    case LED_YELLOW:
      // Set pc9 to output mode, then set high voltage
      GPIOC->MODER |= GPIO_MODER_MODE9_0;
      GPIOC->BSRR |= GPIO_BSRR_BS9;
      break;
    case LED_BLUE:
      // Set pc9 to output mode, then set low voltage
      GPIOC->MODER |= GPIO_MODER_MODE9_0;
      GPIOC->BSRR |= GPIO_BSRR_BR9;
      break;
  }
}
