#include <msp430.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"
#include "fuzzy.h"
#include "utils.h"
#include "sobel.h"
#include "timer_hw.h"

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
    config_timer_crystal_capture();
    float umbral1 = 3;

    // Pin used for timing
    P2DIR |= BIT0;
    P2OUT &= ~BIT0;

    __enable_interrupt();

    // Send button press UART message
    const uint8_t *init_msg = "Press button to start.\r\n";
    uart_transmit(init_msg, strlen(init_msg));

    // Configure control button pin 1.3 register
    P1DIR &= ~BIT3; // set 1.3 as output

    // Wait for button press
    while ((P1IN & BIT3) != 0) {}

    start_timing();

    fuzzy_edge_detect(input_img, output_img);
    //sobelex_edge_detect(input_img, output_img,3);
    //sobelaprox_edge_detect(input_img, output_img);

    uint16_t time_ms = stop_timing();
    show_result();
    print_time(time_ms);

    return 0;
}

void show_result() {
    uint8_t row_chars[IMAGE_SIZE * 2 + 3] = "\0";

    uint16_t row, col;
    for (row = 0; row < IMAGE_SIZE; row++) {
        for (col = 0; col < IMAGE_SIZE; col++) {
            uint16_t pixel = row * IMAGE_SIZE + col;
            uint8_t byte = fast_div2(pixel, 3);
            uint8_t bit = 7 - fast_mod2(pixel, 8);

            char* pixel_char = (output_img[byte] >> bit) & 1 ? "@ " : ". ";
            strcat(row_chars, pixel_char);
        }
        strcat(row_chars, "\r\n");

        // Wait while UART is busy
        while ((UCA0STAT & UCBUSY) == 1) {}
        uart_transmit(row_chars, strlen(row_chars));

        row_chars[0] = '\0';
    }
}

inline void start_timing() {
    restart_timer_capture();
    P2OUT |= BIT0;
}

inline uint16_t stop_timing() {
    P2OUT &= ~BIT0;
    return get_timer_capture();
}

inline void print_time(uint16_t time_ms) {
    // Wait while UART is busy
    while ((UCA0STAT & UCBUSY) == 1) {}

    const uint8_t *msg0 = "Demora del algoritmo: ";
    uart_transmit(msg0, strlen(msg0));
    while ((UCA0STAT & UCBUSY) == 1) {}

    uint8_t msg1[4] = 0;
    itoa(time_ms, msg1);
    uart_transmit(msg1, strlen(msg1));
    while ((UCA0STAT & UCBUSY) == 1) {}

    const uint8_t *msg2 = " ms.\r\n";
    uart_transmit(msg2, strlen(msg2));
    while ((UCA0STAT & UCBUSY) == 1) {}
}
