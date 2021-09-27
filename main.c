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

#include "tree.h" //para as arvores
#include "common.h" //para tudo o que e comum


int main(int argc, char *argv[])
{


    if(argc < 2)
    {
        printf("Usage: %s <fileOfTree> <options>\n", argv[0]);
        printf("options: \n");

        printf(" -g -> prints graphviz format of tree\n");
        error("<fileOfTree> argument not given\n");
    }
    TipoFolha *raiz = carregarArvoreDeUmFicheiro(argv[1]);

    //options in args
    int optImprimirGraphviz = 0;

    limparEcra();
    mostrarBanner();


    //arg option handling
    for(int i = 2; i < argc; i++)
    {

        if(!strcmp(argv[i], "-g"))
        {
            optImprimirGraphviz = 1;
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


    freeArvore(raiz);

    printf("\nx\n");
    return 0;
}