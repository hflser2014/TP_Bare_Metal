// led.c 
#include "led.h"

void* const RCC_base = (void *) 0x40021000;
void* const GPIOB_base = (void *) 0x48000400;
void* const GPIOC_base = (void *) 0x48000800;

void led_init(){	
	// activate clock, set bit 1 and 2
	unsigned int* RCC_AHB2ENR = RCC_base + 0x4c;
	*RCC_AHB2ENR |= ((1 << 1) | (1 << 2));
	
	// Set pin mode, set bit 29:28 to 01
	unsigned int* GPIOB_MODER = GPIOB_base + 0x00;
	*GPIOB_MODER &= ~((1 << 29)|(1 << 28)); 
	*GPIOB_MODER |= (1 << 28);

	unsigned int* GPIOC_MODER = GPIOC_base + 0x00;
	*GPIOC_MODER &= ~((1 << 19)|(1 << 18));
}

void led_g_on(){
	unsigned int* GPIOB_BSRR = GPIOB_base + 0x18;
	*GPIOB_BSRR |= (1 << 14); ;
}

void led_g_off(){
	unsigned int* GPIOB_BSRR = GPIOB_base + 0x18;
	*GPIOB_BSRR |= (1 << 30);
}

void led(enum state s){
	unsigned int* GPIOC_MODER = GPIOC_base + 0x00;
	unsigned int* GPIOC_BSRR = GPIOC_base + 0x18;
	switch(s){
		case LED_OFF:
			*GPIOC_MODER &= ~((1 << 19)|(1 << 18));
			break;
		case LED_YELLOW:
			*GPIOC_MODER &= ~(1 << 19);
			*GPIOC_MODER |= (1 << 18);
			*GPIOC_BSRR = (1 << 9);
			break;
		case LED_BLUE:
			*GPIOC_MODER &= ~(1 << 19);
			*GPIOC_MODER |= (1 << 18);
			*GPIOC_BSRR = (1 << 25);
			break;
	}
}
