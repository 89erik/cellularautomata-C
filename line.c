#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "line.h"
#include "ga.h"
#include "cell.h"

#define right_index(i) ((i+1) < WIDTH ? (i+1) : 0)
#define left_index(i) ((i-1) >= 0 ? (i-1) : (WIDTH-1))


rule_t* rule;
bool line_has_ones;
bool line_has_zeroes;

cell_t cells[WIDTH];

int init_line(rule_t* r) {
    int i;
    rule = r;
    for (i=0; i < WIDTH; i++) {
        cell_set_random_value(cells + i);
    }
}

unsigned int line_state_of_cell(int i) {
	int l1 = left_index(i);
	int l2 = left_index(l1);
	int l3 = left_index(l2);
	int r1 = right_index(i);
	int r2 = right_index(r1);
	int r3 = right_index(r2);

	return (cells[l3].value << 6)
		 | (cells[l2].value << 5)
         | (cells[l1].value << 4)
         | (cells[i].value  << 3)
         | (cells[r1].value << 2)
         | (cells[r2].value << 1)
         | (cells[r3].value);
}

void line_next() {
    int i;
    line_has_ones = false;
    line_has_zeroes = false;
    for (i=0; i<WIDTH; i++) {
        cell_set_next_value(cells+i, rule, line_state_of_cell(i));
    }
    for (i=0; i<WIDTH; i++) {
        cell_go_to_next_state(cells+i);
    }
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

bool line_is_stable(void) {
	return (line_has_ones ^ line_has_zeroes);
}

void line_print(void) {
    int i;
    for (i=0; i<WIDTH; i++) {
        printf("%d", cells[i].value);
    }
	printf("\n");
}
