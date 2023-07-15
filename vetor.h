#ifndef VETOR_H
#define VETOR_H

//CRIAR E LIBERAR VETOR
double* criarVetor(int ordem);
void liberarVetor(double** vetor);

//PREENCHER VETOR
double* preencherVetor(int ordem);

void atribuirVetor(int ordem, double* vetor1, double* vetor2);

//IMPRIMIR VETOR
void imprimirVetor(int ordem, double* vetor);
#endif