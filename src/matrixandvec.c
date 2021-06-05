#include "matrixandvec.h"

/* ARRAYS */

void zera_array(const int n, int v[]){
    int i;
    for(i = 0; i < n; i++) v[i] = 0;
}

void print_array(const int n, int v[]){
    int i;
    for(i=0; i<n; i++)
        printf("%d ", v[i]);
    printf("\n");
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

int * cria_copia_array(const int n, int v[]){
    int i, *u;
    u = calloc(n, sizeof(int));
    for(i=0; i<n; i++) u[i] = v[i];
    return u;
}

void copia_array(const int n, int u[], int v[]){
    /* Faz u = v */
    int i;
    for(i = 0; i < n; i++) u[i] = v[i];
}

int arrays_iguais(const int n, int u[], int v[]){
    /* retorna 1 se os arrays são iguais
    e 0 se os arrays diferem quanto a pelo menos
    1 elemento */
    int i;
    for(i=0; i<n; i++)
        if(u[i] != v[i]) return 0;
    return 1;
}

/* MATRIZES */

int ** alocaMatriz(int lin, int col){
	int i;
	int ** mat = calloc(lin, sizeof(int*));
	for(i=0;i<lin;i++) mat[i] = calloc(col,sizeof(int));
	return mat;
}

void liberaMatriz(void ** mat, int lin){
	int i;
	if(mat!=NULL){
		for(i=0;i<lin;i++) free(mat[i]);
		free(mat);
	}
}

int ** cpMatriz(int ** mat, int lin, int col){
	int i, j, **newMat = alocaMatriz(lin,col);
	for(i=0;i<lin;i++)
		for(j=0;j<col;j++)
			newMat[i][j] = mat[i][j];
	return newMat;
}

void printMatriz(int ** mat, int lin, int col){
	int i, j;
	for(i=0;i<lin;i++){
		for(j=0;j<col;j++)
			printf("%3d", mat[i][j]);
		printf("\n");
	}
}

void printMatrizChar(int ** mat, int lin, int col){
	int i, j;
	for(i=0;i<lin;i++){
		for(j=0;j<col;j++)
			if(mat[i][j] == 0)       printf(".");
            else if(mat[i][j] == -1) printf("#");
			else                     printf("%c",mat[i][j]);
		printf("\n");
	}
}

/* VETORES */

Vetor_Int * Vetor_Int_cria(const int n, const int base_size){
    Vetor_Int * vec = malloc(sizeof(Vetor_Int));
    vec->v = calloc(n, sizeof(int));
    vec->max = n;
    vec->topo = 0;
    vec->base_size = base_size;
    return vec;
}

void Vetor_Int_del(Vetor_Int * vec){
    free(vec->v);
    free(vec);
}

void Vetor_Int_extend(Vetor_Int * vec){
    int i;
    int * v_novo = calloc(vec->max + vec->base_size, sizeof(int));
    for(i = 0; i < vec->max; i++)
        v_novo[i] = vec->v[i];
    free(vec->v);
    vec->v = v_novo;
    vec->max += vec->base_size;
}

void Vetor_Int_add(Vetor_Int * vec, const int novo){
    if(vec->topo < vec->max)
        vec->v[vec->topo++] = novo;
    else {
        Vetor_Int_extend(vec);
        vec->v[vec->topo++] = novo;
    }
}

void Vetor_Int_to_array(Vetor_Int ** lista, const int len, int *v){
    /* recebe uma lista com len vetores (arrays extensíveis)
    *  e copia-os para o array */
    int i, j, cont = 0;
    for(i = 0; i < len; i++)
        for(j = 0; j < lista[i]->topo; j++)
            v[cont++] = lista[i]->v[j];
}