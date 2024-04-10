#include <stdint.h>
#include <string.h>
#include <msp430.h>
#include <stdlib.h>

#include "timer_hw.h"
#include "temperatura.h"
#include "uart.h"
#include "utils.h"
#include "timer.h"


/**
 * main.c
 */

#define LED1 (0x0001)

int main(void)
{
    P1DIR |= LED1; // Configura pin LED1 salida

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    uint16_t counter_max =20; // Periodo de adquicision de temperatura en multiplos de 250 ms.

    char temp_msg[4];
    char counter_msg[4];
    char time_msg[8];
    int32_t watch;                      // Variable que toma el valor de la temperatura.
    volatile uint8_t temp_flag = 0;     // Flag que indica nueva medida de temp. disponible.
    volatile uint8_t counter_flag = 0;  // Flag que indica que el contador del timer dio una vuelta.

    // Init timer module
    config_timer_crystal();
    set_counter_flag(&counter_flag);
    set_counter_max(counter_max);

    // Init temperature module
    initTemp();
    runTemp();
    setFlagTemp(&temp_flag);

    // Init UART module
    p1_init();
    uart_init();


    volatile tiempo_t t_actual = {23, 59, 59, 500};

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

                char dataa[3] = {rx_msg[0], rx_msg[1], '\0'};

                if(strcmp(dataa,"WP")==0){
                    dataa[0]= rx_msg[3];
                    dataa[1]= rx_msg[4];
                    uint8_t new_tick_int = atoi(dataa);
                    counter_max = new_tick_int;
                    set_counter_max(counter_max);

                }
                if(strcmp(dataa,"RP")==0){
                    itoa(counter_max, counter_msg);
                    uart_transmit(counter_msg,strlen(counter_msg));
                }
                if(strcmp(dataa,"RT")==0){
                    itoa(watch, temp_msg);
                    uart_transmit(temp_msg, strlen(temp_msg));

                }
                if (strcmp(dataa,"WH")==0){
                                   dataa[0]= rx_msg[3];
                                   dataa[1]= rx_msg[4];
                                   t_actual.horas = atoi(dataa);
                                   dataa[0]= rx_msg[6];
                                   dataa[1]= rx_msg[7];
                                   t_actual.minutos = atoi(dataa);
                                   dataa[0]= rx_msg[9];
                                   dataa[1]= rx_msg[10];
                                   t_actual.segundos = atoi(dataa);
                                   t_actual.milisegundos = 0;
                               }
                if (strcmp(dataa,"RH")==0){
                    char aux_msg[2];
                    itoa(t_actual.horas, time_msg);
                    strcat(time_msg,":");
                    itoa(t_actual.minutos, aux_msg);
                    strcat(time_msg, aux_msg);
                    strcat(time_msg,":");
                    itoa(t_actual.segundos, aux_msg);
                    strcat(time_msg, aux_msg);
                    uart_transmit(time_msg, strlen(time_msg));
                }
            }
    }

}
