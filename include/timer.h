/*
 * timer.h
 *
 *  Created on: 8 mar. 2024
 *      Author: lucaspereyra
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_


typedef struct {
    int horas;
    int minutos;
    int segundos;
    int milisegundos;

} tiempo_t;

void set_time(tiempo_t nuevoTiempo){}

void get_time(tiempo_t *tiempo){}

void inc_time() {}


#endif /* INCLUDE_TIMER_H_ */
