# Exercise session 02

## Exercise 01
The simplest way to setup your git repository is to first create it on bitbucket/github/gitlab. You can then clone this new empty repository on your machine with:
 `git clone https://github.com/<username>/<new_repo>.git`
 You can then add some files/directories locally, which will not modify the remote version of the repository. Some modifications of the repository (for example a new folder named `solution_exercise_02`) can be pushed to the remote version with the following commands: 
 
 `mkdir solution_exercise_02`
 
 `git add solution_exercise_02`
 
 `git commit -m "added solution directory for exercise 02"`
 
 `git push`
 
## Exercise 02

**What is cc?**

`cc` refers to the C compiler wrapper command on Cray systems (use `CC` for compiling C++ code, `ftn` for Fortran). You can find more information about compiling on Piz Daint here: https://user.cscs.ch/computing/compilation/

**What does the flag -O3 do? What happens if we change this to -O0?**

This flag enables compiler optimizations, which will attempt to improve the performance and/or code size at the expense of compilation time. There are several levels of optimization possible (from 0 to 3). Most optimizations are completely disabled with the level 0 flag `-O0`.

**Which programming environment are you currently using?**

 The default environment on Piz Daint is the Cray environment. To change from Cray to Gnu environment, use the command `module switch PrgEnv-cray PrgEnv-gnu `.
## Exercise 03

**-   Run sinfo -p debug. What can you see? How can you print only your jobs? Or any other user?**

The command `sinfo` is used to view partition and node information for a system running Slurm. Here, we look at the "debug" partition with the `-p debug` flag. A list of submitted jobs can be viewed with `squeue`, to only print one single user's jobs, use `squeue -u <username>`

**First jobscript running hostname**

See `hostname/job_hostname.sbatch`, and `hostname/hostname.logs`

**Running cpi_mpi and cpi_omp**

Jobscripts and outputs can be found in the `mpi` and `omp` folders

**BONUS: customizing squeue**

Use the friendly command `squeue --Format=JOBID,USERNAME,PRIORITY,ACCOUNT,NAME,NUMNODES,STATECOMPACT,REASON,STARTTIME,TIMELEFT,PRIORITY -u <username>`

## Exercise 04

**Serial version** 

See `cpi.c` and `Makefile`

**BONUS: Hybrid version**

See `cpi_hybrid.c` and `Makefile`

||Serial |MPI |OpenMP |MPI+OpenMP |
|-------|---|---|---|---|
|Tasks per node|1|36|1|6|
|CPUs per task|1|1|36|6|
|Running time (s)|1.368|0.04891|0.1112|0.1165|




