FLAGS_DEV=-Wall -g -pg
FLAGS_PROD=-Wall -O3

make: matrixandvec.o my_random.o sort.o main.c
	gcc $(FLAGS_PROD) matrixandvec.o my_random.o sort.o main.c -o ../bin/main

matrixandvec.o: matrixandvec.c matrixandvec.h
	gcc $(FLAGS_PROD) -c matrixandvec.c -o matrixandvec.o

my_random.o: my_random.c my_random.h
	gcc $(FLAGS_PROD) -c my_random.c -o my_random.o

sort.o: sort.c sort.h
	gcc $(FLAGS_PROD) -c sort.c -o sort.o

clean:
	rm matrixandvec.o my_random.o sort.o