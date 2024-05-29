#include <msp430.h>
#include <stdint.h>

#include "uart.h"
#include "fuzzy.h"
#include "utils.h"
#define IMAGE_BYTES 56
#define IMAGE_PIXELS 441


uint8_t data[IMAGE_BYTES] = {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
                     0b00000000,0b00111111,0b11111111,0b10000001,0b11111110,0b00001100,0b00001111,
                     0b11110000,0b00100000,0b01111111,0b10000001,0b00000011,0b11111100,0b00001000,
                     0b00011111,0b11100000,0b01000000,0b11111111,0b00000010,0b00000111,0b11111000,
                     0b00010000,0b00111111,0b01100000,0b10000001,0b11110011,0b10000100,0b00001111,
                     0b00011110,0b00100000,0b01110000,0b11111001,0b00000011,0b00000111,0b11101000,
                     0b00011000,0b00111111,0b11000000,0b11111111,0b11111110,0b00000000,0b00000000,
                     0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b0};

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Init UART module
    config_timer_crystal();
	p1_init();
	uart_init();

    __enable_interrupt();
	const uint8_t *init_msg = "tx init ready";
	uart_transmit(init_msg, strlen(init_msg));

	uint8_t resultado[IMAGE_BYTES];
    fuzzy_edge_detect(data, resultado);

    uint16_t pixel;
	for (pixel = 0; pixel < IMAGE_PIXELS; pixel++) {
		if (pixel % 21 == 0) {
		    uart_transmit("\r", 2);
		    uart_transmit("\n", 2);
		}

		uint8_t byte = pixel / 8;
		uint8_t bit = 7 - (pixel % 8);
		char pixel_str;
		itoa((resultado[byte] >> bit) & 1, &pixel_str);

		uart_transmit(&pixel_str, 1);
	}

	return 0;
}
