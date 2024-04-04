#include <stdint.h>
#include <msp430.h> 
#include "uart.h"

/**
 * main.c
 */

static volatile char msg[4] = "hola";
static volatile uint8_t flag_rx_main = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	p1_init();
	uart_init();

	while (1) {
	    //uart_transmit(&msg, 4);
	    UCA0TXBUF = 'A';
	    int i;
	    for (i = 0; i < 10000; i++) {}
	}

	return 0;
}
