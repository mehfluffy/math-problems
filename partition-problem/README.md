# Partition problem
The partition problem is the task of finding out whether a set of positive integers can be put into two subsets,
such that the sums of the two subsets are equal.

In this version, the integers are defined by the user, but is limited to 20 integers in the closed interval [1, `RAND_MAX`].

## The algorithm
A genetic algorithm is used to solve this problem. The population size is 10 and the number of generations is 200. The programme exits when a solution with equal sums is found, or when the number of generations runs out.
