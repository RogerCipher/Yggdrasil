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

/*---------------------------FUNCOES PARA LINKED LIST---------------------------------------------*/

TipoElementoLinkedList *criarElemento()
{
    //alocar o espaco na memoria para um elemento
    TipoElementoLinkedList *elem = (TipoElementoLinkedList *)malloc(sizeof(TipoElementoLinkedList));

    //meter tudo a "NULL"
    elem->folha = NULL;
    elem->proximo = NULL;
    elem->anterior = NULL;

    return elem;
}


TipoElementoLinkedList *criarElementoComFolha(TipoFolha *folha)
{
    TipoElementoLinkedList *elem = criarElemento();
    elem->folha = folha;
    return elem;
}

int temProximo(TipoElementoLinkedList *elem) //retorna 1 se tiver proximo, 0 se nao tiver
{
    if(elem->proximo == NULL)
    {
        return 0;
    }
    return 1;
}
int temAnterior(TipoElementoLinkedList *elem)//retorna 1 se tiver anterior, 0 se nao tiver
{
    if(elem->anterior == NULL)
    {
        return 0;
    }
    return 1;
}

TipoLinkedList *criarList()
{
    //alocar o espaco na memoria para a linked list
    TipoLinkedList *list = (TipoLinkedList *)malloc(sizeof(TipoLinkedList));

    //meter tudo a "NULL"
    list->cabeca = NULL;
    list->iterador = NULL;
    list->indexElementoActual = -1;
    list->len = 0;

    return list;
}

int resetIterPosition(TipoLinkedList *list)
{
    if(list->cabeca == NULL)
    {
        //a lista ainda nao tem elementos, nao vamos fazer nada
        return 0;
    }

    list->iterador = list->cabeca;
    list->indexElementoActual = 0;
    return 1;
}


int moverIterParaProximo(TipoLinkedList *list)
{
    if(!temProximo(list->iterador))
    {
        //nao ha proximo elemento
        return 0;
    }
    list->iterador = list->iterador->proximo;
    list->indexElementoActual++;
    return 1;
}

int moverIterParaAnterior(TipoLinkedList *list)
{
    if(!temAnterior(list->iterador))
    {
        //nao ha elemento anterior (estamos na cabeca)
        return 0;
    }
    list->iterador = list->iterador->anterior;
    list->indexElementoActual--;
    return 1;
}

int tamanhoLinkedList(TipoLinkedList *list) //da refresh e retorna o tamanho da linked list
{
    if(!resetIterPosition(list))
    {
        //a lista ainda nao tem elementos
        return 0;
    }
    //dar refresh e retornar quantos elementos a linked list tem
    int tamanho = 0;
    while (temProximo(list->iterador))
    {
        moverIterParaProximo(list);
        tamanho++;
    }
    list->len = tamanho;
    return list->len;
    
}

int adicionarElementoFinal(TipoLinkedList *list, TipoElementoLinkedList *elem)
{
    if(list->cabeca == NULL)
    {
        //estamos no primeiro elemento da lista
        list->cabeca = elem;
        list->iterador = list->cabeca;
        list->indexElementoActual = 0;
        list->len = 1;
        return 1;
    }

    //ja existem elementos, por isso vamos mover o iterador ate ao final
    while(temProximo(list->iterador))
    {
        moverIterParaProximo(list);
    }

    list->iterador->proximo = elem;
    list->iterador->proximo->anterior = list->iterador;
    list->len++;

    resetIterPosition(list);

    return 1;
}

void imprimirLista(TipoLinkedList *list)
{
    resetIterPosition(list);
    if(list->cabeca == NULL)
    {
        //esta lista esta vazia
        printf("tentativa de imprimir uma lista sem nada.\n");
    }
    for(int i = 0; i < list->len; i++)
    {
        printf("elemento: %d, valor: ", i);
        if(list->iterador->folha != NULL)
        {
            printf("%d\n", list->iterador->folha->data.valor);
            moverIterParaProximo(list);
        }
        else
        {
            //esta folha nao tem nada
            printf("nada\n");
        } 
    }
}

/*---------------------------FUNCOES PARA A ARVORE---------------------------------------------*/
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

int adicionarFilho(TipoFolha *folhaPai, TipoFolha *folhaFilho)
{
    if(folhaPai->children == NULL)
    {
        //ainda nao existe filhos, vamos criar a lista
        TipoLinkedList *listaFilhos = criarList();

        folhaPai->children = listaFilhos;
    }

    adicionarElementoFinal(folhaPai->children, criarElementoComFolha(folhaFilho));

    folhaFilho->parent = folhaPai;
    folhaFilho->nivelDaFolha = folhaPai->nivelDaFolha+1;

    return 1;
}


void imprimirFilhos(TipoFolha *folha)
{
    if(folha->children == NULL)
    {
        //nao tem filhos
        return;
    }

    for(int i = 0; i < folha->children->len; i++)
    {
        resetIterPosition(folha->children);
        printf(" %d ", folha->children->iterador->folha->data.valor);
        moverIterParaProximo(folha->children);
    }
    printf("||");
}



void imprimirArvore(TipoArvore *arvore)
{
    printf("raiz: %d\n", arvore->raiz->data.valor);

    imprimirFilhos(arvore->raiz);
}

