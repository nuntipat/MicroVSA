#ifndef MICROVSA_BENCHMARK_CONFIG__H_
#define MICROVSA_BENCHMARK_CONFIG__H_

#include "stdint.h"

/****************
 * Model Setting 
 ****************/

/* Uncomment the following line to transpose the F and/or C vectors, depending on the MicroVSA implementation chosen. 
 * See the list of support configuration below for more information */
// # define MODEL_TRANSPOSE_F
// # define MODEL_TRANSPOSE_C

/* Uncomment the following line to store the F, C, and/or V vectors in RAM instead of flash */
// #define MODEL_F_IN_RAM
// #define MODEL_V_IN_RAM
// #define MODEL_C_IN_RAM

/********************************** 
 * MicroVSA Implementation Setting 
 **********************************/

#define MICROVSA_IMPL_WORDSIZE 32           // 8 for 8-bit MCU, 16 for 16-bit MCU and 32 for 32-bit MCU

#define MICROVSA_TMP_DTYPE uint32_t         // datatype for all temporary variables. uint8_t for 8-bit MCU, uint16_t for 16-bit MCU or uint32_t for 32-bit MCU
#define MICROVSA_ACC_DTYPE int32_t          // datatype for all accumulators. int16_t for 8/16-bit MCU or int32_t for 32-bit MCU

// #define MICROVSA_IMPL_USE_LUT	        // 8/16-bit MCU must use LUT, 32-bit MCU can comment this line to use hamming weight based implementation
// #define MICROVSA_IMPL_LUTBIT 8           // 8 (256-entries LUT) or 11 (2048-entries LUT)
#define MICROVSA_IMPL_LUT_IN_RAM            // store the LUT in RAM instead of flash (may result in speedup in some MCUs)
#define MICROVSA_LUT_DTYPE int32_t	        // datatype for the LUT result. int8_t on 8-bit MCU, MICROVSA_ACC_DTYPE on 16/32-bit MCU

// #define MICROVSA_MAX_NUM_CLASS 6         // maximum number of class in the model (must be >= MICROVSA_MODEL_NUM_CLASS in model.h)
// #define MICROVSA_MAX_FHV_DIM 2           // maximum value of Df in word e.g. if Df=64 and MICROVSA_IMPL_WORDSIZE=32, set this value to 2
// #define MICROVSA_MAX_FHV_DIM_BIT 64      // set to MICROVSA_MAX_FHV_DIM * MICROVSA_IMPL_WORDSIZE

/********************************
 * List of support configuration
 ********************************
 *  -------------------------------------------------------------------------------------------
 *	MICROVSA_IMPL   OPTIMIZE_MEM   POINTERIZE   UNROLL   8BITADD   TRANSPOSE_F   TRANSPOSE_C
 *  -------------------------------------------------------------------------------------------
 *   VANILLA_LDC         -             -          -         -          -             -
 *   BINARY_LDC          -             -          -         -          Y             -
 *                       -             -          -         Y          Y             -
 *   MCU_OPT_CC          -             -          -         -          -             -
 *                       Y             -          -         -          Y             Y
 *                       Y             Y          -         -          Y             Y
 *                       Y             -          -         Y          Y             Y
 *                       Y             -          Y         -          Y             Y
 *                       Y             -          Y         Y          Y             Y
 *   MCU_OPT_CR          -             -          -         -          -             -
 *                       Y             -          -         -          -             Y
 *                       Y             Y          -         -          -             Y
 *                       Y             -          -         Y          -             Y
 *   MCU_OPT_RRI         -             -          -         -          -             -
 *                       -             Y          -         -          -             -
 *                       -             Y          -         Y          -             -
 *                       -             -          Y         -          -             -
 *                       -             -          Y         Y          -             -
 *   MCU_OPT_RRII        -             -          -         -          -             -
 *                       Y             -          -         -          -             -
 *                       Y             Y          -         -          -             -
 *                       Y             -          -         Y          -             -
 * ---------------------------------------------------------------------------------------------
 */

/* List of constant for using as a value of MICROVSA_IMPL */ 
#define MICROVSA_IMPL_VANILLA_LDC 0      // Vanilla LDC
#define MICROVSA_IMPL_BINARY_LDC 1       // Binary LDC
#define MICROVSA_IMPL_MCU_OPT_CC 2       // MCU-Optimized LDC / C (Col-wise) F (Col-wise)
#define MICROVSA_IMPL_MCU_OPT_CR 3       // MCU-Optimized LDC / C (Col-wise) F (Row-wise)
#define MICROVSA_IMPL_MCU_OPT_RRI 4      // MCU-Optimized LDC / C (Row-wise) F (Row-wise) I
#define MICROVSA_IMPL_MCU_OPT_RRII 5     // MCU-Optimized LDC / C (Row-wise) F (Row-wise) II

// #define MICROVSA_IMPL MICROVSA_IMPL_MCU_OPT_CC
// #define MICROVSA_IMPL_OPTIMIZE_MEM
// #define MICROVSA_IMPL_POINTERIZE
// #define MICROVSA_IMPL_UNROLL
// #define MICROVSA_IMPL_FLAVOR_8BITADD
// #define MICROVSA_IMPL_FIX_SIZE       //  must be enable if MICROVSA_IMPL_UNROLL is enabled
// #define MICROVSA_IMPL_DEBUG_P

/******************** 
 * Benchmark Setting 
 ********************/

// #define USE_DUMMY_DATA
// #define MICROVSA_BENCHMARK_TEST_RUN
#define TIMER_COUNTER_DTYPE uint32_t

#endif
