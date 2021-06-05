/*
 *
 * A nomenclatura estabelecida é:
 * Array:  vetor unidimensional
 * Matriz: vetor multidimensional
 * Vetor:  vetor unidimensional extensível, dinamicamente alocado
 * 
 */

#ifndef MATRIXANDVEC_H
#define MATRIXANDVEC_H

#include <stdio.h>
#include <stdlib.h>

/* ARRAYS */

void zera_array(const int n, int v[]);

void print_array(const int n, int v[]);

void concatena_array(const int n, const int p,
                     int u[], int v[], int w[]);

int * cria_copia_array(const int n, int v[]);

void copia_array(const int n, int u[], int v[]);

int arrays_iguais(const int n, int u[], int v[]);

/* MATRIZES */

int ** alocaMatriz(int lin, int col);

void liberaMatriz(void ** mat, int lin);

void printMatriz(int ** mat, int lin, int col);

void printMatrizChar(int ** mat, int lin, int col);

/* VETORES */

typedef struct {
    int *v;
    int max;
    int topo;
    int base_size;
} Vetor_Int;

Vetor_Int * Vetor_Int_cria(const int n, const int base_size);

void Vetor_Int_del(Vetor_Int * vec);

void Vetor_Int_extend(Vetor_Int * vec);

void Vetor_Int_add(Vetor_Int * vec, const int novo);

void Vetor_Int_to_array(Vetor_Int ** lista, const int len, int *v);


#endif /* MATRIXANDVEC_H */