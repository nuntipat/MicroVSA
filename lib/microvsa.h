#ifndef INC_LDC_INFERENCE_H_
#define INC_LDC_INFERENCE_H_

#include <stdint.h>
#include "microvsa_config.h"

#if defined(MICROVSA_IMPL_UNROLL) && !defined(MICROVSA_IMPL_FIX_SIZE)
#define MICROVSA_IMPL_FIX_SIZE
#endif

#if MICROVSA_IMPL == MICROVSA_IMPL_VANILLA_LDC
#define MICROVSA_MODEL_DTYPE uint8_t
#else
#define MICROVSA_MODEL_DTYPE MICROVSA_TMP_DTYPE
#endif

uint8_t microvsa_run_single_inference(const uint8_t in[], const uint16_t in_length
#ifndef MICROVSA_IMPL_FIX_SIZE
		, const MICROVSA_MODEL_DTYPE* __restrict__ f, const MICROVSA_MODEL_DTYPE* __restrict__ v, const MICROVSA_MODEL_DTYPE* __restrict__ c
		, uint8_t num_class, uint16_t num_feature, uint8_t fhv_dim_word, uint8_t fhv_dim_bit
#endif
#ifdef MICROVSA_IMPL_DEBUG_P
        , MICROVSA_ACC_DTYPE* debugP
#endif
);

#endif /* INC_LDC_INFERENCE_H_ */
