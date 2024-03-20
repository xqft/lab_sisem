/**
 * @file temperatura.h
 * @brief Laboratorio 2 - Sistemas Embebidos - Fing
 * Modulo temperatura
 *
 * @author Javier Schandy <jschandy@fing.edu.uy>
 * @version 1.0
 * 
 * @date 16/3/2020
 * @author  Carolina Cabrera <ccabrera@fing.edu.uy>
 * @version 1.1
 */

#ifndef __TEMPERATURA_H__
#define __TEMPERATURA_H__

#include <stdint.h>

/**
 * @brief Inicializa el ADC, lo configura en modo "sensar temperatura" y espera que estabilice la Ref0
 */
void initTemp();

/**
 * @brief Le indica al modulo temperatura qué bandera activar cuando haya una medida de temperatura lista
 * @param char* flag_main: bandera a encender cuando haya una medida de temperatura lista
 *
 */
void setFlagTemp(char* flag_main);

/**
 * @brief Comienza una lectura de temperatura
 */
void runTemp();

/**
 * Obtengo la ultima medida de temperatura en miligrados Celsius
 *
 * @return int32_t temperatura en miligrados celsius
 *
 */
int32_t getTemp();

#endif // __TEMPERATURA_H__
