#!/bin/sh
#PBS -N jobc1
#PBS -j oe
#PBS -l nodes=5:ppn=1
#PBS -l walltime=00:00:30
mpirun ~/lab/mtl6/c1
