#include <stdlib.h>
#include <limits.h>
#include <time.h>

/* For generating random array */

void time_seed()
{
    srand(time(NULL));
}

void set_seed(const int seed)
{
    srand(seed);
}

unsigned randint_mod(const int mod)
{
    unsigned end, r;
    if ((mod - 1) == INT_MAX) {
        return rand();
    }

    end = INT_MAX / mod;
    end *= mod;
    do {
        r = rand();
    }
    while(r >= end);

    return r % mod;
}

void rand_int_array(const int n, const int r_max, int v[])
{
    int i;
    for(i = 0; i < n; i++) {
        v[i] = randint_mod(r_max);
    }
}

/* For sorting */

int separate(const int p, const int r, int v[]){
    /**
     * Receives a vector v[p..r] with p <= r. Rearranges the elements
     * in the vector and returns j such that v[p..j-1] <= v[j] < v[j+1..r]
     */

    const int pivot = v[r];
    int j, k, temp;

    for(j = p, k = p; k < r; ++k){
        if(v[k] <= pivot){
            temp = v[j];
            v[j] = v[k];
            v[k] = temp;
            ++j;
        }
    }
    v[r] = v[j];
    v[j] = pivot;

    return j;
}

void quick_sort_2(const int p, const int r, int v[])
{
    if(p >= r)
        return;
    int j;
    j = separate(p, r, v);
    quick_sort_2(p, j-1, v);
    quick_sort_2(j+1, r, v);
}

void quick_sort(const int n, int v[])
{
    /* Wrapper */
    quick_sort_2(0, n-1, v);
}

/* API */

void shuffle_and_sort(int sz, int * v, int max)
{
    rand_int_array(sz, max, v);
    quick_sort(sz, v);
}