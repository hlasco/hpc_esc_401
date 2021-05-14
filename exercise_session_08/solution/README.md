## Exercise 1
Once connected to the VM, update the package list and install cowsay:
```console
ubuntu@172.23.80.210:-$ sudo apt update -q
...
ubuntu@172.23.80.210:-$ sudo apt install -q cowsay
...
ubuntu@172.23.80.210:-$ cowsay 'Alligators are better than cows'
 _________________________________
< Alligators are better than cows >
 ---------------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
```

Now install g++ and make:

```console
ubuntu@172.23.80.210:-$ sudo apt install -q g++ make
...
ubuntu@172.23.80.210:-$ g++
g++: fatal error: no input files
compilation terminated.
ubuntu@172.23.80.210:-$ make
make: *** No targets specified and no makefile found.  Stop.
```
You can now compile the poisson solver. To visualize the outputs:


```console
ubuntu@172.23.80.210:-$ sudo apt install -q python-pip
...
ubuntu@172.23.80.210:-$ pip install numpy
...
ubuntu@172.23.80.210:-$ pip install matplotlib
...
ubuntu@172.23.80.210:-$ pip install tk
...
ubuntu@172.23.80.210:-$ sudo apt install -q python-tk
...
```


## Exercise 2
Use the following Dockerfile to create a container for the Poisson solver:
```dockerfile
# Use the official image as a parent image.
FROM ubuntu:trusty

# Install dependencies
RUN apt-get update -q && \
    apt-get install -y make g++

# Copy the file from your host to your current location.
COPY . /poisson

# Compile the code
RUN cd /poisson && make

# Work from the Output directory
WORKDIR /poisson

# Run the hydro code within the container.
CMD ./main
```
Now run the build command:
```console
hlasco@hdl:~/hpc_esc_401/exercise_session_08/poisson_solver$ docker build --tag poisson .
Sending build context to Docker daemon  30.72kB
Step 1/6 : FROM ubuntu:trusty
 ---> 13b66b487594
Step 2/6 : RUN apt-get update -q &&     apt-get install -y make g++
 ---> Using cache
 ---> 6f120133521c
Step 3/6 : COPY . /poisson
 ---> b71095ee3987
Step 4/6 : RUN cd /poisson && make
 ---> Running in 9e228f7997b5
g++ -O3 -ffast-math -mavx2 -std=c++11 -c -o init.o init.cpp
g++ -O3 -ffast-math -mavx2 -std=c++11 -c -o io.o io.cpp
g++ -O3 -ffast-math -mavx2 -std=c++11 -c -o jacobi.o jacobi.cpp
g++ -O3 -ffast-math -mavx2 -std=c++11 -c -o main.o main.cpp
g++ -O3 -ffast-math -mavx2 -std=c++11 -o main main.o init.o io.o jacobi.o
Removing intermediate container 9e228f7997b5
 ---> 1aa1be13156f
Step 5/6 : WORKDIR /poisson
 ---> Running in d2611749bd0d
Removing intermediate container d2611749bd0d
 ---> ffbef84480ed
Step 6/6 : CMD ./main
 ---> Running in 45e473f785e6
Removing intermediate container 45e473f785e6
 ---> b343fa837660
Successfully built b343fa837660
Successfully tagged poisson:latest
```

Push the container to Docker Hub:
```console
hlasco@hdl:~/hpc_esc_401/exercise_session_08/poisson_solver$ docker tag poisson:latest hlasco/poisson:latest
hlasco@hdl:~/hpc_esc_401/exercise_session_08/poisson_solver$ docker push hlasco/poisson:latest
```

Finaly run the container with the -v flag to retreive the outputs:
```console
hlasco@hdl:~/hpc_esc_401/exercise_session_08/poisson_solver$ docker run -v "$(pwd)"/output:/poisson/output poisson:latest
...
hlasco@hdl:~/hpc_esc_401/exercise_session_08/poisson_solver$ ls output
output_0001000.csv  output_0010000.csv  output_0019000.csv  output_0028000.csv  output_0037000.csv
output_0002000.csv  output_0011000.csv  output_0020000.csv  output_0029000.csv  output_0038000.csv
output_0003000.csv  output_0012000.csv  output_0021000.csv  output_0030000.csv  output_0039000.csv
output_0004000.csv  output_0013000.csv  output_0022000.csv  output_0031000.csv  output_0040000.csv
output_0005000.csv  output_0014000.csv  output_0023000.csv  output_0032000.csv  output_0041000.csv
output_0006000.csv  output_0015000.csv  output_0024000.csv  output_0033000.csv  output_0041021.csv
output_0007000.csv  output_0016000.csv  output_0025000.csv  output_0034000.csv  output_source.csv
output_0008000.csv  output_0017000.csv  output_0026000.csv  output_0035000.csv  plot.py
output_0009000.csv  output_0018000.csv  output_0027000.csv  output_0036000.csv
```
