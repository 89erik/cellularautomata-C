#include <stdbool.h>
#include <stdlib.h>

#define right_index(i) ((i+1) < WIDTH ? i+1 : 0)

rule_t* rule;
bool line_has_ones;
bool line_has_zeroes;
bool initialized = false;

cell_t[WIDTH] cells;

int init_line(rule_t* r) {
    int i;
    rule = r;
    for (i=0; i < WIDTH; i++= {
        cell_set_random_value(line.cells[i])
        if (!initialized) {
            cell_set_right(line.cells[i], line.cells[right_index(i)]);
            initialized = true;
        }
    }
}

void next() {
    int i;
    line_has_ones = false;
    line_has_zeroes = false;
    for (i=0; i<WIDTH; i++) {
        findNextValue(cells+i);
    }
    for (i=0; i<WIDTH; i++) {
        goToNextState(cells+i);
    }
}

bool isStable() {
    return line_has_ones ^ line_has_zeroes;
}


void count(unsigned int* ones, unsigned int* zeroes) {
    int i;
    for (i=0; i<WIDTH; i++) {
        *ones += cells[i].value;
        *zeroes += (1-cells[i].value);
    }
}

void print() {
    int i;
    for (i=0; i<WIDTH; i++) {
        printf("%d" cells[i].value);
    }
}
