# Yggdrasil
A tree in C, for minmax, alpha beta, huffman encoding and generally messing around

the way Im compilling this: $ gcc -Wall -o main main.c tree.c common.c

New! -> Random tree generator (treeGen.c) compiled with: $ gcc -Wall -o treeGen treeGen.c

treeGen takes 3 arguments:
 the name of the file to create/rewrite with the tree
 the maximum number of children per node
 the maximum number of the leafs of the tree