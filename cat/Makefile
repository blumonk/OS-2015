all: cat.c
	gcc -fPIC -Wall -o cat cat.c -L ../lib -lhelpers -Wl,-rpath=../lib -I ../lib
clean:
	rm cat
