#!/bin/sh
#PBS -N job5
#PBS -j oe
#PBS -m n
#PBS -l nodes=5:ppn=1
#PBS -l walltime=00:05:00
mpirun ~/lab/lab6/c5 1 2 3 4 5 6
