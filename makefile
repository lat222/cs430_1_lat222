CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -c -lpthread $(DEBUG)
LFLAGS = -Wall -std=c99 -lpthread $(DEBUG)

ppmrw : mainprog.o
	$(CC) $(LFLAGS) mainprog.o -o ppmrw

mainprog.o : mainprog.c
	$(CC) $(CFLAGS) mainprog.c


clean:
	\rm *.o run