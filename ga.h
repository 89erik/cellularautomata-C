#ifndef GA_H
#define GA_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* Debug constants */
#define     SURVIVOR_STATS              false
#define     GENERATION_PRINT_SEQUENCE   1
#define     GENERATION_PRINT_AMOUNT     44

/* Debug constants */
#define     DEBUG
#ifdef DEBUG
    #define     D(S) printf(S)
#else
    #define     D(S) ;
#endif


/* GA constants */
#define     POPULATION_SIZE             500
#define     MUTATION_PROBABILITY        0.015 * RAND_MAX //TODO verify math
#define     WIDTH                       49
#define     STEPS_PER_FITNESS           WIDTH*2
#define     FITNESS_TESTS_PER_INDV      100
#define     GENERATIONS                 1000

int  main(void);
void start_GA(void);
void generateInitialPopulation(void);
void make_new_generation();
int  fittestIndividual();
void printGeneration();
int  calculateFitnesses();
bool singleFitness(int individual);
int  printRuleTest(int rule, int n);

#endif

