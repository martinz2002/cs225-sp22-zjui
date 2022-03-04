all: blist.o test

test: test.cpp blist.o blist.h
	g++ test.cpp blist.o -g -o test
blist.o: blist.cpp blist.h
	g++ -c blist.cpp -g -o blist.o