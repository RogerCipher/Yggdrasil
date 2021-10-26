# Yggdrasil
A tree in C, for MiniMax, Alpha–beta pruning and generally messing around.

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

treeGen takes 3 arguments:
* the name of the file to create/rewrite with the tree
* the maximum number of children per node
* the maximum number of the leafs of the tree

example: $ `./treeGen "testTree.txt" 3 3`

