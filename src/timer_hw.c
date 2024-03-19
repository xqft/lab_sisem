#include <msp430.h>
#include "timer.h"

void config_timer_crystal()
{
    TACTL   |= TASSEL_1;        // Selecciono ACLK para el Timer A.
    TACTL   |= MC_1;            // Modo 1 para el Timer A: cuenta de forma ascendente.
    TACCR0  = 8192;             // Constante a decrementar por el Timer A cada t=1/32768.


    BCSCTL1 &= ~XTS;            // Modo 0 para el oscilador LFXT1 (selecciona low frequency).
    BCSCTL1 |= DIVA_0;          // Divisor en /1.
    BCSCTL3 |= LFXT1S_0;        // Cristal de 32768-Hz para el oscilador LFXT1.

    //TACTL   |= TAIE;            // Habilito las interrupciones del Timer A.
    TACCTL0 |= CCIE;            // Habilito las interrupciones del Timer A en modo comparacion.
}

void config_timer_VLO(){
    TACTL   |= TASSEL_1;        // Selecciono ACLK para el Timer A.
    TACTL   |= MC_1;            // Modo 1 para el Timer A: cuenta de forma ascendente.
    TACCR0  = 3000;             // Constante a decrementar por el Timer A cada t=1/12000.

    BCSCTL1 &= ~XTS;            // Modo 0 para el oscilador VLO (selecciona low frequency).
    BCSCTL1 |= DIVA_0;          // Divisor en /1.
    BCSCTL3 |= LFXT1S_2;        // Oscilador VLO de frecuencia 12-KHz.

    //TACTL   |= TAIE;             // Habilito las interrupciones del Timer A.
    TACCTL0 |= CCIE;            // Habilito las interrupciones del Timer A en modo comparacion.
}
