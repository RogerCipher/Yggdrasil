/*
--------------------------------------------------------
by: Rogério Chaves (AKA CandyCrayon), 2021
//    __                       __                       
//   /  )             /       /  )                      
//  /   __.  ____  __/ __  , /   __  __.  __  , __ ____ 
// (__/(_/|_/ / <_(_/_/ (_/_(__// (_(_/|_/ (_/_(_)/ / <_
//                       /                  /           
//                      '                  '            
--------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"

TipoNode *createWeightedList(char *nomeFicheiro)
{
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if(ficheiro == NULL)
    {
        printf("Couldnt find file\n");
        exit(1);
    }

    char currentChar = fgetc(ficheiro);
    if(currentChar == EOF)
    {
        printf("File was empty\n");
        exit(1);
    }

    TipoNode *cabeca =  (TipoNode *)malloc(sizeof(TipoNode));
    cabeca->left = NULL;
    cabeca->parent = NULL;
    cabeca->right = NULL;
    cabeca->value = currentChar;
    cabeca->weight = 1;

    TipoNode *iterador;
    int found;
    currentChar = (char)fgetc(ficheiro);
    while(currentChar != EOF)
    {
        //para cada char no ficheiro:
        found = 0;
        iterador = cabeca;
        while (iterador != NULL)
        {
            //iterar pela linked list ate encontrarmos um elemento
            //com este "value"
            if(iterador->value == currentChar)
            {
                iterador->weight++;
                found = 1;
                break;
            }
            iterador = iterador->right;
        }

        if(!found)
        {
            //se nao foi encontrado vamos andar pela lista ate ao final
            //e adicionar no final da lista um novo node com este value
            TipoNode *novoNode = (TipoNode *)malloc(sizeof(TipoNode));
            novoNode->parent = NULL;
            novoNode->right = NULL;
            novoNode->value = currentChar;
            novoNode->weight = 1;

            iterador = cabeca;
            while (iterador->right != NULL)
            {
                iterador = iterador->right;
            }

            iterador->right = novoNode;
            novoNode->left = iterador;
        }
        

        currentChar = (char)fgetc(ficheiro);
    }
    printf("EOF\n");

    return cabeca;


    fclose(ficheiro);
}

int orderByLowestWeight(TipoNode *cabeca)
{
    //ter o tamanho da lista
    int tamanhoLista = 0;
    TipoNode *iterador = cabeca;
    while(iterador != NULL)
    {
        tamanhoLista++;
        iterador = iterador->right;
    }

    //temporary variables for the swap in the bubble sort
    char tempChar;
    int tempInt;

    printf("\nbubble\n");
    printf("tamanhoLista = %d\n", tamanhoLista);
    //bubble sort na lista
    for(int i = 0; i < tamanhoLista; i++)
    {
        printf("*i = %d\n", i);
        //reset the iterator to the right position
        iterador = cabeca;
        for(int pos = 0; pos < i; pos++)
            iterador = iterador->right;
            

        
        for(int j = 0; j < tamanhoLista - i -1; j++)
        {
            printf("j = %d\n", j);
            if(iterador->weight > iterador->right->weight)
            {
                //swap the information of these nodes
                tempInt = iterador->weight;
                tempChar = iterador->value;

                iterador->weight = iterador->right->weight;
                iterador->value = iterador->right->value;

                iterador->right->weight = tempInt;
                iterador->right->value = tempChar;
            }
            iterador = iterador->right;
        }
    }



    return 0;
}

int printLL(TipoNode *cabeca)
{
    TipoNode *iterador = NULL;
    iterador = cabeca;
    while (iterador != NULL)
    {
        printf("valor: %c, peso: %d\n", iterador->value, iterador->weight);
        iterador = iterador->right;
    }
    return 1;
    
}



int main(int argc, char *argv[])
{
    TipoNode *cabeca = createWeightedList(argv[1]);
    printLL(cabeca);
    printf("---------\n");
    orderByLowestWeight(cabeca);
    printLL(cabeca);

    printf("\nx\n");
    return 0;
}