#include <stdlib.h>
#include <stdint.h>
#include "cell.h"
#include "line.h"
#include "ga.h"

void cell_set_random_value(cell_t* cell) {
    cell->value = rand() > RAND_MAX/2;
}

void cell_set_next_value(cell_t* this, rule_t* rule, unsigned int state) {
    this->nextValue = rule_effect(rule, state);
}

int8_t cell_go_to_next_state(cell_t* this) {
    return this->value = this->nextValue;
}

