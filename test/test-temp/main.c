#include <msp430.h> 
#include "Temp.h"


/**
 * main.c
 */
int dato = 750;
float temp;

int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	temp = ConvTemp(dato);
	return 0;
}
