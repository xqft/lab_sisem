#include <msp430.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"
#include "fuzzy.h"
#include "utils.h"

const static uint8_t input_img[IMAGE_PIXELS] = {
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
                             0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,
                             0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,1,0,0,0,
                             0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,
                             0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
static uint8_t output_img[OUTPUT_BYTES];


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Init UART module
    p1_init();
    uart_init();

    __enable_interrupt();

    // Send ready UART message
    const uint8_t *init_msg = "System ready.\r\n";
    uart_transmit(init_msg, strlen(init_msg));

    fuzzy_edge_detect(data, resultado);

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
