#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"
#include "fatoracaoLU.h"
#include "vetor.h"

double** criarMatriz(int ordem) {
    double** matriz = (double**) malloc (sizeof(double*) * ordem);

    for(int i = 0; i < ordem; i++) {
        matriz[i] = (double*) calloc (ordem, sizeof(double));
    }

    return matriz;
}

double** createMatrix(int rows, int columns) {
    double** matrix = malloc(rows * sizeof(double*));
    for(int i = 0; i < rows; i++) {
        matrix[i] = calloc(columns, sizeof(double));
    }
    return matrix;
}


double** createSquareMatrix(int size) {
    double** squareMatrix = createMatrix(size, size);
    return squareMatrix;
}

void liberarMatriz(int ordem, double*** matriz) {
    for(int i = 0; i < ordem; i++) {
        free((*matriz)[i]);
    }

    free(*matriz);
    *matriz = NULL;
}

//PREENCHER MATRIZ
double** preencherMatriz(int ordem) {
    double** matriz = criarMatriz(ordem);

    for(int i = 0; i < ordem; i++) {
        for(int j = 0; j < ordem; j++) {
            scanf ("%lf", &matriz[i][j]);
        }
    }

    return matriz;
}

void imprimirMatriz(int ordem, double** matriz) {
    for (int i = 0; i < ordem; i++) {
        for (int j = 0; j < ordem; j++) {
            printf ("%11.6lf ", matriz[i][j]);
        }
        printf ("\n");
    }
}

double** createIdentityMatrix(int size){
    double** identityMatrix = createSquareMatrix(size);

    for(int i = 0; i < size; i++){
        identityMatrix[i][i] = 1;
    }
    
    return identityMatrix;
}

double** submatriz(int ordem, double** matriz, int linha, int coluna) {
    double** submatriz = criarMatriz(ordem - 1);
    int cont1 = 0,cont2 = 0;

    #pragma omp parallel for
    for(int i = 0; i < ordem; i++) {
        cont2 = 0;
        for(int j = 0; j < ordem; j++) {
            if(i != linha && j != coluna) {
                submatriz[cont1][cont2] = matriz[i][j];
                cont2++;
            }
        }

        if(cont2 == ordem - 1) cont1++;
    }
    return submatriz;
}

int matrizNaoSingular(int ordem, double** matriz) {
    if(determinante(ordem, matriz) == 0) return 0;
    return 1;
}

double determinante(int ordem, double** matriz) {
    if(ordem == 1) return matriz[0][0];
    else if(ordem == 2) return matriz[0][0] * matriz[1][1] - (matriz[0][1] * matriz[1][0]);
    else if(ordem == 3) {
        return matriz[0][0] * matriz[1][1] * matriz[2][2] + matriz[0][1] * matriz[1][2] * matriz[2][0] + matriz[0][2] * matriz[1][0] * matriz[2][1] - (matriz[0][2] * matriz[1][1] * matriz[2][0] + matriz[0][1] * matriz[1][0] * matriz[2][2] + matriz[0][0] * matriz[1][2] * matriz[2][1]);
    }
    else {
        return teoremaLaplace(ordem, matriz);
    }

    return NAN;
}

double teoremaLaplace(int ordem, double** matriz) {
    int j = 0;//escolho a primeira coluna
    double det = 0;
    double* cofator = criarVetor(ordem);
    double** sub;

    #pragma omp parallel for
    for(int i = 0; i < ordem; i++) {
        sub = submatriz(ordem, matriz, i, j);
        cofator[i]=((i%2==0) ? 1 : -1) * determinante(ordem - 1, sub);
        liberarMatriz(ordem - 1, &sub);
    }

    #pragma omp parallel for
    for(int i = 0; i < ordem; i++) {
        det += matriz[i][j] * cofator[i];
    }
    liberarVetor(&cofator);
    return det;
}

int submatrizesPrincipaisNaoSingulares(int ordem, double** matriz) {
    double** principal;
    double** temp = matriz;

    #pragma omp parallel for
    for(int i = ordem - 1; i > 0; i--) {
        principal = submatriz(i + 1, temp, i, i);
        if(i < ordem - 1) liberarMatriz(i, &temp);
        if(!(matrizNaoSingular(i, principal))) return 0;
        temp = principal;
    }
    return 1;
}



