#!/bin/sh
#PBS -N job3
#PBS -j oe
#PBS -m n
#PBS -l nodes=4:ppn=2
#PBS -l walltime=00:00:30
cd ~/lab/lab3
mpirun ./c7
