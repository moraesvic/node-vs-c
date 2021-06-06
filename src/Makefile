FLAGS_DEV=-Wall -g -pg
FLAGS_PROD=-Wall -O3

make: my_random.o sort.o binary.c text.c
	gcc $(FLAGS_PROD) my_random.o sort.o binary.c -o ../bin/binary
	gcc $(FLAGS_PROD) my_random.o sort.o text.c -o ../bin/text

binary:  my_random.o sort.o binary.c
	gcc $(FLAGS_PROD) my_random.o sort.o binary.c -o ../bin/binary

text:  my_random.o sort.o text.c
	gcc $(FLAGS_PROD) my_random.o sort.o text.c -o ../bin/text

my_random.o: my_random.c my_random.h
	gcc $(FLAGS_PROD) -c my_random.c -o my_random.o

sort.o: sort.c sort.h
	gcc $(FLAGS_PROD) -c sort.c -o sort.o

clean:
	rm my_random.o sort.o