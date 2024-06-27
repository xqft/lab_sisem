#include <msp430.h>
#include <stdint.h>
#include <string.h>

#include "uart.h"
#include "fuzzy.h"
#include "utils.h"
#include "sobel.h"
#include "timer_hw.h"

const static uint8_t input_img[IMAGE_PIXELS] =
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
          1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
          1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
          0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
          0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
          0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1,
          0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
          0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
          0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
          1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1,
          1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
          0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
          0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0 };
static uint8_t output_img[OUTPUT_BYTES];
static uint8_t rx_msg[7];

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    static uint8_t rx_received_flag = 0;
    static uint8_t rx_largo;

    // Init unused ports
    P3DIR = 0xFF;
    P3OUT = 0;

    // Init UART module

    CPU_16MHz(); // Set CPU frec 16MHz
    p1_init();
    uart_init();
    config_timer_crystal_capture();
    set_flag_rx(&rx_received_flag);

    // Pin used for timing
    P2DIR |= BIT0;
    P2OUT &= ~BIT0;

    __enable_interrupt();

    // Send button press UART message
    const uint8_t *init_msg = "Elige un algoritmo para procesar.\r\n";
    uart_transmit(init_msg, strlen(init_msg));

    for (;;)
    {
        if (rx_received_flag)
        {
            copy_rx_buff(rx_msg, &rx_largo);
            char data[3] = { rx_msg[0], rx_msg[1], '\0' };
            uint16_t time_ms;
            if (strcmp(data, "FU") == 0)
            {
                rx_received_flag = 0;
                // Asumimos que el comando viene en el formato correcto
                start_timing();
                fuzzy_edge_detect(input_img, output_img);
                time_ms = stop_timing();
            }
            else if (strcmp(data, "SE") == 0)
            {
                rx_received_flag = 0;
                data[0] = rx_msg[3];
                data[1] = rx_msg[4];
                data[2] = rx_msg[5];

                float umbral = atoi(data) / 100;
                start_timing();
                sobelex_edge_detect(input_img, output_img, umbral);
                time_ms = stop_timing();
            }
            else if (strcmp(data, "SA") == 0)
            {
                rx_received_flag = 0;
                data[0] = rx_msg[3];
                data[1] = rx_msg[4];
                data[2] = rx_msg[5];

                float umbral = atoi(data) / 100;
                start_timing();
                sobelaprox_edge_detect(input_img, output_img, umbral);
                time_ms = stop_timing();
            }
            else
            {
                continue;
            }
            show_result();
            print_time(time_ms);
        }
    }
    return 0;
}

void show_result()
{
    uint8_t row_chars[IMAGE_SIZE * 2 + 3] = "\0";

    uint16_t row, col;
    for (row = 0; row < IMAGE_SIZE; row++)
    {
        for (col = 0; col < IMAGE_SIZE; col++)
        {
            uint16_t pixel = row * IMAGE_SIZE + col;
            uint8_t byte = fast_div2(pixel, 3);
            uint8_t bit = 7 - fast_mod2(pixel, 8);

            char *pixel_char = (output_img[byte] >> bit) & 1 ? "@ " : ". ";
            strcat(row_chars, pixel_char);
        }
        strcat(row_chars, "\r\n");

        // Wait while UART is busy
        while ((UCA0STAT & UCBUSY) == 1)
        {
        }
        uart_transmit(row_chars, strlen(row_chars));

        row_chars[0] = '\0';
    }
}

inline void start_timing()
{
    restart_timer_capture();
    P2OUT |= BIT0;
}

inline uint16_t stop_timing()
{
    P2OUT &= ~BIT0;
    return get_timer_capture();
}

inline void print_time(uint16_t time_ms)
{
    // Wait while UART is busy
    while ((UCA0STAT & UCBUSY) == 1)
    {
    }

    uint8_t time_msg[4] = { };
    itoa(time_ms, time_msg);

    uint8_t *msg[32 + 1] = { '\0' };
    strcat(msg, "Demora del algoritmo: ");
    strcat(msg, time_msg);
    strcat(msg, " ms.\r\n");
    uart_transmit(msg, strlen(msg));
}
