#!/bin/bash -l

# OPTION="serial"
OPTION="for1"
for N in 100 500 1000 5000 10000 20000 30000 40000 50000 60000 75000
do
    sbatch --output=scaling_${OPTION}_${N}.out run_nbody_${OPTION}_args.job ${N}
    sleep 20
done
