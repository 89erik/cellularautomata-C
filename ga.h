#ifndef GA_H
#define GA_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* Debug constants */
#define     SURVIVOR_STATS              false
#define     GENERATION_PRINT_SEQUENCE   2
#define     GENERATION_PRINT_AMOUNT     44

/* Debug constants */
#ifdef DEBUG_MAX
    #define     D(S) printf(S)
#else
    #define     D(S) ;
#endif

#define     probability(p)              ((int) (p * (double) RAND_MAX))

/* GA constants */
#define     POPULATION_SIZE             100
#define     MUTATION_PROBABILITY        (int) (0.010 * (double)RAND_MAX)
#define     CROSSOVER_PROBABILITY       probability(0.5)
#define     WIDTH                       49
#define     STEPS_PER_FITNESS           WIDTH*2
#define     FITNESS_TESTS_PER_INDV      100
#define     GENERATIONS                 100

/* Prototypes */
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

