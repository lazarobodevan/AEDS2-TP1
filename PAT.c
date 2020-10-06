#include "PAT.h"
#include <string.h>

void InicializarPat(TipoArvore *tree){
    *tree = NULL;
}


int Bit(int numQueDifereNoInterno, char *palavra){  /// Funcao Bit
    return palavra[numQueDifereNoInterno -1];
}

int VerificarNoExterno(TipoArvore tree){
    return (tree->idEstruturalNo == Externo);
}

TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir){ /// i -> quantidade que difere enre pontos
    TipoArvore pAjudante;
    pAjudante = (TipoArvore) malloc(sizeof(PatriciaNo));

    pAjudante->idEstruturalNo = Interno;
    pAjudante->No.NoInterno.Esq = *Esq;
    pAjudante->No.NoInterno.Dir = *Dir;

    pAjudante->No.NoInterno.numBitOndeDifere = i;

    return pAjudante;

}


TipoArvore CriaNoExterno(char *palavra){
    int j;
    TipoArvore pAjudante;

    pAjudante = (TipoArvore) malloc(sizeof(PatriciaNo));

    pAjudante->idEstruturalNo = Externo;

    pAjudante->No.Chave = (char*) malloc (strlen(palavra) * sizeof(char));
    strcpy(pAjudante->No.Chave, palavra);

    /// PRECISA ARRUMAR OS BITS NO NO
    ///strcpy(pAjudante->No.Chave.codigoBinario, palavra.codigoBinario);

    for (j = 0; j < 10; j++){
        pAjudante->No.Chave = palavra;
    }
    return pAjudante;
}

TipoArvore InsereEntre(char *palavra, TipoArvore *tree, int i){

    TipoArvore pAjudante;
    if (VerificarNoExterno(*tree) || i < (*tree)->No.NoInterno.numBitOndeDifere){
        pAjudante = CriaNoExterno(palavra);

        if (Bit(i, palavra) == 1) {

            return CriaNoInterno(i, tree, &pAjudante);

        } else {

            return CriaNoInterno(i, &pAjudante, tree);
        }

    } else {

        if (Bit((*tree)->No.NoInterno.numBitOndeDifere, palavra) == 1){

            (*tree)->No.NoInterno.Dir = InsereEntre(palavra, &(*tree)->No.NoInterno.Dir, i);
        } else {

            (*tree)->No.NoInterno.Esq = InsereEntre(palavra, &(*tree)->No.NoInterno.Esq, i);
        }

        return (*tree);
    }
}

TipoArvore InserePat(char *palavra, TipoArvore *tree){

    TipoArvore pAjudante;
    int i;
    printf("bao memo\n");

    if (*tree == NULL){

        return CriaNoExterno(palavra);

    } else {

        pAjudante = *tree;

        while (!VerificarNoExterno(pAjudante)){

            if (Bit(pAjudante->No.NoInterno.numBitOndeDifere, palavra) == 1){

                pAjudante = pAjudante->No.NoInterno.Dir;

            } else {

                pAjudante = pAjudante->No.NoInterno.Esq;
            }
        }

        /// Atencao, esta acessando o vetor a partir do indice 1
        i = 1;

        while ((i <= Tamanho) && (Bit(i, palavra) == Bit(i, pAjudante->No.Chave))){

            i++;
        }

        if (i > Tamanho){

            printf("Necessario trabalhar aqui. i > tamanho\n");
            return (*tree);
        } else {

            return InsereEntre(palavra, tree, i);
        }
    }
}

//-------------------------------------------------
void leArquivo(TipoArvore *pat, NoTST **tst, FILE *arq){
    arq = fopen("testes.txt", "r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        return;
    }
    char aux[20];
    while(!feof(arq)){
        fscanf(arq, "%s ", aux);
        strcpy(&aux[strlen(aux)], "\0");
        InserePat(aux, pat);
        InsereTst(tst, aux);
    }

}