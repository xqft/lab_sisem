/*
 * timer.h
 *
 *  Created on: 8 mar. 2024
 *      Author: lucaspereyra
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include "stdint.h"

/// Representa tiempo transcurrido
typedef struct {
    int horas;
    int minutos;
    int segundos;
    int milisegundos;

} tiempo_t;

/// Asigna la variable de tiempo interna del modulo.
void set_time(tiempo_t nuevoTiempo);
/// Devuelve una copia de la variable de tiempo interna del modulo.
void get_time(tiempo_t *tiempo);
/// Incrementa la variable de tiempo interna del modulo en 250 ms.
void inc_time();

/// Crear un arreglo con el tiempo
void create_time_msg(tiempo_t *time, uint8_t *time_msg);

#endif /* INCLUDE_TIMER_H_ */
