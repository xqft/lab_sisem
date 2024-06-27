#include <msp430.h>
#include <stdint.h>

#include "timer.h"
#ifdef QUEUE
#include "queue.h"
#endif
#define LED1 (0x0001)

volatile static uint32_t counter = 0;

#ifdef QUEUE
static uint8_t *counter_flag;
static uint32_t counter_max = 0;

static func_ptr_t counter_callback;
#endif

void config_timer_crystal()
{
    TACTL |= TASSEL_1;        // Selecciono ACLK para el Timer A.
    TACTL |= MC_1;        // Modo 1 para el Timer A: cuenta de forma ascendente.
    TACCR0 = 9011;     // Constante a decrementar por el Timer A cada t=1/32768.
    TACTL |= ID_3;             // Preescalador /8.
    //TACCR0 = 4915;             // Constante a decrementar por el Timer A.

    BCSCTL1 &= ~XTS; // Modo 0 para el oscilador LFXT1 (selecciona low frequency).
    BCSCTL1 |= DIVA_0;          // Divisor en /1.
    BCSCTL3 |= LFXT1S_0;        // Cristal de 32768-Hz para el oscilador LFXT1.

    //TACTL   |= TAIE;            // Habilito las interrupciones del Timer A.
    //TACCTL0 |= CCIE; // Habilito las interrupciones del Timer A en modo comparacion.
}

void config_timer_crystal_capture()
{
    TACTL |= TACLR;
    TACTL |= TASSEL_1;  // Selecciono ACLK para el Timer A.
    TACCTL0 |= CAP;   // Modo capture (sirve para capturar intervalos de tiempo)
    //TACCTL0 |= CM_1;    // Captura en flanco de subida del input

    BCSCTL1 &= ~XTS; // Modo 0 para el oscilador LFXT1 (selecciona low frequency).
    BCSCTL1 |= DIVA_0;  // Divisor en /1.
    BCSCTL3 |= LFXT1S_0;  // Cristal de 32768-Hz para el oscilador LFXT1.
}

void config_timer_VLO()
{
    TACTL |= TASSEL_1;        // Selecciono ACLK para el Timer A.
    TACTL |= MC_1;        // Modo 1 para el Timer A: cuenta de forma ascendente.
    TACCR0 = 3000;     // Constante a decrementar por el Timer A cada t=1/12000.

    BCSCTL1 &= ~XTS; // Modo 0 para el oscilador VLO (selecciona low frequency).
    BCSCTL1 |= DIVA_0;          // Divisor en /1.
    BCSCTL3 |= LFXT1S_2;        // Oscilador VLO de frecuencia 12-KHz.

    //TACTL   |= TAIE;             // Habilito las interrupciones del Timer A.
    TACCTL0 |= CCIE; // Habilito las interrupciones del Timer A en modo comparacion.
}

#ifdef QUEUE
void set_counter_flag(uint8_t *flag) {
	counter_flag = flag;
}

void set_counter_max(uint32_t max) {
	counter_max = max;
}
void set_callback_counter(func_ptr_t func_counter){
    counter_callback = func_counter;
}
#endif

#ifdef QUEUE
#pragma vector = TIMER0_A0_VECTOR
__interrupt void int_timer_A(void) {
	P1OUT ^= LED1;  // Conmuta LED1 usando XOR
	inc_time();
	if (counter >= counter_max) {
		*counter_flag = 1;
        enqueue(counter_callback);
		counter = 0;
		//__low_power_mode_off_on_exit();
	} else {
		counter++;
	}
}
#endif

inline void restart_timer_capture()
{
    TACTL |= MC_0;  // Modo 0 para el Timer A: apagado
    TACTL |= TACLR; // Reset TAR y ID
    TACTL |= ID_1;  // Divisor /2. Cuenta maximo 4 segundos.
    TACTL |= MC_2;  // Modo 2 para el Timer A: cuenta hasta 0xFFFF (enceder)
}

inline uint16_t get_timer_capture()
{
    TACTL &= MC_0;  // Modo 0 para el Timer A: apagado
    // Para calcular la cantidad de tiempo en milisegundos, dividimos
    // por la cantidad de ticks en un milisegundo. O sea
    // f / 2 * 1000 = 16.339 ticks. Redondeamos a 16 ticks.
    // Entonces tenemos que dividir entre 16. Es lo mismo que
    // hacer x >> 4.
    float timer_exacto = TAR/16.339;
    return timer_exacto;
}
