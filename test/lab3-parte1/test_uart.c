#include <stdint.h>
#include <msp430.h> 
#include "uart.h"

/**
 * main.c
 */

static volatile char msg[4] = "hola";
static volatile char* msg[10];
static volatile uint8_t * flag_rx_main = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	p1_init();
	uart_init();
    uart_transmit(&msg, 4);
    set_flag_rx(&flag_rx_main);

    _enable_interrupt();
while(1){

    if(*flag_rx_main == 1){

            *flag_rx_main =0;

            copy_rx_buff(&msgg);
            uart_transmit(&msgg,1);

            while (1) {
                    int i;
                    for (i = 0; i < 10000; i++) {}
            }
    }

}

	return 0;
}
