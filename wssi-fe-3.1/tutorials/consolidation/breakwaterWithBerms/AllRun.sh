#!/bin/bash

blockMesh >blockMesh.log
echo blockMesh completed

cp -r 0.org 0
echo copied 0.org to 0

biotConsolidationFoam
#decomposePar >decomposePar.log
#echo decomposePar completed

#mpirun -np 16 biotConsolidationFoam -parallel &>TEST_C1_cons.log &




