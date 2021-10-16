#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__


typedef struct Node
{
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    int weight;
    char value;
} TipoNode;

#endif