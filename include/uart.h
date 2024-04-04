/*
 * uart.h
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

void p1_init();
void uart_init();
void uart_transmit(uint8_t *data_ptr, uint8_t largo);
void copy_rx_buff(char *rx_buff);
void set_flag_rx(uint8_t *flag_main);

#endif /* INCLUDE_UART_H_ */
