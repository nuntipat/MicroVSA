#ifndef MICROVSA_BENCHMARK_UTIL_H
#define	MICROVSA_BENCHMARK_UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "microvsa_config.h"

/* Timer */
    
void timer_initialize();
void timer_reset();
TIMER_COUNTER_DTYPE timer_elapsed_cycle();

void delay_10000us();

/* Trigger Signal */

void trigger_init();
void trigger_pattern_1();
void trigger_pattern_2();
void trigger_pattern_3();
void trigger_off();

/* Power good Signal */

void power_good_init();

/* Push Button */

void button_init();
int button_press();
int button_release();
void wait_button_press();

/* UART Communication */

void uart_initialize();
void uart_send_result(uint8_t result, TIMER_COUNTER_DTYPE runtime);
void uart_send_debug_p(MICROVSA_ACC_DTYPE arr[], uint8_t len);

#ifdef MICROVSA_ENABLE_INTERMITTENT
void log_fram_state();
#endif

void get_inference_data(uint8_t arr[], uint16_t len);

#ifdef	__cplusplus
}
#endif

#endif

