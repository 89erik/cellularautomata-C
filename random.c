#include <stdlib.h>
#include <time.h>
#include "random.h"

void random_init(void) {
	printf("inne i random \n");
    time_t t;
    time(&t);
    srand(t);
}

