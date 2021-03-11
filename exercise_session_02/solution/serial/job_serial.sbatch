#!/bin/bash -l 
#SBATCH --job-name="cpi_serial" 
#SBATCH --account="uzh8" 
#SBATCH --time=00:05:00 
#SBATCH --nodes=1 
#SBATCH --ntasks-per-core=1 
#SBATCH --ntasks-per-node=1 
#SBATCH --cpus-per-task=1
#SBATCH --partition=debug 
#SBATCH --constraint=mc 
#SBATCH --hint=nomultithread
#SBATCH --output=cpi_serial.logs 
#SBATCH --error=cpi_serial_errors.logs 


export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

srun ./cpi
