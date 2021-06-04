cc=cc
# CFLAGS=-fopenacc
# LDFLAGS=-fopenacc
CFLAGS=-ta=tesla,cc60
LDFLAGS=
all: cpi_openacc 

cpi_openacc:
	${cc} ${CFLAGS} -o cpi_openacc cpi_openacc.c gettime.c ${LDFLAGS}

clean:
	rm -fd cpi_openacc cpi_openacc.o gettime.o
