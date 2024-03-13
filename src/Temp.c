/*
 * Temp.c
 *
 *  Created on: Mar 12, 2024
 *      Author: lucas
 */


#include "temp.h"
#include <msp430.h>

float ConvTemp (int datotemp){
    int i;
    float temperatura = (datotemp*0.413 -277.75) ;

    return temperatura;
}



