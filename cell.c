#include <stdlib.h>
#include "cell.h"
#include "line.h"

extern bool line_has_ones, line_has_zeroes;

void cell_set_random_value(cell_t* cell) {
    cell->value = rand() > RAND_MAX/2;
}

void cell_set_right(cell_t* this, cell_t* right) {
    this->right = right;
    right->left = this;
}

void cell_find_next_value(cell_t* this) {
    unsigned int currentState = (this->left->left->left->value  << 6) 
                     | (this->left->left->value       << 5) 
                     | (this->left->value            << 4) 
                     | (this->value                  << 3) 
                     | (this->right->value           << 2) 
                     | (this->right->right->value     << 1) 
                     | (this->right->right->right->value);
    
    rule_t rule; // TODO get rule
    this->nextValue = rule_effect(&rule, currentState);
}

void cell_go_to_next_state(cell_t* this) {
    if (this->nextValue == 1) {
        line_has_ones = true;
    } else if (this->nextValue == 0) {
        line_has_zeroes = true;
    }
    this->value = this->nextValue;
}

