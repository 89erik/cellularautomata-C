#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "line.h"
#include "ga.h"
#include "cell.h"

#define right_index(i) ((i+1) < WIDTH ? i+1 : 0)

rule_t* rule;
bool line_has_ones;
bool line_has_zeroes;
bool initialized = false;

cell_t cells[WIDTH];

int init_line(rule_t* r) {
    int i;
    rule = r;
    for (i=0; i < WIDTH; i++) {
        cell_set_random_value(cells + i);
        if (!initialized) { //TODO is this the best solution?
            cell_set_right(cells + i, cells + right_index(i));
            initialized = true;
        }
    }
}

void line_next() {
    int i;
    line_has_ones = false;
    line_has_zeroes = false;
    for (i=0; i<WIDTH; i++) {
        cell_find_next_value(cells+i);
    }
    for (i=0; i<WIDTH; i++) {
        cell_go_to_next_state(cells+i);
    }
}

bool line_is_stable() {
    return line_has_ones ^ line_has_zeroes;
}


void line_count(unsigned int* ones, unsigned int* zeroes) {
    int i;
    *ones = 0;
    *zeroes = 0;
    for (i=0; i<WIDTH; i++) {
        *ones += cells[i].value;
        *zeroes += (1-cells[i].value);
    }
}

void line_print() {
    int i;
    for (i=0; i<WIDTH; i++) {
        printf("%d", cells[i].value);
    }
}
