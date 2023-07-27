#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fatoracaoLU.h"
#include "matriz.h"
#include "vetor.h"

//Trabalho Métodos Numéricos 2023.1
//Alunos: Alexia Assumpção e Ítalo Emanoel

double*** fatoracaoLU(int ordem, double** matrizA) {
    double*** matrizLU = (double***) malloc( sizeof( double** ) * 2 );
    /*LU As matrizes L e U tem como inicial uma matriz Identidade.
    para ja existirem elementos nela, mas todos sao alterados e nao alteram
    o resultado.*/
    double** matrizL = createIdentityMatrix(ordem);
    double** matrizU = createIdentityMatrix(ordem);

    double somatorio;
    int i, j, k;


    for(i = 0; i < ordem; i++) {
        for(j = 0; j < ordem; j++) {
            if(i == j || i < j) {
                somatorio = 0;

                #pragma omp parallel for reduction (+:somatorio)
                for(k = 0; k < i; k++) {
                    somatorio = somatorio + (matrizU[k][j] * matrizL[i][k]);
                }
                
                matrizU[i][j] = matrizA[i][j] - somatorio;
            } else if(i != j && i > j) {
                somatorio = 0;

                #pragma omp parallel for reduction (+:somatorio)
                for(k = 0; k < j; k++) {
                    somatorio = somatorio + (matrizU[k][j] * matrizL[i][k]);
                }

                matrizL[i][j] = (matrizA[i][j] - somatorio) / matrizU[j][j];
            }
        }
    }

    matrizLU[0] = matrizL;
    matrizLU[1] = matrizU;
    return matrizLU;
}

//SUBSTITUICAO
double* substituicaoParaFrente(int ordem, double** matrizA, double* matrizB) {
    double* vetorX = criarVetor(ordem); //cria o vetor solucao
    double somatoria;
    int i, j;

    for (i = 0; i < ordem; i++) {
        somatoria = 0;

        #pragma omp parallel for reduction (+:somatoria)
        for (j = 0; j < i; j++) {
            if(i >= 1)
            {
                somatoria += (matrizA[i][j] * vetorX[j]);
                //nao sendo a primeira iteracao sabe-se que ja existem valores no vetorX,entao multiplica-se o elemento pelo respectivo valor da sua variavel encontrado no vetorX
            }
        }
        //faz-se o valor da matriz B menos a somatoria dividido pelo elemento que multiplica a variavel que queremos encontrar
        vetorX[i] = (matrizB[i] - somatoria) / matrizA[i][i];
    }
    return vetorX;
}

double* substituicaoParaTras(int ordem, double** matrizA, double* matrizB) {
    double* vetorX = criarVetor(ordem);//cria o vetor solucao
    double somatoria;
    int i, j;

    for (i = ordem - 1; i >= 0; i--) {
        somatoria = 0;

        #pragma omp parallel for reduction (+:somatoria)
        for (j = ordem - 1; j > i; j--) {
            if(i <= ordem-2)
            {
                somatoria += (matrizA[i][j] * vetorX[j]);
                //nao sendo a primeira iteracao sabe-se que ja existem valores no vetorX, entao multiplica-se o elemento pelo respectivo valor da sua variavel encontrado no vetorX
            }
        }

        //faz-se o valor da matriz B menos a somatoria dividido pelo elemento que multiplica a variavel que queremos encontrar
        vetorX[i] = (matrizB[i] - somatoria) / matrizA[i][i];
    }

    return vetorX;
}

void metodoLU(Sistema* psist) {
    double*** matrizLU;
    double** matrizL;
    double** matrizU;
    double* Y;
    double* X;

    matrizLU = fatoracaoLU(psist->ordem, psist->matrizA);
    matrizL = matrizLU[0];
    matrizU = matrizLU[1];

    printf("A matriz L eh:\n");
    imprimirMatriz(psist->ordem, matrizL);
    printf("\n");

    printf("A matriz U eh:\n");
    imprimirMatriz(psist->ordem, matrizU);
    printf("\n");

    //Continuacao da Fatoracao LU:
    //LY= B, substituicao para frente.
    Y = substituicaoParaFrente(psist->ordem, matrizL, psist->matrizB);
    //UX = Y, substituicao para tras.
    X = substituicaoParaTras(psist->ordem, matrizU, Y);
    
    psist->solucao = X;
    liberarMatriz(psist->ordem, &matrizL);
    liberarMatriz(psist->ordem, &matrizU);
    liberarVetor(&Y);
    free(matrizLU);
}
