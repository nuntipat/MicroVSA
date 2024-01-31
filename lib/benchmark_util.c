#include "benchmark_util.h"

#include <stdio.h>

#ifdef USE_DUMMY_DATA
#include "test_data.h"
#endif

void timer_initialize()
{
}

void timer_reset()
{
}

TIMER_COUNTER_DTYPE timer_elapsed_cycle()
{
}

void delay_10000us()
{
}

void uart_initialize()
{
}

char buffer[32];

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
    sprintf(buffer, "%d %u us\n", result, runtime);
    uart_write_string(buffer);
}

void uart_send_debug_p(MICROVSA_ACC_DTYPE arr[], uint8_t len)
{
    uint8_t i;
    for (i=0; i<len; i++)
    {
        sprintf(buffer, "%d\n", arr[i]);
        uart_write_string(buffer);
    }
}

void get_inference_data(uint8_t arr[], uint16_t len)
{
#ifdef USE_DUMMY_DATA
    static uint8_t currentTestIndex = 0;
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
