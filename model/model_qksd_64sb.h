#ifndef MODEL_QKSD_H_
#define MODEL_QKSD_H_

#include <stdint.h>
#include "microvsa_config.h"

#define MICROVSA_MODEL_FHV_DIMENSION_BIT 64
#if MICROVSA_IMPL_WORDSIZE == 8
#define MICROVSA_MODEL_FHV_DIMENSION_WORD 8
#elif MICROVSA_IMPL_WORDSIZE == 16
#define MICROVSA_MODEL_FHV_DIMENSION_WORD 4
#elif MICROVSA_IMPL_WORDSIZE == 32
#define MICROVSA_MODEL_FHV_DIMENSION_WORD 2
#else
# error Unsupport look up configuration
#endif
#define MICROVSA_MODEL_NUM_CLASS 2
#define MICROVSA_MODEL_NUM_FEATURE 810

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

extern MODEL_F_QUALIFIER uint8_t MICROVSA_MODEL_F[];
extern MODEL_V_QUALIFIER uint8_t MICROVSA_MODEL_V[];
extern MODEL_C_QUALIFIER uint8_t MICROVSA_MODEL_C[];

#endif