#include "user_main.h"
#include "benchmark_util.h"
#include "microvsa.h"
#include "model.h"
#include <stdio.h>
#include <stdint.h>

#ifdef MICROVSA_ENABLE_INTERMITTENT

int user_main()
{
    TIMER_COUNTER_DTYPE runtime = 0;

    uart_initialize();
    timer_initialize();
    trigger_init();
    trigger_off();
    button_init();
    power_good_init();

//    log_fram_state();
    recover_state();

	while (1) {
#ifdef MICROVSA_ENABLE_BUTTON
        if (microvsa_current_state == MICROVSA_STATE_WAIT_TRIGGER) {
            trigger_off();
            wait_button_press();
            microvsa_current_state = MICROVSA_STATE_LOAD_INPUT;
        }
#endif

#ifndef MICROVSA_BENCHMARK_TEST_RUN
	    if (microvsa_current_state == MICROVSA_STATE_LOAD_INPUT) {
            trigger_pattern_1();
	        get_inference_data(input_sample, MICROVSA_MODEL_NUM_FEATURE);
	        microvsa_current_state = MICROVSA_STATE_INFERENCE_INIT;
//            trigger_off();
	    }
#endif

	    if (microvsa_current_state == MICROVSA_STATE_INFERENCE_INIT ||
	        microvsa_current_state == MICROVSA_STATE_INFERENCE_COMPUTE_P ||
	        microvsa_current_state == MICROVSA_STATE_INFERENCE_ARGMAX) {

	        timer_reset();
	        trigger_pattern_2();

#ifdef MICROVSA_BENCHMARK_TEST_RUN
	        delay_10000us();
#else
	        microvsa_inference_result = microvsa_run_intermittent_inference(input_sample, MICROVSA_MODEL_NUM_FEATURE
#ifndef MICROVSA_IMPL_FIX_SIZE
	                                                     , MICROVSA_MODEL_F, MICROVSA_MODEL_V, MICROVSA_MODEL_C, MICROVSA_MODEL_NUM_CLASS, MICROVSA_MODEL_NUM_FEATURE, MICROVSA_MODEL_FHV_DIMENSION_WORD, MICROVSA_MODEL_FHV_DIMENSION_BIT
#endif
	        );
#endif
            
            runtime = timer_elapsed_cycle();
            microvsa_current_state = MICROVSA_STATE_SEND_RESULT;
//            trigger_off();
	    }

	    if (microvsa_current_state == MICROVSA_STATE_SEND_RESULT) {
	        trigger_pattern_3();
	        __disable_interrupt();
#ifdef MICROVSA_IMPL_DEBUG_P
	        uart_send_debug_p(state1.fram_p, MICROVSA_MODEL_NUM_CLASS);
#endif
            uart_send_result(microvsa_inference_result, runtime);

#ifdef MICROVSA_ENABLE_BUTTON
            microvsa_current_state = MICROVSA_STATE_WAIT_TRIGGER;
#else
            microvsa_current_state = MICROVSA_STATE_LOAD_INPUT;
#endif
//            trigger_off();
            __enable_interrupt();
	    }
	}
   
    return 0;
}

#else

#ifdef __MSP430FR5994__
#pragma NOINIT(input_sample)
#endif
uint8_t input_sample[MICROVSA_MODEL_NUM_FEATURE];

int user_main()
{
    uint8_t result = 0;
    TIMER_COUNTER_DTYPE runtime = 0;
#ifdef MICROVSA_IMPL_DEBUG_P
    MICROVSA_ACC_DTYPE debugP[MICROVSA_MAX_NUM_CLASS];
#endif

    uart_initialize();
    timer_initialize();
    trigger_init();
    trigger_off();
    button_init();

#ifdef MICROVSA_ENABLE_BUTTON
    wait_button_press();
#endif

    while (1) {
#ifndef MICROVSA_BENCHMARK_TEST_RUN
        trigger_pattern_1();
        get_inference_data(input_sample, MICROVSA_MODEL_NUM_FEATURE);
#endif

        timer_reset();
        trigger_pattern_2();

#ifdef MICROVSA_BENCHMARK_TEST_RUN
        delay_10000us();
#else
        result = microvsa_run_single_inference(input_sample, MICROVSA_MODEL_NUM_FEATURE
#ifndef MICROVSA_IMPL_FIX_SIZE
                                                     , MICROVSA_MODEL_F, MICROVSA_MODEL_V, MICROVSA_MODEL_C, MICROVSA_MODEL_NUM_CLASS, MICROVSA_MODEL_NUM_FEATURE, MICROVSA_MODEL_FHV_DIMENSION_WORD, MICROVSA_MODEL_FHV_DIMENSION_BIT
#endif
#ifdef MICROVSA_IMPL_DEBUG_P
                                                     , debugP
#endif
        );
#endif

        runtime = timer_elapsed_cycle();


        trigger_pattern_3();
#ifdef MICROVSA_IMPL_DEBUG_P
        uart_send_debug_p(debugP, MICROVSA_MODEL_NUM_CLASS);
#endif
        uart_send_result(result, runtime);

#ifdef MICROVSA_ENABLE_BUTTON
        wait_button_press();
#endif
    }

    return 0;
}

#endif
