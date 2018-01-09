all:	redmirror

redmirror:
	cc -I/usr/local/include -c -o redmirror.o redmirror.c
	cc -L/usr/local/lib -o redmirror  redmirror.o -lkcgi -lz
	cc -I/usr/local/include -c -o test.o test.c
	cc -L/usr/local/lib -o test  test.o -lkcgi -lz

install:
	doas cp redmirror /var/www/cgi-bin
	doas cp test /var/www/cgi-bin

clean:
	rm redmirror redmirror.o
