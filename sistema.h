#ifndef SISTEMA_H
#define SISTEMA_H

//Trabalho Métodos Numéricos 2023.1
//Alunos: Alexia Assumpção e Ítalo Emanoel

typedef struct
{
    int ordem;
    double** matrizA;
    double* matrizB;
    double* solucao;
}Sistema;

#endif
