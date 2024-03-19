#include <msp430.h>
#include "timer.h"

void config_timer_crystal()
{
    TACTL |= TASSEL_1; // Selecciono ACLK para el Timer A
    BCSCTL1 |= LFXT1S0 | DIVA_0; // Modo 0 (low frec) para LFXT1 (crystal), divisor en 1
}
