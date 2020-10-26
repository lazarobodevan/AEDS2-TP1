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
