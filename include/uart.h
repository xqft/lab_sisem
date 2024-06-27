/*
 * uart.h
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */


#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

/**
 * Inicializa el puerto 1
 */
void p1_init();
/**
 * Inicializa configuracion del modulo UART
 */
void uart_init();
/**
 * Transmistir un mensaje por UART
 * @param data datos del mensaje a transmitir
 * @param length largo del mensaje a transmitir
 */
void uart_transmit(uint8_t *data, uint8_t length);

#ifdef UART_RX_H
/**
 * Copiar un mensaje recibido por UART
 * @param external_buff buffer externo de destino
 * @param length largo del mensaje
 *
 */
void copy_rx_buff(char *external_buff, uint8_t *length);
/**
 * Establece la flag de recepcion
 * @param flag puntero a la flag
 */
void set_flag_rx(uint8_t *flag);
/**
 * Establece la flag de error recepcion
 * @param flag puntero a la flag
 */
void set_flag_error_rx(uint8_t *flag);

#endif /* INCLUDE_UART_H_ */

#endif /* INCLUDE_UART_H_ */
