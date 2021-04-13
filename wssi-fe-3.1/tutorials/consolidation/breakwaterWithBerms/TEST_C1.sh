#!/bin/bash
#PBS -N test_c1
#PBS -S /bin/bash 
#PBS -l walltime=08:00:00  
#PBS -l select=2:ncpus=32:mpiprocs=16
#PBS -A nn9372k

# Load modules
module load bison/2.6.5  
module load gcc/4.8.2      
module load mpt/2.06       
module load openfoam/extend-3.1  

#module load openfoam/extend-3.1           
                       
cd /work/danielece04/TEST_C/TEST_C1

# Run OpenFOAM
mpiexec_mpt -np 32 elasticConsolidationFoam -parallel > TEST_C1_cons.log

