test:subroutines.o main.cpp
	g++ -g subroutines.o main.cpp -o test
subroutines.o:fiboheap.o id_hash.o profile.o subroutines.cpp
	g++ -g -c fiboheap.o id_hash.o profile.o subroutines.cpp -o subroutines.o
fiboheap.o:fiboheap.cpp
	g++ -g -c -lm fiboheap.cpp -o fiboheap.o
id_hash.o:id_hash.cpp
	g++ -g -c id_hash.cpp -o id_hash.o
profile.o:profile.cpp
	g++ -g -c profile.cpp -o profile.o
clean:
	del *.o
clear:
	del *.o
	del *.exe