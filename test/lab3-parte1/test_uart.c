#include <stdint.h>
#include <msp430.h> 
#include "uart.h"

/**
 * main.c
 */

static volatile char msg[5] = "listo";
static volatile uint8_t *flag_rx_main = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    p1_init();
    uart_init();
    uart_transmit(&msg, 5);
    set_flag_rx(&flag_rx_main);

    _enable_interrupt();
    while (1)
    {
        if (*flag_rx_main == 1)
        {
            *flag_rx_main = 0;

            copy_rx_buff(&msg);
            uart_transmit(&msg, 5);

            while (1)
            {
                int i;
                for (i = 0; i < 10000; i++)
                {
                }
            }
        }

    }

    return 0;
}
