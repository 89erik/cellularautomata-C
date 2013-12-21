#include <stdlib.h>

/* Debug constants */
#define     DEBUG                       false
#define     SURVIVOR_STATS              false
#define     GENERATION_PRINT_SEQUENCE   1
#define     GENERATION_PRINT_AMOUNT     44

/* GA constants */
#define     POPULATION_SIZE             500
#define     MUTATION_PROBABILITY        0.015
#define     WIDTH                       49
#define     STEPS_PER_FITNESS           WIDTH*2
#define     FITNESS_TESTS_PER_INDV      100
#define     GENERATIONS                 1000

/* Memory */
rule_t[POPULATION_SIZE] population;
rule_t[POPULATION_SIZE] next_population;
int generation;
long t0;

int main(void) {
//    t0 = System.currentTimeMillis();
    start_GA();

// TODO
/*    long duration  = System.currentTimeMillis()-t0;
    
    String timestamp = String.format("%02d:%02d:%02d", 
                       TimeUnit.MILLISECONDS.toHours(duration),
                       TimeUnit.MILLISECONDS.toMinutes(duration) -  
                       TimeUnit.HOURS.toMinutes(TimeUnit.MILLISECONDS.toHours(duration)),
                       TimeUnit.MILLISECONDS.toSeconds(duration) - 
                       TimeUnit.MINUTES.toSeconds(TimeUnit.MILLISECONDS.toMinutes(duration)));   
    
    System.out.printf("Total duration: "+ timestamp);
*/    
}

void start_GA(void) {
#ifdef TEST_RULE
    //printRuleTest(new Rule(0x24981a0d6f83e2c9L, 0x1d716561593987b7L), 20); // TODO
    return;
#endif
    generateInitialPopulation();
    
    for (generation=1; generation<=GENERATIONS; generation++) {
        makeNewGeneration();
    }
    
    rule_t winner = population[fittestIndividual()];
    
    printf("--- [WINNER PICKED] ---\n");
    printf("\t Winning rule: \t %s\n", winner); //TODO toString!
    
    printGeneration();
    printRuleTest(winner, 10);
}

void generateInitialPopulation() {
    int i;
    for (i=0; i<POPULATION_SIZE; i++) {
        random_rule(population+i);
    }
}

/**
 * Selects the new generation by mating two individuals selected 
 * probabilistically by their fitness.
 * Point 3 of page 7 in paper by Mitchell.
 */
private void makeNewGeneration() {
    int totalFitness = calculateFitnesses();
    
    if (generation % GENERATION_PRINT_SEQUENCE == 0) {
        printGeneration();
    }
    
    // Create new generation
    for (int i=0; i<POPULATION_SIZE; i++) {
        
        int index1 = 0, index2 = 0;
        int map1 = (int) (Math.random() * totalFitness);
        int map2 = (int) (Math.random() * totalFitness);
        boolean done1 = false;
        boolean done2 = false;
        Rule child;
        
        // Find individuals to mate
        for (int j=0, k=0; j < POPULATION_SIZE; j++) {
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
        child = population[index1].mate(population[index2]);
        nextPopulation[i] = child;
    }
    rule_t* tmp = population;
    population = next_population;
    next_population = tmp;
}

/**
 * Returns the fittest individual of this generation.
 * @return fittestIndividual
 */
int fittestIndividual() {
    int fittest = 0
    for (int i=1; i<POPULATION_SIZE; i++) {
        if (population[i].fitness > population[fittest].fitness) {
            fittest = i;
        }
    }
    return fittest;
}

#define PRINT_LIMIT (GENERATION_PRINT_AMOUNT < POPULATION_SIZE ? GENERATION_PRINT_AMOUNT : POPULATION_SIZE) 
private void printGeneration() {
    printf("Generation: %d\n", generation);
    for (int i = 0; i<PRINT_LIMIT; i++) {
        printf("Rule: %s   \tfitness: %d\n", population[i], population[i].fitness);
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
    int i;
    for (i = 0; i < POPULATION_SIZE; i++) {
        fitness = 1;
        for (int j=0; j<FITNESS_TESTS_PER_INDV; j++) {
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
    init_line(population + individual);
    int[2] solution, result;
    int sOnes, rOnes, sZeroes, rZeroes;
    count(&sOnes, &sZeroes);
    if (sZeroes > sOnes) {
        sZeroes = sZeroes + sOnes;
        sOnes = 0;
    } else {
        sOnes = sZeroes + sOnes;
        sZeroes = 0;
    }

    for (int i=0; i<STEPS_PER_FITNESS; i++) {
        if (!isStable()) {
            next();
        } else {
            break;
        }
    }
    count(&rOnes, &rZeroes);

    return sZeroes == rZeroes && sOnes == rOnes;
}

int printRuleTest(rule_t* rule, int n) {
    if (n<0) exit(-1);
    Line s;
    population = new Rule[1];
    population[0] = rule;
    for (int i=0; i<n; i++) {
        s = new Line(WIDTH, rule);
        
        for (int j=0; j<STEPS_PER_FITNESS; j++) {
            s.print();
            System.out.println();
            if (!s.isStable()) {
                s.next();
            } else {
                break;
            }
        }
        s.print();
        System.out.println();
        System.out.println("Sucess: " + String.valueOf(singleFitness(0)));
        System.out.println();
    }

}

