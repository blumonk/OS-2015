all:
	gcc -std=c99 -fPIC -Wall -o filter filter.c -L ../lib -lhelpers -Wl,-rpath=../lib -I ../lib
clean:
	rm filter
test1:
	/bin/echo -ne "/bin/sh\n/blablabla\n/bin/cat" | ./filter /
test2:
	/bin/echo -ne "/bin\n/blablabla\n\n\n/bin/cat\n\n\n" | ./filter tar cf /tmp/filter.tar
