#ifndef FATORACAOLU_H
#define FATORACAOLU_H
#include "sistema.h"

double*** fatoracaoLU(int ordem, double** A);

double* substituicaoParaFrente(int ordem, double** matrizA, double* matrizB);
double* substituicaoParaTras(int ordem, double** matrizA, double* matrizB);

void metodoLU(Sistema* psist);

#endif
