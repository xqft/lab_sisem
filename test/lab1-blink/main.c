#include <msp430.h>
#define LED1 (0x0001)

int main(void)
{
    volatile unsigned int i;
    WDTCTL = WDTPW + WDTHOLD; // Detiene el watchdog timer
    P1DIR |= LED1; // Configura pin LED1 salida


    while(1)
    {
        P1OUT ^= LED1; // Conmuta LED1 usando XOR
        for (i=10000; i>0; i--); // Retardo software
    }
}
