MIPSasm2mc: MIPSasm2mc.o parser.o auxtool.o
	g++ -Wall -Wextra -pedantic -o MIPSasm2mc MIPSasm2mc.o parser.o auxtool.o

MIPSasm2mc.o: MIPSasm2mc.cpp
	g++ -c -std=c++14 -g MIPSasm2mc.cpp

parser.o: parser.cpp parser.hpp
	g++ -c -std=c++14 -g parser.cpp parser.hpp

auxtool.o: auxtool.cpp auxtool.hpp
	g++ -c -std=c++14 -g auxtool.cpp auxtool.hpp

clean:
	rm MIPSasm2mc MIPSasm2mc.o parser.o auxtool.o
