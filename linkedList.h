#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "tree.h"
/*---------------- estruturas --------------------*/

//estrutura para guardar um elemento numa linked list com informacao de um elemento da arvore
typedef struct TipoELL
{
    struct TipoELL *proximo;
    struct TipoELL *anterior;
    TipoFolha *folha;
}TipoElementoLinkedList;

//estrutura para uma linked list que guarda um elemento da arvore
typedef struct TipoLL
{
    TipoElementoLinkedList *cabeca; //primeiro elemento da linked list
    TipoElementoLinkedList *iterador; //elemento em que estamos actualmente na linked list
    int indexElementoActual; //index do elemento que estamos actualmente  na linked list
    int len; //tamanho da linked list
}TipoLinkedList;


/*---------- funcoes --------------*/
TipoElementoLinkedList *criarElemento();

TipoElementoLinkedList *criarElementoComFolha(TipoFolha *folha);

int temProximo(TipoElementoLinkedList *elem);
int temAnterior(TipoElementoLinkedList *elem);

TipoLinkedList *criarList();
int resetIterPosition(TipoLinkedList *list);
int moverIterParaProximo(TipoLinkedList *list);
int moverIterParaAnterior(TipoLinkedList *list);
int tamanhoLinkedList(TipoLinkedList *list);

int adicionarElementoFinal(TipoLinkedList *list, TipoElementoLinkedList *elem);


/*---debugging stuff---*/
void imprimirLista(TipoLinkedList *list);
#endif