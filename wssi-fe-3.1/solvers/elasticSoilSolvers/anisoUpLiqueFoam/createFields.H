    Info<< "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    volTensorField gradU = fvc::grad(U);

    Info<< "Reading pore pressure field p\n" << endl;

    volScalarField p
    (
       IOobject
      (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
    );

    volSymmTensorField epsilon
    (
        IOobject
        (
            "epsilon",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimless, symmTensor::zero)
    );

    volSymmTensorField sigma
    (
        IOobject
        (
            "sigma",
            runTime.timeName(),
            mesh,
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedSymmTensor("zero", dimForce/dimArea, symmTensor::zero)
    );

   Info<<"reading the fake structural stress field\n"<<endl;
    volSymmTensorField sigma_S
    (
        IOobject
        (
            "sigma_S",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

   Info<<"reading the initial effective vertical stress from consolidation process\n" <<endl;

    volScalarField initEffSigmazz
    (
       IOobject
      (
        "initEffSigmazz",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
    );


  Info<<"reading the initial effective mean stress from consolidation process\n" <<endl;

    volScalarField initEffSigmaMean
    (
       IOobject
      (
        "initEffSigmaMean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
    );

   Info<< "creating liquefaction flag field liqueFlag\n" << endl;

    volScalarField liqueFlagOkusa
    (
       IOobject
      (
        "liqueFlagOkusa",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("liqueFlagOkusa",dimless,0)
    );  
/*
    volScalarField liqueFlagTsai
    (
       IOobject
      (
        "liqueFlagTsai",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("liqueFlagTsai",dimless,0)
    );  
*/
    volScalarField liqueFlagZen
    (
       IOobject
      (
        "liqueFlagZen",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("liqueFlagZen",dimless,0)
    );  

surfaceVectorField n = mesh.Sf()/mesh.magSf();

