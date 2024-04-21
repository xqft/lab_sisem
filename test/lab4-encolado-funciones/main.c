#include <stdint.h>
#include <string.h>
#include <msp430.h>
#include <stdlib.h>

#include "timer_hw.h"
#include "temperatura.h"
#include "uart.h"
#include "utils.h"
#include "timer.h"
#include "queue.h"

#define LED1 (0x0001)

#define TIME_MSG_MAX_LEN 16
#define TEMP_MSG_MAX_LEN 4
#define COUNTER_MSG_MAX_LEN 4

const tiempo_t t_inicial = { 23, 59, 59, 500 };

uint16_t counter_max = 20; // Periodo de adquicision de temperatura en multiplos de 250 ms.
int32_t watch;              // Variable que toma el valor de la temperatura.

void func_rx()
{
    uint8_t temp_msg[TEMP_MSG_MAX_LEN]; // Mensaje a transmitir para el comando RT
    uint8_t counter_msg[COUNTER_MSG_MAX_LEN]; // Mensaje a transmitir para el comando RP
    uint8_t time_msg[TIME_MSG_MAX_LEN]; // Mensaje a transmitir para el comando RH y periodico
    static char rx_msg[16];
    uint8_t rx_largo;
    tiempo_t t_actual;
    copy_rx_buff(rx_msg, &rx_largo);

    char data[3] = { rx_msg[0], rx_msg[1], '\0' };

    if (strcmp(data, "WP") == 0)
    {
        // Asumimos que el comando viene en el formato correcto

        data[0] = rx_msg[3];
        data[1] = rx_msg[4];

        counter_max = atoi(data);
        set_counter_max(counter_max);
    }
    if (strcmp(data, "RP") == 0)
    {
        itoa(counter_max, counter_msg);
        strcat(counter_msg, "\r");
        strcat(counter_msg, "\n");
        uart_transmit(counter_msg, strlen(counter_msg));
    }
    if (strcmp(data, "RT") == 0)
    {
        itoa(watch, temp_msg);
        strcat(temp_msg, "\r");
        strcat(temp_msg, "\n");
        uart_transmit(temp_msg, strlen(temp_msg));
    }
    if (strcmp(data, "WH") == 0)
    {
        // Asumimos que el comando viene en el formato correcto

        data[0] = rx_msg[3];
        data[1] = rx_msg[4];
        t_actual.horas = atoi(data);
        data[0] = rx_msg[6];
        data[1] = rx_msg[7];
        t_actual.minutos = atoi(data);
        data[0] = rx_msg[9];
        data[1] = rx_msg[10];
        t_actual.segundos = atoi(data);
        t_actual.milisegundos = 0;
        set_time(t_actual);
    }
    if (strcmp(data, "RH") == 0)
    {
        // Armo el mensaje con el tiempo actual
        get_time(&t_actual);
        create_time_msg(&t_actual, time_msg);

        // Nueva linea
        strcat(time_msg, "\r");
        strcat(time_msg, "\n");

        uart_transmit(time_msg, strlen(time_msg));
    }
}
void func_temp()
{
    tiempo_t t_actual;
    uint8_t temp_msg[TEMP_MSG_MAX_LEN]; // Mensaje a transmitir para el comando RT
    uint8_t time_msg[TIME_MSG_MAX_LEN]; // Mensaje a transmitir para el comando RH y periodico
    // Armo el mensaje con el tiempo actual
    get_time(&t_actual);
    create_time_msg(&t_actual, time_msg);

    watch = getTemp();

    // Añado temperatura
    itoa(watch, temp_msg);
    strcat(time_msg, " T=");
    strcat(time_msg, temp_msg);

    // Nueva linea
    strcat(time_msg, "\r");
    strcat(time_msg, "\n");

    uart_transmit(time_msg, strlen(time_msg));
}

void func_counter()
{
// Inicio una medida de temperatura
    runTemp();
}

int main(void)
{
    P1DIR |= LED1; // Configura pin LED1 salida

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    uint8_t temp_msg[TEMP_MSG_MAX_LEN]; // Mensaje a transmitir para el comando RT
    uint8_t counter_msg[COUNTER_MSG_MAX_LEN]; // Mensaje a transmitir para el comando RP
    uint8_t time_msg[TIME_MSG_MAX_LEN]; // Mensaje a transmitir para el comando RH y periodico

// Init timer module
    config_timer_crystal();
    set_counter_max(counter_max);

// Init temperature module
    initTemp();

// Init UART module
    p1_init();
    uart_init();

    set_time(t_inicial);

    const uint8_t *init_msg = "tx init ready";
    uart_transmit(init_msg, strlen(init_msg));

    set_callback_temp(func_temp);
    set_callback_rx(func_rx);
    set_callback_counter(func_counter);
    __enable_interrupt();

    while (1)
    {

        if (!queue_empty())
        {
            func_ptr_t next = dequeue();
            next();
        }
        else
        {
            // Ir a modo LPM3 si no hay mas procesamiento que realizar
            __bis_SR_register(LPM3_bits + GIE);
        }
    }
}
