#ifndef TP1_PAT_H
#define TP1_PAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TRIE.h"

#define Tamanho 10

typedef unsigned char TipoChave; /* a definir, dependendo da aplicacao */
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;

typedef enum {
    Interno, Externo
} TipoNo;

typedef struct PatriciaNo* TipoArvore;
typedef struct PatriciaNo {

    TipoNo idEstruturalNo;

    union {
        struct {

            char numBitOndeDifere;
            TipoArvore Esq, Dir;

        } NoInterno ;

        char* Chave;

    } No;

} PatriciaNo;

void InicializarPat(TipoArvore *tree);
int Bit(int numQueDifereNoInterno, char *palavra);
int VerificarNoExterno(TipoArvore tree);
TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir);
TipoArvore CriaNoExterno(char *palavra);
TipoArvore InsereEntre(char *palavra, TipoArvore *tree, int i);
TipoArvore InserePat(char *palavra, TipoArvore *tree);

//----------------------
void leArquivo(TipoArvore *pat, NoTST **tst, FILE *arq);

#endif //TP1_PAT_H