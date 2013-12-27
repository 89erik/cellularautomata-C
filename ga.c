#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "line.h"
#include "rule.h"
#include "cell.h"
#include "ga.h"
#include "random.h"

/* Memory */
rule_t populations[2][POPULATION_SIZE];
int p_buf;
rule_t* population;


unsigned int generation;

int main(void) {
    random_init();
	time_t t0,tn;
    time(&t0);
    start_GA();
    time(&tn);

    printf("Total duration: %d seconds\n", (unsigned int)(tn-t0));
}

void start_GA(void) { 
#ifdef TEST_RULE
    //printRuleTest(new Rule(0x24981a0d6f83e2c9L, 0x1d716561593987b7L), 20); // TODO
    return;
#endif
    generateInitialPopulation();
    
    for (generation=1; generation<=GENERATIONS; generation++) {
        make_new_generation();
    }
    int winner_index = fittestIndividual();
    rule_t winner = population[winner_index];
   
	char buf[WIDTH+1];
	rule_to_string(buf, &winner); 
    printf("--- [WINNER PICKED] ---\n");
    printf("\t Winning rule: \t %s\n", buf);
    
//    printGeneration();
    printRuleTest(winner_index, 10);
}

void generateInitialPopulation(void) {
    int i;
	p_buf = 0;
	population = populations[p_buf];
    for (i=0; i<POPULATION_SIZE; i++) {
        random_rule(population+i);
    }
}

/**
 * Selects the new generation by mating two individuals selected 
 * probabilistically by their fitness.
 * Point 3 of page 7 in paper by Mitchell.
 */
void make_new_generation() {
    int totalFitness = calculateFitnesses();
	int i,j,k;
	rule_t* next_population = populations[1-p_buf];
    
    if (generation % GENERATION_PRINT_SEQUENCE == 0) {
        printGeneration();
    }
    
    // Create new generation
    for (i=0; i<POPULATION_SIZE; i++) {
        
        int index1 = 0, index2 = 0;
        int map1 = (int) random_max(totalFitness);
        int map2 = (int) random_max(totalFitness);
        bool done1 = false;
        bool done2 = false;
        
        // Find individuals to mate
        for (j=0, k=0; j < POPULATION_SIZE; j++) {
            if (done1 && done2) break;
            
            k += population[j].fitness;
            if (!done1 && k >= map1) {
                index1 = j;
                done1 = true;
            }
            if (!done2 && k >= map2) {
                index2 = j;
                done2 = true;
            }
        }
		rule_mate(population+index1, population+index2, next_population + i);
    }

	p_buf = 1-p_buf;
	population = populations[p_buf];
}

/**
 * Returns the fittest individual of this generation.
 * @return fittestIndividual
 */
int fittestIndividual() {
    int fittest = 0;
	int i;
    for (i=1; i<POPULATION_SIZE; i++) {
        if (population[i].fitness > population[fittest].fitness) {
            fittest = i;
        }
    }
    return fittest;
}

#define PRINT_LIMIT (GENERATION_PRINT_AMOUNT < POPULATION_SIZE ? GENERATION_PRINT_AMOUNT : POPULATION_SIZE) 
void printGeneration() {
	int i;
	char rule_string[WIDTH+1];
    printf("Generation: %d\n", generation);
    for (i = 0; i<PRINT_LIMIT; i++) {
		rule_to_string(rule_string, population+i);
        printf("Rule: %s   \tfitness: %d\n", rule_string, population[i].fitness);
    }
}

/**
 * Calculates the fitness of all individuals in this generation.
 * Returns the total amount of fitness.
 * @return totalFitness
 */
int calculateFitnesses() {
    int fitness;
    int totalFitness = 0;
    int i,j;
    for (i=0; i < POPULATION_SIZE; i++) {
        fitness = 1;
        for (j=0; j < FITNESS_TESTS_PER_INDV; j++) {
            if (singleFitness(i)) {
                fitness++;
            }
        }
        population[i].fitness = fitness; 
        totalFitness += fitness;
        //debug("Total fitness for rule %s:\t%d\n", population[i], fitness);
    }
    return totalFitness;
}


bool singleFitness(int individual) {
    int sOnes, rOnes, sZeroes, rZeroes;
	int i;    
	init_line(population + individual);
    line_count(&sOnes, &sZeroes);
    if (sZeroes > sOnes) {
        sZeroes = sZeroes + sOnes;
        sOnes = 0;
    } else {
        sOnes = sZeroes + sOnes;
        sZeroes = 0;
    }

    for (i=0; i<STEPS_PER_FITNESS; i++) {
        if (!line_is_stable()) {
            line_next();
        } else {
            break;
        }
    }
    line_count(&rOnes, &rZeroes);

    return sZeroes == rZeroes && sOnes == rOnes;
}

int printRuleTest(int rule, int n) {
    if (n<0) exit(-1);
	int i,j;
    for (i=0; i<n; i++) {
        init_line(population+rule);
        for (j=0; j<STEPS_PER_FITNESS; j++) {
            line_print();
            printf("\n");
            if (!line_is_stable()) {
                line_next();
            } else {
                break;
            }
        }
        line_print();
        printf("\nSucess: %s\n\n", (singleFitness(rule)? "true" : "false"));
    }

}

