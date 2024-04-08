#pragma once

/// Rutina de inicializacion del timer hardware usando el cristal como fuente de reloj.
void config_timer_crystal();
/// Rutina de inicializacion del timer hardware usando el VLO como fuente de reloj.
void config_timer_VLO();
/// Establecer la flag del contador que indica cuando el mismo mide un periodo.
///
/// La flag se debe desactivar manualmente.
void set_counter_flag(uint8_t *flag);
/// Establecer el periodo del contador.
void set_counter_max(uint32_t max);
