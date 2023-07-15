#ifndef MATRIZ_H
#define MATRIZ_H

//CRIAR E LIBERAR MATRIZ
double** criarMatriz(int ordem);
double** createSquareMatrix(int size);
double** createMatrix(int rows, int columns);
void liberarMatriz(int ordem, double*** matriz);

//PREENCHER MATRIZ
double** preencherMatriz(int ordem);

//IMPRIMIR MATRIZ
void imprimirMatriz(int ordem, double** matriz);

//CRIA MATRIZ IDENTIDADE
double** createIdentityMatrix( int size );

double determinante(int ordem, double** matriz);
double teoremaLaplace(int ordem, double** matriz);

int submatrizesPrincipaisNaoSingulares(int ordem, double** matriz);

#endif
