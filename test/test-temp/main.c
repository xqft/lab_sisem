#include <msp430.h> 
#include "temp.h"

int dato = 750;
float temp;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	temp = conv_temp(dato);
	return 0;
}
