#include "microvsa.h"
#if defined(MICROVSA_IMPL_FIX_SIZE)
#include "model.h"
#endif

#ifdef MICROVSA_IMPL_USE_LUT
#ifndef MICROVSA_IMPL_LUT_IN_RAM
#define LDC_LUT_MODIFIER const
#else
#ifdef ESP32
#include "esp_attr.h"
#define LDC_LUT_MODIFIER const DRAM_ATTR
#else
#define LDC_LUT_MODIFIER
#endif
#endif
#if MICROVSA_IMPL_LUTBIT == 8
LDC_LUT_MODIFIER int8_t LUT[] = {
	 8,  6,  6,  4,  6,  4,  4,  2,  6,  4,  4,  2,  4,  2,  2,  0,
	 6,  4,  4,  2,  4,  2,  2,  0,  4,  2,  2,  0,  2,  0,  0, -2,
	 6,  4,  4,  2,  4,  2,  2,  0,  4,  2,  2,  0,  2,  0,  0, -2,
	 4,  2,  2,  0,  2,  0,  0, -2,  2,  0,  0, -2,  0, -2, -2, -4,
	 6,  4,  4,  2,  4,  2,  2,  0,  4,  2,  2,  0,  2,  0,  0, -2,
	 4,  2,  2,  0,  2,  0,  0, -2,  2,  0,  0, -2,  0, -2, -2, -4,
	 4,  2,  2,  0,  2,  0,  0, -2,  2,  0,  0, -2,  0, -2, -2, -4,
	 2,  0,  0, -2,  0, -2, -2, -4,  0, -2, -2, -4, -2, -4, -4, -6,
	 6,  4,  4,  2,  4,  2,  2,  0,  4,  2,  2,  0,  2,  0,  0, -2,
	 4,  2,  2,  0,  2,  0,  0, -2,  2,  0,  0, -2,  0, -2, -2, -4,
	 4,  2,  2,  0,  2,  0,  0, -2,  2,  0,  0, -2,  0, -2, -2, -4,
	 2,  0,  0, -2,  0, -2, -2, -4,  0, -2, -2, -4, -2, -4, -4, -6,
	 4,  2,  2,  0,  2,  0,  0, -2,  2,  0,  0, -2,  0, -2, -2, -4,
	 2,  0,  0, -2,  0, -2, -2, -4,  0, -2, -2, -4, -2, -4, -4, -6,
	 2,  0,  0, -2,  0, -2, -2, -4,  0, -2, -2, -4, -2, -4, -4, -6,
	 0, -2, -2, -4, -2, -4, -4, -6, -2, -4, -4, -6, -4, -6, -6, -8
};
#elif MICROVSA_IMPL_LUTBIT == 11
LDC_LUT_MODIFIER int8_t LUT[] = {
	 11,   9,   9,   7,   9,   7,   7,   5,   9,   7,   7,   5,   7,   5,   5,   3,   9,   7,   7,   5,   7,   5,   5,   3,   7,   5,   5,   3,   5,   3,   3,   1,
	  9,   7,   7,   5,   7,   5,   5,   3,   7,   5,   5,   3,   5,   3,   3,   1,   7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,
	  9,   7,   7,   5,   7,   5,   5,   3,   7,   5,   5,   3,   5,   3,   3,   1,   7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  9,   7,   7,   5,   7,   5,   5,   3,   7,   5,   5,   3,   5,   3,   3,   1,   7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  9,   7,   7,   5,   7,   5,   5,   3,   7,   5,   5,   3,   5,   3,   3,   1,   7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  9,   7,   7,   5,   7,   5,   5,   3,   7,   5,   5,   3,   5,   3,   3,   1,   7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -3,  -5,  -5,  -7,  -5,  -7,  -7,  -9,
	  9,   7,   7,   5,   7,   5,   5,   3,   7,   5,   5,   3,   5,   3,   3,   1,   7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -3,  -5,  -5,  -7,  -5,  -7,  -7,  -9,
	  7,   5,   5,   3,   5,   3,   3,   1,   5,   3,   3,   1,   3,   1,   1,  -1,   5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -3,  -5,  -5,  -7,  -5,  -7,  -7,  -9,
	  5,   3,   3,   1,   3,   1,   1,  -1,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -3,  -5,  -5,  -7,  -5,  -7,  -7,  -9,
	  3,   1,   1,  -1,   1,  -1,  -1,  -3,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,   1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,
	  1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -3,  -5,  -5,  -7,  -5,  -7,  -7,  -9,
	  1,  -1,  -1,  -3,  -1,  -3,  -3,  -5,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -3,  -5,  -5,  -7,  -5,  -7,  -7,  -9,
	 -1,  -3,  -3,  -5,  -3,  -5,  -5,  -7,  -3,  -5,  -5,  -7,  -5,  -7,  -7,  -9,  -3,  -5,  -5,  -7,  -5,  -7,  -7,  -9,  -5,  -7,  -7,  -9,  -7,  -9,  -9, -11,
};
#endif
#endif

#ifdef MICROVSA_IMPL_UNROLL
#define _LOAD_VAR(var, i) MICROVSA_TMP_DTYPE var##i = *c++;
#define _SET_ARR_I_TO_VF_XOR_C_I(arr, i) arr[i] += lookup(vf ^ c##i);
#define _SET_VAR_TO_V_XOR_F_XOR_C_I(var, i) var += lookup(v_val ^ *f_ptr++ ^ c##i);

#define _INST1(INST, arg) INST(arg, 0)
#define _INST2(INST, arg) _INST1(INST, arg) INST(arg, 1)
#define _INST3(INST, arg) _INST2(INST, arg) INST(arg, 2)
#define _INST4(INST, arg) _INST3(INST, arg) INST(arg, 3)
#define _INST5(INST, arg) _INST4(INST, arg) INST(arg, 4)
#define _INST6(INST, arg) _INST5(INST, arg) INST(arg, 5)
#define _INST7(INST, arg) _INST6(INST, arg) INST(arg, 6)
#define _INST8(INST, arg) _INST7(INST, arg) INST(arg, 7)
#define _INST9(INST, arg) _INST8(INST, arg) INST(arg, 8)
#define _INST10(INST, arg) _INST9(INST, arg) INST(arg, 9)
#define _INST11(INST, arg) _INST10(INST, arg) INST(arg, 10)
#define _INST12(INST, arg) _INST11(INST, arg) INST(arg, 11)
#define _INST13(INST, arg) _INST12(INST, arg) INST(arg, 12)
#define _INST14(INST, arg) _INST13(INST, arg) INST(arg, 13)
#define _INST15(INST, arg) _INST14(INST, arg) INST(arg, 14)
#define _INST16(INST, arg) _INST15(INST, arg) INST(arg, 15)
#define LOOP(N, INST, ARG) _INST##N(INST, ARG)

#define LOAD_VAR(ARG, N) LOOP(N, _LOAD_VAR, ARG)
#define SET_ARR_I_TO_VF_XOR_C_I(ARG, N) LOOP(N, _SET_ARR_I_TO_VF_XOR_C_I, ARG)
#define SET_VAR_TO_V_XOR_F_XOR_C_I(ARG, N) LOOP(N, _SET_VAR_TO_V_XOR_F_XOR_C_I, ARG)
#endif

uint8_t argmax(MICROVSA_ACC_DTYPE* arr, uint8_t len)
{
	uint8_t i;
	uint8_t maxIndex = 0;
	MICROVSA_ACC_DTYPE max = arr[0];
	for (i=1; i<len; i++)
	{
		if (arr[i] > max)
		{
			maxIndex = i;
			max = arr[i];
		}
	}
	return maxIndex;
}

MICROVSA_LUT_DTYPE lookup(MICROVSA_TMP_DTYPE v) {
#if defined(MICROVSA_IMPL_USE_LUT) && MICROVSA_IMPL_WORDSIZE == 8 && MICROVSA_IMPL_LUTBIT == 8
	return LUT[v];
#elif defined(MICROVSA_IMPL_USE_LUT) && MICROVSA_IMPL_WORDSIZE == 16 && MICROVSA_IMPL_LUTBIT == 8
	return LUT[v & 0xFF] + LUT[v >> 8];
#elif defined(MICROVSA_IMPL_USE_LUT) && MICROVSA_IMPL_WORDSIZE == 32 && MICROVSA_IMPL_LUTBIT == 8
    return LUT[v & 0xFF] + LUT[(v >> 8) & 0xFF] + LUT[(v >> 16) & 0xFF] + LUT[v >> 24];
#elif defined(MICROVSA_IMPL_USE_LUT) && MICROVSA_IMPL_WORDSIZE == 32 && MICROVSA_IMPL_LUTBIT == 11
	// all LUT result will be greater than the actual result by 1 which doesn't affect classification result as we only interested in relative value between class
	return LUT[v & 0x000007FF] + LUT[(v >> 11) & 0x000007FF] + LUT[(v >> 22) & 0x000007FF];
#elif !defined(MICROVSA_IMPL_USE_LUT) && MICROVSA_IMPL_WORDSIZE == 32
	// From: https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
	v = v - ((v >> 1) & 0x55555555);
	v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
	MICROVSA_LUT_DTYPE count = ((v + (v >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
	return 32 - (count * 2);
#else
#error Unsupport look up configuration
#endif
}

uint8_t microvsa_run_single_inference(const uint8_t in[], const uint16_t in_length
#ifndef MICROVSA_IMPL_FIX_SIZE
							, const MICROVSA_MODEL_DTYPE* __restrict__ f, const MICROVSA_MODEL_DTYPE* __restrict__ v, const MICROVSA_MODEL_DTYPE* __restrict__ c
							, uint8_t num_class, uint16_t num_feature, uint8_t fhv_dim_word, uint8_t fhv_dim_bit
#endif
#ifdef MICROVSA_IMPL_DEBUG_P
                            , MICROVSA_ACC_DTYPE* debugP
#endif
							)
{
#if defined(MICROVSA_IMPL_FIX_SIZE)
	const MICROVSA_MODEL_DTYPE* __restrict__ f = MICROVSA_MODEL_F;
	const MICROVSA_MODEL_DTYPE* __restrict__ v = MICROVSA_MODEL_V;
	const MICROVSA_MODEL_DTYPE* __restrict__ c = MICROVSA_MODEL_C;
	const uint8_t num_class = MICROVSA_MODEL_NUM_CLASS;
	const uint16_t num_feature = MICROVSA_MODEL_NUM_FEATURE;
	const uint8_t fhv_dim_word = MICROVSA_MODEL_FHV_DIMENSION_WORD;
	const uint8_t fhv_dim_bit = MICROVSA_MODEL_FHV_DIMENSION_BIT;
#endif

	uint16_t i;
	uint8_t j, k, m;
    int8_t l;
	MICROVSA_ACC_DTYPE p[MICROVSA_MAX_NUM_CLASS] = {0};
#if MICROVSA_IMPL == MICROVSA_IMPL_VANILLA_LDC
	MICROVSA_ACC_DTYPE s[MICROVSA_MAX_FHV_DIM_BIT] = {0};
	for (j=0; j<fhv_dim_bit; j++) 
	{
		s[j] = 0;
	}

	for (i=0; i<num_feature; i++)
	{
		for (j=0; j<fhv_dim_bit; j++) 
		{
			s[j] += (v[(in[i] * 8) + (j % 8)]) ^ f[(i * fhv_dim_bit) + j];
		}
	}

	for (j=0; j<fhv_dim_bit; j++) 
	{
		s[j] = ((s[j] > num_feature / 2) ? 0 : 1);
	}

	for (k=0; k<num_class; k++)
	{
		for (j=0; j<fhv_dim_bit; j++) 
		{
			p[k] += s[j] ^ c[(k * fhv_dim_bit)+ j];
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_BINARY_LDC && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_F
	MICROVSA_TMP_DTYPE s[MICROVSA_MAX_FHV_DIM] = {0};
	MICROVSA_ACC_DTYPE t[MICROVSA_IMPL_WORDSIZE] = {0};
	for (j=0; j<fhv_dim_word; j++)
	{
		for(l=0; l<MICROVSA_IMPL_WORDSIZE; l++)
		{
			t[l] = 0;
		}
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE vf = v[in[i]] ^ f[j * num_feature + i];
			for(l=MICROVSA_IMPL_WORDSIZE-1; l>=0; l--)
			{
				t[l] += vf & 1;	// t[l] += ((vf & 1) == 0) ? 1 : -1;
				vf = vf >> 1;
			}
		}
		for(l=0; l<MICROVSA_IMPL_WORDSIZE; l++)
		{
			s[j] = s[j] << 1;
			s[j] |= ((t[l] > num_feature / 2) ? 1 : 0); 	// 0 => 1, 1 => -1   // ((t[l] >= 0) ? 0 : 1)
		}
	}
	for (k=0; k<num_class; k++)
	{
		for (j=0; j<fhv_dim_word; j++)
		{
			p[k] += lookup(s[j] ^ c[k*fhv_dim_word + j]);
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_BINARY_LDC && defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_F
	MICROVSA_TMP_DTYPE s[MICROVSA_MAX_FHV_DIM] = {0};
	MICROVSA_ACC_DTYPE t[MICROVSA_IMPL_WORDSIZE] = {0};
    MICROVSA_TMP_DTYPE partial_t[MICROVSA_IMPL_WORDSIZE] = {0};
	for (j=0; j<fhv_dim_word; j++)
	{
        const uint8_t* __restrict__ in_ptr = in;
		for(l=0; l<MICROVSA_IMPL_WORDSIZE; l++)
		{
			t[l] = 0;
		}
		for (m=0; m<num_feature/64; m++)
		{
            for (k=0; k<64; k++)
            {
                MICROVSA_TMP_DTYPE vf = v[*in_ptr++] ^ *f++;
                for(l=MICROVSA_IMPL_WORDSIZE-1; l>=0; l--)
                {
                    partial_t[l] += vf & 1;	// t[l] += ((vf & 1) == 0) ? 1 : -1;
                    vf = vf >> 1;
                }
            }
			for(l=0; l<MICROVSA_IMPL_WORDSIZE; l++)
            {
                t[l] += partial_t[l];
                partial_t[l] = 0;
            }
		}
        if (num_feature%64 != 0)
        {
            for (k=0; k<num_feature%64; k++)
            {
                MICROVSA_TMP_DTYPE vf = v[*in_ptr++] ^ *f++;
                for(l=MICROVSA_IMPL_WORDSIZE-1; l>=0; l--)
                {
                    partial_t[l] += vf & 1;	// t[l] += ((vf & 1) == 0) ? 1 : -1;
                    vf = vf >> 1;
                }
            }
			for(l=0; l<MICROVSA_IMPL_WORDSIZE; l++)
            {
                t[l] += partial_t[l];
                partial_t[l] = 0;
            }
        }
		for(l=0; l<MICROVSA_IMPL_WORDSIZE; l++)
		{
			s[j] = s[j] << 1;
			s[j] |= ((t[l] > num_feature / 2) ? 1 : 0); 	// 0 => 1, 1 => -1   // ((t[l] >= 0) ? 0 : 1)
		}
	}
	for (k=0; k<num_class; k++)
	{
		for (j=0; j<fhv_dim_word; j++)
		{
			p[k] += lookup(s[j] ^ c[k*fhv_dim_word + j]);
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CC && !defined(MICROVSA_IMPL_OPTIMIZE_MEM)
	for (j=0; j<fhv_dim_word; j++)
	{
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE vf = v[in[i]] ^ f[i * fhv_dim_word + j];
			for (k=0; k<num_class; k++)
			{
				MICROVSA_TMP_DTYPE vfc = vf ^ c[k * fhv_dim_word + j];
				p[k] += lookup(vfc);
			}

		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CC && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && !defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_UNROLL) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_C
	#define NEED_MODEL_TRANSPOSE_F
	for (j=0; j<fhv_dim_word; j++)
	{
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE vf = v[in[i]] ^ f[j * num_feature + i];
			for (k=0; k<num_class; k++)
			{
				MICROVSA_TMP_DTYPE vfc = vf ^ c[j * num_class + k];
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CC && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_UNROLL) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_C
	#define NEED_MODEL_TRANSPOSE_F
	for (j=0; j<fhv_dim_word; j++)
	{
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE vf = v[in[i]] ^ *f++;
			for (k=0; k<num_class; k++)
			{
				MICROVSA_TMP_DTYPE vfc = vf ^ c[k];
				p[k] += lookup(vfc);
			}
		}
		c += num_class;
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CC && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && !defined(MICROVSA_IMPL_UNROLL) && defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_C
	#define NEED_MODEL_TRANSPOSE_F
	int8_t tmp[MICROVSA_MAX_NUM_CLASS] = {0};
	for (j=0; j<fhv_dim_word; j++)
	{
		const uint8_t* __restrict__ in_ptr = in;
		for (i=0; i<num_feature/16; i++)
		{
			for (l=0; l<16; l++)
			{
				MICROVSA_TMP_DTYPE vf = v[*in_ptr++] ^ *f++;
				for (k=0; k<num_class; k++)
				{
					tmp[k] += lookup(vf ^ c[k]);
				}
			}
			for (l=0; l<MICROVSA_MAX_NUM_CLASS; l++)
			{
				p[l] += tmp[l];
				tmp[l] = 0;
			}
		}
        if ((num_feature % 16) != 0)
        {
            for (l=0; l<num_feature%16; l++)
            {
                MICROVSA_TMP_DTYPE vf = v[*in_ptr++] ^ *f++;
                for (k=0; k<num_class; k++)
                {
                    tmp[k] += lookup(vf ^ c[k]);
                }
            }
            for (l=0; l<MICROVSA_MAX_NUM_CLASS; l++)
            {
                p[l] += tmp[l];
                tmp[l] = 0;
            }
        }
		c += num_class;
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CC && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && defined(MICROVSA_IMPL_UNROLL) && defined(MICROVSA_IMPL_FIX_SIZE) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_C
	#define NEED_MODEL_TRANSPOSE_F
	for (j=0; j<fhv_dim_word; j++)
	{
		LOAD_VAR(c, MICROVSA_MODEL_NUM_CLASS)
        for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE vf = v[in[i]] ^ *f++;
			SET_ARR_I_TO_VF_XOR_C_I(p, MICROVSA_MODEL_NUM_CLASS)
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CC && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && defined(MICROVSA_IMPL_UNROLL) && defined(MICROVSA_IMPL_FIX_SIZE) && defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_C
	#define NEED_MODEL_TRANSPOSE_F
    int8_t tmp[MICROVSA_MAX_NUM_CLASS]= {0};
	for (j=0; j<fhv_dim_word; j++)
	{
		LOAD_VAR(c, MICROVSA_MODEL_NUM_CLASS)
        const uint8_t* __restrict__ in_ptr = in;
        for (k=0; k<num_feature/16; k++)
        {
            for (l=0; l<16; l++)
            {
                MICROVSA_TMP_DTYPE vf = v[*in_ptr++] ^ *f++;
                SET_ARR_I_TO_VF_XOR_C_I(tmp, MICROVSA_MODEL_NUM_CLASS)
            }
            for (l=0; l<MICROVSA_MAX_NUM_CLASS; l++)
            {
                p[l] += tmp[l];
                tmp[l] = 0;
            }
        }
        if ((num_feature%16) != 0)
        {
            for (l=0; l<num_feature%16; l++)
            {
                MICROVSA_TMP_DTYPE vf = v[*in_ptr++] ^ *f++;
                SET_ARR_I_TO_VF_XOR_C_I(tmp, MICROVSA_MODEL_NUM_CLASS)
            }
            for (l=0; l<MICROVSA_MAX_NUM_CLASS; l++)
            {
                p[l] += tmp[l];
                tmp[l] = 0;
            }
        }
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CR && !defined(MICROVSA_IMPL_OPTIMIZE_MEM)
	for (i=0; i<num_feature; i++)
	{
		const MICROVSA_TMP_DTYPE v_val = v[in[i]];
		for (j=0; j<fhv_dim_word; j++)
		{
			const MICROVSA_TMP_DTYPE vf = v_val ^ *f++;
			for (k=0; k<num_class; k++)
			{
				const MICROVSA_TMP_DTYPE vfc = vf ^ c[k * fhv_dim_word + j];
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CR && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && !defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_C
	for (i=0; i<num_feature; i++)
	{
		MICROVSA_TMP_DTYPE v_val = v[in[i]];
		for (j=0; j<fhv_dim_word; j++)
		{
			MICROVSA_TMP_DTYPE vf = v_val ^ f[i * fhv_dim_word + j];
			for (k=0; k<num_class; k++)
			{
				MICROVSA_TMP_DTYPE vfc = vf ^ c[j * num_class + k];
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CR && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_C
	for (i=0; i<num_feature; i++)
	{
		const MICROVSA_TMP_DTYPE v_val = v[*in++];
		const MICROVSA_TMP_DTYPE* __restrict__ c_ptr = c;
		for (j=0; j<fhv_dim_word; j++)
		{
			const MICROVSA_TMP_DTYPE vf = v_val ^ *f++;
			for (k=0; k<num_class; k++)
			{
				const MICROVSA_TMP_DTYPE vfc = vf ^ *c_ptr++;
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_CR && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	#define NEED_MODEL_TRANSPOSE_C
    int8_t tmp[MICROVSA_MAX_NUM_CLASS]= {0};
	for (i=0; i<num_feature; i++)
	{
		const MICROVSA_TMP_DTYPE v_val = v[*in++];
		const MICROVSA_TMP_DTYPE* __restrict__ c_ptr = c;
		for (j=0; j<fhv_dim_word; j++)
		{
			const MICROVSA_TMP_DTYPE vf = v_val ^ *f++;
			for (k=0; k<num_class; k++)
			{
				const MICROVSA_TMP_DTYPE vfc = vf ^ *c_ptr++;
				tmp[k] += lookup(vfc);
			}
		}
        for (l=0; l<MICROVSA_MAX_NUM_CLASS; l++)
        {
            p[l] += tmp[l];
            tmp[l] = 0;
        }
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRI && !defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_UNROLL) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	for (k=0; k<num_class; k++)
	{
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE v_val = v[in[i]];
			for (j=0; j<fhv_dim_word; j++)
			{
				MICROVSA_TMP_DTYPE vfc = v_val ^ f[(i * fhv_dim_word) + j] ^ c[(k * fhv_dim_word) + j];
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRI && defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_UNROLL) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	for (k=0; k<num_class; k++)
	{
		const MICROVSA_TMP_DTYPE* __restrict__ f_ptr = f;
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE v_val = v[in[i]];
			const MICROVSA_TMP_DTYPE* __restrict__ c_ptr = &c[k * fhv_dim_word];
			for (j=0; j<fhv_dim_word; j++)
			{
				MICROVSA_TMP_DTYPE vfc = v_val ^ *f_ptr++ ^ *c_ptr++;
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRI && defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_UNROLL) && defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	for (k=0; k<num_class; k++)
	{
		const MICROVSA_TMP_DTYPE* f_ptr = f;
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE v_val = v[in[i]];
			const MICROVSA_TMP_DTYPE* __restrict__ c_ptr = &c[k * fhv_dim_word];
			int8_t tmp = 0;
			for (j=0; j<fhv_dim_word; j++)
			{
				MICROVSA_TMP_DTYPE vfc = v_val ^ *f_ptr++ ^ *c_ptr++;
				tmp += lookup(vfc);
			}
			p[k] += tmp;
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRI && defined(MICROVSA_IMPL_UNROLL) && defined(MICROVSA_IMPL_FIX_SIZE) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	for (k=0; k<num_class; k++)
	{
		LOAD_VAR(c, MICROVSA_MODEL_FHV_DIMENSION_WORD)

		const MICROVSA_TMP_DTYPE* __restrict__ f_ptr = f;
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE v_val = v[in[i]];
			SET_VAR_TO_V_XOR_F_XOR_C_I(p[k], MICROVSA_MODEL_FHV_DIMENSION_WORD)
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRI && defined(MICROVSA_IMPL_UNROLL) && defined(MICROVSA_IMPL_FIX_SIZE) && defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	for (k=0; k<num_class; k++)
	{
		LOAD_VAR(c, MICROVSA_MODEL_FHV_DIMENSION_WORD)

		const MICROVSA_TMP_DTYPE* __restrict__ f_ptr = f;
		for (i=0; i<num_feature; i++)
		{
			MICROVSA_TMP_DTYPE v_val = v[in[i]];

			int8_t tmp = 0;
			SET_VAR_TO_V_XOR_F_XOR_C_I(tmp, MICROVSA_MODEL_FHV_DIMENSION_WORD)
			p[k] += tmp;
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRII && !defined(MICROVSA_IMPL_OPTIMIZE_MEM)
	for (i=0; i<num_feature; i++)
	{
		MICROVSA_TMP_DTYPE v_val = v[in[i]];
		for (k=0; k<num_class; k++)
		{
			for (j=0; j<fhv_dim_word; j++)
			{
				MICROVSA_TMP_DTYPE vfc = v_val ^ f[(i * fhv_dim_word) + j] ^ c[(k * fhv_dim_word) + j];
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRII && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && !defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	MICROVSA_TMP_DTYPE t[MICROVSA_MAX_FHV_DIM] = {0};
	for (i=0; i<num_feature; i++)
	{
		const MICROVSA_TMP_DTYPE v_val = v[in[i]];
		for (j=0; j<fhv_dim_word; j++)
		{
			t[j] = v_val ^ f[(i * fhv_dim_word) + j];
		}
		for (k=0; k<num_class; k++)
		{
			for (j=0; j<fhv_dim_word; j++)
			{
				MICROVSA_TMP_DTYPE vfc = t[j] ^ c[k * fhv_dim_word + j];
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRII && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && defined(MICROVSA_IMPL_POINTERIZE) && !defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	MICROVSA_TMP_DTYPE t[MICROVSA_MAX_FHV_DIM] = {0};
	for (i=0; i<num_feature; i++)
	{
		MICROVSA_TMP_DTYPE v_val = v[in[i]];
		for (j=0; j<fhv_dim_word; j++)
		{
			t[j] = v_val ^ *f++;
		}
		const MICROVSA_TMP_DTYPE* __restrict__ c_ptr = c;
		for (k=0; k<num_class; k++)
		{
			for (j=0; j<fhv_dim_word; j++)
			{
				MICROVSA_TMP_DTYPE vfc = t[j] ^ *c_ptr++;
				p[k] += lookup(vfc);
			}
		}
	}
#elif MICROVSA_IMPL == MICROVSA_IMPL_MCU_OPT_RRII && defined(MICROVSA_IMPL_OPTIMIZE_MEM) && defined(MICROVSA_IMPL_FLAVOR_8BITADD)
	MICROVSA_TMP_DTYPE t[MICROVSA_MAX_FHV_DIM] = {0};
	for (i=0; i<num_feature; i++)
	{
		MICROVSA_TMP_DTYPE v_val = v[*in++];
		for (j=0; j<fhv_dim_word; j++)
		{
			t[j] = v_val ^ *f++;
		}
		const MICROVSA_TMP_DTYPE* __restrict__ c_ptr = c;
		for (k=0; k<num_class; k++)
		{
			int8_t tmp = 0;
			for (j=0; j<fhv_dim_word; j++)
			{
				MICROVSA_TMP_DTYPE vfc = t[j] ^ *c_ptr++;
				tmp += lookup(vfc);
			}
			p[k] += tmp;
		}
	}
#else
#error LDC Implementation not found!!! Please check the value of MICROVSA_IMPL.
#endif

#ifdef MICROVSA_IMPL_DEBUG_P
    for (j=0; j<num_class; j++)
    {
#if MICROVSA_IMPL == MICROVSA_IMPL_VANILLA_LDC
		debugP[j] = (p[j] * 2) - fhv_dim_bit;
#else
        debugP[j] = p[j];
#endif
    }
#endif
	return argmax(p, num_class);
}

#if defined(NEED_MODEL_TRANSPOSE_C) && !defined(MODEL_TRANSPOSE_C)
	#error The C vector of the LDC model need to be transpose
#endif
#if !defined(NEED_MODEL_TRANSPOSE_C) && defined(MODEL_TRANSPOSE_C)
	#error The C vector of the LDC model must not be transpose
#endif
#if defined(NEED_MODEL_TRANSPOSE_F) && !defined(MODEL_TRANSPOSE_F)
	#error The F vector of the LDC model need to be transpose
#endif
#if !defined(NEED_MODEL_TRANSPOSE_F) && defined(MODEL_TRANSPOSE_F)
	#error The F vector of the LDC model must not be transpose
#endif
