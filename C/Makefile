FLAGS_DEV=-Wall -g -pg
FLAGS_PROD=-Wall -O3
FLAGS_DYNLIB=-shared -fpic

SRC=shuffle_and_sort.c

make: $(SRC)
	gcc $(FLAGS_PROD) $(FLAGS_DYNLIB) $(SRC) -o shuffle_and_sort.so