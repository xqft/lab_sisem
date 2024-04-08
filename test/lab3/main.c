#include <msp430.h> 
#include "temperatura.h"
#include "uart.h"
#include "utils.h"
/**
 * main.c
 */

static volatile char tx_msg[5] = "listo";
static volatile char rx_msg[5];

static volatile uint8_t * flag_rx_main;
static volatile uint8_t rx_largo;
static  uint8_t cont_temp;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
        volatile int32_t watch;        //Variable que toma el valor de la temperatura
        volatile char* flag_de_temp;         //Puntero a flag
        *flag_de_temp = 0;          //Arranco con flag baja
        setFlagTemp(flag_de_temp);  //Apunto flag a flag_de_main
        initTemp();
        runTemp();

        *flag_rx_main = 0;
        set_flag_rx(flag_rx_main);

        p1_init();
        uart_init();
        uart_transmit(&tx_msg, 5);


        _enable_interrupt();        //Habilito interrupciones

        for(;;){

                if (*flag_de_temp == 1){
                    watch = getTemp();
                    cont_temp++;
                }

            if(cont_temp == 2){
                cont_temp =0;

                if (*flag_rx_main == 1){
                          *flag_rx_main = 0;

                          itoa(watch,&rx_msg);
                          uart_transmit(&rx_msg, 16);
                }
            }
        }
    return 0;
}
