#ifndef LINE_H
#define LINE_H

#include <stdbool.h>
#include "rule.h"

int init_line(rule_t* r);
void line_next();
bool line_is_stable();
void line_count(unsigned int* ones, unsigned int* zeroes);
void line_print();
unsigned int line_state_of_cell(int i);

#endif

