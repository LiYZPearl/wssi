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

\*---------------------------------------------------------------------------*/

#include "timeVaryingMappedPressureLoadFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

timeVaryingMappedPressureLoadFvPatchVectorField::
timeVaryingMappedPressureLoadFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedGradientFvPatchVectorField(p, iF)
{
    fvPatchVectorField::operator=(patchInternalField());
    gradient() = vector::zero;
}


timeVaryingMappedPressureLoadFvPatchVectorField::
timeVaryingMappedPressureLoadFvPatchVectorField
(
    const timeVaryingMappedPressureLoadFvPatchVectorField& tdpvf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedGradientFvPatchVectorField(tdpvf, p, iF, mapper)
{}


timeVaryingMappedPressureLoadFvPatchVectorField::
timeVaryingMappedPressureLoadFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedGradientFvPatchVectorField(p, iF)
{
    fvPatchVectorField::operator=(patchInternalField());
    gradient() = vector::zero;
}


timeVaryingMappedPressureLoadFvPatchVectorField::
timeVaryingMappedPressureLoadFvPatchVectorField
(
    const timeVaryingMappedPressureLoadFvPatchVectorField& tdpvf
)
:
    fixedGradientFvPatchVectorField(tdpvf)
{}


timeVaryingMappedPressureLoadFvPatchVectorField::
timeVaryingMappedPressureLoadFvPatchVectorField
(
    const timeVaryingMappedPressureLoadFvPatchVectorField& tdpvf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedGradientFvPatchVectorField(tdpvf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void timeVaryingMappedPressureLoadFvPatchVectorField::autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedGradientFvPatchVectorField::autoMap(m);
}


// Reverse-map the given fvPatchField onto this fvPatchField
void timeVaryingMappedPressureLoadFvPatchVectorField::rmap
(
    const fvPatchVectorField& ptf,
    const labelList& addr
)
{
    fixedGradientFvPatchVectorField::rmap(ptf, addr);
}


// Update the coefficients associated with the patch field
void timeVaryingMappedPressureLoadFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const dictionary& mechanicalProperties =
        db().lookupObject<IOdictionary>("mechanicalProperties");

    const dictionary& thermalProperties =
        db().lookupObject<IOdictionary>("thermalProperties");

    dimensionedScalar rho(mechanicalProperties.lookup("rho"));
    dimensionedScalar rhoE(mechanicalProperties.lookup("E"));
    dimensionedScalar nu(mechanicalProperties.lookup("nu"));

    dimensionedScalar E = rhoE/rho;
    dimensionedScalar mu = E/(2.0*(1.0 + nu));
    dimensionedScalar lambda = nu*E/((1.0 + nu)*(1.0 - 2.0*nu));
    dimensionedScalar threeK = E/(1.0 - 2.0*nu);

    Switch planeStress(mechanicalProperties.lookup("planeStress"));

    if (planeStress)
    {
        lambda = nu*E/((1.0 + nu)*(1.0 - nu));
        threeK = E/(1.0 - nu);
    }

    vectorField n = patch().nf();

    const fvPatchField<tensor>& gradU =
        patch().lookupPatchField<volTensorField, tensor>("grad(U)");

    const fvPatchField<scalar>& wavePressure =
        patch().lookupPatchField<volScalarField, scalar>("p_w");

    gradient() =
    (
        (- (wavePressure)*n)/rho.value()
      - (n & (mu.value()*gradU.T() - (mu + lambda).value()*gradU))
      - n*tr(gradU)*lambda.value()
    )/(2.0*mu + lambda).value();


    Switch thermalStress(thermalProperties.lookup("thermalStress"));

    if (thermalStress)
    {
        dimensionedScalar alpha(thermalProperties.lookup("alpha"));
        dimensionedScalar threeKalpha = threeK*alpha;

        const fvPatchField<scalar>& T =
            patch().lookupPatchField<volScalarField, scalar>("T");

        gradient() += n*threeKalpha.value()*T/(2.0*mu + lambda).value();
    }

    fixedGradientFvPatchVectorField::updateCoeffs();
}


// Write
void timeVaryingMappedPressureLoadFvPatchVectorField::write(Ostream& os) const
{
    fvPatchVectorField::write(os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePatchTypeField(fvPatchVectorField, timeVaryingMappedPressureLoadFvPatchVectorField);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
