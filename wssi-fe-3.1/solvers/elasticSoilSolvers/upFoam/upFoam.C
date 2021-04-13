/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Application
    anisotropicBiotFoam

Description
    Segregated finite-volume solver for poro-linear-elastic,
    small-strain deformation of a soil material, with mechanical anisotropy
    (in particular, the orthotropy with 9 independent parameters) and hydraulic 
    anisotropy (directional-different soil permeability).

    Note that a new sigma_S field is added to facilitate a displacement boundary 
    condtion, timeVaryingMappedTotalTraction, which can describe a time and spatial 
    varying traction load (e.g. from the structure). This bc is derived from 
    tractionDisplacement + timeVaryingMappedFixedValue in OpenFOAM.   

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "Switch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

#   include "setRootCase.H"

#   include "createTime.H"
#   include "createMesh.H"
#   include "readSoilProperties.H"
#   include "createFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nCalculating displacement field\n" << endl;

    lduMatrix::debug=1;

    for (runTime++; !runTime.end(); runTime++)
    {
        Info<< "Iteration: " << runTime.timeName() << nl << endl;

#       include "readUpFoamControls.H"
        
        int iCorr = 0;
        scalar initialResidual = 0;
        scalar UResidual = 1.0e10;
        scalar pResidual = 1.0e10;

        sigma_S.correctBoundaryConditions();

#       include "calculateSigmaEpsilonOrtho.H"

        do
        {

    #       include "pEqn.H"  
    #       include "UEqn.H"   
    #       include "calculateSigmaEpsilonOrtho.H"  
         
            initialResidual = max(pResidual,UResidual);
            if (iCorr % 1 == 0){ Info << "\tTime " << runTime.value()
	         << ", Corrector " << iCorr
	         << ", Solving for " << U.name()
	         << ", residual = " << initialResidual << endl;   
              }   
        } while (initialResidual > convergenceTolerance && ++iCorr < nCorr);

#       include "calculateStress.H"
//#       include "evaluateLiquefactionRisk.H"
        
       Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return(0);
}


// ************************************************************************* //
