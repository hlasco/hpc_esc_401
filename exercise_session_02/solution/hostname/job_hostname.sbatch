#!/bin/bash -l 
#SBATCH --job-name="hostname" 
#SBATCH --account="uzh8" 
#SBATCH --time=00:05:00 
#SBATCH --nodes=1 
#SBATCH --ntasks-per-core=1 
#SBATCH --ntasks-per-node=1 
#SBATCH --cpus-per-task=36 
#SBATCH --partition=debug 
#SBATCH --constraint=mc 
#SBATCH --hint=nomultithread
#SBATCH --output=hostname.logs 
#SBATCH --error=hostname_errors.logs 


export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

srun hostname
