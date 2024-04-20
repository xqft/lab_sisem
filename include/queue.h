#pragma once

#include <stdint.h>
#include <stdbool.h>

#define QUEUE_MAX_LENGTH 32

typedef void (*func_ptr_t)();

/// Indica si la cola esta vacia
bool queue_empty();
/// Indica si la cola esta llena
bool queue_full();
/// Encolar un byte
void enqueue(func_ptr_t ptr);
/// Desencolar un byte
func_ptr_t dequeue();
