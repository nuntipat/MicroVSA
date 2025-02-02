#include "microvsa_state.h"

#ifdef MICROVSA_ENABLE_INTERMITTENT

#pragma PERSISTENT(microvsa_current_state)
#ifdef MICROVSA_ENABLE_BUTTON
volatile int microvsa_current_state = MICROVSA_STATE_WAIT_TRIGGER;
#else
volatile int microvsa_current_state = MICROVSA_STATE_LOAD_INPUT;
#endif

#pragma PERSISTENT(microvsa_inference_result)
uint8_t microvsa_inference_result = 0;

#pragma PERSISTENT(input_sample)
uint8_t input_sample[MICROVSA_MAX_NUM_FEATURE] = {0};

#pragma PERSISTENT(state1)
volatile MICROVSA_INFERENCE_STATE_T state1 = {0};

#pragma PERSISTENT(state2)
volatile MICROVSA_INFERENCE_STATE_T state2 = {0};

void recover_state()
{
    uint8_t i = 0;
    if (state1.counter == state2.counter)
    {
        state1.fram_i = state2.fram_i;
        state1.fram_j = state2.fram_j;
        state1.fram_k = state2.fram_k;
        for (i=0; i<MICROVSA_MAX_NUM_CLASS; i++) {
           state1.fram_p[i] = state2.fram_p[i];
       }
       state1.counter = state2.counter;
    }
    if (state1.counter > state2.counter)
    {
        state2.fram_i = state1.fram_i;
        state2.fram_j = state1.fram_j;
        state2.fram_k = state1.fram_k;
        for (i=0; i<MICROVSA_MAX_NUM_CLASS; i++) {
           state2.fram_p[i] = state1.fram_p[i];
       }
       state2.counter = state1.counter;
    }
}

#endif
