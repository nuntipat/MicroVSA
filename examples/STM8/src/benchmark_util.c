#include "benchmark_util.h"
#include "stm8s.h"
#include <stdio.h>

#ifdef USE_DUMMY_DATA
#include "test_data.h"
#endif

void timer_initialize()
{
    TIM3_DeInit();
    TIM3_TimeBaseInit(TIM3_PRESCALER_256, 65535);   // resolution = 16us
    TIM3_Cmd(ENABLE);
}

void timer_reset()
{
    TIM3_SetCounter(0);
}

TIMER_COUNTER_DTYPE timer_elapsed_cycle()
{
    return TIM3_GetCounter();
}

void delay_10000us()
{
    timer_reset();
    while (timer_elapsed_cycle() < 625);
}

void uart_initialize()
{
    UART3_DeInit();
    UART3_Init((uint32_t) 115200, UART3_WORDLENGTH_8D, UART3_STOPBITS_1, UART3_PARITY_NO, UART3_MODE_TXRX_ENABLE);
    UART3_Cmd(ENABLE);
}

void uart_send_result(uint8_t result, TIMER_COUNTER_DTYPE runtime)
{
    printf("%d %dus\n", result, (int) runtime); // timer resolution = 16us (16MHz / 256)
}

void uart_send_debug_p(MICROVSA_ACC_DTYPE arr[], uint8_t len)
{
    uint8_t i;
    for (i=0; i<len; i++)
    {
        printf("%d\n", arr[i]);
    }
}

uint8_t current = 0;

void get_inference_data(uint8_t arr[], uint16_t len)
{
#ifdef USE_DUMMY_DATA
    if (current == NUM_TEST_DATA) {
        current = 0;
    }
    uint16_t i;
    for (i=0; i<len; i++)
    {
        arr[i] = test_data_sample[current * TEST_DATA_SAMPLE_LENGTH + i];
    }
    current++;
#else
    uint16_t i;
    for (i=0; i<len; i++)
    {
        arr[i] = getchar();
    }
#endif
}
