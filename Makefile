all: main.o Model.o
	g++ main.o Model.o -o fpu

main.o: main.cpp
	g++ -c main.cpp

Model.o: Model.cpp
	g++ -c Model.cpp


clean:
	rm -rf *o fpu
