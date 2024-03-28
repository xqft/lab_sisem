/*
 * uart.c
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */
#include "timer.h"

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

