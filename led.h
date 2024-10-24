// led.h
#ifndef LED_H
#define LED_H
extern void* const RCC_base;
extern void* const GPIOB_base;
extern void* const GPIOC_base;
enum state {LED_OFF, LED_YELLOW, LED_BLUE};

void led_init(void);
void led_g_on(void);
void led_g_off(void);
void led(enum state s);

#endif
