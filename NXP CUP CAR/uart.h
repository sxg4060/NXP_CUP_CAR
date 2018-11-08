/***********************************************
* Author: Sahil Gogna and Patrick Landers
* Date: 11-8-18
* Description: UART Initialization Header
************************************************/
#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_put(char *ptr_str);
void putnumU(int i);
void uart_init(void);
uint8_t uart_getchar(void);
void uart_putchar(char ch);

#endif /* ifndef UART_H */
