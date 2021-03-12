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
    elasticStructureFoam

Description
    Transient/steady-state segregated finite-volume solver of linear-elastic,
    small-strain deformation of a solid structure, with optional thermal
    diffusion and thermal stresses.

    A new scalar field p_w is introduced to represent a (e.g. wave) pressure 
    loading on the boundary. p_w has values on the boundary patch(es) while all 
    zero in the internal domain. 

    This elastic structure solver is a slight modification of the stressedFoam 
    solver in OpenFOAM. Only the externalPatchToPatchMapping and 
    timeVaryingMappedPressureLoading boundaries are new contributions.   

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "Switch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

#   include "setRootCase.H"

#   include "createTime.H"
#   include "createMesh.H"
#   include "readMechanicalProperties.H"
#   include "readThermalProperties.H"
#   include "createFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nCalculating displacement field\n" << endl;
 
    for (runTime++; !runTime.end(); runTime++)
    {
        Info<< "Iteration: " << runTime.timeName() << nl << endl;

#       include "readElasticStructureFoamControls.H"

        int iCorr = 0;
        scalar initialResidual = 0;

        // UPDATE THE WAVE PRESSURE LOADING
        p_w.correctBoundaryConditions();

        do
        {
            volTensorField gradU = fvc::grad(U);

            if (thermalStress)
            {
                solve
                (
                    fvm::ddt(T) == fvm::laplacian(DT, T)
                );
            }

            fvVectorMatrix UEqn
            (
                fvm::d2dt2(U)
             ==
                fvm::laplacian(2*mu + lambda, U, "laplacian(DU,U)")

              + fvc::div
                (
                    mu*gradU.T() + lambda*(I*tr(gradU)) - (mu + lambda)*gradU,
                    "div(sigma)"
                )
            );

            if (thermalStress)
            {
                UEqn += threeKalpha*fvc::grad(T);
            }

            initialResidual = UEqn.solve().initialResidual();

        } while (initialResidual > convergenceTolerance && ++iCorr < nCorr);

#       include "calculateStress.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    deleteDemandDrivenData(Tptr);

    Info<< "End\n" << endl;

    return(0);
}


// ************************************************************************* //
