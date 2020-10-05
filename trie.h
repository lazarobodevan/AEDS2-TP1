#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoTST {
    char caractere;
    int NumerodePalavras;
    struct NoTST * Central;
    struct NoTST * Esquerda;
    struct NoTST * Direita;
    
}NoTST;


int InicializaNoTST( NoTST ** no);
int CriarNoTST(NoTST **no, char caractere);
int InserirNaArvore(NoTST ** no, char palavra);
