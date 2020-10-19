//
// Created by lazarus on 18/10/20.
//

#ifndef TP1_INTERFACE_H
#define TP1_INTERFACE_H
#include "Pat.h"
#include "trie.h"

void interface();
void printOpc();
void lerOpc(int *opc);

void leArquivo(TipoArvore *pat, NoTST **tst, FILE *arq);
#endif //TP1_INTERFACE_H
