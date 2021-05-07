#!/bin/bash -l 
#SBATCH --job-name="omp_critical" 
#SBATCH --account="uzh8" 
#SBATCH --time=00:05:00 
#SBATCH --nodes=1 
#SBATCH --ntasks-per-core=1 
#SBATCH --ntasks-per-node=1 
#SBATCH --cpus-per-task=36 
#SBATCH --partition=debug 
#SBATCH --constraint=mc 
#SBATCH --hint=nomultithread
#SBATCH --output=omp_critical.logs 

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

for i in {1..10}
do
    echo "omp_critical run $i"
    srun ../omp_critical
done
