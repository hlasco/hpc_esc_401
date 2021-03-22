CFLAGS=-O3 -ffast-math -mavx2
CC=cc

all: gettime.o cpi.o cpi cpi_mpi.o cpi_mpi

gettime.o: gettime.c gettime.h

cpi.o: cpi.c gettime.h

cpi: cpi.o gettime.o 

cpi_mpi.o: cpi_mpi.c gettime.h

cpi_mpi: cpi_mpi.o gettime.o

clean: 
	rm -f cpi cpi.o gettime.o cpi_mpi.o cpi_mpi
