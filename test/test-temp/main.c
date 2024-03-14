#include <msp430.h> 
#include "temp.h"

int datotemp = 751;

// float temp;
temp_celsius_t temp;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	// temp = conv_temp(datotemp);
	// conv_temp_fast(datotemp, &temp);
    conv_temp_faster(datotemp, &temp);
	return 0;
}
