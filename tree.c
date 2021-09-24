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
    int tamanho = 1;
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

int apagarUltimoElemento(TipoLinkedList * list)
{
    if(list->cabeca == NULL)
    {
        printf("tentativa de apagar o ultimo elemento de uma lista sem elementos\n");
        return 0;
    }


    resetIterPosition(list);
    //ir ate ao ultimo elemento
    while(temProximo(list->iterador))
    {
        moverIterParaProximo(list);
    }

    //dar free da folha
    freeFolha(list->iterador->folha);

    //apagar as outras conexoes
    if(list->iterador->anterior != NULL)
    {
        list->iterador->anterior->proximo = NULL;
    }
    list->iterador->anterior = NULL;

    //dar free do elemento, seguido de dar reset do iterador e refresh do tamanho da linkedlist
    free(list->iterador);
    resetIterPosition(list);
    tamanhoLinkedList(list);

    return 1;
}

int freeLinkedList(TipoLinkedList *list)
{
    int quantidadeElementos = list->len;

    list->cabeca->folha->parent->children = NULL;

    for(int i = 0; i < quantidadeElementos; i++)
    {
        apagarUltimoElemento(list);
    }

    list->indexElementoActual = -1;
    list->iterador = NULL;
    list->cabeca = NULL;
    list->len = 0;

    free(list);
    return 1;
}


void imprimirLista(TipoLinkedList *list)
{
    resetIterPosition(list);
    if(list->cabeca == NULL)
    {
        //esta lista esta vazia
    }
    for(int i = 0; i < list->len; i++)
    {
        if(list->iterador->folha != NULL)
        {
            printf("%d\n", list->iterador->folha->data.valor);
            moverIterParaProximo(list);
        }
        else
        {
            //esta folha nao tem nada
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
    arvore->iterador = NULL;
    return arvore;
}

TipoArvore *criarArvoreComRaiz(TipoFolha *raiz)
{
    TipoArvore *arvore = (TipoArvore *)malloc(sizeof(TipoArvore));
    arvore->raiz = raiz;
    arvore->raiz->nivelDaFolha = 0;
    arvore->iterador = arvore->raiz;
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


TipoArvore *carregarArvoreDeFicheiro(char *fileName)
{
    char buffer[maxTreeElements*3];

    FILE *fp;

    fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        error("");
    }

    fscanf(fp, "%s", buffer);


    //sabemos que a primeira vai sempre ser a raiz
    TipoArvore *arvore = criarArvoreComRaiz(criarFolhaComInt(atoi(buffer)));

    printf("raiz criada com o valor: %d\n", arvore->raiz->data.valor);

    //TODO: METER O ITERADOR COMO "NODE ACTUAL" PARA O RESTO DESTA FUNCAO:

    for(int i = 1; i < strlen(buffer); i++)
    {
        //printf("%c", buffer[i]);
        if(buffer[i] == '(')
        {
            adicionarFilho(arvore->iterador, criarFolhaComInt(atoi(buffer+i+1)));
            i++;

            //ir para o ultimo filho da folha actual
            while(temProximo(arvore->iterador->children->iterador))
            {
                moverIterParaProximo(arvore->iterador->children);
            }
            //meter o iterador da arvore igual a este filho
            arvore->iterador = arvore->iterador->children->iterador->folha;

        }
        if(buffer[i] == ')')
        {
            //ir para o node "pai"
            arvore->iterador = arvore->iterador->parent;
        }
    }



    printf("\ncarregado:\n");
    fclose(fp);

    return arvore;
}


int freeFolha(TipoFolha *folha)
{
    if(folha->children != NULL)
    {
        //vamos ter que apagar os filhos primeiro
        freeLinkedList(folha->children);
    }

    free(folha);

    return 1;
}

int freeArvore(TipoArvore *arvore)
{
    if(arvore->raiz == NULL)
    {
        free(arvore);
        return 1;
    }

    freeFolha(arvore->raiz);
    arvore->raiz = NULL;
    free(arvore);

    return 1;

}



void imprimirFilhos(TipoFolha *folha)
{
    printf("pai: %d\n", folha->data.valor);

    if(folha->children == NULL)
    {
        printf(" nao tem filhos\n");
        return;
    }
    tamanhoLinkedList(folha->children);
    resetIterPosition(folha->children);
    for(int i = 0; i < folha->children->len; i++)
    {
        printf(" filho nr %d : %d \n", i, folha->children->iterador->folha->data.valor);
        if(!moverIterParaProximo(folha->children))
        {
            break;
        }
    }
    tamanhoLinkedList(folha->children);
    resetIterPosition(folha->children);
    
    for(int i = 0; i < folha->children->len; i++)
    {
        imprimirFilhos(folha->children->iterador->folha);
        if(!moverIterParaProximo(folha->children))
        {
            break;
        }
    }

    return;
}



void imprimirArvore(TipoArvore *arvore)
{
    if(arvore->raiz == NULL)
    {
        return;
    }

    imprimirFilhos(arvore->raiz);
    
}



//TODO: THIS IS BUGGED, EITHER FIX IT OR MOVE ON
// Print the tree in graphviz format
void imprimirArvore_graphviz(TipoFolha *folha) {
    if (folha->parent == NULL) {
        printf("Copy the following code to https://dreampuf.github.io/GraphvizOnline\n");
        printf("graph {\n");
    }
    if (folha == NULL) {
        printf("\tn%p [label = \"\"]\n", folha);
    } else {
        printf("\tn%p [label = \"%d\"]\n", folha, folha->data.valor);
    }
    if (folha->parent != NULL) {
        printf("\tn%p -- n%p\n", folha->parent, folha);
    }

    if(folha->children != NULL)
    {
        resetIterPosition(folha->children);
        int tamanho = tamanhoLinkedList(folha->children);
        for (int i = 0; i < tamanho; i++) {
            if (folha->children->iterador != NULL) {
                imprimirArvore_graphviz(folha->children->iterador->folha);
            }
            moverIterParaProximo(folha->children);
        }
    }

    if (folha->parent == NULL) {
        printf("}\n");
    }
}
