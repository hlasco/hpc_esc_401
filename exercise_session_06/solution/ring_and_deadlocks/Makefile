CFLAGS=-O3 -ffast-math -mavx2
CC=mpicc

all: ring_deadlock ring_split ring_nonblocking ring_cartesian 
ring_deadlock: ring_deadlock.c
ring_split: ring_split.c
ring_nonblocking: ring_nonblocking.c
ring_cartesian: ring_cartesian.c
clean: 
	rm -f ring_deadlock ring_split ring_nonblocking ring_cartesian

