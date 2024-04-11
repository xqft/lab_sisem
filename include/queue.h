#pragma once

#include <stdint.h>
#include <stdbool.h>

/// Indica si la cola esta vacia
bool empty();
/// Indica si la cola esta llena
bool full();
/// Encolar un byte
void enqueue(uint8_t data);
/// Desencolar un byte
uint8_t dequeue();
