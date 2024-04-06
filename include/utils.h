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


#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

//#include "timer.h"

/**
 * Convierte un entero a ASCII
 * @param int value: valor entero a covertir
 * @param char* str: puntero a char donde guardar el resultado
 */
void itoa(int value, char* str);

#endif // UTILS_H_INCLUDED
