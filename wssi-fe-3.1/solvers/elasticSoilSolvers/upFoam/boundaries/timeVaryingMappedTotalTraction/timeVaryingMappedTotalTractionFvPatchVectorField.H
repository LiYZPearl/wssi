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

Class
    timeVaryingMappedTotalTractionFvPatchVectorField

Description
    a time and spatial varying traction load (e.g. from the structure)
    for the anisotropic porous soil solver (anisotropicBiotFoam).

    This bc is derived from tractionDisplacement + timeVaryingMappedFixedValue 
    in OpenFOAM. 

SourceFiles
    timeVaryingMappedTotalTractionFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef timeVaryingMappedTotalTractionFvPatchVectorField_H
#define timeVaryingMappedTotalTractionFvPatchVectorField_H

#include "fvPatchFields.H"
#include "fixedGradientFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                   Class timeVaryingMappedTotalTractionFvPatch Declaration
\*---------------------------------------------------------------------------*/

class timeVaryingMappedTotalTractionFvPatchVectorField
:
    public fixedGradientFvPatchVectorField
{


public:

    //- Runtime type information
    TypeName("timeVaryingMappedTotalTraction");


    // Constructors

        //- Construct from patch and internal field
        timeVaryingMappedTotalTractionFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        timeVaryingMappedTotalTractionFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  timeVaryingMappedTotalTractionFvPatchVectorField onto a new patch
        timeVaryingMappedTotalTractionFvPatchVectorField
        (
            const timeVaryingMappedTotalTractionFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        timeVaryingMappedTotalTractionFvPatchVectorField
        (
            const timeVaryingMappedTotalTractionFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new timeVaryingMappedTotalTractionFvPatchVectorField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        timeVaryingMappedTotalTractionFvPatchVectorField
        (
            const timeVaryingMappedTotalTractionFvPatchVectorField&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchVectorField> clone
        (
            const DimensionedField<vector, volMesh>& iF
        ) const
        {
            return tmp<fvPatchVectorField>
            (
                new timeVaryingMappedTotalTractionFvPatchVectorField(*this, iF)
            );
        }


    // Member functions

        // Access



        // Mapping functions

            //- Map (and resize as needed) from self given a mapping object
            virtual void autoMap
            (
                const fvPatchFieldMapper&
            );

            //- Reverse map the given fvPatchField onto this fvPatchField
            virtual void rmap
            (
                const fvPatchVectorField&,
                const labelList&
            );


        //- Update the coefficients associated with the patch field
        virtual void updateCoeffs();

        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
