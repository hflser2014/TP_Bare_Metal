// uart.h
#ifndef UART_H
#define UART_H

#include "typedef.h"

void uart_init(void);
void uart_putchar(uint8_t c);
uint8_t uart_getchar(void);
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);

#endif