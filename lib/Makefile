BUFIO = bufio.c bufio.h 
HELPERS = helpers.c helpers.h
CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -fPIC -shared $(DEBUG)

all: libbufio.so libhelpers.so

libbufio.so: $(BUFIO)
	$(CC) $(CFLAGS) $(BUFIO) -o libbufio.so
libhelpers.so: $(HELPERS)
	$(CC) $(CFLAGS) $(HELPERS) -o libhelpers.so
clean:
	rm -f *.so
