#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include "matrixandvec.h"

#define MAX_COUNT_SORT 0xffffffff
#define BUCKET_AVG_SIZE 8

void selection_sort(const int n, int v[]);

void bubble_sort(const int n, int v[]);

void insert_sort_2(const int n, int v[]);

void insert_sort(const int n, int v[]);

void intercala(const int p, const int q, const int r, int v[]);

void merge_sort_2(const int p, const int r, int v[]);

void merge_sort(const int n, int v[]);

int separa(const int p, const int r, int v[]);

void quick_sort_2(const int p, const int r, int v[]);

void quick_sort(const int n, int v[]);

void count_sort(const int n, const int r_max, const int r_min, int v[]);

void radix_sort(const int n, int v[]);

/* */

int ceil_div(int a, int b);

int floor_div(int a, int b);

int overflow_mult(int a, int b);

void bucket_sort(const int n, const int r_max, const int r_min, int v[]);

#endif /* SORT_H */