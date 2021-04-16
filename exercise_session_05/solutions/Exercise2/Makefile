CC=CC
CFLAGS= -g -ffast-math -O3 -mavx2
all: forces.o init.o main.o main

forces.o: forces.cpp particles.h forces.h
	${CC} ${CFLAGS} -c -o forces.o forces.cpp
init.o: init_conditions.cpp particles.h init_conditions.h
	${CC} ${CFLAGS} -c -o init.o init_conditions.cpp
main.o: main.cpp particles.h
	${CC} ${CFLAGS} -c -o main.o main.cpp
main: main.o forces.o init.o  
	${CC} ${CFLAGS} -o main main.o forces.o init.o
clean: 
	rm -f forces.o init.o main.o main
