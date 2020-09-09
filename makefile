all: Polynomial.h ex6_q2.cpp
	g++ ex6_q2.cpp -o main
all-GDB: Polynomial.h ex6_q2.cpp
	g++ -g ex6_q2.cpp -o main
