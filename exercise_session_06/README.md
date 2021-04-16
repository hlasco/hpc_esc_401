# Exercise Session 06 #
In this session, we will mostly practice MPI communications.

In the first exercise, we establish communication between processes on a ring. Each process will send and receive information from its closest neighbours. Without being careful, it is not rare to encounter deadlocks in such problems. A bonus question (a bit more involved) will guide you to learn how to use MPI cartesian communicators on a 1D periodic grid in order to set-up the ring.  

In the second exercise, you have to estimate the Euler constant using a famous series. Your implementation have to be parallelized with MPI.

In the third exercise, you will implement the missing routines of an incomplete 2D Poisson Solver. 

In this folder you can find:

* ring_and_deadlocks/ring.c : a skeleton code that you can use to solve Exercise 1
* poisson_solver/ : the incomplete Poisson Solver for exercise 3
