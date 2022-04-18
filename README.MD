# wssi
Wave-structure-soil interaction 

This is a one-way coupling wave-structure-soil interaction toolbox for wave-induced seabed response around coastal and offshore structures. The soil solvers include liquefaction analysis with various liquefaction criteria. 

For any usage of these models please refer to

@article{li2019numerical,
  title={A numerical toolbox for wave-induced seabed response analysis around marine structures in the OpenFOAM{\textregistered} framework},
  author={Li, Yuzhu and Ong, Muk Chen and Tang, Tian},
  journal={Ocean Engineering},
  pages={106678},
  year={2019},
  publisher={Elsevier}
}

The work enviroment for the solvers is foam-extend-3.1. 

For wave modeling, please select any wave generation toolbox.

To download the wssi structure and soil solvers and tutorials:

First, load your OpenFOAM environment for fe-3.1. Then:

    git clone https://github.com/LiYZPearl/wssi

    cd wssi/wssi-fe-3.1/

    chmod u+x Allwclean
    
    ./Allwclean

    chmod u+x Allwmake

    ./Allwmake

# foam-extend-4.0
(For foam-extend-4.0, please download the compressed package and compile in the same way.)

# Boundary
Regarding boundary conditions, if you would like to map curved surfaces, for example, piles,
it is recommended to use externalPatchToPatchMapping (example in /tutorials/3D-wssi/seabed/30/sigma_S). 
Then you need to sample with cell, interpolate false; so that
the face numbers will match the number of data in your time folders. 

The user manual of this toolbox is now available.


