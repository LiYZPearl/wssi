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
    timeVaryingMappedPressureLoadFvPatchVectorField

Description
    Mapped pressure boundary condition for the linear elastic structural solver
    (elasticStructureFoam).

SourceFiles
    timeVaryingMappedPressureLoadFvPatchVectorField.C

\*---------------------------------------------------------------------------*/

#ifndef timeVaryingMappedPressureLoadFvPatchVectorField_H
#define timeVaryingMappedPressureLoadFvPatchVectorField_H

#include "fvPatchFields.H"
#include "fixedGradientFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                   Class timeVaryingMappedPressureLoadFvPatch Declaration
\*---------------------------------------------------------------------------*/

class timeVaryingMappedPressureLoadFvPatchVectorField
:
    public fixedGradientFvPatchVectorField
{

    // Private Data

     
public:

    //- Runtime type information
    TypeName("timeVaryingMappedPressureLoad");


    // Constructors

        //- Construct from patch and internal field
        timeVaryingMappedPressureLoadFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        timeVaryingMappedPressureLoadFvPatchVectorField
        (
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given
        //  timeVaryingMappedPressureLoadFvPatchVectorField onto a new patch
        timeVaryingMappedPressureLoadFvPatchVectorField
        (
            const timeVaryingMappedPressureLoadFvPatchVectorField&,
            const fvPatch&,
            const DimensionedField<vector, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        timeVaryingMappedPressureLoadFvPatchVectorField
        (
            const timeVaryingMappedPressureLoadFvPatchVectorField&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchVectorField> clone() const
        {
            return tmp<fvPatchVectorField>
            (
                new timeVaryingMappedPressureLoadFvPatchVectorField(*this)
            );
        }

        //- Construct as copy setting internal field reference
        timeVaryingMappedPressureLoadFvPatchVectorField
        (
            const timeVaryingMappedPressureLoadFvPatchVectorField&,
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
                new timeVaryingMappedPressureLoadFvPatchVectorField(*this, iF)
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
