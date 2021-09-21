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

#include "tree.h"

TipoFolha *criarFolha()
{
    TipoFolha *folha = (TipoFolha *)malloc(sizeof(TipoFolha));
    folha->children = NULL;
    folha->parent = NULL;
    return folha;
}

TipoFolha *criarFolhaComInt(int valor)
{
    TipoFolha *folha = criarFolha();
    folha->data.valor = valor;
    return folha;
}

TipoArvore *criarArvore()
{
    TipoArvore *arvore = (TipoArvore *)malloc(sizeof(TipoArvore));
    arvore->raiz = NULL;
    return arvore;
}

TipoArvore *criarArvoreComRaiz(TipoFolha *raiz)
{
    TipoArvore *arvore = (TipoArvore *)malloc(sizeof(TipoArvore));
    arvore->raiz = raiz;
    arvore->raiz->nivelDaFolha = 0;
    return arvore;
}



