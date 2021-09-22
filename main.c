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

#include "tree.h" //para as arvores
#include "common.h" //para tudo o que e comum


int main()
{

    #if 0
    //debugging para a linked list
    TipoLinkedList *lista = criarList();

    adicionarElementoFinal(lista, criarElementoComFolha(criarFolhaComInt(1)));
    adicionarElementoFinal(lista, criarElementoComFolha(criarFolhaComInt(2)));
    adicionarElementoFinal(lista, criarElementoComFolha(criarFolhaComInt(3)));
    adicionarElementoFinal(lista, criarElementoComFolha(criarFolhaComInt(4)));

    imprimirLista(lista);
    #endif

    TipoArvore *arvore = criarArvoreComRaiz(criarFolhaComInt(10));

    adicionarFilho(arvore->raiz, criarFolhaComInt(1));
    adicionarFilho(arvore->raiz, criarFolhaComInt(2));
    adicionarFilho(arvore->raiz, criarFolhaComInt(3));
    adicionarFilho(arvore->raiz, criarFolhaComInt(4));


    
    imprimirArvore(arvore);
    printf("\nx\n");
    return 0;
}