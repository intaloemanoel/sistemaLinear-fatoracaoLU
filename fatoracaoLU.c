#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fatoracaoLU.h"
#include "matriz.h"
#include "vetor.h"

double*** fatoracaoLU( int ordem, double** A ){
    double*** matrizLU = (double***) malloc( sizeof( double** ) * 2 );
    /*LU As matrizes L e U tem como inicial uma matriz Identidade.
    para ja existirem elementos nela, mas todos sao alterados e nao alteram
    o resultado.*/
    double** L = createIdentityMatrix(ordem);
    double** U = createIdentityMatrix(ordem);

    double somatorio;

    for(int i = 0; i < ordem; i++)
    {
        for(int j = 0; j < ordem; j++)
        {
            if(i == j || i < j)
            {
                somatorio = 0;

                for(int k = 0; k < i; k++)
                {
                    somatorio = somatorio + (U[k][j] * L[i][k]);
                }
                
                U[i][j] = A[i][j] - somatorio;
            }
            else if(i != j && i > j)
            {
                somatorio = 0;

                for(int k = 0; k < j; k++)
                {
                    somatorio = somatorio + (U[k][j] * L[i][k]);
                }

                L[i][j] = (1 * (A[i][j] - somatorio)) / U[j][j];
            }
        }
    }

    matrizLU[0] = L;
    matrizLU[1] = U;
    return matrizLU;
}

//SUBSTITUICAO
double* substituicaoParaFrente(int ordem, double** matrizA, double* matrizB)
{
    double* vetorX = criarVetor(ordem); //cria o vetor solucao
    double somatoria;

    for (int i = 0; i < ordem; i++)
    {
        somatoria = 0;

        for (int j = 0; j < i; j++)
        {
            //testa se nao eh a primeira iteracao
            if(i >= 1) somatoria += (matrizA[i][j] * vetorX[j]); //nao sendo a primeira iteracao sabe-se que ja existem valores no vetorX,entao multiplica-se o elemento pelo respectivo valor da sua variavel encontrado no vetorX
        }
        //faz-se o valor da matriz B menos a somatoria dividido pelo elemento que multiplica a variavel que queremos encontrar
        vetorX[i] = (matrizB[i] - somatoria) / matrizA[i][i];
    }
    return vetorX;
}

double* substituicaoParaTras(int ordem, double** matrizA, double* matrizB)
{
    double* vetorX = criarVetor(ordem);//cria o vetor solucao
    double somatoria;

    //roda a matriz comecando do final
    for (int i = ordem - 1; i >= 0; i--)
    {
        somatoria = 0;
        for (int j = ordem - 1; j > i; j--)
        {
            //testa se nao eh a primeira iteracao
            if(i <= ordem-2) somatoria += (matrizA[i][j] * vetorX[j]); //nao sendo a primeira iteracao sabe-se que ja existem valores no vetorX, entao multiplica-se o elemento pelo respectivo valor da sua variavel encontrado no vetorX
        }

        //faz-se o valor da matriz B menos a somatoria dividido pelo elemento que multiplica a variavel que queremos encontrar
        vetorX[i] = (matrizB[i] - somatoria) / matrizA[i][i];
    }

    return vetorX;
}

void metodoLU(Sistema* psist)
{
    double*** LU;
    double** L;
    double** U;
    double* Y;
    double* X;

    LU = fatoracaoLU(psist->ordem, psist->matrizA);
    L = LU[0];
    U = LU[1];

    //Continuacao da Fatoracao LU:
    //LY= B, substituicao para frente.
    Y = substituicaoParaFrente(psist->ordem, L, psist->matrizB);
    //UX = Y, substituicao para tras.
    X = substituicaoParaTras(psist->ordem, U, Y);
    
    psist->solucao = X;
    liberarMatriz(psist->ordem, &L);
    liberarMatriz(psist->ordem, &U);
    liberarVetor(&Y);
    free(LU);
}
