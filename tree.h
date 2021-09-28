#ifndef __TREE_H__
#define __TREE_H__

#include "common.h"

/*------------ESTRUTURA PARA DADOS-------------*/

//estrutura para a data que queremos guardar em cada folha da arvore
typedef struct TipoD
{
    int value;
}TipoData;


/*---------------------------ESTRUTURAS PARA A ARVORE---------------------------------------------*/


//estrutura para cada uma das folhas da arvore
typedef struct TipoF
{
    struct TipoF *parent; //parent da folha
    struct TipoF *children; //primeiro filho desta folha
    struct TipoF *nextSibling; //irmaos desta folha, aka: pointer para o proximo filho do parent
    
    int nivelDaFolha;
    TipoData *data; //informacao sobre a folha actual
}TipoFolha;

/*---------------------------FUNCOES PARA A ARVORE---------------------------------------------*/
int adicionarFilho(TipoFolha *parent, TipoFolha *child);
TipoFolha *novaFolha(TipoFolha *parent);
void imprimirGraphviz(TipoFolha *elem);
void freeArvore(TipoFolha *elem);
TipoFolha *carregarArvoreDeUmFicheiro(char *nomeFicheiro);
TipoData *minmax(TipoFolha *elemento);

#endif