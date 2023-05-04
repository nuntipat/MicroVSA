#ifndef MODEL__H_
#define MODEL__H_

#include <stdint.h>
#include "ldc_inference.h"

//  # define MODEL_TRANSPOSE_F
//  # define MODEL_TRANSPOSE_C
// #define MODEL_F_IN_RAM
// #define MODEL_V_IN_RAM
// #define MODEL_C_IN_RAM

#define LDC_MODEL_FHV_DIMENSION_BIT 128
#if LDC_IMPLEMENTATION_NUMBIT == 8
#define LDC_MODEL_FHV_DIMENSION_WORD 16
#elif LDC_IMPLEMENTATION_NUMBIT == 10
#define LDC_MODEL_FHV_DIMENSION_WORD 13
#elif LDC_IMPLEMENTATION_NUMBIT == 12
#define LDC_MODEL_FHV_DIMENSION_WORD 11
#elif LDC_IMPLEMENTATION_NUMBIT == 16
#define LDC_MODEL_FHV_DIMENSION_WORD 8
#elif LDC_IMPLEMENTATION_NUMBIT == 32
#define LDC_MODEL_FHV_DIMENSION_WORD 4
#else
# error Unsupport look up configuration
#endif
#define LDC_MODEL_NUM_CLASS 10
#define LDC_MODEL_NUM_FEATURE 800

#ifdef MODEL_F_IN_RAM
#define MODEL_F_QUALIFIER
#else
#define MODEL_F_QUALIFIER const
#endif
#ifdef MODEL_V_IN_RAM
#define MODEL_V_QUALIFIER
#else
#define MODEL_V_QUALIFIER const
#endif
#ifdef MODEL_C_IN_RAM
#define MODEL_C_QUALIFIER
#else
#define MODEL_C_QUALIFIER const
#endif

#if LDC_IMPLEMENTATION_NUMBIT == 8
extern MODEL_F_QUALIFIER uint8_t LDC_MODEL_F[];
extern MODEL_V_QUALIFIER uint8_t LDC_MODEL_V[];
extern MODEL_C_QUALIFIER uint8_t LDC_MODEL_C[];
#elif LDC_IMPLEMENTATION_NUMBIT == 10
extern MODEL_F_QUALIFIER uint16_t LDC_MODEL_F[];
extern MODEL_V_QUALIFIER uint16_t LDC_MODEL_V[];
extern MODEL_C_QUALIFIER uint16_t LDC_MODEL_C[];
#elif LDC_IMPLEMENTATION_NUMBIT == 12
extern MODEL_F_QUALIFIER uint16_t LDC_MODEL_F[];
extern MODEL_V_QUALIFIER uint16_t LDC_MODEL_V[];
extern MODEL_C_QUALIFIER uint16_t LDC_MODEL_C[];
#elif LDC_IMPLEMENTATION_NUMBIT == 16
extern MODEL_F_QUALIFIER uint16_t LDC_MODEL_F[];
extern MODEL_V_QUALIFIER uint16_t LDC_MODEL_V[];
extern MODEL_C_QUALIFIER uint16_t LDC_MODEL_C[];
#elif LDC_IMPLEMENTATION_NUMBIT == 32
extern MODEL_F_QUALIFIER uint32_t LDC_MODEL_F[];
extern MODEL_V_QUALIFIER uint32_t LDC_MODEL_V[];
extern MODEL_C_QUALIFIER uint32_t LDC_MODEL_C[];
#else
# error Unsupport look up configuration
#endif

#endif