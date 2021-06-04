#!/bin/bash -l
srun --account=uzg2 --constraint=gpu --time=00:15:00 --partition=debug --cpus-per-task=2 --ntasks-per-node=1 --pty bash
