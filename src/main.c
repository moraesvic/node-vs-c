#include <stdio.h>
#include "my_random.h"
#include "matrixandvec.h"
#include "sort.h"

#define MAX_N 0xffffffff

int main(int argc, char ** argv){
  if(argc != 2){
    fprintf(stderr, "Usage: randvecsort array_length\n");
    return -1;
  }

  const int n  = atoi(argv[1]);
  int *v = calloc(n, sizeof(int));
  sorteia_array(n, MAX_N, v);
  insert_sort(n, v);
  print_array(n, v);
  return 0;
}