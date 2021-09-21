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
    imprimirLista(lista);
    printf("x\n");
    return 0;
}