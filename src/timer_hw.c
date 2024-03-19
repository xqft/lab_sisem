#include <msp430.h>
#include "timer.h"

void config_timer_crystal()
{
    TACTL |= TASSEL_1;      // Selecciono ACLK para el Timer A
    BCSCTL1 &= ~XTS;        // Modo 0 para el oscilador LFXT1 (selecciona low frequency)
    BCSCTL1 |= DIVA_0;      // Divisor en /1.
    BCSCTL3 |= LFXT1S_0;    // Cristal de 32768-Hz para el oscilador LFXT1
}

void config_timer_VLO(){

    TACTL |= TASSEL_1;      // Selecciono ACLK para el Timer A
    BCSCTL1 &= ~XTS;        // Modo 0 para el oscilador VLO (selecciona low frequency)
    BCSCTL1 |= DIVA_0;      // Divisor en /1.
    BCSCTL3 |= LFXT1S_2;    // Oscilador VLO de frecuencia 12-KHz
}
