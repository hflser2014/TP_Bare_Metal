// uart.c
#include "uart.h"
#include "stm32l475xx.h"

void uart_init(){
    // Enable clock for GPIOB
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    // Turn PB6 and PB7 on GPIOB to alternate mode, which means MODE6&7[1:0] = 10
    // GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
    // GPIOB->MODER &= ~(GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0);
    GPIOB->MODER = 0xffffaebf;
    // Turn PB6 and PB7 on USART TX/RX mode(), AFRL corresponds to AFR[0]
    GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL6 | GPIO_AFRL_AFSEL7);
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6_3 | GPIO_AFRL_AFSEL7_3);

    // Enable clock for USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    // Set USART1 to use PCLK
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL;
    // Reset serial port, and this register need to be cleared by ourselves
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

    // Set baud rate to 115200, with 80MHz clock 
    // 80MHz / 115200 = 694d = 2b6h
    USART1->BRR = 80000000 / 115200;
    // Set oversampling rate to 16: OVER8 = 0
    // Set word length to 8 bits: M[1:0]=00
    // Set parity to none: PCE = 0
    // Set stop bits to 1: STOP[1:0] = 00
    USART1->CR1 = 0;
    USART1->CR2 = 0;
    
    // Activate USART1
    // Activate TX and RX
    USART1->CR1 |= USART_CR1_UE
                | USART_CR1_TE | USART_CR1_RE;
}

void uart_putchar(uint8_t c){
    // Wait until TX buffer is empty
    while (!(USART1->ISR & USART_ISR_TXE));
    // Send character
    USART1->TDR = c;
}

uint8_t uart_getchar(){
    // Wait until the RX buffer is filled
    while (!(USART1->ISR & USART_ISR_RXNE));
    uint8_t c = USART1->RDR & USART_RDR_RDR_Msk;
    return c;
}

void uart_puts(const char *s){
   for (size_t i = 0; s[i] != '\0'; i++){
       uart_putchar(s[i]);
   } 
}

void uart_gets(char *s, size_t size){
    uint8_t c;
    for (size_t i = 0; i < size-1; i++){
        c = uart_getchar();
        if (s[i] == '\n' || s[i]=='\r'){
            break;
        }
        s[i] = (char) c;
    }
    s[size-1] = '\0';
}