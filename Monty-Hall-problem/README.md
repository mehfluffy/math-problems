# Monty Hall problem
## The Monty Hall game

## The probabilities
Below is a tree diagram to demonstrate the probability of winning if the contestant switches door choice.

![](https://github.com/mehfluffy/Monty-Hall-problem/blob/main/tree_switch.svg)

We can also count the probability of "winning by switching" by listing all possibilities in a table instead:

| Prize door | First choice | Monty opens | Switch | Don't switch |
| - | - | - | - | - |
| 1 | 1 | 2 or 3 | L | W |
| 1 | 2 | 3 | W | L |
| 1 | 3 | 2 | W | L |
| 2 | 1 | 3 | W | L |
| 2 | 2 | 1 or 3 | L | W |
| 2 | 3 | 1 | W | L |
| 3 | 1 | 2 | W | L |
| 3 | 2 | 1 | W | L |
| 3 | 3 | 1 or 2 | L | W |
| . | . | **W/total =** | **2/3** | **1/3** |

For the table, since the "door numbers" are arbitrary, it would have sufficed to list only the case for `prize door = 1`, which yields the same probabilities overall. Because there is only a 1/3 chance that the first choice aligns with the prize door, there is a 1/3 chance that one could win by _not_ switching. The probability of winning by switching is then 1-1/3 = 2/3, and not 1/3 * 1/2 as intuition might suggest, because the second choice is not random. Since Monty must open a door with no prize, the original probability 2/3 of winning via the two unchosen doors "condenses" towards the door that Monty did _not_ open, because the probability that "the unchosen door x has a prize" becomes 0 when it has been opened by Monty; while the originally chosen door retains its probability to have the prize of 1/3 because Monty's choices did not entail the original door.
