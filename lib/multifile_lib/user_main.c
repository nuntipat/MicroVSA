#include "user_main.h"
#include "benchmark_util.h"
#include "ldc_inference.h"
#include "model.h"
#include <stdio.h>
#include <stdint.h>

int user_main()
{
    uint8_t result = 0;
    TIMER_COUNTER_DTYPE runtime = 0;
    static uint8_t test_data_sample[LDC_MODEL_NUM_FEATURE];

    uart_initialize();
    timer_initialize();

#ifdef LDC_IMPLEMENTATION_DEBUG_P
    LDC_MODEL_ACC_DTYPE debugP[LDC_MAX_NUM_CLASS];
#endif
    
	while (1) {   
#ifndef LDC_BENCHMARK_TEST_RUN
        get_inference_data(test_data_sample, LDC_MODEL_NUM_FEATURE);
#endif
        timer_reset();

#ifdef LDC_BENCHMARK_TEST_RUN
        delay_10000us();
#else
        result = ldc_inference_block(test_data_sample, LDC_MODEL_NUM_FEATURE
#ifndef LDC_IMPLEMENTATION_FIX_SIZE
            , LDC_MODEL_F, LDC_MODEL_V, LDC_MODEL_C, LDC_MODEL_NUM_CLASS, LDC_MODEL_NUM_FEATURE, LDC_MODEL_FHV_DIMENSION_WORD
#endif
#ifdef LDC_IMPLEMENTATION_DEBUG_P
            , debugP
#endif
        );
#endif
            
        runtime = timer_elapsed_cycle();

#ifdef LDC_IMPLEMENTATION_DEBUG_P
        uart_send_debug_p(debugP, LDC_MODEL_NUM_CLASS);
#endif
        uart_send_result(result, runtime);
	}
   
    return 0;
}
