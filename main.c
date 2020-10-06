#include "Pat.h"
#include "trie.h"

int main()
{
    ArvoreTST tst;

    Palavra palavraTeste, segundaPala, tercPala, quaPala;
    palavraTeste = EncapsulaVocabulo("pata");
    segundaPala = EncapsulaVocabulo("pato");
    tercPala = EncapsulaVocabulo("aviao");
    quaPala = EncapsulaVocabulo("pato");

    TipoArvore semente;

    Inicializar(&semente);

    semente = Insere(palavraTeste, &semente);

    semente = Insere(segundaPala, &semente);

    semente = Insere(tercPala, &semente);

    semente = Insere(quaPala, &semente);

    printf("%d\n", semente->No.NoInterno.numBitOndeDifere);






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
