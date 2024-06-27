#pragma once

#include <stdint.h>
#include <msp430.h>
//#define UMBRAL 3
//#define UMBRAL_APROX 3.5

/**
 * Calcular el gradiente de un pixel con el kernel x
 *
 * @param data datos de la imagen
 * @param pixel indice del pixel
 */
int16_t gradiente_x(uint8_t* data, uint16_t pixel);
/**
 * Calcular el gradiente de un pixel con el kernel y
 *
 * @param data datos de la imagen
 * @param pixel indice del pixel
 */
int16_t gradiente_y(uint8_t* data, uint16_t pixel);
/**
 * Ejecuta el algoritmo Sobel exacto
 *
 * @param data datos de la imagen
 * @param result puntero a arreglos con resultados (comprimido en 8 pixeles por byte)
 * @param UMBRAL umbral utilizado para el algoritmo
 */
void sobelex_edge_detect(uint8_t *data, uint8_t *result, float UMBRAL);
/**
 * Ejecuta el algoritmo Sobel aproximado
 *
 * @param data datos de la imagen
 * @param result puntero a arreglos con resultados (comprimido en 8 pixeles por byte)
 * @param UMBRAL umbral utilizado para el algoritmo
 */
void sobelaprox_edge_detect(uint8_t *data, uint8_t *result, float UMBRAL_APROX);
