/*
 * timer.c
 *
 *  Created on: 8 mar. 2024
 *      Author: lucaspereyra
 */

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
    tiempo->horas = tiempoActual.horas;
    tiempo->minutos = tiempoActual.minutos;
    tiempo->segundos = tiempoActual.segundos;
    tiempo->milisegundos = tiempoActual.milisegundos;
}
