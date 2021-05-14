#!/bin/bash -l 
#SBATCH --job-name="serial" 
#SBATCH --account="uzh8" 
#SBATCH --time=00:05:00 
#SBATCH --nodes=1 
#SBATCH --ntasks-per-core=1 
#SBATCH --ntasks-per-node=1 
#SBATCH --cpus-per-task=1 
#SBATCH --partition=debug 
#SBATCH --constraint=mc 
#SBATCH --hint=nomultithread
#SBATCH --output=serial.logs 

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

for i in {1..10}
do
    echo "serial run $i"
    srun ../serial
done
