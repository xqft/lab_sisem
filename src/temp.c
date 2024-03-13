/*
 * Temp.c
 *
 *  Created on: Mar 12, 2024
 *      Author: lucas
 */

#include <msp430.h>
#include <temp.h>

float conv_temp(int datotemp)
{
    return datotemp * 0.413 - 277.75;
}
