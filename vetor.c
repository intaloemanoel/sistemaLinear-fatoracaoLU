#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vetor.h"

//CRIAR E LIBERAR VETOR
double* criarVetor(int ordem)
{
    //cria um vetor nulo para a dimensao informada
    double* vetor = (double*) calloc (ordem, sizeof(double));
    return vetor;
}

double* preencherVetor(int ordem)
{
    //atribui os valores informados pelo usuario ao vetor
    double* vetor = criarVetor(ordem);
    for(int i = 0; i < ordem; i++)
    {
        scanf ("%lf", &vetor[i]);
    }
    return vetor;
}

void atribuirVetor(int ordem, double* vetor1, double* vetor2)
{
    for (int i = 0; i < ordem; ++i)
    {
        vetor1[i] = vetor2[i];
    }
}


void liberarVetor(double** vetor)
{
    //desaloca a memoria utilizada pelas posicoes vinculadas ao ponteiro
    free(*vetor);
    *vetor = NULL;
}

void imprimirVetor(int ordem, double* vetor)
{
    for(int c = 0; c < ordem; c++)
    {
        printf("%11.6lf\n", vetor[c]);
    }
    printf("\n");
}
