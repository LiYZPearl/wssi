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

#include "timeVaryingMappedTotalTractionFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

timeVaryingMappedTotalTractionFvPatchVectorField::
timeVaryingMappedTotalTractionFvPatchVectorField
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


timeVaryingMappedTotalTractionFvPatchVectorField::
timeVaryingMappedTotalTractionFvPatchVectorField
(
    const timeVaryingMappedTotalTractionFvPatchVectorField& tdpvf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedGradientFvPatchVectorField(tdpvf, p, iF, mapper)
{}


timeVaryingMappedTotalTractionFvPatchVectorField::
timeVaryingMappedTotalTractionFvPatchVectorField
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


timeVaryingMappedTotalTractionFvPatchVectorField::
timeVaryingMappedTotalTractionFvPatchVectorField
(
    const timeVaryingMappedTotalTractionFvPatchVectorField& tdpvf
)
:
    fixedGradientFvPatchVectorField(tdpvf)
{}


timeVaryingMappedTotalTractionFvPatchVectorField::
timeVaryingMappedTotalTractionFvPatchVectorField
(
    const timeVaryingMappedTotalTractionFvPatchVectorField& tdpvf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedGradientFvPatchVectorField(tdpvf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void timeVaryingMappedTotalTractionFvPatchVectorField::autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedGradientFvPatchVectorField::autoMap(m);
}


// Reverse-map the given fvPatchField onto this fvPatchField
void timeVaryingMappedTotalTractionFvPatchVectorField::rmap
(
    const fvPatchVectorField& ptf,
    const labelList& addr
)
{
    fixedGradientFvPatchVectorField::rmap(ptf, addr);
}


// Update the coefficients associated with the patch field
void timeVaryingMappedTotalTractionFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    const fvPatchField<tensor>& K =
        patch().lookupPatchField<volTensorField, tensor>("K");
    const tensorField Kinv = inv(K);

    vectorField n = patch().nf();

    const fvPatchField<tensor>& gradU =
        patch().lookupPatchField<volTensorField, tensor>("grad(U)");
    const fvPatchField<symmTensor>& sigma =
        patch().lookupPatchField<volSymmTensorField, symmTensor>("sigma");
    const fvPatchField<scalar>& p =
       patch().lookupPatchField<volScalarField, scalar>("p");
    const fvPatchField<symmTensor>& sigma_S =
        patch().lookupPatchField<volSymmTensorField, symmTensor>("sigma_S");

    vectorField Traction(n.size(), vector::zero);
    tensorField sigmaExp(n.size(), tensor::zero);

    Traction = (sigma_S&n)-p*n;

    sigmaExp = (n*(n & sigma)) - (K & gradU);

    gradient() =
      n &
      (
       Kinv & ( n*(Traction) - sigmaExp )
       );

    fixedGradientFvPatchVectorField::updateCoeffs();
}


// Write
void timeVaryingMappedTotalTractionFvPatchVectorField::write(Ostream& os) const
{
    fvPatchVectorField::write(os);
     writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePatchTypeField(fvPatchVectorField, timeVaryingMappedTotalTractionFvPatchVectorField);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
