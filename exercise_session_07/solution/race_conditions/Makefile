CFLAGS=-Xpreprocessor -fopenmp -O3 -ffast-math -fopenmp -lomp -mavx2
CC=cc

all: serial omp_race 
serial: serial.c
omp_race: omp_race.c
clean: 
	rm serial omp_race

