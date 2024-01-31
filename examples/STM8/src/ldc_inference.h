#ifndef INC_LDC_INFERENCE_H_
#define INC_LDC_INFERENCE_H_

#include <stdint.h>
#include "benchmark_config.h"

#if defined(LDC_IMPLEMENTATION_UNROLL) && !defined(LDC_IMPLEMENTATION_FIX_SIZE)
#define LDC_IMPLEMENTATION_FIX_SIZE
#endif

uint8_t ldc_inference_block(const uint8_t in[], const uint16_t in_length
#ifndef LDC_IMPLEMENTATION_FIX_SIZE
		, const LDC_MODEL_DTYPE* restrict f, const LDC_MODEL_DTYPE* restrict v, const LDC_MODEL_DTYPE* restrict c
		, uint8_t num_class, uint16_t num_feature, uint8_t fhv_dim_word
#endif
#ifdef LDC_IMPLEMENTATION_DEBUG_P
        , LDC_MODEL_ACC_DTYPE* debugP
#endif
);

#endif /* INC_LDC_INFERENCE_H_ */
