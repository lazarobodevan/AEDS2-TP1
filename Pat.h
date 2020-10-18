#ifndef TP1_PAT_H
#define TP1_PAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "TRIE.h"


typedef enum {
    Interno, Externo
} TipoNo;

typedef struct PatriciaNo* TipoArvore;
typedef struct PatriciaNo {

    TipoNo idEstruturalNo;

    union {
        struct {
            char letraNoPontoQueDifere;
            int indiceOndeDifere; /// Ha um nivel de abstracao aqui, no qual o indice da primeira letra de uma palavra eh 1
            TipoArvore Esq, Dir;  /// mas como a caontagem em strings comeca por 0, eh feita uma correcao dentro da funcao Bit
                                  /// logo ao olhar para o valor guardado por esta variavel, atentar que a contagem comeca em 1
        } NoInterno ;

        char* Chave;

    } No;

} PatriciaNo;

void InicializarPat(TipoArvore *tree);
char Bit(int numIndiceDifere, char *palavra);
int VerificarNoExterno(TipoArvore tree);
TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir, char letra);
TipoArvore CriaNoExterno(char *palavra);
TipoArvore InsereEntre(char *palavra, TipoArvore *tree, int i, char letraNoInterno);
TipoArvore InserePat(char *palavra, TipoArvore *tree);
void Pesquisa(TipoArvore *tree, char *palavra);
void PrintPatTree(TipoArvore *tree);
void ContarPalavras(TipoArvore *tree, int *contador);

//----------------------
//void leArquivo(TipoArvore *pat, NoTST **tst, FILE *arq);

#endif //TP1_PAT_H
