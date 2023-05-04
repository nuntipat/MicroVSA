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

// char buffer[32];

// void uart_write_string(char* s)
// {
//     while (*s)
//     {
//          USART0_Write(*s);
//         s++;
//     }
// }

void uart_send_result(uint8_t result, TIMER_COUNTER_DTYPE runtime)
{
    // sprintf(buffer, "%d %u us\n", result, runtime);
    // uart_write_string(buffer);
    Serial.print(result);
    Serial.print(' ');
    Serial.print(runtime);
    Serial.print("us\n");
}

void uart_send_debug_p(LDC_MODEL_ACC_DTYPE arr[], uint8_t len)
{
    uint8_t i;
    for (i=0; i<len; i++)
    {
        // sprintf(buffer, "%d\n", arr[i]);
        // uart_write_string(buffer);
        Serial.println(arr[i]);
    }
}

void get_inference_data(uint8_t arr[], uint16_t len)
{
#ifdef USE_DUMMY_DATA
    uint16_t i;
    for (i=0; i<len; i++)
    {
        arr[i] = test_data_sample[i];
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
