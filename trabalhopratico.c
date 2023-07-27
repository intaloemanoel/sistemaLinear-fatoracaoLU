#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "matriz.h"
#include "vetor.h"
#include "fatoracaolu.h"
#include "sistema.h"

//Trabalho Métodos Numéricos 2023.1
//Alunos: Alexia Assumpção e Ítalo Emanoel

int main(void) {
    freopen("input.txt", "r", stdin);
    float startTime, endTime, timeElapsed;

    startTime = (float)clock()/CLOCKS_PER_SEC;
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

    endTime = (float)clock()/CLOCKS_PER_SEC;
    timeElapsed = endTime - startTime;
    printf("Tempo gasto: %f\n", timeElapsed);
}
