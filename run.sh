#!/bin/bash

make clean

make

export OMP_NUM_THREADS=288
export OMP_PROC_BIND=close
export OMP_PLACES=threads

./polynomial_stencil test.conf
