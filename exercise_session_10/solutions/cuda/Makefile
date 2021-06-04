cc=nvcc
CFLAGS=--gpu-architecture=sm_60

all: cpi_cuda cpi_cuda_loop 

cpi_cuda:
	${cc} ${CFLAGS} -o cpi_cuda cpi_cuda.cu

cpi_cuda_loop:
	${cc} ${CFLAGS} -o cpi_cuda_loop cpi_cuda_loop.cu

clean:
	rm -fd cpi_cuda cpi_cuda_loop
