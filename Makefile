assemble: main.o mipsAssembler.o
	g++ main.o mipsAssembler.o -o assemble

main.o: main.cpp
	g++ -c main.cpp

mipsAssembler.o: mipsAssembler.cpp mipsAssembler.h
	g++ -c mipsAssembler.cpp

clean:
	rm *.o assemble
