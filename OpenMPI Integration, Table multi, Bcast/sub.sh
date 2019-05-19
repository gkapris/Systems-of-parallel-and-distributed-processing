#!/bin/sh
#PBS -N job5
#PBS -j oe
#PBS -m n
#PBS -l nodes=5:ppn=1
#PBS -l walltime=00:05:00
mpirun ~/lab/lab8/c4
