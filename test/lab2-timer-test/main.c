#include <msp430.h> 
#include <stdio.h>
#include "timer_hw.h"
#include "timer.h"

#define LED1 (0x0001)

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= LED1; // Configura pin LED1 salida
    config_timer_crystal();
    //config_timer_VLO();
    _enable_interrupt();

    for(;;) {}
    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void int_timer_A (void)
{
    P1OUT ^= LED1;  // Conmuta LED1 usando XOR
    inc_time();     // Incrementa 250 ms
}
