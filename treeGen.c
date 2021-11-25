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



int child(FILE *ficheiro, int depth, int maxDepth, int maxChilds, int minNumber, int maxNumber)
{

    depth++;
    if(maxDepth < depth)
    {
        //generate random number between max and min
        int randNumb = minNumber + rand() % (maxNumber+1 - minNumber);

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
        child(ficheiro, depth, maxDepth, maxChilds, minNumber, maxNumber);
        fputs(")", ficheiro);
    }
    return 1;
}


int main(int argc, char *argv[])
{


    if(argc < 4)
    {
        printf("For leafs with values between 0 and 9:\n");
        printf("Usage: %s <fileOfTree> <MaxChildrenPerNode> <MaxNumberOfLevels>\n", argv[0]);

        printf("For leafs with values between a chosen range:\n");
        printf("Usage: %s <fileOfTree> <MaxChildrenPerNode> <MaxNumberOfLevels> <MinimumValue> <MaximumValue>\n", argv[0]);
        return 1;
    }

    int minValue = 0;
    int maxValue = 9;

    if(argc == 6)
    {
        minValue = atoi(argv[4]);
        maxValue = atoi(argv[5]);
    }
    else if(argc != 4)
    {
        printf("For leafs with values between 0 and 9:\n");
        printf("Usage: %s <fileOfTree> <MaxChildrenPerNode> <MaxNumberOfLevels> [optional: <MinimumValue> <MaximumValue>]\n", argv[0]);

        printf("For leafs with values between a chosen range:\n");
        printf("Usage: %s <fileOfTree> <MaxChildrenPerNode> <MaxNumberOfLevels> [optional: <MinimumValue> <MaximumValue>]\n", argv[0]);
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
    child(ficheiro, 0, atoi(argv[3]), atoi(argv[2]), minValue, maxValue);
    printf("\n");
    fclose(ficheiro);

    return 0;
}


