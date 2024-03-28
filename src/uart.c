/*
 * uart.c
 *
 *  Created on: Mar 27, 2024
 *      Author: lucas
 */


void initP1 (){
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;

}


void initUART(){

    UCSWRST = 1;
    UCA0CTL0 &= ~UCPEN
    UCA0CTL0 |= UC7BIT
    UCA0CTL1

}

