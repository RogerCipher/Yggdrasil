#ifndef __TREE_H__
#define __TREE_H__

/*------------ESTRUTURA PARA DADOS-------------*/

//estrutura para a data que queremos guardar em cada folha da arvore
typedef struct TipoD
{
    int valor;
}TipoData;


/*---------------------------ESTRUTURAS PARA LINKED LIST---------------------------------------------*/


//estrutura para guardar um elemento numa linked list com informacao de um elemento da arvore
typedef struct TipoELL
{
    struct TipoELL *proximo;
    struct TipoELL *anterior;
    struct TipoF *folha;
}TipoElementoLinkedList;

//estrutura para uma linked list que guarda um elemento da arvore
typedef struct TipoLL
{
    TipoElementoLinkedList *cabeca; //primeiro elemento da linked list
    TipoElementoLinkedList *iterador; //elemento em que estamos actualmente na linked list
    int indexElementoActual; //index do elemento que estamos actualmente  na linked list
    int len; //tamanho da linked list
}TipoLinkedList;

/*---------------------------ESTRUTURAS PARA A ARVORE---------------------------------------------*/


//estrutura para cada uma das folhas da arvore
typedef struct TipoF
{
    struct TipoF *parent; //parent da folha
    TipoLinkedList *children; //lista de filhos desta folha
    int nivelDaFolha;
    TipoData data; //informacao sobre a folha actual
}TipoFolha;


typedef struct 
{
    TipoFolha *raiz;
    TipoFolha *iterador;
    //adicionar mais cenas depois (tipo quantos niveis tem)
}TipoArvore;


/*---------------------------FUNCOES PARA LINKED LIST---------------------------------------------*/

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


int apagarUltimoElemento(TipoLinkedList * list);
int freeLinkedList(TipoLinkedList *list);

//debugging stuff
void imprimirLista(TipoLinkedList *list);


/*---------------------------FUNCOES PARA ARVORE--------------------------------------------*/
#define maxTreeElements 1024


TipoFolha *criarFolha();
TipoFolha *criarFolhaComInt(int valor);

TipoArvore *criarArvore();
TipoArvore *criarArvoreComRaiz(TipoFolha *raiz);


int adicionarFilho(TipoFolha *folhaPai, TipoFolha *folhaFilho);

TipoArvore *carregarArvoreDeFicheiro(char *fileName);

int freeFolha(TipoFolha *folha);
int freeArvore(TipoArvore *arvore);

void imprimirFilhos(TipoFolha *folha);
void imprimirArvore(TipoArvore *arvore);

#endif