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

int ceil_div(int a, int b){
    /* recebe os inteiros a e b e devolve o teto da divisão a/b */
    double c = (double)a / (double)b;
    return (int)c + 1;
}

int floor_div(int a, int b){
    /* recebe os inteiros a e b e devolve o chão da divisão a/b */
    double c = (double)a / (double)b;
    return (int)c;
}

int overflow_mult(int a, int b){
    int c = a * b;
    if(c / a == b) return 0;
    else           return 1;
}

void bucket_sort(const int n, const int r_max, const int r_min, int v[]){
    /* Utiliza insert_sort como auxiliar */
    const int range = r_max - r_min;
    const int n_urnas = ceil_div(n, BUCKET_AVG_SIZE);
    int tam;
    if(overflow_mult(BUCKET_AVG_SIZE, range))
        tam = BUCKET_AVG_SIZE * ceil_div(range, n);
    else
        tam = ceil_div(BUCKET_AVG_SIZE * range, n);
    int i, key;
    /* criação das urnas */
    /* usei aqui uma versão rudimentar do que depois aprendemos
    como listas ligadas */
    Vetor_Int ** urnas = malloc(n_urnas * sizeof(Vetor_Int*));
    for(i = 0; i < n_urnas; i++)
        urnas[i] = Vetor_Int_cria(BUCKET_AVG_SIZE, BUCKET_AVG_SIZE);
    /* distribuição dos elementos em urnas / baldes */
    for(i = 0; i < n; i++){
        key = floor_div((v[i] - r_min), tam);
        Vetor_Int_add(urnas[key], v[i]);
    }
    /* organização interna das urnas */
    for(i = 0; i < n_urnas; i++)
        insert_sort(urnas[i]->topo, urnas[i]->v);
    /* concatenação das urnas */
    Vetor_Int_to_array(urnas, n_urnas, v);
    for(i = 0; i < n_urnas; i++)
        Vetor_Int_del(urnas[i]);
    free(urnas);
}