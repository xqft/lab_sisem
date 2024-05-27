#include <msp430.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"
#include "fuzzy.h"
#include "utils.h"

uint8_t data[IMAGE_BYTES] = {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
                             0b00000000,0b00111111,0b11111111,0b10000001,0b11111110,0b00001100,0b00001111,
                             0b11110000,0b00100000,0b01111111,0b10000001,0b00000011,0b11111100,0b00001000,
                             0b00011111,0b11100000,0b01000000,0b11111111,0b00000010,0b00000111,0b11111000,
                             0b00010000,0b00111111,0b01100000,0b10000001,0b11110011,0b10000100,0b00001111,
                             0b00011110,0b00100000,0b01110000,0b11111001,0b00000011,0b00000111,0b11101000,
                             0b00011000,0b00111111,0b11000000,0b11111111,0b11111110,0b00000000,0b00000000,
                             0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000};

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Init UART module
    config_timer_crystal();
	p1_init();
	uart_init();

    __enable_interrupt();
	const uint8_t *init_msg = "tx init ready\r\n";
	uart_transmit(init_msg, strlen(init_msg));

	uint8_t resultado[IMAGE_BYTES];
    fuzzy_edge_detect(data, resultado);

    uint8_t result_chars[23] = "";
    result_chars[0] = '\0';

    uint16_t row;
	for (row = 0; row < 21; row++) {
	    uint16_t col;
	    for (col = 0; col < 21; col++) {
	        uint8_t pixel = row*21 + col;
	        uint8_t byte = (pixel) / 8;
	        uint8_t bit = 7 - (pixel % 8);

	        char result_char;
	        itoa((resultado[byte] >> bit) & 1, &result_char);
	        strcat(result_chars, &result_char);
	    }
        strcat(result_chars, "\r");
        strcat(result_chars, "\n");
        uart_transmit(result_chars, strlen(result_chars));
        result_chars[0] = '\0';

        uint32_t i;
        for (i = 0; i < 50000; i++);
	}

	return 0;
}
