#!/bin/sh
#PBS -N job4
#PBS -j oe
#PBS -m n
#PBS -l nodes=5:ppn=1
#PBS -l walltime=00:00:30
mpirun ~/lab/lab4/c5
