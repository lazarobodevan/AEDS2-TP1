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
    (*no)->FinalPalavra = 0;
    (*no)->Central = NULL;
    (*no)->Esquerda = NULL;
    (*no)->Direita = NULL;

    return 1;
}


void InserirTST(ApontadorTST *no, char *palavra){
    if(!(*no)) CriarNoTST(no, *palavra); /* if node == null */
    
    if((*palavra) > (*no)->caractere) { 
        InserirTST(&(*no)->Direita, palavra);
        return;
    }
    if((*palavra) < (*no)->caractere) {
        InserirTST(&(*no)->Esquerda, palavra);
        return;
    }

    if(*(palavra+1)){
        InserirTST(&(*no)->Central, palavra+1);
    } else {
        (*no)->FinalPalavra = 1;
    }


}

void PesquisaTST(ApontadorTST no, char *palavra) {
    if(!no) { 
        printf("Chave não encontrada!!");
        return;
    }

    if(*palavra < no->caractere) 
        PesquisaTST(no->Esquerda, palavra);
    else if(*palavra > no->caractere) 
        PesquisaTST(no->Direita, palavra);
    else {
        if(*(palavra+1) == '\0') {
            if(no->FinalPalavra){
                printf("Chave encontrada!\n");
                return;
            } else {
                printf("Chave não encontrada!\n");
                return;
            }
        }
        PesquisaTST(no->Central, palavra+1);
    } 
}

static void _EmOrdemTST(ApontadorTST no, char *buffer, int indice) {
    if(no) {
        _EmOrdemTST(no->Esquerda, buffer, indice);
        buffer[indice] = no->caractere;

        if(no->FinalPalavra) {
            buffer[indice + 1] = '\0';
            printf("%s\n", buffer);
        }

        _EmOrdemTST(no->Central, buffer, indice + 1);

        _EmOrdemTST(no->Direita, buffer, indice);
    }
}

void EmOrdemTST(ApontadorTST no) {
    char Buffer[30]; /* não é possivel q uma palavra seja maior que 30 */ 
    _EmOrdemTST(no, Buffer, 0);
}

