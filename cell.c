//TODO imports

typedef struct {
    int8_t value;
    int8_t nextValue;
    cell_t* left;
    cell_t* right;
} cell_t;

void cell_set_random_value(cell_t* cell) {
    cell->value = rand() > RAND_MAX/2;
}

void cell_set_right(cell_t* this, cell_t* right) {
    this->right = right;
    right->left = this;
}

void findNextValue(cell_t* this) {
    unsigned int currentState = (this->left.left.left.value  << 6) 
                     | (this->left.left.value       << 5) 
                     | (this->left.value            << 4) 
                     | (this->value                 << 3) 
                     | (this->right.value           << 2) 
                     | (this->right.right.value     << 1) 
                     | (this->right.right.right.value);
    
    rule_t rule; // TODO get rule
    this->nextValue = rule_effect(&rule, currentState);
}

void goToNextState(cell_t* this) {
    if (this->nextValue == 1) {
        line.hasOnes = true; // TODO (line state reference)
    } else if (this->nextValue == 0) {
        line.hasZeroes = true; // TODO (line state reference)
    }
    this->value = nextValue;
}

