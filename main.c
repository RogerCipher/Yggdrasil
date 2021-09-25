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

        printf(" -i -> prints information of loaded tree\n");
        printf(" -g -> prints graphviz format of tree\n");
        error("<fileOfTree> argument not given\n");
    }
    TipoArvore *arvore = carregarArvoreDeFicheiro(argv[1]);

    //options in args
    int optImprimirArvore = 0;
    int optImprimirGraphviz = 0;

    limparEcra();
    mostrarBanner();


    //arg option handling
    for(int i = 2; i < argc; i++)
    {

        if(!strcmp(argv[i], "-i"))
        {
            optImprimirArvore = 1;
        }

        else if(!strcmp(argv[i], "-g"))
        {
            optImprimirGraphviz = 1;
        }

        else
        {
            printf("argument %s not an option\n", argv[i]);
            error("argument given not defined.\n");
        }
    }

    if(optImprimirArvore)
    {
        imprimirArvore(arvore);
    }

    if(optImprimirGraphviz)
    {
        imprimirArvore_graphviz(arvore->raiz);
    }




    freeArvore(arvore);

    printf("\nx\n");
    return 0;
}