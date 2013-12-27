#include <stdlib.h>
#include <time.h>
#include "random.h"

void random_init(void) {
    time_t t;
    time(&t);
    srand(t);
}

