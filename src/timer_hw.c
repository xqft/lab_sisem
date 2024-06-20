#include <msp430.h>
#include <stdint.h>

#include "timer.h"
#include "queue.h"
#define LED1 (0x0001)

volatile static uint32_t counter = 0;
static uint8_t *counter_flag;
static uint32_t counter_max = 0;

static func_ptr_t counter_callback;

void config_timer_crystal() {
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

void config_timer_VLO() {
	TACTL |= TASSEL_1;        // Selecciono ACLK para el Timer A.
	TACTL |= MC_1;        // Modo 1 para el Timer A: cuenta de forma ascendente.
	TACCR0 = 3000;     // Constante a decrementar por el Timer A cada t=1/12000.

	BCSCTL1 &= ~XTS; // Modo 0 para el oscilador VLO (selecciona low frequency).
	BCSCTL1 |= DIVA_0;          // Divisor en /1.
	BCSCTL3 |= LFXT1S_2;        // Oscilador VLO de frecuencia 12-KHz.

	//TACTL   |= TAIE;             // Habilito las interrupciones del Timer A.
	TACCTL0 |= CCIE; // Habilito las interrupciones del Timer A en modo comparacion.
}

void set_counter_flag(uint8_t *flag) {
	counter_flag = flag;
}

void set_counter_max(uint32_t max) {
	counter_max = max;
}
void set_callback_counter(func_ptr_t func_counter){
    counter_callback = func_counter;
}

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
