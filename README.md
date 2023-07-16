# Sistema Linear - fatoração LU
Trabalho de Métodos Numéricos 2023.1 UFRRJ/IM.

## Executar
### Com paralelismo
```
 gcc -o trabalho trabalhopratico.c matriz.o vetor.o fatoracaoLU.o -fopenmp
```
ou
```
make compile-paralelismo
```
- executar
```
 time ./trabalho
```
ou
```
make run
```
### Sem paralelismo
- compilar
```
gcc -o trabalho trabalhopratico.c matriz.o vetor.o fatoracaoLU.o
```
ou
```
make compile
```
- executar
```
 time ./trabalho
```
ou 
```
make run
```