/*
 * timer.c
 *
 *  Created on: 8 mar. 2024
 *      Author: lucaspereyra
 */

#include <msp430.h>
#include "timer.h"

static tiempo_t tiempoActual;

void set_time(tiempo_t nuevoTiempo){
    tiempoActual = nuevoTiempo;
}

void inc_time() {
    tiempoActual.milisegundos += 250;

    if (tiempoActual.milisegundos >= 1000) {
        tiempoActual.milisegundos -= 1000;
        tiempoActual.segundos++;

        if (tiempoActual.segundos >= 60) {
            tiempoActual.segundos -= 60;
            tiempoActual.minutos++;
            if (tiempoActual.minutos >= 60) {
                tiempoActual.minutos -= 60;
                tiempoActual.horas++;
                if (tiempoActual.horas >= 24) {
                    tiempoActual.horas -= 24;
                }
            }
        }
    }
}

void get_time(tiempo_t *tiempo){
    unsigned short s = __get_interrupt_state();
    __disable_interrupt();

    tiempo->horas = tiempoActual.horas;
    tiempo->minutos = tiempoActual.minutos;
    tiempo->segundos = tiempoActual.segundos;
    tiempo->milisegundos = tiempoActual.milisegundos;

    __set_interrupt_state(s);
}

void create_time_msg(tiempo_t *time, uint8_t *time_msg) {
	char aux_msg[2];

	// "Borramos" el contenido de time_msg
	time_msg[0] = '\0';

	// horas
	itoa(time->horas, aux_msg);
	if (strlen(aux_msg) == 1) {
		strcat(time_msg, "0");
	}
	strcat(time_msg, aux_msg);
	strcat(time_msg, ":");

	// minutos
	itoa(time->minutos, aux_msg);
	if (strlen(aux_msg) == 1) {
		strcat(time_msg, "0");
	}
	strcat(time_msg, aux_msg);
	strcat(time_msg, ":");

	// segundos
	itoa(time->segundos, aux_msg);
	if (strlen(aux_msg) == 1) {
		strcat(time_msg, "0");
	}
	strcat(time_msg, aux_msg);
}
