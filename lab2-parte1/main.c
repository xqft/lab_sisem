#include <msp430.h> 
#define LED1 (0x0001)
#include "timer_hw.h"
/**
 * main.c
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    int ESTADO_LED = 0;
	P1DIR |= LED1; // Configura pin LED1 salida
	_enable_interrupt();
	while(1){
	    P1OUT = ESTADO_LED;
	}
	return 0;
	
}



#pragma vector = TIMER0_A0_VECTOR
__interrupt void int_timer_A (void){

    ESTADO_LED ^= LED1; // Conmuta LED1 usando XOR

}
