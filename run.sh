#!/bin/bash

make clean

make

export OMP_NUN_THREADS=576
export OMP_PROC_BIND=true
export OMP_PLACES=threads

./polynomial_stencil test.conf
