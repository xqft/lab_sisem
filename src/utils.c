/*
 * funciones_auxiliares.c
 *
 *  Created on: Mar 21, 2019
 *      Author: jschandy
 */

/**
 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C":
 */

#include <utils.h>
//#include "timer.h"

#define BASE 10

void strreverse(char* begin, char* end) {

    char aux;
    while(end>begin)
        aux=*end, *end--=*begin, *begin++=aux;
}

void itoa(int value, char* str) {
    static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* wstr=str;
    int sign;
    // Take care of sign
    if ((sign=value) < 0) value = -value;
    // Conversion. Number is reversed.
    do *wstr++ = num[value%BASE]; while(value/=BASE);
    if(sign<0) *wstr++='-';
    // Reverse string
    strreverse(str,wstr-1);
    *wstr='\0';
}

inline uint8_t fast_mod2(uint16_t num, uint8_t div) {
    return num & (div - 1);
}

inline uint8_t fast_div2(uint16_t num, uint8_t div_log2) {
    return num >> div_log2;
}

