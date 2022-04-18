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

The work enviroment for the solvers is foam-extend 3.1.

For wave modeling, please select any wave generation toolbox.

To download the wssi structure and soil solvers and tutorials:

    git clone https://github.com/LiYZPearl/wssi

    cd wssi/wssi-fe-3.1/

    chmod u+x Allwclean
    
    ./Allwclean

    chmod u+x Allwmake

    ./Allwmake


The user manual of this toolbox is now available.
