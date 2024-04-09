#include <stdint.h>
#include <string.h>
#include <msp430.h>

#include "timer_hw.h"
#include "temperatura.h"
#include "uart.h"
#include "utils.h"

#define LED1 (0x0001)

int main(void)
{
    P1DIR |= LED1; // Configura pin LED1 salida

    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    const uint32_t counter_max = 2; // Periodo de adquicision de temperatura en multiplos de 250 ms.

    char temp_msg[4];
    int32_t watch; 						// Variable que toma el valor de la temperatura.
    volatile uint8_t temp_flag = 0;		// Flag que indica nueva medida de temp. disponible.
    volatile uint8_t counter_flag = 0;	// Flag que indica que el contador del timer dio una vuelta.

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

    __enable_interrupt();

    while (1)
    {
        if (temp_flag) {
        	watch = getTemp();
            runTemp();
        }
        if (counter_flag) {
        	itoa(watch, temp_msg);
        	uart_transmit(temp_msg, strlen(temp_msg));

        	counter_flag = 0;
        }
    }
}
