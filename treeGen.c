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


//cria uma arvore com a syntax dos parentesis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int filho(FILE *ficheiro, int depth, int maxDepth, int maxChilds)
{

    depth++;
    if(maxDepth < depth)
    {
        int randNumb = rand() % 50;
        char randNumString[4];
        
        sprintf(randNumString, "%d", randNumb);

        fputs(randNumString, ficheiro);
        return 1;
    }

    
    int randChilds = rand() % maxChilds;

    printf(".");

    for(int i = 0; i <= randChilds; i++)
    {
        fputs("(", ficheiro);
        filho(ficheiro, depth, maxDepth, maxChilds);
        fputs(")", ficheiro);
    }
    




    return 1;
}


int main(int argc, char *argv[])
{


    if(argc != 4)
    {
        printf("Usage: %s <fileOfTree> <MaxChildrenPerNode> <MaxNumberOfLevels>\n", argv[0]);
        return 1;
    }


        //printf("fds pah\n");
        //fputs(randomNumberString, ficheiro);


    FILE *ficheiro = fopen(argv[1], "w");
    if (ficheiro == NULL) 
    {
        //algo correu mal
        printf("Nao foi possivel abrir o ficheiro \"%s\"\n", argv[1]);
        return 0;
    }



    printf("\nWorking on it chief..\n");
    filho(ficheiro, 0, atoi(argv[3]), atoi(argv[2]));
    printf("\n");
    fclose(ficheiro);

    return 0;
}


