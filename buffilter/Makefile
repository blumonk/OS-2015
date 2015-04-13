all: buffilter.c
	gcc -std=c99 -fPIC -Wall -o buffilter buffilter.c -L ../lib -lbufio -lhelpers -Wl,-rpath=../lib -I ../lib
clean:
	rm buffilter
test1:
	echo -ne "/bin/sh\n/blablabla\n/bin/cat\n" | ./buffilter tar cf /tmp/filter.tar
test2:
	/bin/echo -ne "/bin\n/blablabla\n\n\n/bin/cat\n\n\n" | ./buffilter tar cf /tmp/buffilter.tar
