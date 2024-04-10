#include <stdint.h>
#include <string.h>
#include <msp430.h>

#include "timer_hw.h"
#include "temperatura.h"
#include "uart.h"
#include "utils.h"


/**
 * main.c
 */

#define LED1 (0x0001)

int main(void)
{
    P1DIR |= LED1; // Configura pin LED1 salida

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    int counter_max = 1; // Periodo de adquicision de temperatura en multiplos de 250 ms.

    char temp_msg[4];
    char counter_msg[4];
    int32_t watch;                      // Variable que toma el valor de la temperatura.
    volatile uint8_t temp_flag = 0;     // Flag que indica nueva medida de temp. disponible.
    volatile uint8_t counter_flag = 0;  // Flag que indica que el contador del timer dio una vuelta.

    // Init timer module
    config_timer_crystal();
    set_counter_flag(&counter_flag);
    set_counter_max(counter_max);

    // Init temp module
    initTemp();
    runTemp();
    setFlagTemp(&temp_flag);

    // Init UART module
    p1_init();
    uart_init();

    const uint8_t *init_msg = "tx init ready";
    uart_transmit(init_msg, strlen(init_msg));

    uint8_t rx_received_flag = 0;
        uint8_t rx_largo;

        set_flag_rx(&rx_received_flag);
        static char rx_msg[16];

    __enable_interrupt();

    while(1){

        if (temp_flag && counter_flag) {
            watch = getTemp();
            counter_flag = 0;
            runTemp();
            }

        if (rx_received_flag == 1)
            {
                rx_received_flag = 0;

                copy_rx_buff(rx_msg, &rx_largo);

                if(strcmp(rx_msg,"RP")==0){
                    itoa(counter_max, counter_msg);
                    uart_transmit(counter_msg,strlen(counter_max));
                }
                if(strcmp(rx_msg,"RT")==0){
                    itoa(watch, temp_msg);
                    uart_transmit(temp_msg, strlen(temp_msg));
                    counter_flag = 0;

                }
            }
    }

}
