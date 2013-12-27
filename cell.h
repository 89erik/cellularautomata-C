#ifndef CELL_H
#define CELL_H
#include <stdint.h>


typedef struct cell_t{
    int8_t value;
    int8_t nextValue;
    struct cell_t* left;
    struct cell_t* right;
}cell_t;

void cell_set_random_value(cell_t* cell);
void cell_set_right(cell_t* this, cell_t* right);
void cell_find_next_value(cell_t* this);
void cell_go_to_next_state(cell_t* this);

#endif

