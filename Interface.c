//
// Created by lazarus on 18/10/20.
//

#include "Interface.h"
#include <stdio.h>

void printOpc(){
    printf("----------------------------------\n");
    printf("|              MENU               |\n");
    printf("|(1) Inserir em Patricia          |\n");
    printf("|(2) Inserir em TRIE TST          |\n");
    printf("|(3) Carregar arquivo             |\n");
    printf("|(4) Exibir em ordem alfabetica   |\n");
    printf("|(5) Exibir numero de comparacoes |\n");
    printf("|(6) Exibir uso de memória        |\n");
    printf("|(7) Sair                         |\n");
    printf("----------------------------------\n");
    printf("Opção: ");

}

void leOpc(int *opc) {
    while (*opc != 7) {
        printOpc();

        scanf("%d", opc);
        while (*opc > 6 || *opc < 0) {
            printf("--> Opção inválida!\n");
            scanf("%d", opc);
        }

    }
}

void leArquivo(TipoArvore *pat, NoTST **tst, FILE *arq){
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


void interface(){
    //arquivo
    FILE *arq;

    //declarando arvores
    TipoArvore patricia;
    ArvoreTST tst;

    //inicializando
    InicializarPat(&patricia);
    InicializaNoTST(&tst);

    //variaveis de decisao
    int opc = 0;

    while (1) {

        printOpc();

        //Leitura da opcao
        scanf("%d", &opc);


        if (opc == 1) {
            char palavra[20];
            getchar();
            printf("----> Para encerrar, insira um espaço!\n");
            while (1) {
                fgets(palavra, 20, stdin);
                if (palavra[0] == ' '){
                    printf("---> Encerrado insercao de palavras\n");
                    break;
                }
                patricia = InserePat(palavra, &patricia);
                printf("---> Palavra inserida\n");
            }
        } else if (opc == 2) {
            char palavra[20];
            getchar();
            printf("----> Para encerrar, insira um espaço!\n");
            while (1) {
                fgets(palavra, 20, stdin);
                if (palavra[0] == ' '){
                    printf("---> Encerrado insercao de palavras\n");
                    break;
                }
                InserirTST(&tst, palavra);
                printf("---> Palavra inserida\n");
            }

        } else if (opc == 3) {
            leArquivo(&patricia, &tst, arq);

        } else if (opc == 4) {


        } else if (opc == 5) {


        } else if (opc == 6) {


        } else if (opc == 7) {
            printf("\n----Fim de execução----\n");
            exit(0);
        }

    }
  
}