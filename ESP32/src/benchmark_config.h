#ifndef LDC_BENCHMARK_CONFIG__H_
#define LDC_BENCHMARK_CONFIG__H_

#include "stdint.h"

/* Model Setting */

#define MODEL_NAME 2    // 0 = PTB ECG, 1 = HAR, 2 = Hey Snapdragon, 3 = FSDD

// # define MODEL_TRANSPOSE_F
// # define MODEL_TRANSPOSE_C

// #define MODEL_F_IN_RAM
// #define MODEL_V_IN_RAM
// #define MODEL_C_IN_RAM

/* LDC Implementation Setting */

#define LDC_IMPLEMENTATION_NUMBIT 32
#define LDC_IMPLEMENTATION_LUTBIT 11
#define LDC_MODEL_DTYPE uint32_t
#define LDC_MODEL_ACC_DTYPE int32_t
#define LDC_MODEL_LUT_RET_DTYPE int8_t	// int8_t on 8-bit MCU, LDC_MODEL_ACC_DTYPE on 16/32-bit MCU
#define LDC_USE_LUT_LOOKUP	// 8-bit MCU must use LUT, 32-bit MCU can choose between LUT and hamming weight based implementation
// #define LDC_LUT_IN_MEMORY
#define LDC_MAX_NUM_CLASS 2
#define LDC_MAX_FHV_DIM 2

/********************************
 * List of support configuration
 ********************************
 *	#	OM	UR	PT	8B	FS
 *	1	N	N	N	N	A
 *		Y	N	N	N	A
 *		Y	N	Y	N	A
 *		Y	N	D	Y	A
 *		Y	Y	D	N	(Y)
 *		Y	Y	D	Y	(Y)
 *	2	N	N	N	N	A
 *		Y	N	N	N	A
 *		Y	N	Y	N	A
 *		Y	N	D	Y	A
 *	3	N	N	N	N	A
 *		N	N	Y	N	A
 *		N	N	Y	Y	A
 *		N	Y	Y	N	(Y)
 *		N	Y	Y	Y	(Y)
 *	4	N	N	N	N	A
 *		Y	N	N	N	A
 *		Y	N	Y	N	A
 *		Y	N	D	Y	A
 */
//  #define LDC_IMPLEMENTATION 0
//  #define LDC_IMPLEMENTATION_OPTIMIZE_MEM
// #define LDC_IMPLEMENTATION_POINTERIZE
// #define LDC_IMPLEMENTATION_UNROLL
// #define LDC_IMPLEMENTATION_FLAVOR_8BITADD
//  #define LDC_IMPLEMENTATION_FIX_SIZE
// #define LDC_IMPLEMENTATION_DEBUG_P

/* Benchmark Setting */

// #define USE_DUMMY_DATA
// #define LDC_BENCHMARK_TEST_RUN
#define TIMER_COUNTER_DTYPE uint32_t

#endif


