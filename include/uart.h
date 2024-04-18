/*
 * uart.h
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

/// Inicializar pines de transmision UART del puerto 1.
void p1_init();
/// Inicializar configuracion
void uart_init();
void uart_transmit(uint8_t *data, uint8_t length);
void copy_rx_buff(char *external_buff, uint8_t *length);
void set_flag_rx(uint8_t *flag);
void set_flag_error_rx(uint8_t *flag);


#endif /* INCLUDE_UART_H_ */
