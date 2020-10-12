#include "Pat.h"

int main()
{
    char palavra[] = "bobo";
    char p2[] = "bolo";
    char p3[] = "bao";
    char p4[] = "belo";
    TipoArvore patos;

    InicializarPat(&patos);


    patos = InserePat(palavra, &patos);
    patos = InserePat(p2, &patos);


    patos = InserePat(p3, &patos);
    //patos = InserePat(p4, &patos);
    Pesquisa(&patos, p3);
    //printf("\n\nEsq: %s\n", patos->No.NoInterno.Esq->No.Chave);

    //printf("%c\n", patos->No.NoInterno.letraNoPontoQueDifere);




    printf("\nHello world!\n");
    return 0;
}
