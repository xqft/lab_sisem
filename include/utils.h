/**
 *  @file utils.h
 *  @brief Funciones auxiliares para facilitar el parseo de datos
 *
 *  @Date 14 Feb 2019
 *  @Author  Javier Schandy <jschandy@fing.edu.uy>
 *  @Version 1.0 Implementacion inicial
 * 
 *  @Date 16 Apr 2020
 *  @Author Carolina Cabrera <ccabrera@fing.edu.uy>
 *  @Version 1.1 Se comenta linea de #include "timer.h" incluída por error y se corrige campo @file de doxygen.
 */

#include <stdint.h>

#pragma once

/**
 * Convierte un entero a ASCII
 * @param int value: valor entero a covertir
 * @param char* str: puntero a char donde guardar el resultado
 */
void itoa(int value, char* str);

/**
 * Operacion mod rapida para dos bytes, donde el divisor
 * es una potencia de dos.
 *
 * @param uint16_t num: numerador
 * @param uint8_t div: divisor que debe ser potencia de dos
 */
inline uint8_t fast_mod2(uint16_t num, uint8_t div);

/**
 * Operacion div rapida para dos bytes, donde el divisor
 * es una potencia de dos.
 *
 * @param uint16_t num: numerador
 * @param uint8_t div_log2: logaritmo base 2 del divisor, que
 *                          debe ser potencia de dos.
 */
inline uint8_t fast_div2(uint16_t num, uint8_t div_log2);
