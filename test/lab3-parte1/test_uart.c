#include <stdint.h>
#include <string.h>
#include <msp430.h>

#include "uart.h"

static char rx_msg[16];

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    uint8_t rx_received_flag = 0;
    uint8_t rx_error_flag = 0;
    uint8_t rx_largo;

    set_flag_rx(&rx_received_flag);
    set_flag_error_rx(&rx_error_flag);

    p1_init();
    uart_init();

    const uint8_t *init_msg = "tx init ready";
    uart_transmit(init_msg, strlen(init_msg));

    __enable_interrupt();

    while (1)
    {
        if (rx_received_flag == 1)
        {
            rx_received_flag = 0;

            copy_rx_buff(rx_msg, &rx_largo);
            uart_transmit(&rx_msg, rx_largo);
        }
        if (rx_error_flag == 1) {
        	const uint8_t *error_msg = "rx overflow";
        	uart_transmit(error_msg, strlen(error_msg));
        	rx_error_flag = 0;
        }
    }
}
