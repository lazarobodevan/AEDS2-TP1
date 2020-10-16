#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NoTST* ApontadorTST;
typedef struct NoTST* ArvoreTST;

typedef struct NoTST {
    int FinalPalavra;
    char caractere;
    int NumerodePalavras;
    ApontadorTST Central;
    ApontadorTST Esquerda;
    ApontadorTST Direita;
}NoTST;


int InicializaNoTST( ApontadorTST* no);
int CriarNoTST(ApontadorTST* no, char caractere);
void InserirTST(ApontadorTST* no, char *palavra);
void PesquisaTST(ApontadorTST no, char *palavra);