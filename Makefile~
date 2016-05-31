all: fpu
    
fpu: main.o Model.o Tests.o
	g++ main.o Model.o Tests.o -o fpu

main.o: main.cpp
	g++ -c main.cpp

Model.o: Model.cpp
	g++ -c Model.cpp

Tests.o: Tests.cpp
	g++ -c Tests.cpp


clean:
	rm -rf *o fpu
