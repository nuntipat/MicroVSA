#include "user_main.h"
#include "benchmark_util.h"
#include "microvsa.h"
#include "model.h"
#include <stdio.h>
#include <stdint.h>

int user_main()
{
    uint8_t result = 0;
    TIMER_COUNTER_DTYPE runtime = 0;
    static uint8_t test_data_sample[MICROVSA_MODEL_NUM_FEATURE];

    uart_initialize();
    timer_initialize();

#ifdef MICROVSA_IMPL_DEBUG_P
    MICROVSA_ACC_DTYPE debugP[MICROVSA_MAX_NUM_CLASS];
#endif
    
	while (1) {   
#ifndef MICROVSA_BENCHMARK_TEST_RUN
        get_inference_data(test_data_sample, MICROVSA_MODEL_NUM_FEATURE);
#endif
        timer_reset();

#ifdef MICROVSA_BENCHMARK_TEST_RUN
        delay_10000us();
#else
        result = microvsa_run_single_inference(test_data_sample, MICROVSA_MODEL_NUM_FEATURE
#ifndef MICROVSA_IMPL_FIX_SIZE
            , MICROVSA_MODEL_F, MICROVSA_MODEL_V, MICROVSA_MODEL_C, MICROVSA_MODEL_NUM_CLASS, MICROVSA_MODEL_NUM_FEATURE, MICROVSA_MODEL_FHV_DIMENSION_WORD, MICROVSA_MODEL_FHV_DIMENSION_BIT
#endif
#ifdef MICROVSA_IMPL_DEBUG_P
            , debugP
#endif
        );
#endif
            
        runtime = timer_elapsed_cycle();

#ifdef MICROVSA_IMPL_DEBUG_P
        uart_send_debug_p(debugP, MICROVSA_MODEL_NUM_CLASS);
#endif
        uart_send_result(result, runtime);
	}
   
    return 0;
}
