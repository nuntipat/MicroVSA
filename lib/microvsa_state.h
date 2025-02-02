#ifndef MICROVSA_STATE_H_
#define MICROVSA_STATE_H_

#include "microvsa_config.h"

#ifdef MICROVSA_ENABLE_INTERMITTENT

#define MICROVSA_STATE_LOAD_INPUT           0
#define MICROVSA_STATE_INFERENCE_INIT       1
#define MICROVSA_STATE_INFERENCE_COMPUTE_P  2
#define MICROVSA_STATE_INFERENCE_ARGMAX     3
#define MICROVSA_STATE_SEND_RESULT          4
#define MICROVSA_STATE_WAIT_TRIGGER         5

extern volatile int microvsa_current_state;  // should be set to MICROVSA_STATE_*

extern uint8_t input_sample[MICROVSA_MAX_NUM_FEATURE];
extern uint8_t microvsa_inference_result;

typedef struct {
    uint16_t fram_i;
    uint8_t fram_j;
    uint8_t fram_k;
    MICROVSA_ACC_DTYPE fram_p[MICROVSA_MAX_NUM_CLASS];
    uint16_t counter;
} MICROVSA_INFERENCE_STATE_T;

extern volatile MICROVSA_INFERENCE_STATE_T state1;
extern volatile MICROVSA_INFERENCE_STATE_T state2;

void recover_state();

#endif

#endif /* MICROVSA_STATE_H_ */
