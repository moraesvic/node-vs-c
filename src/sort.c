#include "sort.h"

void selection_sort(const int n, int v[]){
    if(n == 0)
        return;
    int i, j, temp, min, minIndex;
    for(j=0; j < n; j++){
        min = v[j];
        minIndex = j;
        for(i=j+1; i < n; i++)
            if(min > v[i]){
                min = v[i];
                minIndex = i;
            }
        temp = v[j];
        v[j] = v[minIndex];
        v[minIndex] = temp;
    }
}

void bubble_sort(const int n, int v[]){
    if(n < 2)
        return;
    int i, temp, haAlteracao = 1;
    while(haAlteracao){
        haAlteracao = 0;
        for(i=1; i < n; i++)
            if(v[i-1] > v[i]){
                temp = v[i-1];
                v[i-1] = v[i];
                v[i] = temp;
                haAlteracao = 1;
            }
    }
}

void insert_sort(const int n, int v[]){
    int i, j, temp;
    for(j = 1; j < n; j++){
        temp = v[j];
        for(i= j-1; i >= 0 && v[i] > temp; i--)
            v[i+1] = v[i];
        v[i+1] = temp;
    }
}

void intercala(const int p, const int q, const int r, int v[]){
    int i, j, k, *w;
    w = malloc ((r-p) * sizeof (int));
    for(i = p, j = q, k = 0; i < q && j < r; )
        if(v[i] <= v[j])
            w[k++] = v[i++];
        else 
            w[k++] = v[j++];
    for(; i < q; ) w[k++] = v[i++];
    for(; j < r; ) w[k++] = v[j++];
    for(i = p; i < r; i++) v[i] = w[i-p];
    free(w);
}

void merge_sort_2(const int p, const int r, int v[]){
    if(p >= r-1)
        return;
    int q = (p + r)/2;
    merge_sort_2(p, q, v);
    merge_sort_2(q, r, v);
    intercala(p, q, r, v);
}

void merge_sort(const int n, int v[]){
    /* Apenas um wrapper para manter o protótipo da função */
    merge_sort_2(0, n, v);
}

int separa(const int p, const int r, int v[]){
    /* Recebe um vetor v[p..r] com p <= r. Rearranja os
     * elementos do vetor e devolve j em p..r tal que
     * v[p..j-1] <= v[j] < v[j+1..r]. */

    const int pivo = v[r];
    int j, k, temp;

    for(j = p, k = p; k < r; ++k){
        if(v[k] <= pivo){
            temp = v[j];
            v[j] = v[k];
            v[k] = temp;
            ++j;
        }
    }
    v[r] = v[j];
    v[j] = pivo;

    return j;
}

void quick_sort_2(const int p, const int r, int v[]){
    if(p >= r)
        return;    
    int j;
    j = separa(p, r, v);
    quick_sort_2(p, j-1, v);
    quick_sort_2(j+1, r, v);
}

void quick_sort(const int n, int v[]){
    /* Wrapper */
    quick_sort_2(0, n-1, v);
}

void count_sort(const int n, const int r_max, const int r_min, int v[]){
    /* O range ou gama de valores de entrada varia nos inteiros de 
    [r_min, r_max], incluindo extremidades.
    */
    const int range = r_max - r_min;
    /* caso a gama de valores seja muito ampla, vamos interromper
    *  a execução para evitar que o programa crashe */
    if(range > MAX_COUNT_SORT) return;
    int *aux = calloc(range, sizeof(int));
    int i, j;
    for(i = 0; i < n; i++)
        ++aux[ v[i] - r_min];
    
    j = 0;
    for(i = 0; i < range; i++)
        while(aux[i]-- > 0)
            v[j++] = i;
    free(aux);
}

void concatena_array(const int n, const int p,
                     int u[], int v[], int w[]){
    /* faz u = v conc w
    *  p é o tamanho do array v
    *  n é o tamanho final do array u, portanto
    *  q (tamanho de w) = n - p */
    int i;
    for(i = 0; i < p; i++) u[i] = v[i];
    for(i = 0; i < n-p; i++) u[p+1] = w[i];
}

void radix_sort(const int n, int v[]){
    int i, max, dig, size_aux0, size_aux1;
    int *aux0 = malloc(n * sizeof(int));
    int *aux1 = malloc(n * sizeof(int));
    /* determinar o maior número no vetor */
    max = v[0];
    for(i = 1; i < n; i++)
        if(v[i] > max) max = v[i];
    /* tiramos 1 para não dar overflow */
    for(i = 1; (1 << i) < max && i < 8*sizeof(int) - 1; i++);
    const int max_dig = i;
    /* * * * * * * */

    for(dig = 0; dig < max_dig; dig++){
        size_aux0 = 0;
        size_aux1 = 0;
        for(i = 0; i < n; i++){
            if( v[i] & (1 << dig) )
                aux1[size_aux1++] = v[i];
            else
                aux0[size_aux0++] = v[i];
        }
        concatena_array(n, size_aux0, v, aux0, aux1);
    }
    free(aux0);
    free(aux1);
}