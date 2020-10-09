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
            int numBitOndeDifere;
            TipoArvore Esq, Dir;

        } NoInterno ;

        char* Chave;

    } No;

} PatriciaNo;

void InicializarPat(TipoArvore *tree);
char Bit(int numQueDifereNoInterno, char *palavra);
int VerificarNoExterno(TipoArvore tree);
TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir, char *palavra);
TipoArvore CriaNoExterno(char *palavra);
TipoArvore InsereEntre(char *palavra, TipoArvore *tree, int i);
TipoArvore InserePat(char *palavra, TipoArvore *tree);
void Pesquisa(TipoArvore *tree, char *palavra);

//----------------------
//void leArquivo(TipoArvore *pat, NoTST **tst, FILE *arq);

#endif //TP1_PAT_H
