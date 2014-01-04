#ifndef LINE_H
#define LINE_H

#include <stdbool.h>
#include "rule.h"

int init_line(rule_t* r);
void line_next();
void line_count(unsigned int* ones, unsigned int* zeroes);
void line_print(void);
bool line_is_stable(void);
unsigned int line_state_of_cell(int i);


#endif

