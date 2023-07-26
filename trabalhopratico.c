#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"
#include "vetor.h"
#include "fatoracaolu.h"
#include "sistema.h"

int main(void) {
    freopen("input.txt", "r", stdin); // redireciona o stdin para questao05.txt

    Sistema sist;
    Sistema* psist = &sist;

    double*** matrizLU;
    double* X = criarVetor(100);
    double sS;

    psist->matrizA = criarMatriz(100);
    psist->matrizB = criarVetor(100);

    scanf("%d", &psist->ordem);

    psist->matrizA = preencherMatriz(psist->ordem);
    psist->matrizB = preencherVetor(psist->ordem);

    sS = submatrizesPrincipaisNaoSingulares(psist->ordem, psist->matrizA);
    if(sS==1) {
        metodoLU(psist);
        atribuirVetor(psist->ordem, X, psist->solucao);
        liberarVetor(&psist->solucao);
    }
    else printf("A Fatoracao LU nao pode ser realizada, porque as submatrizes principais sao singulares!\n");
    
    printf("A solucao da Fatoracao LU, matriz X, eh:\n");
    imprimirVetor(psist->ordem, X);
    printf("\n");
}
