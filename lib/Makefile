OBJS = bufio.c bufio.h 
CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -fPIC -shared $(DEBUG)

all: libbufio.so

libbufio.so: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o libbufio.so
clean:
	rm -f *.so
