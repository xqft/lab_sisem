/*
 * Temp.h
 *
 *  Created on: Mar 12, 2024
 *      Author: lucas
 */

#ifndef INCLUDE_TEMP_H_
#define INCLUDE_TEMP_H_

typedef struct {
    int enteros;
    int decimales;
} temp_celsius_t;

float conv_temp(int datotemp);
void conv_temp_fast(int datotemp, temp_celsius_t* temp);

#endif /* INCLUDE_TEMP_H_ */
