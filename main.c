#include "Pat.h"
#include "trie.h"

int main()
{
    ArvoreTST tst;

    char palavra[] = "bolo";
    char p2[] = "bobo";
    char p3[] = "bao";
    char p4[] = "belo";
    TipoArvore patos;

    InicializarPat(&patos);

    patos = InserePat(palavra, &patos);
    patos = InserePat(p2, &patos);
    patos = InserePat(p3, &patos);
    patos = InserePat(p4, &patos);
    Pesquisa(&patos, palavra);

    //printf("%d\n", patos->No.NoInterno.numBitOndeDifere);






    /// Testes func basicas
    /*
    Palavra peleps;

    peleps = EncapsulaVocabulo("retangulo");

    printf("%s\n", peleps.vocabulo);

    for (int i = 0; i < 10; i++){
        printf("%d", peleps.codigoBinario[i]);
    }
    */

    InicializaNoTST(&tst);
    InserirNaArvore(&tst, "Teste");
    printf("%c", tst->caractere);
    printf("%c", tst->Central->caractere);
    printf("%c\n", tst->Central->Central->caractere);
    
    return 0;
}
