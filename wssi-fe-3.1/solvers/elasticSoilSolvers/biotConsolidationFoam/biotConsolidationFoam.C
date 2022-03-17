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
    biotConsolidationFoam

Description
    Segregated finite-volume solver for poro-linear-elastic,
    small-strain deformation of a soil material, with mechanical anisotropy
    (in particular, the orthotropy with 9 independent parameters) and hydraulic 
    anisotropy (directional-different soil permeability).

    Note that a new sigma_S field is added to facilitate a displacement boundary 
    condtion, timeVaryingMappedTotalTraction, which can describe a time and spatial 
    varying traction load (e.g. from the structure). This bc is derived from 
    tractionDisplacement + timeVaryingMappedFixedValue in OpenFOAM.   

Authors
    Yuzhu Li, University of Stavanger. All rights reserved.
    Tian Tang, Technical University of Denmark.  All rights reserved.
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "Switch.H"
#include <cmath>
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

#       include "readAnisotropicBiotFoamControls.H"
        
        int iCorr = 0;
        scalar initialResidual = 0;
        scalar UResidual = 1.0e10;
        scalar pResidual = 1.0e10;

        sigma_S.correctBoundaryConditions();

#       include "calculateSigmaEpsilonOrtho.H"

        do
        {
            p.storePrevIter();

	    fvScalarMatrix pEqn
	    (
	        fvm::ddt(p) == fvm::laplacian(Dp, p) - fvc::div(fvc::ddt(Dp2,U)) + rho_w* fvc::div(Dp & g)  //rho_w is water density
	    );

	    pResidual = pEqn.solve().initialResidual();
	    p.relax(); 
    
            U.storePrevIter();
    
	
	    fvVectorMatrix UEqn
            (
                fvm::d2dt2(rho, U)
             ==
                fvm::laplacian(K, U, "laplacian(DU,U)")

              + fvc::div(sigma)

              - fvc::div(K & gradU)

              - fvc::grad(p)

              + ifBodyForce * g *(rho-rho_w)  //this rho is the submerged density 

            );
	   

            UResidual = UEqn.solve().initialResidual();

            U.relax(0.5);
            //U.relax = mesh.solutionDict("relaxFactor");


            gradU = fvc::grad(U);
 
    #       include "calculateSigmaEpsilonOrtho.H"  
         
            initialResidual = max(pResidual,UResidual);
            if (iCorr % 1 == 0){ Info << "\tTime " << runTime.value()
	         << ", Corrector " << iCorr
	         << ", Solving for " << U.name()
	        // << " using " << solverPerf.solverName()
	         << ", residual = " << initialResidual << endl;   
              }   
        } while (initialResidual > convergenceTolerance && ++iCorr < nCorr);

#       include "calculateStress.H"
     
       Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return(0);
}


// ************************************************************************* //
