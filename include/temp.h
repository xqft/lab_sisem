/*
 * Temp.h
 *
 *  Created on: Mar 12, 2024
 *      Author: lucas
 */

#ifndef INCLUDE_TEMP_H_
#define INCLUDE_TEMP_H_

/// Representa una temperatura en punto fijo, en Celsius.
typedef struct {
    int enteros;
    int decimales;
} temp_celsius_t;

/// Convierte la salida cruda del termometro en una temperature en Celsius.
///
/// No se recomienda su uso debido a su ineficiencia y gran cantidad de codigo
/// assembly que genera. Usar @ref conv_temp_faster
float conv_temp(int datotemp);
/// Convierte la salida cruda del termometro en una temperature en Celsius.
///
/// Utiliza la representacion en punto fijo @ref temp_celsius_t para evitar
/// aritmetica de punto flotante, resultando en menor codigo assembly y ciclos.
void conv_temp_fast(int datotemp, temp_celsius_t* temp);
/// Convierte la salida cruda del termometro en una temperature en Celsius.
///
/// Utiliza la representacion en punto fijo @ref temp_celsius_t para evitar
/// aritmetica de punto flotante, resultando en menor codigo y ciclos.
/// A diferencia de @ref conv_temp_fast, no utiliza bucles para simular
/// productos y divisiones, resultando en menos ciclos.
void conv_temp_faster(int datotemp, temp_celsius_t* temp);

#endif /* INCLUDE_TEMP_H_ */
