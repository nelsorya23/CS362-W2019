CFLAGS= -Wall -fpic -coverage -lm -std=c99

all: run

run: testme
	./testme

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out 
