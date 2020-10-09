#include "PAT.h"
#include <string.h>

void InicializarPat(TipoArvore *tree){
    *tree = NULL;
}

char Bit(int numBitDifere, char *palavra){  /// Funcao Bit
                                                                                /// um no interno, olhar dois atributos, se for externo, olha so um

    /// o i na funcao comeca em 1, eh corrigido a seguir
    int posicao = numBitDifere - 1;

    return palavra[posicao];
}

int VerificarNoExterno(TipoArvore tree){
    return (tree->idEstruturalNo == Externo);
}

TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir, char *palavra){ /// i -> quantidade que difere enre pontos
    TipoArvore pAjudante;
    pAjudante = (TipoArvore) malloc(sizeof(PatriciaNo));

    pAjudante->idEstruturalNo = Interno;
    pAjudante->No.NoInterno.Esq = *Esq;
    pAjudante->No.NoInterno.Dir = *Dir;

    pAjudante->No.NoInterno.numBitOndeDifere = i;
    /// Ta colocando no No interno a letra da folha a esquerda no ponto em que as duas palavras diferem
    if ((*Esq)->idEstruturalNo == Interno && (*Dir)->idEstruturalNo == Interno){

        pAjudante->No.NoInterno.letraNoPontoQueDifere = palavra[i-1];

    } else if ((*Dir)->idEstruturalNo == Interno) {
        pAjudante->No.NoInterno.letraNoPontoQueDifere = (*Esq)->No.Chave[i-1];
    } else {

        pAjudante->No.NoInterno.letraNoPontoQueDifere = (*Dir)->No.Chave[i-1];

    }






    return pAjudante;

}

TipoArvore CriaNoExterno(char *palavra){

    TipoArvore pAjudante;

    pAjudante = (TipoArvore) malloc(sizeof(PatriciaNo));

    pAjudante->idEstruturalNo = Externo;

    pAjudante->No.Chave = (char*) malloc (strlen(palavra) * sizeof(char));
    strcpy(pAjudante->No.Chave, palavra);

    return pAjudante;
}

TipoArvore InsereEntre(char *palavra, TipoArvore *tree, int i){

    TipoArvore pAjudante;
    if (VerificarNoExterno(*tree) || i < (*tree)->No.NoInterno.numBitOndeDifere){
        pAjudante = CriaNoExterno(palavra);

        /// i esta marcando o ponto onde houve a diferenca, para verificar onde cada um sera inserido, compara as letras na posicao i
        /// Leva em conta o '\0'

        if ((*tree)->idEstruturalNo == Externo){

            if (Bit(i, palavra) > (*tree)->No.Chave[i]) {

                return CriaNoInterno(i, tree, &pAjudante, palavra);

            }
        }
        if ((*tree)->idEstruturalNo == Interno){

            if (Bit(i, palavra) > (*tree)->No.NoInterno.letraNoPontoQueDifere) {

                return CriaNoInterno(i, tree, &pAjudante, palavra);

            }

        }

        /// Posiciona a nova palavra a esquerda
        return CriaNoInterno(i, &pAjudante, tree, palavra);


    } else {

        /// Nos internos, compara a letra guardada dentro do No com a letra na posicao i (onde difere), se for maior -> direita
        if (Bit((*tree)->No.NoInterno.numBitOndeDifere, palavra) > (*tree)->No.NoInterno.letraNoPontoQueDifere){

            (*tree)->No.NoInterno.Dir = InsereEntre(palavra, &(*tree)->No.NoInterno.Dir, i);
        } else {

            (*tree)->No.NoInterno.Esq = InsereEntre(palavra, &(*tree)->No.NoInterno.Esq, i);
        }

        return (*tree);
    }
}

TipoArvore InserePat(char *palavra, TipoArvore *tree){

    char letra;
    TipoArvore pAjudante;
    int i;
    printf("bao memo\n");

    if (*tree == NULL){

        return CriaNoExterno(palavra);

    } else {

        pAjudante = *tree;

        while (!VerificarNoExterno(pAjudante)){

            /// Tratando casos
            if (pAjudante->No.NoInterno.numBitOndeDifere > strlen(palavra)){

                letra = palavra[strlen(palavra)];
            } else {

                letra = Bit(pAjudante->No.NoInterno.numBitOndeDifere, palavra);
            }


                /// Pega o numero do bit onde difere no No interno e pega aquela posicao na palavra a ser inserida,
                /// depois compara com a letra guardada no No interno para decidir o caminho, maior -> direita
            if (letra > pAjudante->No.NoInterno.letraNoPontoQueDifere){

                pAjudante = pAjudante->No.NoInterno.Dir;

            } else {

                pAjudante = pAjudante->No.NoInterno.Esq;
            }
        }

        /// Atencao, esta acessando o vetor a partir do indice 1
        i = 1;

        /// Ficar atento na diferenca de tamanho das palavras na hora de comparar. Ex, sol - solar
        while (Bit(i, pAjudante->No.Chave)!= '\0' && Bit(i, palavra) != '\0' && (Bit(i, palavra) == Bit(i, pAjudante->No.Chave))){

            i++;
        }

        if (! strcmp(palavra, pAjudante->No.Chave)){

            printf("Chaves sao iguais\n");
            printf("Necessario trabalhar aqui. i > tamanho\n");
            return (*tree);
        } else {
            //printf("chegou ate\n");
            return InsereEntre(palavra, tree, i);
        }
    }
}


void Pesquisa(TipoArvore *tree, char *palavra){

    if (VerificarNoExterno(*tree)){

        if (! strcmp((*tree)->No.Chave, palavra)){

            printf("chave encontrada\n");
            return;
        } else {

            printf("deu ruim\n");
            return;
        }
    }

    if (Bit((*tree)->No.NoInterno.numBitOndeDifere, palavra) > (*tree)]->No.NoInterno.letraNoPontoQueDifere){

        Pesquisa(&(*tree)->No.NoInterno.Dir, palavra);
    } else {
        Pesquisa(&(*tree)->No.NoInterno.Esq, palavra);
    }
}










//-------------------------------------------------
/*
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
*/

