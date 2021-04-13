#!/bin/bash

gmsh -3 circularGBF_wave.geo 

gmshToFoam circularGBF_wave.msh

#Remove the defaultFaces in constant/polyMesh/boundary if any
