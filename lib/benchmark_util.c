#include "benchmark_util.h"
#include "microvsa_state.h"

#include <stdio.h>

#ifdef USE_DUMMY_DATA
#include "test_data.h"
#endif

#ifdef MICROVSA_MEASURE_RUNTIME
void timer_initialize()
{
}

void timer_reset()
{
}

TIMER_COUNTER_DTYPE timer_elapsed_cycle()
{
}
#else
void timer_initialize()
{
}

void timer_reset()
{
}

TIMER_COUNTER_DTYPE timer_elapsed_cycle()
{
}
#endif

void delay_10000us()
{
}

#ifdef MICROVSA_ENABLE_TRIGGER
void trigger_init()
{
}

void trigger_pattern_1()
{
}

void trigger_pattern_2()
{
}

void trigger_pattern_3()
{
}

void trigger_off()
{
 
}
#else
void trigger_init()
{
}

void trigger_pattern_1()
{
}

void trigger_pattern_2()
{
}

void trigger_pattern_3()
{
}

void trigger_off()
{
}
#endif

void button_init()
{
}

int button_press()
{
}

int button_release()
{
}

void wait_button_press()
{
    while (button_release());
}

void power_good_init()
{
}

void uart_initialize()
{
}

char buffer[64];

void uart_write_string(char* s)
{
    while (*s)
    {
        // TODO: send *s to transmit buffer
        s++;
    }
}

void uart_send_result(uint8_t result, TIMER_COUNTER_DTYPE runtime)
{
    sprintf(buffer, "%d %u us\r\n", result, runtime);
    uart_write_string(buffer);
}

void uart_send_debug_p(MICROVSA_ACC_DTYPE arr[], uint8_t len)
{
    uint8_t i;
    for (i=0; i<len; i++)
    {
        sprintf(buffer, "%d\r\n", arr[i]);
        uart_write_string(buffer);
    }
}

#ifdef MICROVSA_ENABLE_INTERMITTENT
void log_fram_state()
{
    sprintf(buffer, "State = %d %d %d %d %d / %d %d %d %d\r\n", microvsa_current_state
            , (int) state1.fram_i, (int) state1.fram_j, (int) state1.fram_k, (int) state1.counter
            , (int) state2.fram_i, (int) state2.fram_j, (int) state2.fram_k, (int) state2.counter);
    uart_write_string(buffer);

    uint8_t i;
    for (i=0; i<MICROVSA_MAX_NUM_CLASS; i++)
    {
        sprintf(buffer, "%d\r\n", (int) state1.fram_p[i]);
        uart_write_string(buffer);
    }
    for (i=0; i<MICROVSA_MAX_NUM_CLASS; i++)
    {
        sprintf(buffer, "%d\r\n", (int) state2.fram_p[i]);
        uart_write_string(buffer);
    }
}
#endif

uint8_t currentTestIndex = 0;

void get_inference_data(uint8_t arr[], uint16_t len)
{
#ifdef USE_DUMMY_DATA
    uint16_t i;
    for (i=0; i<len; i++)
    {
        arr[i] = test_data_sample[currentTestIndex * TEST_DATA_SAMPLE_LENGTH + i];
    }
    currentTestIndex++;
    if (currentTestIndex >= NUM_TEST_DATA) {
        currentTestIndex = 0;
    }
#else
    uint16_t i;
    for (i=0; i<len; i++)
    {
         arr[i] = /* TODO: get byte from receive buffer */;
    }
#endif
}
