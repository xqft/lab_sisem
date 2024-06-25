#pragma once

#include <stdint.h>

/// Rutina de inicializacion del timer hardware usando el cristal como fuente de reloj.
void config_timer_crystal();
/// Rutina de inicializacion del timer hardware usando el cristal como fuente de reloj, para captura.
void config_timer_crystal_capture();
/// Rutina de inicializacion del timer hardware usando el VLO como fuente de reloj.
void config_timer_VLO();
#ifdef QUEUE
/// Establecer la flag del contador que indica cuando el mismo mide un periodo.
///
/// La flag se debe desactivar manualmente.
void set_counter_flag(uint8_t *flag);
/// Establecer el periodo del contador.
void set_counter_max(uint32_t max);
#endif

/// Comienza una cuenta del timer (previamente configurado en modo capture).
inline void restart_timer_capture();
/// Para el timer y devuelve la cuenta en milisegundos.
inline uint16_t get_timer_capture();
