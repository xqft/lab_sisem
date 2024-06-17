#include <msp430.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"
#include "fuzzy.h"
#include "utils.h"
#include "sobel.h"



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
uint8_t rx_received_flag = 0;
uint8_t rx_largo;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    // Init UART module

    set_flag_rx(&rx_received_flag);
    static char rx_msg[7];
    p1_init();
    uart_init();
    float UMBRAL1;

    __enable_interrupt();
    const uint8_t *init_msg22 = "Elige otro algoritmo para procesar \r\n";
    // Send button press UART message
    const uint8_t *init_msg = "Elige un algoritmo para procesar \r\n";
    uart_transmit(init_msg, strlen(init_msg));

    uint8_t on = 1;

    while(on){
    while(rx_received_flag) {
                on =0;
                copy_rx_buff(rx_msg, &rx_largo);
                char data[3] = { rx_msg[0], rx_msg[1], '\0' };
                if (strcmp(data, "FU") == 0) {
                    rx_received_flag = 0;
                    // Asumimos que el comando viene en el formato correcto
                    fuzzy_edge_detect(input_img, output_img);
                }else if (strcmp(data, "SE") == 0){
                    rx_received_flag = 0;
                    data[0] = rx_msg[3];
                    data[1] = rx_msg[5];
                    data[2] = rx_msg[6];

                    UMBRAL1 = atoi(data);
                    sobelex_edge_detect(input_img, output_img,UMBRAL1);
                }else if (strcmp(data, "SA") == 0){
                    rx_received_flag = 0;
                    data[0] = rx_msg[3];
                    data[1] = rx_msg[5];
                    data[2] = rx_msg[6];

                    UMBRAL1 = ((atoi(data))/100);
                    sobelaprox_edge_detect(input_img, output_img,UMBRAL1);
                }
     }
    if(!on){
    show_result();

    uart_transmit(init_msg22, strlen(init_msg22));}
    on = 1;

    }


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
