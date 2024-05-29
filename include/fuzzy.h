#pragma once

#include <stdint.h>

// 0: white
// 1: black
#define RULE1 0b00000111
#define RULE2 0b11100000
#define RULE3 0b10010100
#define RULE4 0b00101001
#define RULE5 0b11010100
#define RULE6 0b00101011
#define RULE7 0b10010110
#define RULE8 0b01101001

/**
 * Corre el algoritmo fuzzy de deteccion de bordes, escribiendo la salida
 * en el segundo bit menos significativo de los bytes de entrada.
 *
 * @param data 	Puntero a arreglo de 441 bytes, en cuyo bit menos significativo
 * 				se contiene cada pixel de la imagen de entrada. Los pixeles
 * 				resultantes se escribiran en el segundo bit mas significativo
 * 				de cada byte.
 */
void fuzzy_edge_detect(uint8_t* data,uint8_t* result);

/**
 * Evalua los 8 pixeles vecinos correspondientes al indice enviado como parametro y
 * guarda el resultado en un unico byte.
 *
 * La convencion utilizada es: 0 para un pixel blanco, 1 para un pixel negro.
 *
 * La codificacion para el byte resultante es guardar, en cada bit, la informacion de un pixel;
 * si enumeramos cada bit del byte resultante de manera:
 *
 * byte: 0000 0000
 * enum: 0123 4567
 *
 * entonces el mapeo a la grilla 3x3 de pixeles es:
 *
 * | 0 | 1 | 2 |
 * | 3 | E | 4 |
 * | 5 | 6 | 7 |
 *
 * donde el pixel E se evalua por separado.
 *
 * @param data 	Puntero a arreglo de 441 bytes, en cuyo bit menos significativo
 * 				se contiene cada pixel de la imagen de entrada.
 * @param pixel Indice del pixel cuyos vecinos se quiere evaluar.
 */
uint8_t get_neighbours(uint8_t* data, int16_t pixel);
