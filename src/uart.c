/*
 * uart.c
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <msp430.h>

//#include "timer.h"
//#include "queue.h"
#define TX_DATA_MAX_LEN 16
#define RX_DATA_MAX_LEN 16

/// Buffer de datos de transmision
static uint8_t tx_data[TX_DATA_MAX_LEN];
/// Largo del buffer de transmision en bytes
static uint8_t tx_data_length = 0;
/// Siguiente dato disponible del buffer de transmision
static uint8_t tx_data_count = 0;

/// Buffer de datos de transmision
//static char rx_data[RX_DATA_MAX_LEN];
/// Largo del buffer de datos de transmision
//static volatile uint8_t rx_data_length = 0;
/// Puntero a flag que indica la recepcion de un dato
//static volatile uint8_t *rx_received_flag;
/// Bandera de error de recepcion
//static volatile uint8_t *rx_error_flag;
/// Bandera que bloquea la recepcion
//static volatile uint8_t rx_block_flag;
///puntero que toma el valor de la funcion callback de rx
//static func_ptr_t rx_callback;

/*
void set_callback_rx(func_ptr_t func_rx){
    rx_callback = func_rx;
}
*/
void p1_init() {
	P1SEL |= BIT1 + BIT2;       // Set pines RXD y TXD
	P1SEL2 |= BIT1 + BIT2;      // ""
}

void uart_init() {
	UCA0CTL1 |= UCSWRST;    // Set reset

	// Estado por defecto luego de un reset
	// UCA0CTL0 &= ~UCPEN;  // Set paridad off
	// UCA0CTL0 |= UC7BIT;  // Set 8-bit

	UCA0CTL1 |= UCSSEL_1;   // Set fuente ACLK
	UCA0CTL1 |= UCSSEL0;    // ""

	// Estado por defecto luego de un reset
	// BCSCTL1 &= ~XTS;     // Modo 0 para el oscilador LFXT1 (selecciona low frequency).
	// BCSCTL1 |= DIVA_0;   // Divisor en /1.
	// BCSCTL3 |= LFXT1S_0; // Cristal de 32768-Hz para el oscilador LFXT1.

	// Establecer baud-rate 9600 con fuente de 32 kHz.
	// Ref: Tabla 15-4, Family User's Guide.
	UCA0BR1 = 0x00;
	UCA0BR0 = 0x03;
	UCA0MCTL |= UCBRS_3;
	UCA0MCTL |= UCBRF_0;

	UCA0CTL1 &= ~UCSWRST;   // Reestablecer reset
	IE2 |= UCA0RXIE;        // Habilito interrupciones de recepcion
}

void uart_transmit(uint8_t *data, uint8_t length) {
	const uint8_t *error_msg = "tx overflow";

	if (length > TX_DATA_MAX_LEN) {
		data = error_msg;
		length = strlen(data);
	}

	memcpy(tx_data, data, length);
	tx_data_length = length;

	// Transmito el primer byte
	UCA0TXBUF = tx_data[0];
	tx_data_count = 1;

	// Habilito interrupcion de registro vacio
	IE2 |= UCA0TXIE;
}
/*
void copy_rx_buff(char *external_buff, uint8_t *length) {
	memcpy(external_buff, rx_data, rx_data_length);
	*length = rx_data_length;
}


void set_flag_rx(uint8_t *flag) {
	rx_received_flag = flag;   // En main inicializar flag en cero
}

void set_flag_error_rx(uint8_t *flag) {
	rx_error_flag = flag;
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void tx_isr(void) {
	if (tx_data_count < tx_data_length) {
		UCA0TXBUF = tx_data[tx_data_count];
		tx_data_count++;
	} else {
		IE2 &= ~UCA0TXIE;
		tx_data_count = 0;
	}
	//__low_power_mode_off_on_exit();
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void rx_isr(void) {
	// Siguiente dato disponible del buffer de recepcion
	static volatile uint8_t rx_data_count = 0;

	char received_char = UCA0RXBUF; // Leer el caracter recibido

	if (received_char == '\r') {

		if (rx_block_flag) {
			// Al terminar el mensaje invalido, levanto el bloqueo
			rx_block_flag = 0;

			return;
		}

		rx_data_length = rx_data_count;
		rx_data_count = 0;
		*rx_received_flag = 1;
		enqueue(rx_callback);
		__low_power_mode_off_on_exit();

	} else if (rx_data_count < RX_DATA_MAX_LEN) // saturar en el limite del buffer
	{
		if (rx_block_flag) {
			// Si hay un error, bloqueo la recepcion hasta terminar el mensaje.
			return;
		}

		rx_data[rx_data_count] = received_char;
		rx_data_count++;
	} else {
		// Buffer overflow, bloqueo la recepcion y reinicio el buffer
		rx_data_length = 0;
		rx_data_count = 0;

		*rx_error_flag = 1;
		rx_block_flag = 1;
	}
	//__low_power_mode_off_on_exit();
}
*/
