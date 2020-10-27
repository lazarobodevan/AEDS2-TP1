
//
// Grupo: C-TAD-oido
//

#include "Interface.h"
#include "Pat.h"
#include <stdio.h>
#include <time.h>


void printOpcArvore(){
    printf("----------------------------------\n");
    printf("|         MENU DE ARVORES         |\n");
    printf("|(1) Patricia                     |\n");
    printf("|(2) TRIE TST                     |\n");
    printf("----------------------------------\n");
    printf("Opção: ");
}

void printOpcPat(){
    printf("----------------------------------\n");
    printf("|           MENU - PAT            |\n");
    printf("|(1) Inserir palavra              |\n");
    printf("|(2) Carregar arquivo             |\n");
    printf("|(3) Pesquisar palavra            |\n");
    printf("|(4) Exibir em ordem alfabetica   |\n");
    printf("|(5) Contar palavras              |\n");
    printf("|(6) Trocar de arvore             |\n");
    printf("|(7) Sair                         |\n");
    printf("----------------------------------\n");
    printf("Opção: ");

}

void printOpcTst(){
    printf("----------------------------------\n");
    printf("|           MENU - TST            |\n");
    printf("|(1) Inserir palavra              |\n");
    printf("|(2) Carregar arquivo             |\n");
    printf("|(3) Pesquisar palavra            |\n");
    printf("|(4) Exibir em ordem alfabetica   |\n");
    printf("|(5) Contar palavras              |\n");
    printf("|(6) Trocar de arvore             |\n");
    printf("|(7) Sair                         |\n");
    printf("----------------------------------\n");
    printf("Opção: ");

}


void leArquivoPat(TipoArvore *pat, FILE *arq, int *comparacoes){
    char nomeArq[20];
    printf("Arquivo: ");
    fgets(nomeArq, 20, stdin);
    nomeArq[strlen(nomeArq)-1] = '\0';

    arq = fopen(nomeArq, "r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        return;
    }
    printf("Arquivo encontrado!\n");
    char aux[20];
    while(!feof(arq)){
        fscanf(arq, "%s ", aux);
        strcpy(&aux[strlen(aux)], "\0");
        *pat = InserePat(aux, pat, comparacoes);
    }
}

void leArquivoTst(NoTST **tst, FILE *arq, int *comparacoes){

    char nomeArq[20];
    printf("Arquivo: ");
    fgets(nomeArq, 20, stdin);
    nomeArq[strlen(nomeArq)-1] = '\0';

    arq = fopen(nomeArq, "r");
    if(arq == NULL){
        printf("Arquivo não encontrado!\n");
        return;
    }
    printf("Arquivo encontrado!\n");
    char aux[20];
    while(!feof(arq)){
        fscanf(arq, "%s ", aux);
        strcpy(&aux[strlen(aux)], "\0");
        InserirTST(tst, aux, comparacoes);
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

    //variaveis de uso de memoria
    size_t memPat = 0;
    size_t memTst = 0;

    //escolha da arvore a ser utilizada
    do {
        system("clear");
        printOpcArvore();
        scanf("%d", &opcArvore);
        if (opcArvore > 3 || opcArvore < 0) {
            printf("Opção Invalida. Tente novamente!\n");
        }
    } while (opcArvore > 3 || opcArvore < 0);
    getchar();

    system("clear");
    //repeticao da interface de escolha de operacoes
    while (1) {

        if (opcArvore == 1){ //opcao de arvore == patricia

            printOpcPat();
            //Leitura da opcao
            scanf("%d", &opcOper);
            getchar();
            system("clear");

            if (opcOper == 1) { //inserir palavra pelo terminal
                char palavra[20];

                //variavel de tempo;
                clock_t tempo;

                printf("\n");
                printf("---------------------------------------\n");
                printf("----> Para encerrar, insira um espaço!\n");
                printf("---------------------------------------\n");
                printf("\n");

                while (1) { //insercao ininterrupta de palavra a palavra
                    printf("Palavra: ");
                    fgets(palavra, 20, stdin);
                    if (palavra[0] == ' ') {
                        system("clear");
                        printf("---> Encerrado insercao de palavras\n");
                        break;
                    }
                    palavra[strlen(palavra)-1] = '\0';
                    tempo = clock();
                    patricia = InserePat(palavra, &patricia, &contCompPat);
                    tempo = clock() - tempo;
                    system("clear");
                    printf("--> Tempo: %lf s\n", ((double)tempo)/CLOCKS_PER_SEC);
                    printf("--> Comparacoes: %d\n", contCompPat);
                    contCompPat = 0;
                }

                CalcularQntMemoriaPat(&patricia, &memPat);
                printf("--> Memoria: %lu bytes\n", memPat);
                memPat = 0;

            } else if (opcOper == 2) { //leitura de arquivo pat
                //variavel de tempo;
                clock_t tempo;

                system("clear");
                tempo = clock();
                leArquivoPat(&patricia, arq, &contCompPat);
                tempo = clock() - tempo;



                printf("--> Tempo: %lf s \n", ((double)tempo)/CLOCKS_PER_SEC);
                CalcularQntMemoriaPat(&patricia, &memPat);
                printf("--> Memoria: %lu bytes\n", memPat);
                memPat = 0;
                printf("--> Comparacoes: %d\n", contCompPat);
                contCompPat = 0;

            } else if (opcOper == 3) { //pesquisa pat
                char palavra[20];
                int comp = 0;

                //variavel de tempo;
                clock_t tempo;
                if(patricia == NULL){ //impede tentativa de pesquisa em caso de arvore vazia
                    system("clear");
                    printf("--> Arvore vazia!\n");

                }else {
                    printf("Palavra: ");
                    fgets(palavra, 20, stdin);
                    palavra[strlen(palavra) - 1] = '\0'; //utilizado para remover o \n no final e colocar \0 no lugar

                    system("clear");
                    tempo = clock();
                    Pesquisa(&patricia, palavra, &comp);
                    tempo = clock() - tempo;


                    printf("--> Tempo: %lf s\n", ((double) tempo) / CLOCKS_PER_SEC);
                    printf("--> Comparacoes: %d\n", comp);
                    contCompPat = 0;
                }

            } else if (opcOper == 4) { //exibir em ordem alfabetica pat
                system("clear");
                PrintPatTree(&patricia); // imprime em ordem alfabetica

            } else if (opcOper == 5) { //contar palavras pat
                system("clear");
                int contPalaPat = 0;
                ContarPalavras(&patricia, &contPalaPat);
                printf("--> %d palavras!\n", contPalaPat);

            } else if (opcOper == 6) { //troca de arvores

                do {
                    system("clear");
                    printOpcArvore();
                    scanf("%d", &opcArvore);
                    if (opcArvore > 3 || opcArvore < 0) {
                        printf("Opção Invalida. Tente novamente!\n");
                    }
                } while (opcArvore > 3 || opcArvore < 0);
                getchar();
                system("clear");

            } else if(opcOper == 7){ //encerra o programa
                system("clear");
                printf("\n----Fim de execução----\n");
                exit(0);
            }

        }else if(opcArvore == 2){ // Arvore TST
            system("clear");
            printOpcTst();
            //Leitura da opcao
            scanf("%d", &opcOper);
            getchar();

            if (opcOper == 1) { //inserir palavra pelo terminal
                char palavra[20];

                printf("\n");
                printf("---------------------------------------\n");
                printf("----> Para encerrar, insira um espaço!\n");
                printf("---------------------------------------\n");
                printf("\n");

                //variavel de tempo;
                clock_t tempo;

                while (1) { //insercao ininterrupta de palavra a palavra
                    printf("Palavra: ");
                    fgets(palavra, 20, stdin);
                    if (palavra[0] == ' ') {
                        printf("---> Encerrado insercao de palavras\n");
                        break;
                    }
                    palavra[strlen(palavra)-1] = '\0';
                    contCompTst = 0;

                    tempo = clock();
                    InserirTST(&tst, palavra, &contCompTst);
                    tempo = clock() - tempo;
                    system("clear");
                    printf("--> Tempo: %lf s\n", ((double)tempo)/CLOCKS_PER_SEC);

                    printf("--> Comparacoes: %d\n", contCompTst);
                    contCompTst = 0;
                }

                printf("--> Memoria: %d bytes\n", MemoriaUsada(tst));

            } else if (opcOper == 2) { //leitura de arquivo tst
                //variavel de tempo;
                clock_t tempo;
                contCompTst = 0;

                tempo = clock();
                leArquivoTst(&tst, arq, &contCompTst);
                tempo = clock() - tempo;
                system("clear");
                printf("--> Tempo: %lf s\n", ((double)tempo)/CLOCKS_PER_SEC);
                printf("--> Memoria: %d bytes\n", MemoriaUsada(tst));
                printf("--> Comparacoes: %d\n", contCompTst);
                contCompTst = 0;

            } else if (opcOper == 3) { //pesquisa tst
                char palavra[20];
                int comp = 0;

                //variavel de tempo;
                clock_t tempo;

                if(tst == NULL){ //impede pesquisa em arvore vazia
                    system("clear");
                    printf("--> Arvore vazia!\n");
                }else {

                    printf("Palavra: ");
                    fgets(palavra, 20, stdin);
                    palavra[strlen(palavra) - 1] = '\0'; //utilizado para remover o \n no final e colocar \0 no lugar

                    system("clear");
                    tempo = clock();
                    PesquisaTST(tst, palavra, &comp);
                    tempo = clock() - tempo;


                    printf("\n--> Tempo: %lf s\n", ((double) tempo) / CLOCKS_PER_SEC);
                    printf("--> Comparacoes: %d\n", comp);
                }

            } else if (opcOper == 4) { //exibir em ordem alfabetica
                system("clear");
                EmOrdemTST(tst); // imprime em ordem alfabetica

            } else if (opcOper == 5) { //mostra a quantidade de palavras
                system("clear");
                printf("--> %d palavras!\n", ContarPalavrasTST(tst));

            } else if (opcOper == 6) { //troca de arvore
                do {
                    system("clear");
                    printOpcArvore();
                    scanf("%d", &opcArvore);
                    if (opcArvore > 3 || opcArvore < 0) {
                        printf("Opção Invalida. Tente novamente!\n");
                    }
                } while (opcArvore > 3 || opcArvore < 0);
                getchar();
            }else if(opcOper == 7){ //encerra o programa

                printf("\n----Fim de execução----\n");
                exit(0);

            }
        }
    }
  
}