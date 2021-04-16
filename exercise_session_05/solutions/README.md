## Exercise 1
We provide a single bash script solving for options 1)-5):

```scala
  1 #!/bin/bash -l
  2 
  3 BINARY_FILE="./../../binary.txt"
  4 
  5 GREP_OPTIONS='-i --color'
  6 
  7 echo "1): end with 00"
  8 egrep $GREP_OPTIONS ".{14}00" ${BINARY_FILE}
  9 # egrep "[01]{${STRING_LENGTH}}00" ${BINARY_FILE} # alternatively, this can be used
 10 if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi
 11 
 12 echo "2): start and end with 1"
 13 egrep ${GREP_OPTIONS} "1.{14}1" ${BINARY_FILE}
 14 if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi
 15 
 16 echo "3): contain pattern 110"
 17 egrep ${GREP_OPTIONS} "110" ${BINARY_FILE}
 18 if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi
 19 
 20 echo "4): contain at least three times a 1"
 21 egrep ${GREP_OPTIONS} "1+.*1+.*1+" ${BINARY_FILE}
 22 if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi
 23 
 24 echo "5): contain at least three consecutive 1s"
 25 egrep ${GREP_OPTIONS} "111+" ${BINARY_FILE}
 26 if [[ $? -ne 0 ]]; then echo "no such sequence found"; fi
```

which can be executed using `./grep_binary.sh`.

The second part can be solved using e.g. a following script:

```scala
  1 #!/bin/bash
  2 
  3 RE="Temperature\: ([0-9]+\.[0-9]+) deg at time\: ([0-9]+\.[0-9]+) sec"
  4 TEMP=0
  5 n=0
  6 :>out.txt
  7 while read A; do
  8         if [[ "$A" =~ $RE ]] ; then
  9                 echo "${BASH_REMATCH[1]}   ${BASH_REMATCH[2]}" >> out.txt
 10                 TEMP=$(echo "scale=5;${TEMP} + ${BASH_REMATCH[1]}" | bc)
 11                 n=$((n+1))
 12                 echo "temp: ${TEMP} n: ${n}" 
 13 
 14         fi
 15 done
 16 AVERAGE=$(echo "scale=5;$TEMP/$n" | bc)
 17 echo "Average time: ${AVERAGE}"
```

By executing `./temp_time.sh< ../../measurements.txt`, we get a file `out.txt` (see `Exercise1/out.txt`) containing requested output. Moreover, we obtain the average temperature of 20.44653.


## Exercise 2

* **log in to Daint and load the `perftools-lite module`**

After login, we run `module load daint-gpu` (as always when using `uzg2` project, for `uzh8` load `daint-mc`) and then load the profiling module using `module load perftools-lite`

* **compile the MPI code `nbody.cpp` (do not forget about -g flag). Do you observe any changes in the terminal output compared to usual compilation during the previous sessions? Run the produced executable using a jobscript (you do not need to include any changes into it)**

Now we compile the n-body code using e.g.

```
CC -g -o nbody -O3 -ffast-math -mavx2 nbody.cpp
```

(do not forget to use capital `CC` as `nbody.cpp` is a C++ code). You might get some warning about where the object files will be stored but the improtant thing to get is the following:

```
INFO: creating the PerfTools-instrumented executable 'nbody' (lite-samples) ...OK
```
With this, the compilation with perftools-lite added was correct and we can run the code using a standard .job script (see `Exercise2/run_nbody.job`). 

* **once the job is successfully finished, inspect the produced files/folder(s) and read few details about the output structure in the manual (`man perftools-lite`)**

Except from the executable `nbody`, there is an executable `nbody+orig` created by the profiler during the compilation and directory `nbody+19918-2359s` (the name can differ here), which contains three subdirectories (describtion taken from `man` output): 


* A rpt-files subdirectory, which contains a copy of the text report.

* An ap2-files subdirectory, which contains processed data files, in the format required to examine the program's behavior more closely using Cray Apprentice2
           or pat_report.
* An xf-files subdirectory, which contains the raw data files written by the instrumented executable.

The relevant part of the output file reads:

```
Experiment:                  lite  lite-samples
Number of PEs (MPI ranks):      1
Numbers of PEs per Node:        1
Numbers of Threads per PE:      1
Number of Cores per Socket:    12
Execution start time:  Fri Mar 26 16:42:03 2021
System name and speed:  nid02359  2.601 GHz (nominal)
Intel Haswell    CPU  Family:  6  Model: 63  Stepping:  2
DRAM:  64 GiB DDR4-2400 on 2.6 GHz nodes



Avg Process Time:          3.94 secs
High Memory:               37.3 MiBytes 37.3 MiBytes per PE
Observed CPU clock boost: 126.0 %
Percent cycles stalled:    65.3 %
Instr per Cycle:           1.10

Notes for table 1:

  This table shows functions that have significant exclusive sample
    hits, averaged across ranks.
  For further explanation, see the "General table notes" below,
    or use:  pat_report -v -O samp_profile ...

Table 1:  Profile by Function

  Samp% |  Samp | Imb. |  Imb. | Group
        |       | Samp | Samp% |  Function=[MAX10]

 100.0% | 388.0 |   -- |    -- | Total
|-------------------------------------------------
| 100.0% | 388.0 |   -- |    -- | USER
||------------------------------------------------
|| 100.0% | 388.0 |   -- |    -- | forces
|=================================================

Notes for table 2:

  This table shows functions, and line numbers within functions, that
    have significant exclusive sample hits, averaged across ranks.
  For further explanation, see the "General table notes" below,
    or use:  pat_report -v -O samp_profile+src ...

Table 2:  Profile by Group, Function, and Line

  Samp% |  Samp | Imb. |  Imb. | Group
        |       | Samp | Samp% |  Function=[MAX10]
        |       |      |       |   Source
        |       |      |       |    Line

 100.0% | 388.0 |   -- |    -- | Total
|-----------------------------------------------------------------------------
| 100.0% | 388.0 |   -- |    -- | USER
||----------------------------------------------------------------------------
|| 100.0% | 388.0 |   -- |    -- | forces
3|        |       |      |       |  exercise_session_05/solutions/Exercise2/nbody.cpp
||||--------------------------------------------------------------------------
4|||   2.8% |  11.0 |   -- |    -- | line.18
4|||   2.8% |  11.0 |   -- |    -- | line.20
4|||   9.3% |  36.0 |   -- |    -- | line.21
4|||   2.3% |   9.0 |   -- |    -- | line.22
4|||  62.6% | 243.0 |   -- |    -- | line.23
4|||   7.5% |  29.0 |   -- |    -- | line.24
4|||  12.6% |  49.0 |   -- |    -- | line.25
|=============================================================================

```

* **which parts of the code took the most CPU time? Can you make sense of why?**

We can learn that line 23 took the most of CPU time. Investigating the `nbody.cpp` (below) we see that the bottleneck is line 22 (as discussed on the lecture, the output line can be 'wrong' by one - so also some part of CPU time deduced for line 21 would fall actually to the line 22). In this line, the floating point division occurs, which is far more heavy to compute that any of `+,-,*`. 

```scala
 16                 for(int j=0; j<n; ++j) { // Depends on all other particles
 17                         if (i==j) continue; // Skip self interaction 
 18                         auto dx = plist[j].x - plist[i].x;
 19                         auto dy = plist[j].y - plist[i].y;
 20                         auto dz = plist[j].z - plist[i].z;
 21                         auto r = sqrt(dx*dx + dy*dy + dz*dz);
 22                         auto ir3 = 1 / (r*r*r);
 23                         plist[i].ax += dx * ir3;
 24                         plist[i].ay += dy * ir3;
 25                         plist[i].az += dz * ir3;
 26                 }
```



* **extract the function `forces()` into a separate file `forces.cpp` and function `ic()` into file init `conditions.cpp`. Do not forget to create one header file (.h) for each of the .cpp file. (You might need to put `#include <cmath>` in `forces.cpp`)**
  
We extract the functions to separate .cpp files and for each create the corresponding header .h file:

`forces.cpp`
```scala
  1 #include "particles.h"
  2 #include <cmath>
  3 void forces(particles &plist) {
  4         int n = plist.size();
  5         for(int i=0; i<n; ++i) { // We want to calculate the force on all particles
  6                 plist[i].ax = plist[i].ay = plist[i].az = 0; // start with zero acceleration
  7                 for(int j=0; j<n; ++j) { // Depends on all other particles
  8                         if (i==j) continue; // Skip self interaction 
  9                         auto dx = plist[j].x - plist[i].x;
 10                         auto dy = plist[j].y - plist[i].y;
 11                         auto dz = plist[j].z - plist[i].z;
 12 		            auto r = sqrt(dx*dx + dy*dy + dz*dz);
 13                         auto ir3 = 1 / (r*r*r);
 14                         plist[i].ax += dx * ir3;
 15                         plist[i].ay += dy * ir3;
 16                         plist[i].az += dz * ir3;
 17                 }
 18         }
 19 }
```
`forces.h`
```scala
  1 #ifndef _FORCES
  2 #define _FORCES
  3 
  4 void forces(particles &plist);
  5 
  6 #endif
```

`init_conditions.cpp`
```scala
  1 #include <random>
  2 #include "particles.h"
  3 // Initial conditions
  4 void ic(particles &plist, int n) {
  5         std::random_device rd; //Will be used to obtain a seed for the random number engine 
  6         std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd() 
  7         std::uniform_real_distribution<float> dis(0.0, 1.0);
  8 
  9         plist.clear(); // Remove all particles 
 10         plist.reserve(n); // Make room for "n" particle 
 11         for( auto i=0; i<n; ++i) {
 12                 particle p { dis(gen),dis(gen),dis(gen),0,0,0,0,0,0 };
 13                 plist.push_back(p);
 14         }
 15 }
```
`init_conditions.h`
```scala
  1 #ifndef _IC
  2 #define _IC
  3 
  4 void ic(particles &plist, int n);
  5 
  6 #endif
```

Then we obtain reduced main file containing only some library loadings and main funtion. However, we need to include the external functions via loading the header files. 

`main.cpp`
```scala
  1 #include <vector>
  2 #include "particles.h"
  3 #include "init_conditions.h"
  4 #include "forces.h"
  5 
  6 
  7 int main(int argc, char *argv[]) {
  8         int N=20000; // number of particles
  9         particles plist; // vector of particles
 10         ic(plist,N); // initialize starting position/velocity 
 11         forces(plist); // calculate the forces
 12         return 0;
 13 }
```

However, within the code, we defined the new type `particles`which is used also in both external functions (see their declatarions in .h files). So we need to create one additional header file containing this new type and so making it accessible for all the local files (main.cpp,...):

`particles.h`
```scala
  1 #ifndef _PARTICLES
  2 #define _PARTICLES
  3 
  4 #include <vector>
  5 struct particle {
  6         float x, y, z; // position 
  7         float vx, vy, vz; // velocity 
  8         float ax, ay, az; // acceleration
  9 };
 10 
 11 typedef std::vector<particle> particles;
 12 
 13 #endif
```
Note, that we do not need to have any `particles.cpp` file here, as we only talk about some type definitions and not any additional piece of code. 

* **make sure you have perftools-lite loaded and try to compile and link the codes. Do you get any error? What about the new type `particles`? Should it also be defined in a separate file?**

We discussed the `particles` type in the previous paragraph, the only thing leaving to do is to compile the code (while still having perftools loaded)

`Makefile`

```scala
  1 CC=CC
  2 CFLAGS= -g -ffast-math -O3 -mavx2
  3 all: forces.o init.o main.o main
  4 
  5 forces.o: forces.cpp particles.h forces.h
  6         ${CC} ${CFLAGS} -c -o forces.o forces.cpp
  7 init.o: init_conditions.cpp particles.h init_conditions.h
  8         ${CC} ${CFLAGS} -c -o init.o init_conditions.cpp
  9 main.o: main.cpp particles.h
 10         ${CC} ${CFLAGS} -c -o main.o main.cpp
 11 main: main.o forces.o init.o
 12         ${CC} ${CFLAGS} -o main main.o forces.o init.o
 13 clean: 
 14         rm -f forces.o init.o main.o main
```
* **run the compiled code and see the perftools-lite output. Is the execution time comparable with the simple case when the whole code was placed within a single .cpp file?**
  
We run the code using `Exercise2/run_main.job` script. The perftools output can be viewed in file `Exercise2/main.log`. The execution time is 3.86s, while in the case of single file, the runtime is 3.94s, so the execution times are practically the same. This is, of course, expected result as during the preprocessing, the header files are included into respective .cpp files. In other words, such structuring of the code helps the developer/user but do not affect the runtime.

PS: the C/C++ compilers throw error when they observe a multiple definition e.g. of the same structure (or function,...). Therefore, it is a good practise to use so called #include guards in header files. When the `#include` commands are executed during pre-processing, all the code from the header files are copied at the spot where this `#include` is located. Once e.g. the content of `particles.h` is included, the existence of `_PARTICLES` is checked. If it is not yet defined, the content of .h file is included (so at the first occurence of `#include "particles.h"`). If there is any other inclusion of `particles.h`,  `_PARTICLES` is already defined and the include command is ignored. 

## Exercise 3

* **Let’s first write an OpenMP version of `nbody.cpp`.  This code is slightly different from what you already encountered as it contains nested for loops.  Here you can decide toadd OpenMP parallel directive to the first, the second, or to both loops.  Which one is the most efficient solution, why?**

First, we add `#include "omp.h"` into `nbody.cpp` (we can again use the original file `nbody.cpp` containing the whole code). To asses which for loop is more efficient to parallelize, we can simply try out three different options: first adding `#pragma omp parallel for` only before the first for loop, then only the second one and at last before both. The first scenario would look as follows:

```scala
 12 void forces(particles &plist) {
 13         int n = plist.size();
 14         #pragma omp parallel for 
 15         for(int i=0; i<n; ++i) { // We want to calculate the force on all particles
 16                 plist[i].ax = plist[i].ay = plist[i].az = 0; // start with zero acceleration
 17                 for(int j=0; j<n; ++j) { // Depends on all other particles
 18                         if (i==j) continue; // Skip self interaction 
 19                         auto dx = plist[j].x - plist[i].x;
 20                         auto dy = plist[j].y - plist[i].y;
 21                         auto dz = plist[j].z - plist[i].z;
 22                         auto r = sqrt(dx*dx + dy*dy + dz*dz);
 23                         auto ir3 = 1 / (r*r*r);
 24                         plist[i].ax += dx * ir3;
 25                         plist[i].ay += dy * ir3;
 26                         plist[i].az += dz * ir3;
 27                 }
 28         }
 29 }
```
We can compile by typing
`CC -g -ffast-math -fopenmp -o nbody_for1 nbody_for1.cpp`
and run via
`sbatch run_nbody_for1.job`. 

To measure time, we can use any timing library we like, in this solutions, we compiled the code under perftools-lite which provides the runtime in the log file.

The resulting run times are:
* loop1: 1.13s
* loop2: 25.12 s
* both loops: 1.16s

So we see that parallelizing the first loop is the best option, comparable to parallelizing both, and paralleling the second loop only yields horrible performance. 
The reason why the first and second case is so different can be explained as follows: in the first case, the force calculation is split to respective threads and then each thread calculates the force on its particles independently of other threads. At the end of the calculation, this thread waits until all other threads are done with the calculations. On the other side, parallelizing the second loop, force acting at each particle is calculated in parallel and so the threads need to synchronize once per each particle calculations (N times intsead of once). As expected, the third option would also produce such synchorization overhead, but in a smaller amounts. 

* **The execution time of the code `nbody.cpp` will obviously increase with the number of particles.  What is the expected scaling relation between the code execution time t and the number of particles N?  Can you justify your answer?**

The expected scaling of the serial code is O(N^2), which can be easily observed from the two nested for loops in `forces` routine, which both iterate over all particles.

* **Edit the code nbody.cpp in order to be able to specify the number of particles with a command line argument.  For example `./nbody 1000`should execute the code with 1000 particles.  Does your implementation still work when not specifying any command line argument?  If not, try to include safety nets while reading the command line arguments.**

We expect one positive integer to be passed when running the script. So `argc` which counts the number of agruments used to run the code should have value of 2. First argument stored in `argv` is the name of executable (default) and the second in our case is the number of particles N. So we check the correct number of arguments in line 57 and whether N is >=1 in line 58. If a float number is given, the `atoi` function truncates the decimal part. To measure the ellapsed time, we can use e.g. `chrono` library (`#include <chrono>`). Lines 61 and 68-71 show an example how to measure and print the time. The serial `main` function looks as follows:   

```scala
 48 int main(int argc, char *argv[]) {
 49 
 50         int i;
 51         printf("number of arguments: %d\n",argc);
 52         for(i=0;i<argc;i++)
 53         {
 54             printf("arg %d: %s \n",i+1,argv[i]);
 55         }
 56 
 57         if (argc!=2) printf("wrong number of aguments provided \n");
 58         else if (atoi(argv[1])<1) printf("Provide positive integer\n");
 59         else
 60         {
 61         auto start = std::chrono::high_resolution_clock::now();
 62         int N=atoi(argv[1]); // number of particles
 63         std::cout<<"N="<<N<<"\n";
 64         particles plist; // vector of particles
 65         ic(plist,N); // initialize starting position/velocity 
 66         forces(plist); // calculate the forces
 67 
 68         auto end = std::chrono::high_resolution_clock::now();
 69         auto diff = std::chrono::duration_cast<std::chrono::seconds>(end - start);
 70         auto diff_milli = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
 71         std::cout<<"Total ellapsed time: "<<diff.count()<<"."<<diff_milli.count()<< "\n";
 72         }
 73         return 0;
 74 }
```

which can be compiled using `CC -g -ffast-math -O3 -fopenmp -o nbody_serial_args nbody_serial_args.cpp`. 

* **Plot the execution time of the serial code with
N= [100,500,1000,5000,10000,20000,50000]
with  1  node  on  the  uzg2  partition  (using  a  bash  script  is  a  good  idea).   Repeat  the experiment with your OpenMP implementation using 12 threads.  Can you find a good fit to your results?**

In this part, we provide the solutions using `uzh8` project, which is again operationl. To get the results for various N, one can e.g. following bash script:

```scala
  1 #!/bin/bash -l
  2 
  3 # OPTION="serial"
  4 OPTION="for1"
  5 for N in 100 500 1000 5000 10000 20000 30000 40000 50000 60000 75000
  6 do
  7     sbatch --output=scaling_${OPTION}_${N}.out run_nbody_${OPTION}_args.job ${N}
  8     sleep 20
  9 done
```

One can choose "serial" of "for1" option stading for serial code vs. OMP code with first for loop parallelized. The resulting scaling is shown in the following plot:

![](./Exercise3/scaling.jpg)

One can clearly observe the quadratic scaling, we display linear and quadratic fits and in the right panel also the serial runtimes divided by 12 for comparison. We include more data points than requested to demonstrate the scaling more clearly.

* **BONUS: Is it possible to reduce the time complexity of N-body force calculations?**

There are ways how to compute forces between particles in O(n log n) instead of O(N^2). One such approach is Barnes-Hut hierarchical tree algorithm. The idea is in the successive halving of the whole domain: in the beginning, there is one root cell (volume) containing all the particles (thus, the original computational domain). Then the algorithm proceeds recursively starting at the root cell and divide the actual cell into 8 subcells (8 equal subvolumes) if it contains more that one particle. At the end, each cell has 0 or 1 particles in it. The tree of cells is constructed, the root cell being on the top and then 8 "doughter cells" following stemming from a "parent" cell. Each tree node (cell) also contains the information about the total mass included in it and the coordinates of centre-of-mass. 

Suppose we want to calculate a total force acting on the particle p. We iterate over the whole tree (starting with root cell on the top) and check whether the centre-of-mass of this cell is sufficiently far away from particle p. If yes, the net force from all particles in such a cell is approximated by only the force coming from the total included mass at the centre-of-mass position. If the centre-of-mass is not sufficiently far away, we proceed with the daughter cells of such cell. The "sufficiently far away" quantitatively reads: if `l/D< s`, where D is the distance between particle p and centre-of-mass of the cell in consideration, l is the size of cell considered and s is free parameter which needs to be set, usually s~1.  Notice that by setting s=0, we recover the original O(N^2) algorithm. For more information, see the original paper: https://www.nature.com/articles/324446a0.pdf. 

