#!/bin/sh
#PBS -N jobhl
#PBS -j oe
#PBS -l walltime=00:15:00
mpirun ~/lab/lab1/helloworld
