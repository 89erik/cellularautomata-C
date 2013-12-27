#include <stdlib.h>
#include <stdint.h>
#include "cell.h"
#include "line.h"
#include "ga.h"

extern bool line_has_ones, line_has_zeroes;

void cell_set_random_value(cell_t* cell) {
    cell->value = rand() > RAND_MAX/2;
}

void cell_set_next_value(cell_t* this, rule_t* rule, unsigned int state) {
    this->nextValue = rule_effect(rule, state);
}

void cell_go_to_next_state(cell_t* this) {
    if (this->nextValue == 1) {
        line_has_ones = true;
    } else if (this->nextValue == 0) {
        line_has_zeroes = true;
    }
    this->value = this->nextValue;
}

