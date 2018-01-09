all:	anymirror

anymirror:
	cc -I/usr/local/include -c -o anymirror.o anymirror.c
	cc -L/usr/local/lib -o anymirror  anymirror.o -lkcgi -lz
