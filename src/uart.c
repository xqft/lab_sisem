/*
 * uart.c
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */

#include <stdint.h>
#include <msp430.h>
#include "timer.h"

static uint8_t *tx_data;
static uint8_t tx_largo;

static char rx_data[10];
static volatile uint8_t rx_cont;

static uint8_t tx_cont;

static volatile uint8_t *flag_rx;

void p1_init()
{
    P1SEL |= BIT1 + BIT2;       // Set pines RXD y TXD
    P1SEL2 |= BIT1 + BIT2;    // ""
}

void uart_init()
{
    UCA0CTL1 |= UCSWRST;        // Set reset

    //Estado basico UART luego de un rst
    //UCA0CTL0 &= ~UCPEN;         // Set paridad off
    //UCA0CTL0 |= UC7BIT;         // Set 8-bit

    UCA0CTL1 |= UCSSEL_1;       // Set aclk fuente
    //UCA0CTL1 |= UCSSEL0;        // ""

    //Estado basico UART luego de un rst
    //BCSCTL1 &= ~XTS; // Modo 0 para el oscilador LFXT1 (selecciona low frequency).
    //BCSCTL1 |= DIVA_0;          // Divisor en /1.
    //BCSCTL3 |= LFXT1S_0;        // Cristal de 32768-Hz para el oscilador LFXT1.

    UCA0BR1 = 0x00;
    UCA0BR0 = 0x03;// baud-rate 9600bps a 32k fuente
    UCA0MCTL |= UCBRS_3;          //""
    UCA0MCTL |= UCBRS_0;

    UCA0CTL1 &= ~UCSWRST;        // Reset reset
    IE2 |= UCA0RXIE; //Habilito interrupciones de recepcion
}

void uart_transmit(uint8_t *data_ptr, uint8_t largo)
{
    tx_data = data_ptr;
    tx_largo = largo;
    UCA0TXBUF = *tx_data;
    tx_cont = 1;
    IE2 |= UCA0TXIE; // Habilito interrupciones de registro vacio
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void tx_isr(void)
{
    tx_cont++;
    if (tx_cont <= tx_largo)
    {
        tx_data++;
        UCA0TXBUF = *tx_data;
    }
    else
    {
        IE2 &= ~UCA0TXIE;
        tx_cont = 0;
    }
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void rx_isr(void)
{
    char received_char = UCA0RXBUF; // Leer el caracter recibido

    if (received_char == '\r')
    {
        // rx_message_complete = 1; // Activar la bandera de mensaje completo
        *flag_rx = 1;
    }

    // Almacenar el caracter en el buffer de recepcion
    else if (rx_cont < 10)
    {
        rx_data[rx_cont++] = received_char;
        // Verificar si se ha recibido el caracter de fin de mensaje
    }
}

void copy_rx_buff(char *rx_buff)
{
    int i;
    for (i = 0; i < rx_cont; i++)
    {
        rx_buff[i] = rx_data[i];
    }
    rx_cont = 0;
}

void set_flag_rx(uint8_t *flag_main)
{
    /*Set flag*/
    flag_rx = flag_main;        // En main inicializar flag_main en cero
}
