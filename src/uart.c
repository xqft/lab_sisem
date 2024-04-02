/*
 * uart.c
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */
#include "timer.h"


static uint8_t * Tx_data;
static uint8_t Tx_largo;
static char Rx_data[10];
static uint8_t cont_pos;
static volatile uint8_t Rx_largo;

static volatile char*    flag_Rx;

void initP1 (){
    P1SEL |= BIT1 + BIT2;       //Set pines RXD y TXD
    P1SEL2 |= BIT1 + BIT2;      // ""

}


void initUART(){
    UCA0CTL1 |= UCSWRST         // Reset Gral
    UCA0CTL0 &= ~UCPEN;         // Set paridad off
    UCA0CTL0 |= UC7BIT;         // Set 8-bit
    UCA0CTL1 &= ~UCSSEL1;       // Set aclk fuente
    UCA0CTL1 |= UCSSEL0;        // ""

    BCSCTL1 &= ~XTS;            // Modo 0 para el oscilador LFXT1 (selecciona low frequency).
    BCSCTL1 |= DIVA_0;          // Divisor en /1.
    BCSCTL3 |= LFXT1S_0;        // Cristal de 32768-Hz para el oscilador LFXT1.

    UCA0BR0 = 3;                //baud-rate 9600bps a 32k fuente
    UCA0MCTL = 3<<1;            //""


}

void Tx_int (uint8_t * data_ptr, uint8_t largo){
    Tx_data = data_ptr;
    Tx_largo = largo;
    UCA0TXBUF = * Tx_data;
    IE2 |= UCA0TXIE; // Habilito interrupciones de registro vacio
    cont_pos = 1;
}

#pragma vector = USCIAB0TX_VECTOR
__interrupt void Tx_isr(void){
    cont_pos++;
    if cont_pos <= Tx_largo{
        Tx_data++;
        UCA0TXBUF = * Tx_data;
    }
    else{
    IE2 &= !UCA0TXIE;
    cont_pos = 0;
    }
}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void Rx_isr(void){

    char received_char = UCA0RXBUF; // Leer el carácter recibido

    if (received_char == '\r') {
                  // rx_message_complete = 1; // Activar la bandera de mensaje completo
                  * flag_Rx = 1;
    }

        // Almacenar el carácter en el buffer de recepción
    else if (Rx_largo < 10) {
           Rx_data[Rx_largo++] = received_char;
           // Verificar si se ha recibido el carácter de fin de mensaje
    }
}

void copy_Rx_buff(char *Rx_buff){
    int i;
    for(i = 0; i < Rx_largo; i++){
    Rx_buff[i] = Rx_data[i];
    }
    Rx_largo = 0;
}

void setFlagRx(char* flag_main){
    /*Set flag*/
    flag_Rx = flag_main;        //En main inicializar flag_main en cero
}
