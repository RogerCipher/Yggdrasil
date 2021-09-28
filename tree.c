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
    int value_digits = 0; // Any valid value, must have at least 1 digit
    
    // enquanto nao chegarmos ao final do ficheiro
    while ((chInt = fgetc(ficheiro)) != EOF) {
        ch = (char)chInt;   // Convert char in int to char
        if ((ch >= '0') && (ch <= '9')) 
        {   // valid digits for value
            value = (10*value) + ch - '0';  // Shift old value one place ot the left (in decimal form)
            value_digits++;                 // Number of digits
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
                folhaActual->data->value = value;
                // dar reset a value e value_digits
                value = 0;  
                value_digits = 0;
            }
            if (ch == '(') 
            {    
                // adicionar um novo filho
                folhaActual = novaFolha(folhaActual);    // add_child_node returns new child node
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

    //ja passou um numero para cima, nos queremos manter o 
    //maior numero se for max ou menor se for min, aka
    //max se for par ou 0, min se for impar
    if(iterador->parent->nivelDaFolha % 2 == 0 || iterador->parent->nivelDaFolha == 0)
    {
        printf("avaluating max player\n");
        //max player
        while(iterador != NULL)
        {
            printf("\nmax\n");
            

            dataActual = minmax(iterador);
            
            printf("\nmax found: %d\n", dataActual->value);
            if(iterador->data == NULL)
            {
                iterador->data = (TipoData *)malloc(sizeof(TipoData));
                iterador->data->value = dataActual->value;
            }
            else if(iterador->data->value < dataActual->value)
            {
                iterador->data->value = dataActual->value;
            }
            printf("\ncurrent max value: %d\n", iterador->data->value);
            iterador = iterador->nextSibling;
        } 
    }
    else
    {
        printf("avaluating min player\n");
        //min player
        while(iterador != NULL)
        {
            printf("\nmin\n");


            dataActual = minmax(iterador);


            printf("\nmin found: %d\n", dataActual->value);
            if(iterador->data == NULL)
            {
                iterador->data = (TipoData *)malloc(sizeof(TipoData));
                iterador->data->value = dataActual->value;
            }
            else if(iterador->data->value > dataActual->value)
            {
                iterador->data->value = dataActual->value;
            }
            printf("\ncurrent min value: %d\n", iterador->data->value);
            iterador = iterador->nextSibling;
        } 
    }

    if(elemento->parent == NULL)
    {
        //se chegarmos a raiz basta fazermos o max do resultado final:
        
        iterador = elemento->children;
        while(iterador != NULL)
        {
            if(elemento->data == NULL)
            {
                elemento->data = (TipoData *)malloc(sizeof(TipoData));
                elemento->data->value = elemento->children->data->value;
            }
            else
            {
                if(iterador->data->value > elemento->data->value)
                {
                    elemento->data->value = iterador->data->value;
                }
            }
            iterador = iterador->nextSibling;
        }
        return elemento->data;
    }

    return dataActual;
}