// uart.c
#include "uart.h"
#include "matrix.h"
#include "stm32l475xx.h"

void uart_init(int baudrate){
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

    // BRR = fclk / baudrate
    USART1->BRR = 80000000 / baudrate;
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

void frame_transmission_init(){
    USART1->CR1 |= USART_CR1_RXNEIE; // Generate interrupt when the RXNE flag is set
    NVIC_EnableIRQ(USART1_IRQn); // enable NVIC irq for USART1 interrupt
}

// Here we choose uint8_t* as type rather than rgb_color
// because we want to write the data once we recieve an octet
extern uint8_t frame[192];
// if octet_count = -1, then we are not in the middle of a frame
// It's set to 0 when we start a frame by 0xff
static int octet_count = 0; 
void USART1_IRQHandler(){
    // Reset the interrupt flag caused by FE, ORE, NE, PE, RXNE
    if (USART1->ISR & (USART_ISR_FE | USART_ISR_ORE | USART_ISR_NE | USART_ISR_PE)){
        USART1->ICR |= (USART_ICR_FECF | USART_ICR_ORECF | USART_ICR_NCF | USART_ICR_PECF);
        return;
    }

    // Interrupt is cleared by reading the RDR register
    // So we don't need to clear it manually
    uint8_t c = USART1->RDR & USART_RDR_RDR_Msk;
    
    if (c == 0xff){
        octet_count = 0;
        return;
    }else if (octet_count == 192){
        octet_count = -1;
        return;
    }else if (octet_count == -1){
        return;
    }

    frame[octet_count++] = c;        
    return;
}