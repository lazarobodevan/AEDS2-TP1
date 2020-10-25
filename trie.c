
/*  
 * Cabecalho
 * 
*/

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


void InserirTST(ApontadorTST *no, char *palavra, int *comparacoes){
    (*comparacoes)++;
    if(!(*no)) CriarNoTST(no, *palavra); /* if node == null */
    else {
        (*comparacoes)++;
        if((*palavra) > (*no)->caractere) { 
            InserirTST(&(*no)->Direita, palavra, comparacoes);
            return;
        }
        
        (*comparacoes)++;
        if((*palavra) < (*no)->caractere) {
            InserirTST(&(*no)->Esquerda, palavra, comparacoes);
            return;
        }
    }

    (*comparacoes)++;
    if(*(palavra+1)){  
        InserirTST(&(*no)->Central, palavra+1, comparacoes);
    } else {
        (*no)->FinalPalavra = 1;
    }


}

void PesquisaTST(ApontadorTST no, char *palavra, int *comparacoes) {
    /* 
    * Funcao responsavel pela pesquisa na TST
    * 
    * Como funciona: 
    * Percorre a arvore comparando os caracteres da chave e os dos nos
    * se o caractere da chave for menor vai pra esq, maior direita e igual pro centro
    * a pesquisa termina com um no nulo ou quando o proximo caractere da chave é um \0
    */

    (*comparacoes)++;
    if(!no) { 
        printf("Chave não encontrada!!");
        return;
    }

    (*comparacoes)++;
    if(*palavra < no->caractere) 
        PesquisaTST(no->Esquerda, palavra, comparacoes);
    else if(*palavra > no->caractere)
        PesquisaTST(no->Direita, palavra, comparacoes);
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
        PesquisaTST(no->Central, palavra+1, comparacoes);
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
    /*
    * Função responsável por printar a TST em ordem alfabetica.
    * 
    * Como funciona:
    * Ela usa um buffer definido a prior que armazena cada letra 
    * de um nó de acordo com o caminho que a função segue (esq, direita, centro),
    * e indo sempre da esquerda pra direita, quando chega em um nó de fim de palavra
    * esse buffer é printando e o "percorrimento" da árvore segue normalmente
    * 
    */ 
    
    char Buffer[30]; 
    _EmOrdemTST(no, Buffer, 0);
}

int MemoriaUsada(ApontadorTST no) {
    if(no) {
        int esq = MemoriaUsada(no->Esquerda);
        int dir = MemoriaUsada(no->Direita);
        int centro = MemoriaUsada(no->Central);
        return (int)(sizeof(*no) + esq + dir + centro);
    } else {
        return 0;
    }
}



int  ContarPalavrasTST(ApontadorTST no) {
    if(no) {
        int noAtual = no->FinalPalavra;
        int esq = ContarPalavrasTST(no->Esquerda);
        int dir = ContarPalavrasTST(no->Direita);
        int centro = ContarPalavrasTST(no->Central);
        return esq + dir + centro + noAtual;
    } else {
        return 0;
    }
}