#include <msp430.h> 
#include <stdio.h>
#include "timer_hw.h"
#include "timer.h"

#define LED1 (0x0001)
const tiempo_t Tiempoini = {0,0,0,50};
tiempo_t tiempo_Real;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= LED1; // Configura pin LED1 salida
    config_timer_crystal();
    //config_timer_VLO();
    set_time(Tiempoini);
    _enable_interrupt();

    for(;;) {
        get_time(&tiempo_Real);
    }
    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void int_timer_A (void)
{
    P1OUT ^= LED1;  // Conmuta LED1 usando XOR
    inc_time();     // Incrementa 250 ms
}
