#ifndef RULE_H
#define RULE_H
#include <stdint.h>

typedef struct {
	uint64_t h;
	uint64_t l;
	unsigned int fitness;
} rule_t;


void random_rule(rule_t* this);
int8_t rule_effect(rule_t* rule, unsigned int state);
void rule_mate(rule_t* mate1, rule_t* mate2, rule_t* child);
void rule_mutate(rule_t* rule, unsigned int pos);
int rule_to_string(char* string, rule_t* rule);

#endif
