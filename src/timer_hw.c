#include <msp430.h>
#include "timer.h"

void config_timer_crystal()
{
    TACTL |= TASSEL_1;
    BCSCTL1 |= LFXT1S0 | DIVA;
}
