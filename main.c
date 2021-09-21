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


#include "tree.h" //para as arvores
#include "linkedList.h" //para as linked lists
#include "common.h" //para tudo o que e comum


int main()
{
    TipoLinkedList *lista = criarList();

    adicionarElementoFinal(lista, criarElementoComFolha(criarFolhaComInt(1)));
    adicionarElementoFinal(lista, criarElementoComFolha(criarFolhaComInt(2)));
    adicionarElementoFinal(lista, criarElementoComFolha(criarFolhaComInt(3)));
    adicionarElementoFinal(lista, criarElementoComFolha(criarFolhaComInt(4)));


    imprimirLista(lista);
    printf("length da lista: %d", lista->len);
    printf("\nx\n");
    return 0;
}