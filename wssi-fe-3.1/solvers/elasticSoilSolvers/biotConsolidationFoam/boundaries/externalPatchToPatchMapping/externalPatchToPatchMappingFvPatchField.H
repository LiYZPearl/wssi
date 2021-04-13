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
    Foam::externalPatchToPatchMappingFvPatchField

Description
    Foam::externalPatchToPatchMappingFvPatchField

SourceFiles
    externalPatchToPatchMappingFvPatchField.C

\*---------------------------------------------------------------------------*/

#ifndef externalPatchToPatchMappingFvPatchField_H
#define externalPatchToPatchMappingFvPatchField_H

#include "fixedValueFvPatchFields.H"
#include "coordinateSystem.H"
#include "FixedList.H"
#include "instantList.H"
#include "patchToPatchInterpolation.H" 

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
              Class externalPatchToPatchMappingFvPatch Declaration
\*---------------------------------------------------------------------------*/

template<class Type>
class externalPatchToPatchMappingFvPatchField
:
    public fixedValueFvPatchField<Type>
{
    // Private data

        //- Name of the field data table, defaults to the name of the field
        word fieldTableName_;

        //- If true adjust the mapped field to maintain average value
        bool setAverage_;

        // PatchToPatch interpolation
  //    autoPtr<PatchToPatchInterpolation> mapperPtr_;

        //- List of boundaryData time directories
        instantList sampleTimes_;

        //- Current starting index in sampleTimes
        label startSampleTime_;

        //- Interpolated values from startSampleTime
        Field<Type> startSampledValues_;

        //- If setAverage: starting average value
        Type startAverage_;

        //- Current end index in sampleTimes
        label endSampleTime_;

        //- Interpolated values from endSampleTime
        Field<Type> endSampledValues_;

        //- If setAverage: end average value
        Type endAverage_;


    // Private Member Functions

        //- Get names of times
        static wordList timeNames(const instantList&);

        //- Find times around current time
        void findTime
        (
            const fileName& instance,
            const fileName& local,
            const scalar timeVal,
            label& lo,
            label& hi
        ) const;

        //- Find boundary data inbetween current time and interpolate
        void checkTable();

public:

    //- Runtime type information
    TypeName("externalPatchToPatchMapping");


    // Constructors

        //- Construct from patch and internal field
        externalPatchToPatchMappingFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&
        );

        //- Construct from patch, internal field and dictionary
        externalPatchToPatchMappingFvPatchField
        (
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const dictionary&
        );

        //- Construct by mapping given externalPatchToPatchMappingFvPatchField
        //  onto a new patch
        externalPatchToPatchMappingFvPatchField
        (
            const externalPatchToPatchMappingFvPatchField<Type>&,
            const fvPatch&,
            const DimensionedField<Type, volMesh>&,
            const fvPatchFieldMapper&
        );

        //- Construct as copy
        externalPatchToPatchMappingFvPatchField
        (
            const externalPatchToPatchMappingFvPatchField<Type>&
        );

        //- Construct and return a clone
        virtual tmp<fvPatchField<Type> > clone() const
        {
            return tmp<fvPatchField<Type> >
            (
                new externalPatchToPatchMappingFvPatchField<Type>(*this)
            );
        }

        //- Construct as copy setting internal field reference
        externalPatchToPatchMappingFvPatchField
        (
            const externalPatchToPatchMappingFvPatchField<Type>&,
            const DimensionedField<Type, volMesh>&
        );

        //- Construct and return a clone setting internal field reference
        virtual tmp<fvPatchField<Type> > clone
        (
            const DimensionedField<Type, volMesh>& iF
        ) const
        {
            return tmp<fvPatchField<Type> >
            (
                new externalPatchToPatchMappingFvPatchField<Type>(*this, iF)
            );
        }


    // Member functions

        // Mapping functions

            //- Map (and resize as needed) from self given a mapping object
            virtual void autoMap
            (
                const fvPatchFieldMapper&
            );

            //- Reverse map the given fvPatchField onto this fvPatchField
            virtual void rmap
            (
                const fvPatchField<Type>&,
                const labelList&
            );


        // Evaluation functions

            //- Update the coefficients associated with the patch field
            virtual void updateCoeffs();


        //- Write
        virtual void write(Ostream&) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
#   include "externalPatchToPatchMappingFvPatchField.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
