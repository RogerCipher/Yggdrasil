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


#include "minMaxAndAlphaBeta.h"
#include "common.h"

/*---------------------------FUNCOES PARA LINKED LIST---------------------------------------------*/
int adicionarFilho(TipoFolha *parent, TipoFolha *child) 
{
    child->parent = parent;
    if (parent == NULL) 
    {
        //criamos a raiz
        return 0;
    }
    if (parent->children == NULL) 
    {
        //primeiro filho
        parent->children = child;
    }
    else 
    {
        //nao é o primeiro filho, vamos iterar ate ao ultimo filho
        TipoFolha *iterador = parent->children;
        while (iterador->nextSibling != NULL) 
        {
            //iterar filho a filho ate ao ultimo
            iterador = iterador->nextSibling;
        }

        //adicionar este filho como irmao do ultimo irmao actual
        iterador->nextSibling = child;
    }
    return 1;
}

TipoFolha *novaFolha(TipoFolha *parent) 
{
    //criar uma nova folha
    TipoFolha *novoElem = (TipoFolha *)malloc(sizeof(TipoFolha));
    if (novoElem == NULL) {
        printf("Nao foi possivel alocar memoria para uma das folhas da arvore\n");
        return NULL;
    }

    //popular a folha com NULL
    novoElem->nextSibling = NULL;
    novoElem->children = NULL;
    novoElem->data = NULL;
    novoElem->pruned = 1;

    //inserir nivel da folha
    if(parent == NULL)
    {
        //estamos na raiz, nivel 0
        novoElem->nivelDaFolha = 0;
    }
    else
    {
        novoElem->nivelDaFolha = parent->nivelDaFolha +1;
    }
    
    //adicionar esta folha como um filho do seu pai
    adicionarFilho(parent, novoElem);    // TODO: Check this return value
    return novoElem;
}

void imprimirGraphviz(TipoFolha *elem)
{
    if (elem->parent == NULL) 
    {
        //estamos na raiz
        printf("Copy the following code to https://dreampuf.github.io/GraphvizOnline\n");
        printf("graph {\n");
    }
    if (elem->data == NULL) 
    {
        //elemento nao tem valor
        printf("\tn%p [label = \"N/A\"]\n", elem);
    } 
    else 
    {
        //elemento tem valor
        printf("\tn%p [label = \"%d\"]\n", elem, elem->data->value);
    }
        
    if (elem->parent != NULL) 
    {
        //criar ligacao do pai ao filho
        printf("\tn%p -- n%p\n", elem->parent, elem);
    }
    if (elem->children != NULL) 
    {
        //imprimir recursivamente para cada filho
        imprimirGraphviz(elem->children);    // imprimir primeiro filho

        //iterar e ir imprimindo cada filho subsequente
        TipoFolha *iterador = elem->children;
        while (iterador->nextSibling != NULL) {
            iterador = iterador->nextSibling;
            imprimirGraphviz(iterador);
        }
    }
    if (elem->parent == NULL) {
        //fim
        printf("}\n");
    }
}

void imprimirGraphviz_WithPrunes(TipoFolha *elem)
{
    if (elem->parent == NULL) 
    {
        //estamos na raiz
        printf("Copy the following code to https://dreampuf.github.io/GraphvizOnline\n");
        printf("graph {\n");
    }
    if (elem->data == NULL || elem->pruned) 
    {
        //elemento nao tem valor
        printf("\tn%p [label = \"N/A\"]\n", elem);
    } 
    else 
    {
        //elemento é uma das folhas sem filhos vamos apenas imprimir o seu valor real
        if(elem->children == NULL)
        {
            printf("\tn%p [label = \"%d\"]\n", elem, elem->data->value);
        }
        else
        {
            //elemento tem valor
            if(elem->data->alpha == -INFINITY && elem->data->beta == INFINITY)
            {
                printf("\tn%p [label = \"alpha: -∞ beta: ∞\"]\n", elem);
            }
            else if(elem->data->alpha == -INFINITY)
            {
                printf("\tn%p [label = \"alpha: -∞ beta: %d\"]\n", elem, elem->data->beta);
            }
            else if(elem->data->beta == INFINITY)
            {
                printf("\tn%p [label = \"alpha: %d beta: ∞\"]\n", elem, elem->data->alpha);
            }
            else
            {
                printf("\tn%p [label = \"alpha: %d beta: %d\"]\n", elem, elem->data->alpha, elem->data->beta);
            }
        }

    }
    if (elem->parent != NULL) 
    {
        //criar ligacao do pai ao filho
        printf("\tn%p -- n%p\n", elem->parent, elem);
    }
    if (elem->children != NULL) 
    {
        //imprimir recursivamente para cada filho
        imprimirGraphviz_WithPrunes(elem->children);    // imprimir primeiro filho

        //iterar e ir imprimindo cada filho subsequente
        TipoFolha *iterador = elem->children;
        while (iterador->nextSibling != NULL) {
            iterador = iterador->nextSibling;
            imprimirGraphviz_WithPrunes(iterador);
        }
    }
    if (elem->parent == NULL) {
        //fim
        printf("\tn%p [label = \"valor: %d\"]\n", elem, elem->data->value);
        printf("}\n");
    }
}

// Recursive post-order traversal of tree
void freeArvore(TipoFolha *elem) 
{
    if (elem == NULL) {
        return;
    }
    TipoFolha *iterador = elem->children;
    while ((iterador != NULL) && (iterador->nextSibling != NULL)) {
        freeArvore(iterador);
        iterador = iterador->nextSibling;
    }
    elem->children = NULL;
    if (elem->data != NULL) {
        free(elem->data);
    }
    free(elem);
}

//Carregar um ficheiro que descreve uma arvore e dar return da raiz
TipoFolha *carregarArvoreDeUmFicheiro(char *nomeFicheiro) 
{
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    if (ficheiro == NULL) 
    {
        //algo correu mal
        printf("Nao foi possivel abrir o ficheiro \"%s\"\n", nomeFicheiro);
        return NULL;
    }

    TipoFolha *raiz = novaFolha(NULL);
    TipoFolha *folhaActual = raiz;

    int chInt;
    char ch;
    int value = 0; 
    int value_digits = 0; // qualquer valor valido precisa de pelo menos 1 digito
    int isNegative = 1; //diz-nos se o valor é positivo ou negativo (tem o valor de -1 ou 1)
    
    // enquanto nao chegarmos ao final do ficheiro
    while ((chInt = fgetc(ficheiro)) != EOF) {
        ch = (char)chInt;   // Convert char in int to char

        if ((ch >= '0') && (ch <= '9')) 
        {   // valid digits for value
            value = (10*value) + ch - '0';  // Shift old value one place ot the left (in decimal form)
            value_digits++;                 // Number of digits
        }
        else if((value_digits == 0) && (ch == '-'))
        {
            //trata-se de um numero negativo
            isNegative = -1;
        }
        else if ((ch == '(') || (ch == ')')) 
        { 
            // Andar pela arvore
            if (value_digits > 0) 
            {
                if (folhaActual->data == NULL) 
                {
                    folhaActual->data = (TipoData *) malloc(sizeof(TipoData));
                }

                folhaActual->data->value = value * isNegative;


                // dar reset a value, value_digits e isnegative
                isNegative = 1;
                value = 0;  
                value_digits = 0;
            }
            if (ch == '(') 
            {    
                // adicionar um novo filho
                folhaActual = novaFolha(folhaActual);
            } 
            else 
            {            
                // ir para o pai
                if (folhaActual->parent == NULL) 
                {
                    //algo correu mal
                    printf("O ficheiro nao descreve uma arvore \"%s\"\n", nomeFicheiro);

                    //remover o que carregamos 
                    freeArvore(raiz);    
                    return NULL;
                }

                folhaActual = folhaActual->parent;
            }
        } 
        else 
        {
            printf("impossivel carregar o caracter: '%02X'\n", ch);

            //remover o que carregamos 
            freeArvore(raiz);
            return NULL;        
        }
    }
    fclose(ficheiro);
    if (raiz != folhaActual) 
    {
        //se nao acabarmos o ficheiro na raiz algo correu mal
        printf("sintax do ficheiro incorrecto, nao acabamos na raiz\n");

        //remover o que carregamos
        freeArvore(raiz);
        return NULL;
    }
    return raiz;
}

TipoData *minmax(TipoFolha *elemento)
{

    if(elemento->children == NULL)
    {
        //se nao ha mais filhos vamos dar return do valor da folha actual
        return elemento->data;
    }

    TipoFolha *iterador = elemento->children;
    TipoData *dataActual;

    //queremos passar para o nos o valor do filho
    //maior numero se for max ou menor se for min, aka
    //max se for par ou 0, min se for impar
    if(elemento->nivelDaFolha % 2 == 0 || elemento->nivelDaFolha == 0)
    {
        //max player
        while(iterador != NULL)
        {
            dataActual = minmax(iterador);
            
            if(elemento->data == NULL)
            {
                //se ele ainda nao tiver nada vamos simplesmente passar o primeiro
                elemento->data = (TipoData *)malloc(sizeof(TipoData));
                elemento->data->value = dataActual->value;
            }
            else if(elemento->data->value < dataActual->value)
            {
                //se ja tem alguma coisa vemos se este numero e maior, se for damos rewrite
                elemento->data->value = dataActual->value;
            }

            iterador = iterador->nextSibling;
        }
    }
    else
    {
        //min player
        while(iterador != NULL)
        {

            dataActual = minmax(iterador);

            if(elemento->data == NULL)
            {
                //se ele ainda nao tiver nada vamos simplesmente passar o primeiro
                elemento->data = (TipoData *)malloc(sizeof(TipoData));
                elemento->data->value = dataActual->value;
            }
            else if(elemento->data->value > dataActual->value)
            {
                //se ja tem alguma coisa vemos se este numero e maior, se for damos rewrite
                elemento->data->value = dataActual->value;
            }

            iterador = iterador->nextSibling;
        }
    }

    return elemento->data;
}

TipoData *alphaBeta(TipoFolha *elemento)
{
    if(elemento->parent == NULL && elemento->data == NULL)
    {
        //estamos na raiz, vamos inicializar os valores do alpha beta
        elemento->data = (TipoData *)malloc(sizeof(TipoData));
        elemento->data->alpha = -INFINITY;
        elemento->data->beta = INFINITY;
        elemento->pruned = 0;
    }
    else if(elemento->data == NULL)
    {
        //se estamos numa folha que ainda nao passamos vamos inicializar a data
        //com o alpha e o beta do seu pai
        elemento->data = (TipoData *)malloc(sizeof(TipoData));
        elemento->data->alpha = elemento->parent->data->alpha;
        elemento->data->beta = elemento->parent->data->beta;
        elemento->pruned = 0;
    }
    else if(elemento->children == NULL)
    {
        //se nao tem filhos vamos so dar return desta data
        elemento->data->alpha = elemento->data->value;
        elemento->data->beta = elemento->data->value;
        elemento->pruned = 0;
        return elemento->data;
    }

    TipoFolha *iterador = elemento->children;
    TipoData *dataActual;

    //queremos ver o alpha para o max player (nivel da folha par ou 0)
    //queremos ver o beta para o min player (nivel da folha impar)
    if(elemento->nivelDaFolha % 2 == 0 || elemento->nivelDaFolha == 0)
    {
        //max player (olhamos para o alpha)
        while(iterador != NULL)
        {
            dataActual = alphaBeta(iterador);
            
            if(elemento->data->alpha < dataActual->beta)
            {
                //se ja tem alguma coisa vemos se este numero e maior, se for damos rewrite
                elemento->data->alpha = dataActual->beta;
                elemento->data->value = dataActual->beta;
                
            }
            if(elemento->data->alpha >= elemento->data->beta)
            {
                //se num elemento tivermos o alpha >= beta damos prune
                break;
            }
            else
            {
                elemento->pruned = 0;
            }

            iterador = iterador->nextSibling;
        }
    }
    else
    {
        //min player (olhamos para o beta)

        while(iterador != NULL)
        {
            dataActual = alphaBeta(iterador);
            
            if(elemento->data->beta > dataActual->alpha)
            {
                //se ja tem alguma coisa vemos se este numero e menor, se for damos rewrite
                elemento->data->beta = dataActual->alpha;
                elemento->data->value = dataActual->alpha;
            }
            if(elemento->data->alpha >= elemento->data->beta)
            {
                //se num elemento tivermos o alpha >= beta damos prune
                break;
            }
            else
            {
                elemento->pruned = 0;
            }

            iterador = iterador->nextSibling;
        }
    }
    


    return elemento->data;
}
