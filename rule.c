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

#include <stddef.h>
#define rule_fraction(rule, offset) (uint64_t*) (((void*) rule) + offset)
#define H64 0xffffffffffffffffL

/**
 * Returns two children of this rule and given mate.
 * They may be mutated.
 * @param mate
 * @return child
 */
void rule_mate(rule_t* mate1, rule_t* mate2, rule_t* child1, rule_t* child2) {

    if (!(rand() < CROSSOVER_PROBABILITY)) {
        *child1 = *mate1;
        *child2 = *mate2;
    }

    unsigned int pivot = random_max(RULE_SIZE);

    unsigned long int pivoted;
    unsigned long int pure;

    if (! (pivot < 64)) {
        pure    = offsetof(rule_t, h);
        pivoted = offsetof(rule_t, l);
    } else {
        pure    = offsetof(rule_t, l);
        pivoted = offsetof(rule_t, h);
    }

    *rule_fraction(child1, pure) = *rule_fraction(mate1, pure);
    *rule_fraction(child2, pure) = *rule_fraction(mate2, pure);

    *rule_fraction(child1, pivoted) = 
          *rule_fraction(mate1, pivoted) & (H64 << pivot)
        | *rule_fraction(mate2, pivoted) & (H64 >> (64-pivot));

    *rule_fraction(child2, pivoted) = 
          *rule_fraction(mate2, pivoted) & (H64 << pivot)
        | *rule_fraction(mate1, pivoted) & (H64 >> (64-pivot));

    rule_mutate(child1, random_max(RULE_SIZE));
    rule_mutate(child2, random_max(RULE_SIZE));
}

void rule_mutate(rule_t* rule, unsigned int pos) {
    if (rand() < MUTATION_PROBABILITY) {
        if (pos < 64) {
            (rule->l) ^= (1 << pos);
        } else {
            (rule->h) ^= (1 << (pos-64));
        }
    }
}

int rule_to_string(char string[], rule_t* rule) {
    return sprintf(string, "%lx%lx", rule->h, rule->l);
}

void rule_to_string_bin(char string[], rule_t* rule) {
	int i;
	for (i=RULE_SIZE-1; i>=0; i--) {
		if (i >= RULE_SIZE/2) {
			string[i] = '0' + ((rule->h >> (i-(RULE_SIZE/2))) & 1);
		} else {
			string[i] = '0' + ((rule->l >> i) & 1);
		}
    }
	string[RULE_SIZE] = '\0';
    string = "hei";
}

