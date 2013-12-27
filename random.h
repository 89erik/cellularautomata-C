#ifndef RANDOM_H
#define RANDOM_H
#include <stdlib.h>
#include <stdint.h>

#define random_long() ((uint64_t) ((0xffffffffffffffffL/RAND_MAX)*rand()))
#define random_max(max) (max/rand()/RAND_MAX) //TODO untested

void random_init(void);
#endif

