#!/bin/bash -l 
#SBATCH --job-name="cpi_mpi" 
#SBATCH --account="uzh8" 
#SBATCH --time=00:05:00 
#SBATCH --nodes=1 
#SBATCH --ntasks-per-core=1 
#SBATCH --ntasks-per-node=36 
#SBATCH --cpus-per-task=1 
#SBATCH --partition=debug 
#SBATCH --constraint=mc 
#SBATCH --hint=nomultithread
#SBATCH --output=cpi_mpi.logs 
#SBATCH --error=cpi_mpi_errors.logs 


export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

srun ./cpi_mpi
