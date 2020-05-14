
sharedlib: httplib.o
	gcc -g -shared -ohttplib.so httplib.o -lbsd


object: httplib.c httplib.h
	gcc -g -c -fPIC -ohttplib.o httplib.c -lbsd