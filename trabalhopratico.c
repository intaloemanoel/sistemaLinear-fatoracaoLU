#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"
#include "vetor.h"
#include "fatoracaolu.h"
#include "sistema.h"

int main(void)
{
    freopen("input.txt", "r", stdin); // redireciona o stdin para questao05.txt

    Sistema sist;
    Sistema* psist = &sist;

    double*** LU;
    double* X = criarVetor(100);
    double sS;

    psist->matrizA = criarMatriz(100);
    psist->matrizB = criarVetor(100);

    scanf("%d", &psist->ordem);

    psist->matrizA = preencherMatriz(psist->ordem);
    psist->matrizB = preencherVetor(psist->ordem);
    LU = fatoracaoLU(psist->ordem, psist->matrizA);

    printf("A matriz L eh:\n");
    imprimirMatriz(psist->ordem, LU[0]);
    printf("\n");

    printf("A matriz U eh:\n");
    imprimirMatriz(psist->ordem, LU[1]);
    printf("\n");
    
    for(int i = 0; i < 2; i++)
    {
        liberarMatriz(psist->ordem, &LU[i]);
    }
    free(LU);

    LU = NULL;

    sS = submatrizesPrincipaisNaoSingulares(psist->ordem, psist->matrizA);
    if(sS==1)
    {
        metodoLU(psist);
        atribuirVetor(psist->ordem, X, psist->solucao);
        liberarVetor(&psist->solucao);
    }
    else printf("A Fatoracao LU nao pode ser realizada, porque as submatrizes principais sao singulares!\n");
    
    printf("A solucao da Fatoracao LU, matriz X, eh:\n");
    imprimirVetor(psist->ordem, X);
    printf("\n");
}
