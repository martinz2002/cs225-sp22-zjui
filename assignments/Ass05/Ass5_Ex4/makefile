all: listkmp.o test
test: test.cpp listkmp.o listkmp.h
	g++ test.cpp listkmp.o -g -o test
listkmp.o: listkmp.cpp listkmp.h
	g++ -c listkmp.cpp -g -o listkmp.o