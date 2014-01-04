#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "rule.h"
#include "ga.h"
#include "random.h"

void random_rule(rule_t* this) {
    this->h = random_long();
    this->l = random_long();
}

/**
 * Returns the effect of the given state according to given rule.
 * @param state
 * @return effect (1 or 0)
 */
int8_t rule_effect(rule_t* rule, unsigned int state) {
    if (state < 64) {
        return (int8_t) ((rule->l >> state) & 1); 
    } else {
        return (int8_t) ((rule->h >> (state-64)) & 1);
    }
}

/**
 * Returns a possibly mutated child of this rule and given mate.
 * @param mate
 * @return child
 */
void rule_mate(rule_t* mate1, rule_t* mate2, rule_t* child) {
    unsigned int pivot = random_max(RULE_SIZE);
    
    uint64_t newH = mate1->h;
    uint64_t newL = mate1->l;
    uint64_t mask;

    if (pivot < 64) {
        mask = 0xffffffffffffffffL << pivot;
        newL &= ~mask;
        newL |= (mate2->l & mask);
        newH = mate2->h;
    } else {
        mask = 0xffffffffffffffffL << (pivot-64);
        newH &= ~mask;
        newH |= (mate2->h & mask);
    }
    
    child->h = newH;
    child->l = newL;
    rule_mutate(child, pivot);
}

/**
 * Mutates this rule
 */
void rule_mutate(rule_t* rule, unsigned int pos) {
    if (rand() < MUTATION_PROBABILITY) {
        if (pos < 64) {
            rule->l ^= (1 << pos);
        } else {
            rule->h ^= (1 << (pos-64));
        }
    }
}

int rule_to_string(char* string, rule_t* rule) {
    return sprintf(string, "%lx%lx", rule->h, rule->l);
}

void rule_to_string_bin(char* string, rule_t* rule) {
	int i;
	for (i=RULE_SIZE-1; i>=0; i--) {
		if (i >= RULE_SIZE/2) {
			string[i] = '0' + (rule->h >> (i-(RULE_SIZE/2))) & 1;
		} else {
			string[i] = '0' + (rule->l >> i) & 1;
		}
		//string[i] = '0';
    }
	string[RULE_SIZE] = '\0';
}

