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

#define INFINITY 2147483647

#include "tree.h" //para as arvores
#include "common.h" //para tudo o que e comum

int main(int argc, char *argv[])
{


    if(argc < 2)
    {
        printf("Usage: %s <fileOfTree> <options>\n", argv[0]);
        printf("options: \n");

        printf(" -g -> prints graphviz format of tree in the file given\n");
        printf(" -m -> does minmax on the tree and gives a graphviz of its final form\n");
        printf(" -ab -> does alphabeta prunning and gives a graphviz of its final form\n");
        error("<fileOfTree> argument not given\n");
    }
    TipoFolha *raiz = carregarArvoreDeUmFicheiro(argv[1]);

    //options in args
    int optImprimirGraphviz = 0;
    int optMinMax = 0;
    int optAlphaBeta = 0;

    limparEcra();
    mostrarBanner();


    //arg option handling
    for(int i = 2; i < argc; i++)
    {

        if(!strcmp(argv[i], "-g"))
        {
            optImprimirGraphviz = 1;
        }
        else if (!strcmp(argv[i], "-m"))
        {
            optMinMax = 1;
        }
        else if (!strcmp(argv[i], "-ab"))
        {
            optAlphaBeta = 1;
        }
        

        else
        {
            printf("argument %s not an option\n", argv[i]);
            error("argument given not defined.\n");
        }
    }

    if(optImprimirGraphviz)
    {
        imprimirGraphviz(raiz);
    }

    if(optMinMax)
    {
        minmax(raiz);
        printf("\n\n------------- Tree after min-max: -------------\n");
        imprimirGraphviz(raiz);
    }
    if(optAlphaBeta)
    {
        alphaBeta(raiz);
        printf("\n\n------------- Tree after alpha-beta prunning: -------------\n");
        imprimirGraphviz_WithPrunes(raiz);
    }




    freeArvore(raiz);

    printf("\nx\n");
    return 0;
}