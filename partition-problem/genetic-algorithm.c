#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define numBlocks 20
#define chromLength numBlocks
#define popSize 10
#define numElites 2
#define numGenerations 200

//initialize arrays
int blocks[numBlocks]; //stores the heights of blocks
bool generation[popSize][chromLength]; //10 chromosomes of length 20 in each generation

//Subfunctions

void readHeights(){ 
  int H = RAND_MAX;
  printf("Heights of blocks must be integers within [1,%d].\n", H); //inputs may repeat as long as in range
  for(int i=0; i<numBlocks; i+=1){
    printf("Enter the height of block %d: ", i+1);
    scanf("%d", &blocks[i]);
    while (blocks[i]<1 || blocks[i]>H){
      printf("Input out of range. Please re-enter the height of block %d: ", i+1);
      scanf("%d", &blocks[i]);
    }
  }
  printf("\nHeights: ");
  for(int i=0; i<numBlocks; i+=1){
    printf("%d ", blocks[i]);
  }
  printf("\n");
  return;
}

void newChrom(int c){ //c is the chromosome ID
	for(int i=0; i<chromLength; i+=1){
    bool r = ( rand() / (RAND_MAX / 2) ); //gives r as either 1 or 0
		generation[c][i] = r;
  }
  return;
}

//make first population
void fillPop(){
  for(int c=0; c<popSize; c+=1){ 
    newChrom(c);
  }
  return;
}

int heightOfTower(int c, bool b){
  int height = 0;
  for (int i=0; i<chromLength; i+=1){
    if (generation[c][i] == b){
      height += blocks[i];
    }
  }
  return height;
}

int heightDifference(int c){
  return abs(heightOfTower(c,true) - heightOfTower(c,false));
}

void getFitness(){
  //fill heightDifferences into the fitness array
  int popFitness[popSize];
  for (int c=0; c<popSize; c+=1){
    popFitness[c] = heightDifference(c);
  }
  return;
}

//Sort the chromosomes themselves according to fitness
void sortPop(){
  for(int i=0; i<popSize; i+=1){
    for(int j=0; j<popSize-i-1; j+=1){
      if (heightDifference(j) > heightDifference(j+1)){
        bool tempChrom[chromLength];
        memcpy(tempChrom,       &generation[j],   chromLength);
        memcpy(generation[j],   &generation[j+1], chromLength);
        memcpy(generation[j+1], &tempChrom,       chromLength);
      }
    }
  }
  return;
}

// mutation
void mutateGene(int c){
	int i = rand() % chromLength; //select random gene position i within 0 to 19
	if (generation[c][i] == true)
		generation[c][i] = false;
  else
		generation[c][i] = true; //flip gene
	return;
}

// crossover
void crossChrom(int c1, int c2){ //c1,2 are IDs of chromosomes to cross with each other
  int p = rand() % (chromLength-1); //select random cutting point p=[0,18]
  bool tempHead[p+1];
  //copy Head
  memcpy(tempHead,       &generation[c1][0], p+1);
  memcpy(generation[c1], &generation[c2][0], p+1);
  memcpy(generation[c2], &tempHead[0], p+1);
  return;
}

// check for identical chromosomes
bool identicalChrom(int c1, int c2){
  for (int i=0; i<chromLength; i+=1){
    if (generation[c1][i] != generation[c2][i]){
      return false;
    }
  }
  return true;
}

// after sorting, replace identical solutions with a unique solution
void promoteNew(){
  if (heightDifference(0) == heightDifference(1) && heightDifference(2) == heightDifference(0)){
    if (identicalChrom(0,1) == true && identicalChrom(1,2) == false){
      memcpy(generation[1], &generation[2], chromLength);
    }
  }
  return;
}

// make new generation
void newGen(){
  for (int c=0; c<numElites; c+=1){
    memcpy(generation[popSize-(c+1)], &generation[c], chromLength);
  }
  for (int c=0; c<(popSize-numElites)/2; c+=1){
    crossChrom(c*2,(c*2)+1);
  }
  for(int c=0; c<popSize-numElites; c+=1){
    mutateGene(c);
  }
  return;
}


// main function
int main(){
	srand((unsigned)time(NULL));
	
	// monitoring counters
	int genCount = 0;
	int sameCount = 0;
	int prevBest = RAND_MAX;
	
	// make new random generation
	readHeights();
	fillPop();

	for (int i=0; i<numGenerations; i+=1){
	  genCount += 1;
	  sortPop();
	  
	  printf ("\nGeneration %d has height differences:", genCount);
	  for (int c=0; c<popSize; c+=1){
	    printf (" %d", heightDifference(c));
	  }

    // count number of generations that the current best solution has survived
    // reset to 0 every time the solution is replaced
    if (heightDifference(0)<prevBest){
      prevBest = heightDifference(0);
      sameCount = 0;
  	}
  	else
      sameCount +=1;

// terminating condition
    if (heightDifference(0) == 0 || sameCount == 0.3*numGenerations){
      printf ("\n\nThe best solution is found after %d generations with a height difference of %d", genCount, heightDifference(0));
    	printf ("\n\nwhere Set 0 has total height %d from blocks:", heightOfTower(0,0));
    	for (i=0; i<chromLength; i+=1){
    	  if (generation[0][i] == false){
    	    printf (" %d", blocks[i]);
    	  }
    	}
    	printf ("\nand Set 1 has total height %d from blocks:", heightOfTower(0,1));
    	for (i=0; i<chromLength; i+=1){
    	  if (generation[0][i] == true){
    	    printf (" %d", blocks[i]);
    	  }
    	}
    	// show unique solutions with same heightDifference
    	if ( heightDifference(0) == heightDifference(1)
        && identicalChrom(0,1) == false){
    	  printf ("\n\nOR Set 0 has total height %d from blocks:", heightOfTower(1,0));
      	for (i=0; i<chromLength; i+=1){
      	  if (generation[1][i] == false){
      	    printf (" %d", blocks[i]);
      	  }
      	}
      	printf ("\nand Set 1 has total height %d from blocks:", heightOfTower(1,1));
      	for (i=0; i<chromLength; i+=1){
      	  if (generation[1][i] == true){
      	    printf (" %d", blocks[i]);
      	  }
      	}
    	}
    	break;
    }
    else
      promoteNew();
      newGen();
	}
	return 0;
}
