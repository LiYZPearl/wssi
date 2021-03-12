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

#include "externalPatchToPatchMappingFvPatchField.H"
#include "Time.H"
#include "triSurfaceTools.H"
#include "triSurface.H"
#include "vector2D.H"
#include "OFstream.H"
#include "long.H"
#include "AverageIOField.H"
//#include "PatchToPatchInterpolation.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
externalPatchToPatchMappingFvPatchField<Type>::
externalPatchToPatchMappingFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF
)
:
    fixedValueFvPatchField<Type>(p, iF),
    fieldTableName_(iF.name()),
    setAverage_(false),
    sampleTimes_(0),
    startSampleTime_(-1),
    startSampledValues_(0),
    startAverage_(pTraits<Type>::zero),
    endSampleTime_(-1),
    endSampledValues_(0),
    endAverage_(pTraits<Type>::zero)
{
    if (debug)
    {
        Pout<< "externalPatchToPatchMapping :"
            << " construct from fvPatch and internalField" << endl;
    }
}


template<class Type>
externalPatchToPatchMappingFvPatchField<Type>::
externalPatchToPatchMappingFvPatchField
(
    const externalPatchToPatchMappingFvPatchField<Type>& ptf,
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchField<Type>(ptf, p, iF, mapper),
    fieldTableName_(ptf.fieldTableName_),
    setAverage_(ptf.setAverage_),
  //  mapperPtr_(ptf.mapperPtr_),
    sampleTimes_(0),
    startSampleTime_(-1),
    startSampledValues_(0),
    startAverage_(pTraits<Type>::zero),
    endSampleTime_(-1),
    endSampledValues_(0),
    endAverage_(pTraits<Type>::zero)
{
    if (debug)
    {
        Pout<< "externalPatchToPatchMapping"
            << " : construct from mappedFixedValue and mapper" << endl;
    }
}


template<class Type>
externalPatchToPatchMappingFvPatchField<Type>::
externalPatchToPatchMappingFvPatchField
(
    const fvPatch& p,
    const DimensionedField<Type, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchField<Type>(p, iF),
    fieldTableName_(iF.name()),
    setAverage_(readBool(dict.lookup("setAverage"))),
  //  mapperPtr_(NULL),
    sampleTimes_(0),
    startSampleTime_(-1),
    startSampledValues_(0),
    startAverage_(pTraits<Type>::zero),
    endSampleTime_(-1),
    endSampledValues_(0),
    endAverage_(pTraits<Type>::zero)
{
    if (debug)
    {
        Pout<< "externalPatchToPatchMapping : construct from dictionary"
            << endl;
    }

    if (dict.found("fieldTableName"))
    {
        dict.lookup("fieldTableName") >> fieldTableName_;
    }

    if (dict.found("value"))
    {
        fvPatchField<Type>::operator==(Field<Type>("value", dict, p.size()));
    }
    else
    {
        updateCoeffs();
    }
}


template<class Type>
externalPatchToPatchMappingFvPatchField<Type>::
externalPatchToPatchMappingFvPatchField
(
    const externalPatchToPatchMappingFvPatchField<Type>& ptf
)
:
    fixedValueFvPatchField<Type>(ptf),
    fieldTableName_(ptf.fieldTableName_),
    setAverage_(ptf.setAverage_),
   // mapperPtr_(ptf.mapperPtr_),
    sampleTimes_(ptf.sampleTimes_),
    startSampleTime_(ptf.startSampleTime_),
    startSampledValues_(ptf.startSampledValues_),
    startAverage_(ptf.startAverage_),
    endSampleTime_(ptf.endSampleTime_),
    endSampledValues_(ptf.endSampledValues_),
    endAverage_(ptf.endAverage_)
{
    if (debug)
    {
        Pout<< "externalPatchToPatchMapping : copy construct"
            << endl;
    }
}



template<class Type>
externalPatchToPatchMappingFvPatchField<Type>::
externalPatchToPatchMappingFvPatchField
(
    const externalPatchToPatchMappingFvPatchField<Type>& ptf,
    const DimensionedField<Type, volMesh>& iF
)
:
    fixedValueFvPatchField<Type>(ptf, iF),
    fieldTableName_(ptf.fieldTableName_),
    setAverage_(ptf.setAverage_),
  //  mapperPtr_(ptf.mapperPtr_),
    sampleTimes_(ptf.sampleTimes_),
    startSampleTime_(ptf.startSampleTime_),
    startSampledValues_(ptf.startSampledValues_),
    startAverage_(ptf.startAverage_),
    endSampleTime_(ptf.endSampleTime_),
    endSampledValues_(ptf.endSampledValues_),
    endAverage_(ptf.endAverage_)
{
    if (debug)
    {
        Pout<< "externalPatchToPatchMapping :"
            << " copy construct, resetting internal field" << endl;
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void externalPatchToPatchMappingFvPatchField<Type>::autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedValueFvPatchField<Type>::autoMap(m);
    if (startSampledValues_.size() > 0)
    {
        startSampledValues_.autoMap(m);
        endSampledValues_.autoMap(m);
    }
    //Clear interpolator
  //  mapperPtr_.clear();
    startSampleTime_ = -1;
    endSampleTime_ = -1;
}


template<class Type>
void externalPatchToPatchMappingFvPatchField<Type>::rmap
(
    const fvPatchField<Type>& ptf,
    const labelList& addr
)
{
    fixedValueFvPatchField<Type>::rmap(ptf, addr);

    const externalPatchToPatchMappingFvPatchField<Type>& tiptf =
        refCast<const externalPatchToPatchMappingFvPatchField<Type> >(ptf);

    startSampledValues_.rmap(tiptf.startSampledValues_, addr);
    endSampledValues_.rmap(tiptf.endSampledValues_, addr);

    //Clear interpolator
 //   mapperPtr_.clear();
    startSampleTime_ = -1;
    endSampleTime_ = -1;
}


template<class Type>
wordList externalPatchToPatchMappingFvPatchField<Type>::timeNames
(
    const instantList& times
)
{
    wordList names(times.size());

    forAll(times, i)
    {
        names[i] = times[i].name();
    }
    return names;
}


template<class Type>
void externalPatchToPatchMappingFvPatchField<Type>::findTime
(
    const fileName& instance,
    const fileName& local,
    const scalar timeVal,
    label& lo,
    label& hi
) const
{
    lo = startSampleTime_;
    hi = -1;

    for (label i = startSampleTime_+1; i < sampleTimes_.size(); i++)
    {
        if (sampleTimes_[i].value() > timeVal)
        {
            break;
        }
        else
        {
            lo = i;
        }
    }

    if (lo == -1)
    {
        FatalErrorIn("findTime")
            << "Cannot find starting sampling values for current time "
            << timeVal << nl
            << "Have sampling values for times "
            << timeNames(sampleTimes_) << nl
            << "In directory "
            <<  this->db().time().constant()/"boundaryData"/this->patch().name()
            << "\n    on patch " << this->patch().name()
            << " of field " << fieldTableName_
            << exit(FatalError);
    }

    if (lo < sampleTimes_.size()-1)
    {
        hi = lo+1;
    }


    if (debug)
    {
        if (hi == -1)
        {
            Pout<< "findTime : Found time " << timeVal << " after"
                << " index:" << lo << " time:" << sampleTimes_[lo].value()
                << endl;
        }
        else
        {
            Pout<< "findTime : Found time " << timeVal << " inbetween"
                << " index:" << lo << " time:" << sampleTimes_[lo].value()
                << " and index:" << hi << " time:" << sampleTimes_[hi].value()
                << endl;
        }
    }
}


template<class Type>
void externalPatchToPatchMappingFvPatchField<Type>::checkTable()
{
    // Initialise
     pointIOField samplePoints
    (
        IOobject
        (
            "points",
            this->db().time().constant(),
            "boundaryData"/this->patch().name(),
            this->db(),
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE,
            false
        )
    );
  Info<< "sample points is done" << endl; 
  
    faceIOList sampleFaces
    (
        IOobject
        (
            "faces",
            this->db().time().constant(),
            "boundaryData"/this->patch().name(),
            this->db(),
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE,
            false
        )
    );
    Info<< "sample faces is done" << endl; 

    typedef PrimitivePatch<face, List, const pointField&> standAlonePatch;

    standAlonePatch fromWavePatch(sampleFaces,samplePoints);

    PatchToPatchInterpolation<standAlonePatch,polyPatch> waveToStruct
        (
           fromWavePatch,
           this->patch().patch()
        );

    //mapperPtr_.reset
   // (
   //     waveToStruct
   // );
                            

    const fileName samplePointsFile = samplePoints.filePath();


    Info<< "externalPatchToPatchMappingFvPatchField :"
            << " Read " << samplePoints.size() << " sample points from "
            << samplePointsFile << endl;

    // Read the times for which data is available

    const fileName samplePointsDir = samplePointsFile.path();

    sampleTimes_ = Time::findTimes(samplePointsDir);

    Info<< "externalPatchToPatchMappingFvPatchField : In directory "
            << samplePointsDir << " found times " << timeNames(sampleTimes_)
            << endl;

    // Find current time in sampleTimes
    label lo = -1;
    label hi = -1;

    findTime
    (
        this->db().time().constant(),
        "boundaryData"/this->patch().name(),
        this->db().time().value(),
        lo,
        hi
    );

    // Update sampled data fields.

    if (lo != startSampleTime_)
    {
        startSampleTime_ = lo;

        if (startSampleTime_ == endSampleTime_)
        {
            // No need to reread since are end values
       
                Pout<< "checkTable : Setting startValues to (already read) "
                    <<   "boundaryData"
                        /this->patch().name()
                        /sampleTimes_[startSampleTime_].name()
                    << endl;
          
            startSampledValues_ = endSampledValues_;
            startAverage_ = endAverage_;
        }
        else
        {
            
                Pout<< "checkTable : Reading startValues from "
                    <<   "boundaryData"
                        /this->patch().name()
                        /sampleTimes_[lo].name()
                    << endl;
          


            // Reread values and interpolate
            AverageIOField<Type> vals
            (
                IOobject
                (
                    fieldTableName_,
                    this->db().time().constant(),
                    "boundaryData"
                   /this->patch().name()
                   /sampleTimes_[startSampleTime_].name(),
                    this->db(),
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE,
                    false
                )
            );

            startAverage_ = vals.average();
            
            Info<<"Start faceInterpolate!!!"<<endl;
            startSampledValues_ = waveToStruct.faceInterpolate(vals);
            Info<<"Complete interpolation!!!"<<endl;
        }
    }

    if (hi != endSampleTime_)
    {
        endSampleTime_ = hi;

        if (endSampleTime_ == -1)
        {
            // endTime no longer valid. Might as well clear endValues.
            
                Pout<< "checkTable : Clearing endValues" << endl;
            
            endSampledValues_.clear();
        }
        else
        {
            
                Pout<< "checkTable : Reading endValues from "
                    <<   "boundaryData"
                        /this->patch().name()
                        /sampleTimes_[endSampleTime_].name()
                    << endl;
          
            // Reread values and interpolate
            AverageIOField<Type> vals
            (
                IOobject
                (
                    fieldTableName_,
                    this->db().time().constant(),
                    "boundaryData"
                   /this->patch().name()
                   /sampleTimes_[endSampleTime_].name(),
                    this->db(),
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE,
                    false
                )
            );
            endAverage_ = vals.average();
            endSampledValues_ = waveToStruct.faceInterpolate(vals);
        }
    }
}

template<class Type>
void externalPatchToPatchMappingFvPatchField<Type>::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    checkTable();

    // Interpolate between the sampled data

    Type wantedAverage;

    if (endSampleTime_ == -1)
    {
        // only start value
        
            Pout<< "updateCoeffs : Sampled, non-interpolated values"
                << " from start time:"
                << sampleTimes_[startSampleTime_].name() << nl;
       

        this->operator==(startSampledValues_);
        wantedAverage = startAverage_;
    }
    else
    {
        scalar start = sampleTimes_[startSampleTime_].value();
        scalar end = sampleTimes_[endSampleTime_].value();

        scalar s = (this->db().time().value()-start)/(end-start);

       
            Pout<< "updateCoeffs : Sampled, interpolated values"
                << " between start time:"
                << sampleTimes_[startSampleTime_].name()
                << " and end time:" << sampleTimes_[endSampleTime_].name()
                << " with weight:" << s << endl;
        

        this->operator==((1-s)*startSampledValues_ + s*endSampledValues_);
        wantedAverage = (1-s)*startAverage_ + s*endAverage_;
    }

    // Enforce average. Either by scaling (if scaling factor > 0.5) or by
    // offsetting.
    if (setAverage_)
    {
        const Field<Type>& fld = *this;

        Type averagePsi =
            gSum(this->patch().magSf()*fld)
           /gSum(this->patch().magSf());

        
            Pout<< "updateCoeffs :"
                << " actual average:" << averagePsi
                << " wanted average:" << wantedAverage
                << endl;
       

        if (mag(averagePsi) < VSMALL)
        {
            // Field too small to scale. Offset instead.
            const Type offset = wantedAverage - averagePsi;
            
                Pout<< "updateCoeffs :"
                    << " offsetting with:" << offset << endl;
            
            this->operator==(fld+offset);
        }
        else
        {
            const scalar scale = mag(wantedAverage)/mag(averagePsi);

           
                Pout<< "updateCoeffs :"
                    << " scaling with:" << scale << endl;
            
            this->operator==(scale*fld);
        }
    }

    if (debug)
    {
        Pout<< "updateCoeffs : set fixedValue to min:" << gMin(*this)
            << " max:" << gMax(*this) << endl;
    }

    fixedValueFvPatchField<Type>::updateCoeffs();
}


template<class Type>
void externalPatchToPatchMappingFvPatchField<Type>::write(Ostream& os) const
{
    fvPatchField<Type>::write(os);
    os.writeKeyword("setAverage") << setAverage_ << token::END_STATEMENT << nl;

    if (fieldTableName_ != this->dimensionedInternalField().name())
    {
        os.writeKeyword("fieldTableName") << fieldTableName_ << token::END_STATEMENT << nl;
    }

    this->writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
