#include "trie.h"

int InicializaNoTST( NoTST ** no){
    (*no) = NULL;
    return 1;
}

int CriarNoTST(NoTST **no, char caractere){
    (*no) = malloc(sizeof(NoTST));

    if(*no == NULL){
        printf("ERRO!");
        return 0;
    }

    (**no).caractere = caractere;
    (**no).NumerodePalavras = 0;
    (**no).Central = NULL;
    (**no).Esquerda = NULL;
    (**no).Direita = NULL;

    return 1;
}


int InserirNaArvore(NoTST ** no, char palavra){
    
}
