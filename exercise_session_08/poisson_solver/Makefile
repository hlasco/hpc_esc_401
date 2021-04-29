CFLAGS=-O3 -ffast-math -mavx2 -std=c++11
CC=g++

all: init.o io.o jacobi.o main.o main
init.o: init.cpp init.h
	${CC} ${CFLAGS} -c -o init.o init.cpp
io.o: io.cpp io.h
	${CC} ${CFLAGS} -c -o io.o io.cpp
jacobi.o: jacobi.cpp jacobi.h
	${CC} ${CFLAGS} -c -o jacobi.o jacobi.cpp
main.o: main.cpp jacobi.o io.o init.o
	${CC} ${CFLAGS} -c -o main.o main.cpp
main:
	${CC} ${CFLAGS} -o main main.o init.o io.o jacobi.o 
clean:
	rm -f main main.o init.o io.o jacobi.o
