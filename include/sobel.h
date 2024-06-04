#pragma once

#include <stdint.h>
#include <msp430.h>
#define UMBRAL 3.5

int16_t gradiente_x(uint8_t* data, uint16_t pixel);

int16_t gradiente_y(uint8_t* data, uint16_t pixel);

void sobelex_edge_detect(uint8_t *data, uint8_t *result);

void sobelaprox_edge_detect(uint8_t *data, uint8_t *result);
