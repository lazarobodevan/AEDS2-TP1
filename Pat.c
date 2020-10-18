#include "Pat.h"
#include <string.h>

void InicializarPat(TipoArvore *tree){
    *tree = NULL;
}

char Bit(int numIndiceDifere, char *palavra){  /// Funcao Bit
                                                                                /// um no interno, olhar dois atributos, se for externo, olha so um

    /// o i na funcao comeca em 1, eh corrigido a seguir
    int posicao = numIndiceDifere - 1;

    return palavra[posicao];
}

int VerificarNoExterno(TipoArvore tree){
    return (tree->idEstruturalNo == Externo);
}

TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir, char letra){ /// i -> quantidade que difere enre pontos
    TipoArvore pAjudante;
    pAjudante = (TipoArvore) malloc(sizeof(PatriciaNo));

    pAjudante->idEstruturalNo = Interno;
    pAjudante->No.NoInterno.Esq = *Esq;
    pAjudante->No.NoInterno.Dir = *Dir;

    pAjudante->No.NoInterno.indiceOndeDifere = i;
    pAjudante->No.NoInterno.letraNoPontoQueDifere = letra;

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

TipoArvore InsereEntre(char *palavra, TipoArvore *tree, int i, char letraNoInterno){

    TipoArvore pAjudante;

    /// Chegou num No externo
    if (VerificarNoExterno(*tree)){

        pAjudante = CriaNoExterno(palavra);
        /// Verifica qual das letras eh maior na posicao i, vai para a direita se for maior ou igual
        if (Bit(i, palavra) >= Bit(i, (*tree)->No.Chave)) {

            return (CriaNoInterno(i, tree, &pAjudante, letraNoInterno));

        } else {

            return (CriaNoInterno(i, &pAjudante, tree, letraNoInterno));
        }
    /// Verifica se o i eh menor que o indice guardado no No interno
    } else if (i < (*tree)->No.NoInterno.indiceOndeDifere) {

        pAjudante = CriaNoExterno(palavra);
        /// Compara a letra guardada no No interno com a letra da palavra -mesma posicao-, se for menor vai para a esquerda
         if (Bit((*tree)->No.NoInterno.indiceOndeDifere, palavra) < (*tree)->No.NoInterno.letraNoPontoQueDifere ) {
            /// Verifica se a palavra que ira ser inserida na esquerda nao viola a regra dos iguais deve ir a direita
            if (Bit(i, palavra) != letraNoInterno) {

                return (CriaNoInterno(i, &pAjudante, tree, letraNoInterno));
            }
         }

        return (CriaNoInterno(i, tree, &pAjudante, letraNoInterno));


    } else {

        /// Nos internos, compara a letra guardada dentro do No com a letra na posicao i (onde difere), se for maior -> direita
        if (Bit((*tree)->No.NoInterno.indiceOndeDifere, palavra) >= (*tree)->No.NoInterno.letraNoPontoQueDifere){

            (*tree)->No.NoInterno.Dir = InsereEntre(palavra, &(*tree)->No.NoInterno.Dir, i, letraNoInterno);
        } else {

            (*tree)->No.NoInterno.Esq = InsereEntre(palavra, &(*tree)->No.NoInterno.Esq, i, letraNoInterno);
        }
    }
    return (*tree);
}

TipoArvore InserePat(char *palavra, TipoArvore *tree){

    char letra;
    char letraDiferente;
    TipoArvore pAjudante;
    int i;
    printf("bao memo\n");

    if (*tree == NULL){

        return CriaNoExterno(palavra);
    } else {

        pAjudante = *tree;

        while (!VerificarNoExterno(pAjudante)){

            /// Tratando casos
            /// Caso o numero no NO interno seja maior que o tamanho da palavra
            if (pAjudante->No.NoInterno.indiceOndeDifere > strlen(palavra)){

                letra = palavra[strlen(palavra)];
            } else {

                letra = Bit(pAjudante->No.NoInterno.indiceOndeDifere, palavra);
            }

                /// Pega o numero do bit onde difere no No interno e pega aquela posicao na palavra a ser inserida,
                /// depois compara com a letra guardada no No interno para decidir o caminho, maior/igual -> direita
            if (letra >= pAjudante->No.NoInterno.letraNoPontoQueDifere){

                pAjudante = pAjudante->No.NoInterno.Dir;
            } else {

                pAjudante = pAjudante->No.NoInterno.Esq;
            }
        }

        if (strcmp(palavra, pAjudante->No.Chave) == 0){

                printf("Chaves sao iguais\n");
                return (*tree);
        }

        /// Atencao, esta acessando o vetor a partir do indice 1
        i = 1;

        while ( Bit(i, palavra) == Bit(i, pAjudante->No.Chave) ){

            i++;
        }

        /// Pega a maior letra no ponto que difere entre as duas palavras
        if (Bit(i, palavra) > Bit(i, pAjudante->No.Chave)){

            letraDiferente = palavra[i - 1]; /// Poderia substituir pela funcao Bit, caso nao impacte no desempenho, realizar mudanca
        } else {

            letraDiferente = pAjudante->No.Chave[i - 1];
        }

        //printf("chegou ate\n");
        return InsereEntre(palavra, tree, i, letraDiferente);
    }
}


void Pesquisa(TipoArvore *tree, char *palavra, int *comparacoes){

    if ((*comparacoes)++ && VerificarNoExterno(*tree)){

        if ((*comparacoes)++ && (!strcmp((*tree)->No.Chave, palavra))){

            printf("chave encontrada\n");
            return;
        } else {

            printf("deu ruim\n");
            return;
        }
    }
    if ((*comparacoes)++ && Bit((*tree)->No.NoInterno.indiceOndeDifere, palavra) >= (*tree)->No.NoInterno.letraNoPontoQueDifere){

        Pesquisa(&(*tree)->No.NoInterno.Dir, palavra, comparacoes);
    } else {

        Pesquisa(&(*tree)->No.NoInterno.Esq, palavra, comparacoes);
    }
}

void PrintPatTree(TipoArvore *tree){

    if (*tree != NULL){

        if ((*tree)->idEstruturalNo == Externo){

            printf("%s\n", (*tree)->No.Chave);
        } else {

            PrintPatTree(&(*tree)->No.NoInterno.Esq);
            PrintPatTree(&(*tree)->No.NoInterno.Dir);
        }
    }
}

void ContarPalavras(TipoArvore *tree, int *contador){

    if (*tree != NULL){

        if ((*tree)->idEstruturalNo == Externo){

            (*contador)++;
        } else {

            ContarPalavras(&(*tree)->No.NoInterno.Esq, contador);
            ContarPalavras(&(*tree)->No.NoInterno.Dir, contador);
        }
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
