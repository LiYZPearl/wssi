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

   Info<<"reading the initial effective stress from consolidation process\n" <<endl;

    volScalarField initEffSigmazz
    (
       IOobject
      (
        "initEffSigmazz",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimForce/dimArea, 0)
    );



    Info<< "creating liquefaction flag field liqueFlag\n" << endl;

    volScalarField liqueFlag
    (
       IOobject
      (
        "liqueFlag",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("liqueFlag",dimless,0)
    );  

surfaceVectorField n = mesh.Sf()/mesh.magSf();

