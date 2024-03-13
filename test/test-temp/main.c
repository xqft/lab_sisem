#include <msp430.h> 
#include "../../include/Temp.h"


/**
 * main.c
 */
int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	int dato = 750;
	float temp = ConvTemp(dato);
	return 0;
}
