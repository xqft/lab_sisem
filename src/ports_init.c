/*
 * ports_init.c
 *
 *  Created on: Apr 23, 2024
 *      Author: lucas
 */
#include <msp430.h>


void p2_p3_init(){

    //P1DIR |= BIT3;
    //P2DIR |= BIT0 +BIT3 + BIT4 + BIT5 + BIT7;

        P1DIR = 0xFF;
        P1OUT = 0;

        P2DIR = 0xFF;
        P2OUT = 0x00;

        P3DIR = 0xFF;
        P3OUT = 0x00;
}
