#ifndef CELL_H
#define CELL_H
#include <stdint.h>
#include "rule.h"

typedef struct cell_t{
    int8_t value;
    int8_t nextValue;
} cell_t;

void cell_set_random_value(cell_t* cell);
void cell_find_next_value(cell_t* this, rule_t* rule);
int8_t cell_go_to_next_state(cell_t* this);

#endif

