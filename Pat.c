
//
// Grupo: C-TAD-oido
//

#include "Pat.h"
#include <string.h>

void InicializarPat(TipoArvore *tree){
    *tree = NULL;
}

char Bit(int numIndiceDifere, char *palavra){                                                                      
    /// o i na funcao de insercao comeca em 1, eh corrigido a seguir
    int posicao = numIndiceDifere - 1;

    return palavra[posicao];
}

int VerificarNoExterno(TipoArvore tree){
    return (tree->idEstruturalNo == Externo);
}

TipoArvore CriaNoInterno(int i, TipoArvore *Esq, TipoArvore *Dir, char letra){ 
    /// Variavel i -> indice onde as palavras se diferem
    /// Variavel letra -> letra escolhida para ser armazenada no NO interno
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
    pAjudante->No.Chave = (char*) malloc (strlen(palavra) * sizeof(char));
    
    pAjudante->idEstruturalNo = Externo;
    strcpy(pAjudante->No.Chave, palavra);

    return pAjudante;
}

TipoArvore InsereEntre(char *palavra, TipoArvore *tree, int i, char letraNoInterno, int *comparacoes){
    TipoArvore pAjudante;

    /// Verifica se o NO da chamada atual eh um NO externo
    if ((*comparacoes)++ && VerificarNoExterno(*tree)){

        pAjudante = CriaNoExterno(palavra);
        /// Verifica qual das letras eh maior na posicao i, vai para a direita se for maior ou igual
        if ((*comparacoes)++ && Bit(i, palavra) >= Bit(i, (*tree)->No.Chave)) {

            return (CriaNoInterno(i, tree, &pAjudante, letraNoInterno));
        } else {

            return (CriaNoInterno(i, &pAjudante, tree, letraNoInterno));
        }
    /// Verifica se o i eh menor que o indice guardado no No interno
    } else if ((*comparacoes)++ && i < (*tree)->No.NoInterno.indiceOndeDifere) {

        pAjudante = CriaNoExterno(palavra);
        /// Compara a letra na posicao que diferiu com a letra escolhida para o No interno
         if ((*comparacoes)++ && Bit(i, palavra) >= letraNoInterno) {
    
            return (CriaNoInterno(i, tree, &pAjudante, letraNoInterno));
         } else {
         
            return (CriaNoInterno(i, &pAjudante, tree, letraNoInterno));
         }

    } else {

        /// Nos internos, compara a letra guardada dentro do No com a letra na posicao i (onde difere), se for maior -> direita
        if ((*comparacoes)++ && Bit((*tree)->No.NoInterno.indiceOndeDifere, palavra) >= (*tree)->No.NoInterno.letraNoPontoQueDifere){

            (*tree)->No.NoInterno.Dir = InsereEntre(palavra, &(*tree)->No.NoInterno.Dir, i, letraNoInterno, comparacoes);
        } else {

            (*tree)->No.NoInterno.Esq = InsereEntre(palavra, &(*tree)->No.NoInterno.Esq, i, letraNoInterno, comparacoes);
        }
    }
    return (*tree);
}

TipoArvore InserePat(char *palavra, TipoArvore *tree, int *comparacoes){
    char letra;
    char letraDiferente;
    TipoArvore pAjudante;
    int i;

    (*comparacoes)++;
    if (*tree == NULL){

        return CriaNoExterno(palavra);
    } else {

        pAjudante = *tree;
        /// Verifica se o No da execucao do momento eh um No interno, caso nao seja -> nao entra no while
        while ((*comparacoes)++ && !VerificarNoExterno(pAjudante)){
           
            /// Caso o numero no NO interno seja maior que o tamanho da palavra, verificacao para evitar o acesso em posicoes invalidas
            if ((*comparacoes)++ && pAjudante->No.NoInterno.indiceOndeDifere > strlen(palavra)){
                /// Caso afirmativo, o caractere "\0" eh pego para as comparacoes
                letra = palavra[strlen(palavra)];
            } else {
                /// Caso contrario, pega a letra na posicao indicada pelo NO interno
                letra = Bit(pAjudante->No.NoInterno.indiceOndeDifere, palavra);
            }
                /// Pega o numero do indice onde difere no No interno e pega aquela posicao na palavra a ser inserida,
                /// depois compara com a letra guardada no No interno para decidir o caminho, maior/igual -> direita
            if ((*comparacoes)++ && letra >= pAjudante->No.NoInterno.letraNoPontoQueDifere){

                pAjudante = pAjudante->No.NoInterno.Dir;
            } else {

                pAjudante = pAjudante->No.NoInterno.Esq;
            }
        }
        /// Caso a palavra ja esteja na arvore, eh encerrado o processo de insercao
        if ((*comparacoes)++ && strcmp(palavra, pAjudante->No.Chave) == 0){

                printf("Chaves sao iguais\n");
                return (*tree);
        }
       
        printf("Palavra inserida!\n");
        /// Atencao, esta acessando o vetor a partir do indice 1
        i = 1;
        while ((*comparacoes)++ && Bit(i, palavra) == Bit(i, pAjudante->No.Chave) ){
            i++;
        }
       
        /// Pega a maior letra no ponto que difere entre as duas palavras comparadas
        if ((*comparacoes)++ && Bit(i, palavra) > Bit(i, pAjudante->No.Chave)){

            letraDiferente = palavra[i - 1];
        } else {

            letraDiferente = pAjudante->No.Chave[i - 1];
        }
       
        return InsereEntre(palavra, tree, i, letraDiferente, comparacoes);
    }
}

void Pesquisa(TipoArvore *tree, char *palavra, int *comparacoes){
    /// Checa se o No atual eh do tipo externo
    (*comparacoes)++;
    if (VerificarNoExterno(*tree)){
        /// Verifica se a palavra pesquisada eh igual a armazenada no No que entrou
        if ((*comparacoes)++ && (!strcmp((*tree)->No.Chave, palavra))){

            printf("Chave encontrada\n");
            return;
        } else {

            printf("Chave nao se encontra na arvore\n");
            return;
        }
    }
    /// Caso o No seja interno -> vai para a direita se eh maior/igual
    if ((*comparacoes)++ && Bit((*tree)->No.NoInterno.indiceOndeDifere, palavra) >= (*tree)->No.NoInterno.letraNoPontoQueDifere){

        Pesquisa(&(*tree)->No.NoInterno.Dir, palavra, comparacoes);
    } else {

        Pesquisa(&(*tree)->No.NoInterno.Esq, palavra, comparacoes);
    }
}

void PrintPatTree(TipoArvore *tree){

    if (*tree != NULL){
        /// Caso o No atual seja externo -> eh realizada a impressao do conteudo guardado por ele
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
        /// Caso o No atual seja externo -> eh contabilizado em 1 a variavel referente a quantidade de palavras na arvore 
        if ((*tree)->idEstruturalNo == Externo){

            (*contador)++;
        } else {

            ContarPalavras(&(*tree)->No.NoInterno.Esq, contador);
            ContarPalavras(&(*tree)->No.NoInterno.Dir, contador);
        }
    }
}

void CalcularQntMemoriaPat(TipoArvore *tree, size_t *nos){

    if (*tree != NULL){
        /// Eh contabilizado a quantidade de memoria, por meio do sizeof, para cada No da arvore
        *nos += sizeof((**tree));
        /// Para nao acessar posicoes invalidas eh feita a verificacao se o No atual eh externo
        if ((*tree)->idEstruturalNo == Externo){
            return;
        }
        CalcularQntMemoriaPat(&(*tree)->No.NoInterno.Esq, nos);
        CalcularQntMemoriaPat(&(*tree)->No.NoInterno.Dir, nos);
    }
}








//-------------------------------------------------
/*

*/
