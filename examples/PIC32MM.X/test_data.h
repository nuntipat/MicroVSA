#ifndef TEST_DATA__H_
#define TEST_DATA__H_

#include <stdint.h>
#include "benchmark_config.h"

#if MODEL_NAME == 0
#define NUM_TEST_DATA 5
#define TEST_DATA_SAMPLE_LENGTH 187
#elif MODEL_NAME == 1
#define NUM_TEST_DATA 3
#define TEST_DATA_SAMPLE_LENGTH 561
#elif MODEL_NAME == 2
#define NUM_TEST_DATA 5
#define TEST_DATA_SAMPLE_LENGTH 810
#elif MODEL_NAME == 3
#define NUM_TEST_DATA 3
#define TEST_DATA_SAMPLE_LENGTH 800
#endif

extern const uint8_t test_data_sample[];
extern const uint8_t test_data_actual[];
extern const int32_t test_data_class_score[];

#endif


