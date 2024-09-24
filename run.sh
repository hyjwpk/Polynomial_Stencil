#!/bin/bash

make clean

make

export OMP_NUM_THREADS=288
export OMP_PROC_BIND=close
export OMP_PLACES=threads

numactl --cpubind=0,1 ./polynomial_stencil test2.conf
