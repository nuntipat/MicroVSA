#include "benchmark_util.h"

#include <stdio.h>
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/tmr1.h"

#ifdef USE_DUMMY_DATA
#include "test_data.h"
#endif

void timer_initialize()
{
    
}

void timer_reset()
{
    TMR1_Counter16BitSet(0);
}

TIMER_COUNTER_DTYPE timer_elapsed_cycle()
{
    return TMR1_Counter16BitGet();
}

void delay_10000us()
{
    TMR1_Counter16BitSet(0);
    while (TMR1_Counter16BitGet() < 3750);
}

void uart_initialize()
{
    
}

char buffer[32];

void uart_write_string(char* s)
{
    while (*s)
    {
        UART1_Write(*s);
        s++;
    }
}

void uart_send_result(uint8_t result, TIMER_COUNTER_DTYPE runtime)
{
    sprintf(buffer, "%d %d us\n", result, runtime);
    uart_write_string(buffer);
}

static uint8_t currentDataset = 0;

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
    uint16_t i;
    for (i=0; i<len; i++)
    {
        arr[i] = test_data_sample[currentDataset * TEST_DATA_SAMPLE_LENGTH + i];
    }
    currentDataset++;
    if (currentDataset >= NUM_TEST_DATA)
    {
        currentDataset = 0;
    }
#else
    uint16_t i;
    for (i=0; i<len; i++)
    {
         arr[i] = UART1_Read();
    }
#endif
}
