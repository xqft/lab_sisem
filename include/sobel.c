#include <stdint.h>
#include <stdlib.h>
#include <msp430.h>
#include <math.h>
#include "fuzzy.h"
#include "sobel.h"

const int opg_x[8] = {-1,0,1,-2,2,-1,0,1}; //Se obvia el pixel en el que se está calculando porque no aporta información
const int opg_y[8] = {1,2,1,0,0,-1,-2,-1};

int gradiente_x(uint8_t* data,uint16_t pixel){
    uint8_t vecinos = get_neighbours(data, pixel);
    int g_x = 0;
    int i;
    for (i = 0; i <= 7; i++){
        g_x = g_x + opg_x[i] * ((vecinos >> 7-i) & 1);
    }
    return g_x;
}

int gradiente_y(uint8_t* data,uint16_t pixel){
    uint8_t vecinos = get_neighbours(data, pixel);
    int g_y = 0;
    int i;
    for (i = 0; i <= 7; i++){
        g_y = g_y + opg_y[i] * ((vecinos >> 7-i) & 1);
    }
    return g_y;
}

void sobelex_edge_detect(uint8_t *data, uint8_t *result){
    int16_t pixel;
    for (pixel = 0; pixel < IMAGE_PIXELS; pixel++)
    {
        uint8_t byte = pixel / 8;
        uint8_t bit = 7 - (pixel % 8);
        int gx = gradiente_x(data,pixel);
        int gy = gradiente_y(data,pixel);
        float gradiente = sqrt(gx * gx + gy * gy);
        if (gradiente > umbral){
            result[byte] |= 1 << bit;
            }
        else {
                result[byte] &= ~(1 << bit);
            }
    }
}
void sobelaprox_edge_detect(uint8_t *data, uint8_t *result){
    int16_t pixel;
        for (pixel = 0; pixel < IMAGE_PIXELS; pixel++)
        {
            uint8_t byte = pixel / 8;
            uint8_t bit = 7 - (pixel % 8);
            int gx = abs(gradiente_x(data,pixel));
            int gy = abs(gradiente_y(data,pixel));
            float gradiente = gx  + gy;
            if (gradiente > umbral){
                result[byte] |= 1 << bit;
                }
            else {
                    result[byte] &= ~(1 << bit);
                }
        }
}



