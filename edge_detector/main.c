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

    // Send button press UART message
    const uint8_t *init_msg = "Press button to start.\r\n";
    uart_transmit(init_msg, strlen(init_msg));

    // Configure control button pin 1.3 register
    P1DIR &= ~BIT3; // set 1.3 as output

    // Wait for button press
    while ((P1IN & BIT3) != 0) {}

    fuzzy_edge_detect(input_img, output_img);

    show_result();

    return 0;
}

void show_result() {
    uint8_t result_chars[23] = "\0";

    uint16_t row;
    for (row = 0; row < 21; row++) {
        uint16_t col;
        for (col = 0; col < 21; col++) {
            uint16_t pixel = row * 21 + col;
            uint8_t byte = fast_div2(pixel, 3);
            uint8_t bit = 7 - fast_mod2(pixel, 8);

            char* pixel_char = (output_img[byte] >> bit) & 1 ? "+" : ".";
            strcat(result_chars, pixel_char);
        }
        strcat(result_chars, "\r\n");

        // Wait while UART is busy
        while ((UCA0STAT & UCBUSY) == 1) {}
        uart_transmit(result_chars, strlen(result_chars));

        result_chars[0] = '\0';
    }
}
