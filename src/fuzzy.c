#include <stdint.h>
#include <stdbool.h>

#include "fuzzy.h"

void fuzzy_edge_detect(uint8_t *data, uint8_t *result)
{
    int16_t pixel;
    for (pixel = 0; pixel < IMAGE_PIXELS; pixel++)
    {
        uint8_t byte = pixel / 8;
        uint8_t bit = 7 - (pixel % 8);

        switch (get_neighbours(data, pixel))
        {
        case RULE1:
        case RULE2:
        case RULE3:
        case RULE4:
        case RULE5:
        case RULE6:
        case RULE7:
        case RULE8:
        {
            if (data[pixel] == 0)
            {
                result[byte] |= 1 << bit;
                break;
            } else {
                result[byte] &= ~(1 << bit);
            }
        }
        default:
            result[byte] &= ~(1 << bit);
        }
    }
}

uint8_t get_neighbours(uint8_t *data, int16_t pixel)
{
    uint8_t result = 0;

    uint8_t i_0 = pixel / 21;
    uint8_t j_0 = pixel % 21;

    int8_t i;
    int8_t j;

    for (i = i_0 - 1; i <= i_0 + 1; i++)
    {
        for (j = j_0 - 1; j <= j_0 + 1; j++)
        {
            if (i == i_0 && j == j_0)
                continue;

            result <<= 1;

            uint8_t i_v = i;
            uint8_t j_v = j;

            // saturo bordes
            if (i < 0)
                i_v = 0;
            if (j < 0)
                j_v = 0;
            if (i > 20)
                i_v = 20;
            if (j > 20)
                j_v = 20;

            result |= data[i_v * 21 + j_v];
        }
    }
    return result;
}
