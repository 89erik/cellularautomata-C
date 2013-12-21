#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define random_long() ((uint64_t) ((0xffffffffffffffffL/RAND_MAX)*rand()))

typedef struct {
    uint64_t h;
    uint64_t l;
    unsigned int fitness;
} rule_t;

void random_rule(rule_t* this) {
    this->h = random_long();
    this->l = random_long();
}

/**
 * Instantiates a rule of given parameters
 * @param highEnd
 * @param lowEnd
 
public Rule(long h, long l) {
    this.h = h;
    this.l = l;
}*/

/**
 * Returns the effect of the given state according to given rule.
 * @param state
 * @return effect (1 or 0)
 */
int8_t rule_effect(rule_t* rule, unsigned int state) {
    if (state < 64) {
        return (int8_t) ((rule->l >>> state) & 1); 
    } else {
        return (int8_t) ((rule->h >>> (state-64)) & 1);
    }
}

/**
 * Returns a possibly mutated child of this rule and given mate.
 * @param mate
 * @return child
 */
void mate(rule_t* mate1, rule_t* mate2, rule_t* child) {
    unsigned int pivot = random.nextInt(128); // TODO 
    
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
void mutate(rule_t* rule, unsigned int pos) {
    if (Math.random() < GA.MUTATION_PROBABILITY) { // TODO
        if (pos < 64) {
            rule->l ^= (1 << pos);
        } else {
            rule->h ^= (1 << pos-64);
        }
    }
}

int to_string(rule_t* rule, char* string) {
    return sprintf(string, "%x%x", rule->h, rule->l);
}


/*
@Deprecated
private long getRandomLong() {
    return (long)(double) (Math.random() * Integer.MAX_VALUE) | (long)(double) (Math.random() * Integer.MAX_VALUE) << 32;
}
*/

