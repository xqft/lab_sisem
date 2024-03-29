#include <msp430.h> 
#include "temperatura.h"

/**
 * main.c
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    volatile int32_t temperatura;        //Variable que toma el valor de la temperatura
    volatile char* flag_de_main;         //Puntero a flag
    *flag_de_main = 0;          //Arranco con flag baja
    setFlagTemp(flag_de_main);  //Apunto flag a flag_de_main
	initTemp();
	runTemp();

	
	_enable_interrupt();        //Habilito interrupciones

	for(;;){
	    if (*flag_de_main == 1){
	        temperatura = getTemp();
	    }
	}
}
