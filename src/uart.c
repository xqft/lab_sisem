/*
 * uart.c
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */

#include <stdint.h>
#include <string.h>
#include <msp430.h>

#include "timer.h"

/// Buffer de datos de transmision
static uint8_t tx_data[16];
/// Largo del buffer de transmision en bytes
static uint8_t tx_data_length;
/// Siguiente dato del buffer a enviar
static uint8_t tx_data_count;

/// Buffer de datos de transmision
static char rx_data[16];
/// Largo del buffer de datos de transmision
static volatile uint8_t rx_data_length;
/// Puntero a flag que indica la recepcion de un dato
static volatile uint8_t *rx_received_flag;

void p1_init()
{
    P1SEL |= BIT1 + BIT2;       // Set pines RXD y TXD
    P1SEL2 |= BIT1 + BIT2;      // ""
}

void uart_init()
{
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

void uart_transmit(uint8_t *data, uint8_t length)
{
    memcpy(tx_data, data, length);
    tx_data_length = length;

    // Transmito el primer byte
    UCA0TXBUF = *tx_data;
    tx_data_count = 1;
    // Habilito interrupcion de registro vacio
    IE2 |= UCA0TXIE;
}

void copy_rx_buff(char *external_buff, uint8_t *length)
{
    memcpy(external_buff, rx_data, rx_data_length);
    *length = rx_data_length;
}

void set_flag_rx(uint8_t *flag)
{
    rx_received_flag = flag;   // En main inicializar flag en cero
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void tx_isr(void)
{
    if (tx_data_count <= tx_data_length)
    {
        UCA0TXBUF = tx_data[tx_data_count];
        tx_data_count++;
    }
    else
    {
        IE2 &= ~UCA0TXIE;
        tx_data_count = 0;
    }
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void rx_isr(void)
{
    char received_char = UCA0RXBUF; // Leer el caracter recibido

    if (received_char == '\r')
    {
        *rx_received_flag = 1;
    }
    else if (rx_data_length < 16) // saturar en el limite del buffer
    {
        rx_data[rx_data_length++] = received_char;
    }
}
