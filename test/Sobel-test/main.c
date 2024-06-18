#include <msp430.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

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
    config_timer_crystal();
    float umbral1 = 3;

    __enable_interrupt();
    // Send button press UART message
    const uint8_t *init_msg = "Press button to start.\r\n";
    uart_transmit(init_msg, strlen(init_msg));

    // Wait for button press
    // while ((P1IN & BIT3) != 0) {}

    // Leer el valor inicial del contador del Timer_A
    uint16_t start_time = TAR;

    // Ejecutar el algoritmo
    //fuzzy_edge_detect(input_img, output_img);
    sobelex_edge_detect(input_img, output_img, umbral1);
    //sobelaprox_edge_detect(input_img, output_img, umbral1);

    // Leer el valor final del contador del Timer_A
    uint16_t end_time = TAR;

    // Calcular el tiempo transcurrido
    int final_time = (end_time - start_time);

    // Convertir el tiempo transcurrido a microsegundos (ACLK = 32768 Hz, cada tick = ~0.030.5 ms)
    float final_time_us = final_time * 0.0305;

    show_result();

    // Transmitir el tiempo transcurrido por UART
    uint8_t msg[40]= "\r\n Demora del algoritmo: ";
   // itoa(final_time_us, msg);
    uint8_t aux_msg[4];
    itoa(final_time_us, aux_msg);
    strcat(msg,aux_msg);
    strcat(msg," ms");
    uart_transmit(msg, strlen(msg));




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
