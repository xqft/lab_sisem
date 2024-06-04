#include <msp430.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"
#include "fuzzy.h"
#include "utils.h"
#include "sobel.h"

const uint8_t data[IMAGE_PIXELS] = {
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,0,1,1,0,0,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,1,1,0,0,1,1,1,0,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,0,0,0,
                             0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0, // asd
                             0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,1,0,0,0,
                             0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


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
	int i;
    for (i = 0; i < 5000; i++);


	uint8_t resultado[RESULT_BYTES];
    //fuzzy_edge_detect(data, resultado);
	//sobelex_edge_detect(data,resultado);
	sobelaprox_edge_detect(data,resultado);
    uint8_t result_chars[23] = "";
    result_chars[0] = '\0';

    uint16_t row;
	for (row = 0; row < 21; row++) {
	    uint16_t col;
	    for (col = 0; col < 21; col++) {
	        uint16_t pixel = row*21 + col;
	        uint8_t byte = (pixel) / 8;
	        uint8_t bit = 7 - (pixel % 8);
	        if ((resultado[byte] >> bit) & 1 == 1){
	            strcat(result_chars, "+");
	        }
	        else {
	            strcat(result_chars, ".");
	        }
	      //  char result_char;
	      //  itoa((resultado[byte] >> bit) & 1, &result_char);
	      //  strcat(result_chars, &result_char);
	    }
        strcat(result_chars, "\r");
        strcat(result_chars, "\n");
        uart_transmit(result_chars, strlen(result_chars));
        result_chars[0] = '\0';

        for (i = 0; i < 8000; i++);
	}

	return 0;
}
