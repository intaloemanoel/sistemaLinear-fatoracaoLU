run: time ./trabalho

compile: trabalhopratico.c matriz.o vetor.o fatoracaoLU.o
	gcc -o trabalho trabalhopratico.c matriz.o vetor.o fatoracaoLU.o

compile-paralelismo: trabalhopratico.c matriz.o vetor.o fatoracaoLU.o
	gcc -o trabalho trabalhopratico.c matriz.o vetor.o fatoracaoLU.o -fopenmp

matriz.o: matriz.c
	gcc -c -o matriz.o matriz.c

vetor.o: vetor.c
	gcc -c -o vetor.o vetor.c

fatoracaoLU.o: fatoracaoLU.c
	gcc -c -o fatoracaoLU.o fatoracaoLU.c
