//
// Created by lazarus on 18/10/20.
//

#ifndef TP1_INTERFACE_H
#define TP1_INTERFACE_H
#include "Pat.h"
#include "trie.h"

void interface();
void printOpcPat();
void printOpcTst();
void printOpcArvore();
void leArquivoPat(TipoArvore *pat, FILE *arq, int *comparacoes);
void leArquivoTst(NoTST **tst, FILE *arq, int *comparacoes);

#endif //TP1_INTERFACE_H
