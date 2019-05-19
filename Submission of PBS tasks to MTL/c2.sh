#!/bin/sh
#PBS -l select=1:ncpus=1
#PBS -N jobC06-7
#PBS -j oe
#PBS -l walltime=00:00:30
echo "Working directory is $PWD, at `hostname`"
echo "I see disks `mount`"
