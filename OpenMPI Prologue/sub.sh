#!/bin/sh
#PBS -N jobhl
#PBS -j oe
#PBS -l nodes=2:ppn=5
#PBS -l walltime=00:15:00
mpirun ~/lab/lab2/c4

