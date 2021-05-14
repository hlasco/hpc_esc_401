<<<<<<< HEAD
CFLAGS=-O3 -ffast-math -fopenmp -mavx2
CC=cc

all: serial omp_race omp_atomic omp_critical omp_reduction
serial: serial.c
omp_race: omp_race.c
omp_atomic: omp_atomic.c
omp_critical: omp_critical.c
omp_reduction: omp_reduction.c
clean: 
	rm serial omp_race omp_atomic omp_critical omp_reduction
=======
CFLAGS=-Xpreprocessor -fopenmp -O3 -ffast-math -fopenmp -lomp -mavx2
CC=cc

all: serial omp_race 
serial: serial.c
omp_race: omp_race.c
clean: 
	rm serial omp_race
>>>>>>> 39f62edb8369bb4f178839c054f4c78ad7a89ede

