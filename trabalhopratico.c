#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "matriz.h"
#include "vetor.h"
#include "fatoracaolu.h"
#include "sistema.h"

int main(void) {
    freopen("input.txt", "r", stdin);
    float startTime, endTime, timeElapsed;

    startTime = (float)clock()/CLOCKS_PER_SEC;
    Sistema sist;
    Sistema* psist = &sist;

    double*** matrizLU;
    double* X = criarVetor(100);
    
    psist->matrizA = criarMatriz(100);
    psist->matrizB = criarVetor(100);

    scanf("%d", &psist->ordem);

    psist->matrizA = preencherMatriz(psist->ordem);
    psist->matrizB = preencherVetor(psist->ordem);

    metodoLU(psist);
        atribuirVetor(psist->ordem, X, psist->solucao);
        liberarVetor(&psist->solucao);

    printf("A solucao da Fatoracao LU, matriz X, eh:\n");
    imprimirVetor(psist->ordem, X);
    printf("\n");

    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    printf("Tempo gasto: %f\n", timeElapsed);
}
