/*
 * Temp.c
 *
 *  Created on: Mar 12, 2024
 *      Author: lucas
 */

#include <msp430.h>
#include "temp.h"

float conv_temp(int datotemp)
{
    return datotemp * 0.413 - 277.75;
}

// ~5149 cycles
void conv_temp_fast(int datotemp, temp_celsius_t* temp)
{
    int temp_raw = 0;
    int i;
    for (i = 0; i < datotemp; i++) {
      temp_raw += 413;
    }
    temp_raw -= 277750;

    int temporal = temp_raw;
    int enteros;
    for (enteros = 0; temporal >= 1000; enteros++) {
        temporal -= 1000;
    }

    int decimales = temp_raw;
    for (i = 0; i < enteros; i++) {
        decimales -= 1000;
    }

    temp->enteros = enteros;
    temp->decimales = decimales;
}

// ~554 cycles
void conv_temp_faster(int datotemp, temp_celsius_t* temp)
{
    int temp_raw = datotemp * 413 - 277750;

    int enteros = temp_raw / 1000;
    int decimales = temp_raw - enteros * 1000;

    temp->enteros = enteros;
    temp->decimales = decimales;
}
