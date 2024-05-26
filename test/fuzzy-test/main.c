#include <msp430.h>
#include <stdint.h>

#include "uart.h"
#include "fuzzy.h"
#include "utils.h"

uint8_t data[210] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
					 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
					 0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
					 0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
					 0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
					 0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
					 0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
					 0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0};

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Init UART module
	p1_init();
	uart_init();

	fuzzy_edge_detect(data);

	uint16_t pixel;
	for (pixel = 0; pixel < 210; pixel++) {
		if (pixel % 21 == 0) uart_transmit("\n\r", 1);

		char pixel_str;
		itoa(data[pixel] >> 1, &pixel_str);

		uart_transmit(&pixel_str, 1);
	}

	return 0;
}
