# N-Queens problem
The goal is to place N chess queens on an N*N chessboard, so that none of the queens are under attack from another.

In this version, the integer 0<N<100 is defined by the user when they run the compiled code.

## The algorithm
An elitist genetic algorithm is used to solve this problem, keeping two elites every generation to replace the two worst performers in the population. The population size is 10 and the maximum number of generations is 100000.

After a no-conflict configuration is found, or the generations run out, the time used is printed.
It is found that the genetic algorithm is much faster than another solution using hill climbing, but is a little slower than one using simulated annealing.
![](https://raw.githubusercontent.com/mehfluffy/math-problems/main/N-Queens-problem/index.png)
