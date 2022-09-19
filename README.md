# Yggdrasil
### A tree in C, for MiniMax, Alpha–beta pruning and generally messing around.

Stuff implemented in this project (so far):
|function|status|where 
|--|--|--|
|Random generated trees|✅ Implemented|treeGen.c|
|MiniMax|✅ Implemented|main.c|
|Alpha–beta pruning|✅ Implemented|main.c|
|Huffman coding|⭕ moved to another repo|[Ymir repo](https://github.com/RogerCipher/Ymir)|

the way I'm compiling this: 
$ `gcc -Wall -o main main.c minMaxAndAlphaBeta.c common.c`

*main* will take at least one argument, the name of the file in which the the tree (in bracket representation) is.

to run a simple test do:
$ `./main "testTree.txt" -g`

this will print the tree that's in the "testTree.txt" file in [graphviz](https://dreampuf.github.io/GraphvizOnline) format.
## Random tree generator (treeGen.c)

compiled with: $ `gcc -Wall -o treeGen treeGen.c`

treeGen takes 3 or 5 arguments:
* the name of the file to create/rewrite with the tree
* the maximum number of children per node
* the maximum depth of the tree

---[OPTIONALLY]---

* the minimum leaf value
* the maximum leaf value

(if no values are given as the maximum and minimum value of the leafs it will use 0 as min and 9 as max values)

examples:
##### generate a tree to file "testTree.txt" with:
 * maximum number of children per node = 3
 * the maximum depth of the tree = 2
 
 $ `./treeGen "testTree.txt" 3 2`

##### generate a tree to file "testTree.txt" with:
 * maximum number of children per node = 3
 * the maximum depth of the tree = 2
 * the minimum value of a leaf node = -10
 * the maximum value of a leaf node = 10
 
 $ `./treeGen "testTree.txt" 3 2 -10 10`


