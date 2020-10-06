#include "trie.h"

int InicializaNoTST( ApontadorTST * no){
    (*no) = NULL;
    return 1;
}

int CriarNoTST(ApontadorTST *no, char caractere){
    (*no) = malloc(sizeof(NoTST));

    if(*no == NULL){
        printf("ERRO!");
        return 0;
    }

    (*no)->caractere = caractere;
    (*no)->NumerodePalavras = 0;
    (*no)->Central = NULL;
    (*no)->Esquerda = NULL;
    (*no)->Direita = NULL;

    return 1;
}


void InserirNaArvore(ApontadorTST * no, char *palavra){
    if(!(*no)) CriarNoTST(no, *palavra); /* if node == null */
    
    if((*palavra) > (*no)->caractere) { 
        InserirNaArvore(&(*no)->Direita, palavra);
        return;
    }
    if((*palavra) < (*no)->caractere) {
        InserirNaArvore(&(*no)->Esquerda, palavra);
        return;
    }

    if(*(palavra+1)){
        InserirNaArvore(&(*no)->Central, palavra+1);
    } else {
        (*no)->FinalPalavra = 1;
    }


}
