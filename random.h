#ifndef RANDOM_H
#define RANDOM_H
#include <stdlib.h>
#include <stdint.h>

#define random_long() ((uint64_t) ((0xffffffffffffffffL/RAND_MAX)*rand())) // TODO needs testing
#define random_max(max)  (int) (max*(double)(rand()) / (double) (RAND_MAX)) 

void random_init(void);
#endif

