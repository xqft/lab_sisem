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
    int i,enteros;

    int temp_raw;
    for(i = 1;i<=datotemp; i++){
      temp_raw += 413;
    }
    temp_raw = temp_raw -277750;


    int temporal = temp_raw;
       for(enteros = 0; 1000 <= temporal; enteros++){
           temporal -= 1000;
       }

    int decimales = temp_raw;
       for(i = 1; i <= enteros; i++){
           decimales -= 1000;
       }

    temp->enteros = enteros;
    temp->decimales = decimales;
}
