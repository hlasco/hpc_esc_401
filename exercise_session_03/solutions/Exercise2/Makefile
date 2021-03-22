CC=cc

all: sum_O0 sum_O1 sum_O2 sum_O3 sum_O3_math_mavx2 sum_Ofast_math_mavx2 sum_omp

sum_O0: sum.c gettime.h
	${CC} -O0 -o sum_O0 sum.c gettime.c

sum_O1: sum.c gettime.h
	${CC} -O1 -o sum_O1 sum.c gettime.c

sum_O2: sum.c gettime.h
	${CC} -O2 -o sum_O2 sum.c gettime.c

sum_O3: sum.c gettime.h
	${CC} -O3 -o sum_O3 sum.c gettime.c

sum_O3_math_mavx2: sum.c gettime.h
	${CC} -O3 -ffast-math -o mavx2 -o sum_O3_math_mavx2 sum.c gettime.c

sum_Ofast_math_mavx2: sum.c gettime.h
	${CC} -Ofast -ffast-math -mavx2 -o sum_Ofast_math_mavx2 sum.c gettime.c

sum_omp: sum_omp.c gettime.h
	${CC} -fopenmp -O3 -ffast-math -mavx2 -o sum_omp sum_omp.c gettime.c

clean: 
	rm -f sum_O0 sum_O1 sum_O2 sum_O3 sum_O3_math_mavx2 sum_Ofast_math_mavx sum_omp2
