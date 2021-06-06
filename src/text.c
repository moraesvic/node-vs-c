#include <stdio.h>
#include <stdlib.h>
#include "my_random.h"
#include "sort.h"

#define MAX_N 0xffffffff
#define BASE  10

/* */

void print_array(const int n, int v[]){
    int i;
    for(i=0; i<n; i++)
        printf("%d ", v[i]);
    printf("\n");
}

void print_usage(){
  fprintf(stderr, "Usage: \"./randvecsort array_length\"\n");
  fprintf(stderr, "  array_length is how long array is\n\n");
}

int main(int argc, char ** argv){
  int n, *v;

  if(argc != 2){
    print_usage();
    return -1;
  }
  
  const char * start_ch = argv[3];
  char * endptr;
  n = strtol(argv[1], &endptr, 10);
  if(endptr == start_ch){
    fprintf(stderr, "Argument array_length received a bad parameter.");
    return -1;
  }

  v = calloc(n, sizeof(int));
  
  sorteia_array(n, MAX_N, v);
  quick_sort(n, v);
  print_array(n, v);

  return 0;
}