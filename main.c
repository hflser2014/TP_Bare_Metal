#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"

int global_var;
extern const uint8_t _binary_image_raw_start; // this is the start of the image
extern const uint8_t _binary_image_raw_end;
extern const int _binary_image_raw_size;
uint8_t frame[192];

int fibo(int n);
unsigned int sum32(int num);
void print_hex32(unsigned int sum);
void echo(void);



int main(){
	global_var+=1;

	/* section 4 */
	clocks_init();

	/* section 6 Data transmission */
	int baudrate = 38400;
	uart_init(baudrate);
	// uart_putchar('T');
	// uart_puts("Hello World!\n");
	// echo(); // echo function used to test uart_getchar and uart_putchar
	// unsigned int sum = sum32(128);
	// uart_puts("Sum is: ");
	// print_hex32(sum);

	/* section 8 */
	irq_init();
	button_init();

	/* section 7 */ 
	matrix_init();
	for (int i = 0; i < 1000; i++) {
		asm volatile("nop");
	}

	// for (int i = 0; i < 2; i++) {
	// 	test_pixels();
	// }
	// while (1){
	// 	display_static_image(&_binary_image_raw_start, _binary_image_raw_size);
	// }
	frame_display_init();
	print_frame();

	// /* section 3 */
	// led_init();

	// led(LED_OFF);
	// led_g_off();

	// for (int i=0; i<20; i++){
	// 	led_g_on();
	// 	for (int i=0; i<1000000; i++){
	// 		asm volatile("nop");
	// 	}
	// 	led_g_off();

	// 	led(LED_YELLOW);
	// 	for (int i=0; i<1000000; i++){
	// 		asm volatile("nop");
	// 	}
	// 	led(LED_OFF);

	// 	led(LED_BLUE);
	// 	for (int i=0; i<1000000; i++){
	// 		asm volatile("nop");
	// 	}
	// 	led(LED_OFF);
	// }
	
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

void echo(){
	uint8_t c;
	while(1){
		c = uart_getchar();
		uart_putchar(c);
		if (c == '\n'){
			break;
		}
	}
}


unsigned int sum32(int num){
	int sum = 0;
	int n;
	for (int i=0; i<num; i++){
		n = uart_getchar();
		sum += n;
	}
	return sum;
}

void print_hex32(unsigned int sum) {
	uart_puts("0x");
    for (int i = 7; i >= 0; i--) {
        uint8_t byte = (sum >> (i * 4)) & 0xF;
        if (byte < 10) {
            uart_putchar('0' + byte);  // Output '0' to '9'
        } else {
            uart_putchar('A' + (byte - 10));  // Output 'A' to 'F'
        }
    }
    uart_putchar('\n');
}