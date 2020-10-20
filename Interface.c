//
// Created by lazarus on 18/10/20.
//

#include "Interface.h"
#include <stdio.h>


void printOpcArvore(){
    printf("----------------------------------\n");
    printf("|         MENU DE ARVORES         |\n");
    printf("|(1) Patricia                     |\n");
    printf("|(2) TRIE TST                     |\n");
    printf("|(3) Patricia e TST               |\n");
    printf("----------------------------------\n");
    printf("Opção: ");
}

void printOpc(){
    printf("----------------------------------\n");
    printf("|              MENU               |\n");
    printf("|(1) Inserir palavra              |\n");
    printf("|(2) Carregar arquivo             |\n");
    printf("|(3) Pesquisar palavra            |\n");
    printf("|(4) Exibir em ordem alfabetica   |\n");
    printf("|(5) Contar palavras              |\n");
    printf("|(6) Sair                         |\n");
    printf("----------------------------------\n");
    printf("Opção: ");

}

void leArquivoPatTst(TipoArvore *pat, NoTST **tst, FILE *arq){
    arq = fopen("testes.txt", "r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        return;
    }
    printf("Arquivo encontrado!\n");
    char aux[20];
    while(!feof(arq)){
        fscanf(arq, "%s ", aux);
        strcpy(&aux[strlen(aux)], "\0");
        InserePat(aux, pat);
        InserirTST(tst, aux);
    }
}

void leArquivoPat(TipoArvore *pat, FILE *arq){
    arq = fopen("testes.txt", "r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        return;
    }
    printf("Arquivo encontrado!\n");
    char aux[20];
    while(!feof(arq)){
        fscanf(arq, "%s ", aux);
        strcpy(&aux[strlen(aux)], "\0");
        InserePat(aux, pat);
    }
}

void leArquivoTst(NoTST **tst, FILE *arq){
    arq = fopen("testes.txt", "r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        return;
    }
    printf("Arquivo encontrado!\n");
    char aux[20];
    while(!feof(arq)){
        fscanf(arq, "%s ", aux);
        strcpy(&aux[strlen(aux)], "\0");
        InserirTST(tst, aux);
    }
}

void interface() {
    //arquivo
    FILE *arq;

    //declarando arvores
    TipoArvore patricia;
    ArvoreTST tst;

    //inicializando
    InicializarPat(&patricia);
    InicializaNoTST(&tst);

    //variaveis de decisao
    int opcOper = 0;
    int opcArvore = 0;

    //variaveis de contagem
    int contCompPat = 0; //contagem de comparacoes
    int contCompTst = 0;
    int contPalaPat = 0; //contagem de palavras
    int contPalaTst = 0;


    //escolha da arvore a ser utilizada
    do {
        printOpcArvore();
        scanf("%d", &opcArvore);
        if (opcArvore > 3 || opcArvore < 0) {
            printOpcArvore("Opção Invalida. Tente novamente!\n");
        }
    } while (opcArvore > 3 || opcArvore < 0);
    getchar();
    //repeticao da interface de escolha de operacoes
    while (1) {

        printOpc();

        //Leitura da opcao
        scanf("%d", &opcOper);
        getchar();

        if (opcArvore == 1){ //opcao de arvore == patricia
            if (opcOper == 1) { //inserir palavra pelo terminal
                char palavra[20];
                getchar();
                printf("----> Para encerrar, insira um espaço!\n");
                while (1) {
                    fgets(palavra, 20, stdin);
                    if (palavra[0] == ' ') {
                        printf("---> Encerrado insercao de palavras\n");
                        break;
                    }
                    patricia = InserePat(palavra, &patricia);
                    printf("---> Palavra inserida\n");
                }
            } else if (opcOper == 2) {
                //leArquivoPat(&patricia, arq);

            } else if (opcOper == 3) {
                char palavra[20];
                printf("Palavra: ");
                fgets(palavra, 20, stdin);
                palavra[strlen(palavra)-1] = '\0'; //utilizado para remover o \n no final e colocar \0 no lugar
                Pesquisa(&patricia, palavra, &contCompPat);

            } else if (opcOper == 4) {
                PrintPatTree(&patricia); // imprime em ordem alfabetica

            } else if (opcOper == 5) {
                ContarPalavras(&patricia, &contPalaPat);
                printf("--> %d palavras!\n", contPalaPat);

            } else if (opcOper == 6) {
                printf("\n----Fim de execução----\n");
                exit(0);

            }

        }else if(opcArvore == 2){ // Arvore TST
            if (opcOper == 1) { //inserir palavra pelo terminal
                char palavra[20];
                getchar();
                printf("----> Para encerrar, insira um espaço!\n");
                while (1) {
                    fgets(palavra, 20, stdin);
                    if (palavra[0] == ' ') {
                        printf("---> Encerrado insercao de palavras\n");
                        break;
                    }
                    InserirTST(&tst, palavra);
                    printf("---> Palavra inserida\n");
                }
            } else if (opcOper == 2) {
                leArquivoTst(&tst, arq);

            } else if (opcOper == 3) {
                char palavra[20];
                printf("Palavra: ");
                fgets(palavra, 20, stdin);
                palavra[strlen(palavra)-1] = '\0'; //utilizado para remover o \n no final e colocar \0 no lugar
                PesquisaTST(tst, palavra);

            } else if (opcOper == 4) {
                EmOrdemTST(tst); // imprime em ordem alfabetica

            } else if (opcOper == 5) {
                printf("Ainda nao tem\n");
                printf("--> %d palavras!\n", contPalaPat);

            } else if (opcOper == 6) {
                printf("\n----Fim de execução----\n");
                exit(0);

            }
        }
    }
  
}