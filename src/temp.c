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

void conv_temp_fast(int datotemp, temp_celsius_t* temp)
{
    int temp_raw = datotemp * 413 - 277750;

    int enteros = temp_raw / 1000;
    int decimales = temp_raw - enteros * 1000;

    temp->enteros = enteros;
    temp->decimales = decimales;
}
