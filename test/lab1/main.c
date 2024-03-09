#include <timer.h>
#include <msp430.h>

tiempo_t t_inicial = {23, 59, 59, 500};
tiempo_t t1;
tiempo_t t2;
//tiempo_t tiempoActual;

int main (void)
{
      tiempo_t t_local;

      WDTCTL = WDTPW | WDTHOLD;
      set_time(t_inicial);
      get_time(&t1);
      inc_time();
      inc_time();
      inc_time();
      inc_time();
      get_time(&t2);
      get_time(&t_local);

return 0;
}

