#ifndef SISTEMA_H
#define SISTEMA_H

typedef struct
{
    int ordem;
    double** matrizA;
    double* matrizB;
    double* solucao;
}Sistema;

#endif
