#include "benchmark_util.h"
#include "tim.h"
#include "usart.h"

#include <stdio.h>
#include <string.h>

#ifdef USE_DUMMY_DATA
#include "test_data.h"
#endif

void timer_initialize()
{
	HAL_TIM_Base_Start(&htim2);
}

void timer_reset()
{
	__HAL_TIM_SET_COUNTER(&htim2, 0);
}

TIMER_COUNTER_DTYPE timer_elapsed_cycle()
{
	return __HAL_TIM_GET_COUNTER(&htim2);
}

void delay_10000us()
{
	HAL_Delay(10);
}

void uart_initialize()
{
    
}

char buffer[32];

void uart_send_result(uint8_t result, TIMER_COUNTER_DTYPE runtime)
{
    sprintf(buffer, "%d %dus\r\n", result, runtime);
    HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), HAL_MAX_DELAY);
}

void uart_send_debug_p(LDC_MODEL_ACC_DTYPE arr[], uint8_t len)
{
    uint8_t i;
    for (i=0; i<len; i++)
    {
        sprintf(buffer, "%ld\r\n", arr[i]);
        HAL_UART_Transmit(&huart2, (uint8_t*) buffer, strlen(buffer), HAL_MAX_DELAY);
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
    HAL_UART_Receive(&huart2, arr, len, HAL_MAX_DELAY);
#endif
}
