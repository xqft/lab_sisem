#include <stdint.h>
#include <msp430.h> 
#include "uart.h"

/**
 * main.c
 */

static volatile char tx_msg[5] = "listo";
static volatile char rx_msg[5];

static volatile uint8_t * flag_rx_main;
static volatile uint8_t rx_largo;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    *flag_rx_main = 0;
    set_flag_rx(flag_rx_main);

    p1_init();
    uart_init();
    uart_transmit(&tx_msg, 5);


    __enable_interrupt();

    while (1)
    {
      //  if (IFG2 & UCA0RXIFG == 1) {
        //    char received_char = UCA0RXBUF;
          //  tx_msg[0] = received_char;
          //  uart_transmit(&tx_msg, 1);
        //}
        if (*flag_rx_main == 1)
        {
            *flag_rx_main = 0;

            copy_rx_buff(&rx_msg, &rx_largo);
            uart_transmit(&rx_msg, rx_largo);

            int i;
            for (i = 0; i < 10000; i++)
            {

            }
        }

    }

    return 0;
}
