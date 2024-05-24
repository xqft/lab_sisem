#include <stdint.h>

#include "fuzzy.h"

void fuzzy_edge_detect(uint8_t* data) {

}

uint8_t get_neighbours(uint8_t* data, uint16_t index) {
	uint16_t result = 0;

	// inicializo al primer vecino
	uint8_t* neighbour = data[index - 22];
	result |= *neighbour & 1;

	// segundo vecino
	neighbour += 1;
	result |= (*neighbour & 1) << 1;

	// tercer vecino
	neighbour += 1;
	result |= (*neighbour & 1) << 2;

	// cuarto vecino
	neighbour += 19;
	result |= (*neighbour & 1) << 3;

	// quinto vecino
	neighbour += 2;
	result |= (*neighbour & 1) << 4;

	// sexto vecino
	neighbour += 19;
	result |= (*neighbour & 1) << 5;

	// septimo vecino
	neighbour += 1;
	result |= (*neighbour & 1) << 6;

	// octavo vecino
	neighbour += 1;
	result |= (*neighbour & 1) << 7;
}
