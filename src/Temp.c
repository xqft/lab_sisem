/*
 * Temp.c
 *
 *  Created on: Mar 12, 2024
 *      Author: lucas
 */


#include "../../include/Temp.h"
#include <msp430.h>

float ConvTemp (int datotemp){
    int i;
    float temperatura = (datotemp*0.413 -277.75);
  /*  for (i = 1; i =< datotemp; i++){
        temperatura = temperatura + 0.413;
    }
    */
    return temperatura;

}


