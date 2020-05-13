
sharedlib: httplib.o
	gcc -shared -ohttplib.so httplib.o -lbsd


object: httplib.c httplib.h
	gcc -c -fPIC -ohttplib.o httplib.c -lbsd