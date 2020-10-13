#include "Pat.h"

int main()
{
    
    char palavra[] = "poquer";
    char p2[] = "porrete";
    char p3[] = "paladar";
    char p4[] = "peixe";
    TipoArvore patos;

    InicializarPat(&patos);


    patos = InserePat(palavra, &patos);
    patos = InserePat(p2, &patos);
    patos = InserePat(p3, &patos);
    patos = InserePat(p4, &patos);
    Pesquisa(&patos, palavra);




    printf("\nHello world!\n");
    return 0;
}
