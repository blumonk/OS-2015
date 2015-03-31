all: helpers.c helpers.h
	gcc -std=c99 -fPIC -Wall -shared helpers.c -o libhelpers.so
clean:
	rm -f *.so
