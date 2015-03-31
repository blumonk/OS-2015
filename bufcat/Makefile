OBJS = bufcat.c
CC = gcc
DEBUG = -g
CFLAGS = -Wall -std=c99 -fPIC $(DEBUG)
LIB_PATH = -L ../lib -lbufio -Wl,-rpath=../lib -I ../lib

all: bufcat

bufcat: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_PATH) -o bufcat

clean:
	rm bufcat
