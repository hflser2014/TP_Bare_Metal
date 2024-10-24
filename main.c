#include "led.h"

int fibo(int n);
int global_var;

int main(){
	global_var+=1;
	led_init();

	led(LED_OFF);
	led_g_off();

	for (int i=0; i<5; i++){
		led_g_on();
		for (int i=0; i<100000; i++){
			asm volatile("nop");
		}
		led_g_off();

		led(LED_YELLOW);
		for (int i=0; i<100000; i++){
			asm volatile("nop");
		}
		led(LED_OFF);

		led(LED_BLUE);
		for (int i=0; i<100000; i++){
			asm volatile("nop");
		}
		led(LED_OFF);
	}
	return fibo(8);
}

int fibo(int n){
	if ((n == 0)|(n == 1)) {
		return 1;
	}
	else{
		return fibo(n-1) + fibo(n-2);
	}
}
