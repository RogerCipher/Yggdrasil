#ifndef __TREE_H__
#define __TREE_H__


/*-------------- estruturas -----------------*/
//estrutura para a data que queremos guardar em cada folha da arvore
typedef struct TipoD
{
    int valor;
}TipoData;

//estrutura para cada uma das folhas da arvore
typedef struct TipoF
{
    struct TipoF *parent; //parent da folha
    struct TipoLinkedList *children; //lista de filhos desta folha
    int nivelDaFolha;
    TipoData data; //informacao sobre a folha actual
}TipoFolha;


typedef struct 
{
    TipoFolha *raiz;

    //adicionar mais cenas depois (tipo quantos niveis tem)
}TipoArvore;


TipoFolha *criarFolha();
TipoFolha *criarFolhaComInt(int valor);

TipoArvore *criarArvore();
TipoArvore *criarArvoreComRaiz(TipoFolha *raiz);

#endif