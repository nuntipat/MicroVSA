#include <Arduino.h>
#include "benchmark_util.h"

#include <stdio.h>

#ifdef USE_DUMMY_DATA
#include "test_data.h"
#endif

static unsigned long startTime = 0;

void timer_initialize()
{
    
}

void timer_reset()
{
    startTime = micros();
}

TIMER_COUNTER_DTYPE timer_elapsed_cycle()
{
    return micros() - startTime;
}

void delay_10000us()
{
    delay(10);
}

void uart_initialize()
{
    
}

void uart_send_result(uint8_t result, TIMER_COUNTER_DTYPE runtime)
{
    Serial.print(result);
    Serial.print(' ');
    Serial.print(runtime);
    Serial.print("us\n");
}

void uart_send_debug_p(MICROVSA_ACC_DTYPE arr[], uint8_t len)
{
    uint8_t i;
    for (i=0; i<len; i++)
    {
        Serial.println(arr[i]);
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
        while (Serial.available() == 0);
        arr[i] = Serial.read();
    }
#endif
}
