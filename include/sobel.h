#pragma once

#include <stdint.h>
#include <msp430.h>
#define umbral 3.5

int gradiente_x(uint8_t* data,uint16_t pixel);

int gradiente_y(uint8_t* data,uint16_t pixel);

void sobel_edge_detect(uint8_t *data, uint8_t *result);
