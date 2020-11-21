#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAXQ 100
#define POPSIZE 10
#define MAXITER 100000

#define FALSE 0
#define TRUE  1

#define ABS(a) ((a) < 0 ? (-(a)) : (a))

int nqueens;      /* number of queens: global variable */

typedef struct {
  int *queens;   /* queen at (r,c) is represented by queens[r] == c */
  int conflicts;
} State;

void initializeRandomGenerator() {
  /* this routine initializes the random generator. You are not
   * supposed to understand this code. You can simply use it.
   */
  time_t t;
  srand((unsigned) time(&t));
}

/* returns TRUE if position (row0,column0) is in
 * conflict with (row1,column1), otherwise FALSE.
 */
int inConflict(int row0, int column0, int row1, int column1) {
  if (row0 == row1) return TRUE; /* on same row, */
  if (column0 == column1) return TRUE; /* column, */
  if (ABS(row0-row1) == ABS(column0-column1)) return TRUE;/* diagonal */
  return FALSE; /* no conflict */
}

/* returns TRUE if position (row,col) is in
 * conflict with any other queen on the board, otherwise FALSE.
 */
int inConflictWithAnotherQueen_State(int row, int col, State s) {
  int queen;
  for (queen=0; queen < nqueens; queen++) {
    if (inConflict(row, col, queen, s.queens[queen])) {
      if ((row != queen) || (col != s.queens[queen])) return TRUE;
    }
  }
  return FALSE;
}

void printState_State(State s) {
	int row, column;
  printf("\n");
  for(row = 0; row < nqueens; row++) {
    for(column = 0; column < nqueens; column++) {
      if (s.queens[row] != column) {
        printf (".");
      } else {
        if (inConflictWithAnotherQueen_State(row, column, s)) {
          printf("Q");
        } else {
          printf("q");
        }
      }
    }
    printf("\n");
  }
  printf("Number of conflicts = %d\n", s.conflicts);
}

/* returns the number of pairs of queens that are in conflict */
int countConflicts_State(State s) {
  int cnt = 0;
  int queen, other;
  for (queen=0; queen < nqueens; queen++) {
    for (other=queen+1; other < nqueens; other++) {
      if (inConflict(queen, s.queens[queen], other, s.queens[other])) {
        cnt++;
      }
    }
  }
  return cnt;
}

State makeState(int config[]){
  State state;
  state.queens = calloc(nqueens,sizeof(int));
  for (int i=0; i<nqueens; i++) {
    state.queens[i] = config[i];
  }
  state.conflicts = countConflicts_State(state);
  return state;
}

void initializePopulation(State population[]) {
  for (int i=0; i<POPSIZE; i++) {
    int config[MAXQ];
    for (int j=0; j<nqueens; j++) {
      config[j] = random()%nqueens;
    }
    population[i] = makeState(config);
  }
}

int * mutateArray(int config[]) {
  int index = random()%nqueens;
  config[index] = random()%nqueens;
  return config;
}

typedef struct {
  State c1;
  State c2;
} Children;   // this is to store the 2 returns of reproduce()

Children reproduce(State parent1, State parent2) {
  int *childArr1 = calloc(nqueens,sizeof(int));
  int *childArr2 = calloc(nqueens,sizeof(int));
  /* random cutting point to crossover */
  int cut = random() % (nqueens-1);
  for (int i=0; i<cut; i++) {
    childArr1[i] = parent1.queens[i];
    childArr2[i] = parent2.queens[i];
  }
  for (int i=cut; i<nqueens; i++) {
    childArr1[i] = parent2.queens[i];
    childArr2[i] = parent1.queens[i];
  }
  /* mutate one gene */
  childArr1 = mutateArray(childArr1);
  childArr2 = mutateArray(childArr2);
  /* make into States */
  State child1, child2;
  child1 = makeState(childArr1);
  child2 = makeState(childArr2);
  Children result;
  result.c1 = child1;
  result.c2 = child2;
  return result;
}

void sortPopulation(State population[POPSIZE]) {
  State temp;
  for (int i=0; i<(POPSIZE-1); i++) {
    for (int j=0; j<(POPSIZE-1-i); j++) {
      if (population[j].conflicts > population[j+1].conflicts){
        /* least conflicts first */
        temp = population[j];
        population[j] = population[j+1];
        population[j+1] = temp;
      }
    }
  }
}

/* after population is sorted */
void newGeneration(State population1[POPSIZE]) {
  State population2[POPSIZE];
  /* we keep the top 2 */
  int numElites = 2;
  for (int i=0; i<numElites; i++) {
    population2[POPSIZE-1-i] = population1[i];
  }
  /* top 8 can reproduce, bottom 2 die out */
  for (int i=0; i<(POPSIZE-numElites)/2; i++) {   // i = 0,1,2,3
    Children children = reproduce(population1[i*2], population1[i*2+1]);
    population2[i*2] = children.c1;
    population2[i*2+1] = children.c2;
  }
  /* copy */
  for (int i=0; i<POPSIZE; i++) {
    population1[i] = population2[i];
  }
}

void geneticAlgorithm() {
  State Population[POPSIZE];
  initializePopulation(Population);
  sortPopulation(Population);   // for initial print, and solution checking
  printf("Initial best state:");
  printState_State(Population[0]);
  for (int iter=0; iter<MAXITER; iter++) {
    /* check for solution */
    if (Population[0].conflicts == 0) {
      printf("\nSOLVED");
      break;
    }
    newGeneration(Population);
    sortPopulation(Population);
  }
  printf("\nFinal best state:");
  printState_State(Population[0]);
}


int main(int argc, char *argv[]) {
  int algorithm;

  do {
    printf ("Number of queens (1<=nqueens<%d): ", MAXQ);
    scanf ("%d", &nqueens);
  } while ((nqueens < 1) || (nqueens > MAXQ));

  do {
    printf ("Algorithm: (4) Genetic Algorithm: ");
    scanf ("%d", &algorithm);
  } while ((algorithm < 3) || (algorithm > 4));

  initializeRandomGenerator();

  clock_t begin = clock();

  switch (algorithm) {
    case 4: geneticAlgorithm(); 		break;
  }

  clock_t end = clock();
  float timeSpent = (float)(end - begin)/CLOCKS_PER_SEC;
  printf("\nTime spent: %f seconds\n", timeSpent);

  return 0;
}
