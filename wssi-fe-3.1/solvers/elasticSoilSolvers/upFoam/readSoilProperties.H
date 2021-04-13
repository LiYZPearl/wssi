    Info<< "Reading soil properties\n" << endl;

    IOdictionary soilProperties
    (
        IOobject
        (
            "soilProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );

    dimensionedScalar kx(soilProperties.lookup("kx"));
    dimensionedScalar ky(soilProperties.lookup("ky"));
    dimensionedScalar kz(soilProperties.lookup("kz"));  
    dimensionedScalar K_(soilProperties.lookup("K"));
    dimensionedScalar Sr(soilProperties.lookup("Sr"));
    dimensionedScalar p0(soilProperties.lookup("p0"));
    dimensionedScalar rho_w(soilProperties.lookup("rho_w"));
    dimensionedScalar rho_s(soilProperties.lookup("rho_s"));
    dimensionedScalar K0(soilProperties.lookup("K0"));
    dimensionedScalar n_(soilProperties.lookup("n"));
    //word wave(soilProperties.lookup("wave"));
    //dimensionedScalar T_(soilProperties.lookup("T"));
    //dimensionedScalar L_(soilProperties.lookup("L"));
    //dimensionedScalar pb0(soilProperties.lookup("pb0"));
    dimensionedScalar Kprime = 1.0/(1.0/K_ + (1.0-Sr)/p0);

    dimensionedVector g(soilProperties.lookup("gravity"));
    dimensionedScalar gamma_w = rho_w * mag(g);
    dimensionedScalar gamma_s = rho_s * mag(g);
    //calculate the rho for mixture
    dimensionedScalar rho = n_ * rho_w + (1 - n_) * rho_s;


    tensor Dpu( (kx/gamma_w*Kprime/n_).value(), 0,   0,
	  0,    (ky/gamma_w*Kprime/n_).value(), 0,
	  0,   0,    (kz/gamma_w*Kprime/n_).value());

    volTensorField Dp
   (
     IOobject
     (
      "Dp",
      runTime.timeName(),
      mesh,
      IOobject::NO_READ,
      IOobject::NO_WRITE
     ),
     mesh,
     dimensionedTensor
     (
      "Dp",
      dimensionSet(0, 2, -1 , 0, 0),
      Dpu
     ),
     zeroGradientFvPatchTensorField::typeName    
    );

    Dp.correctBoundaryConditions();
    dimensionedScalar Dp1
    (
        "Dp1",
        dimensionSet(0, 2, -1, 0, 0),
        (kx/gamma_w*Kprime/n_).value()
    );
    dimensionedScalar Dp2
    (
        "Dp2",
        dimensionSet(1, -1, -2 , 0, 0),
        (Kprime/n_).value()
    );
    
    Info<< "Dp = " << Dpu << " m^2/s \n";
    Info<< "Dp2 = " << Dp2.value() << " kg/m/s^2\n";

    
    scalar Ex = 0;
    scalar Ey = 0;
    scalar Ez = 0;
    scalar vxy = 0;
    scalar vyz = 0;
    scalar vzx = 0;
    scalar Gxy = 0;
    scalar Gyz = 0;
    scalar Gzx = 0;

    scalar vyx = 0;
    scalar vxz = 0;
    scalar vzy = 0;

    Switch model2d(soilProperties.lookup("model2D"));
   
    if(model2d)
    {
     Ex = readScalar(soilProperties.lookup("Ex"));
     Ey = readScalar(soilProperties.lookup("Ey"));
     vxy = readScalar(soilProperties.lookup("nuxy"));
     Gxy = readScalar(soilProperties.lookup("Gxy"));

     //- material contraints
     vyx = vxy*Ey/Ex;

     Info << "2D model (z is assumed to be the empty direction)" << nl
	  << "Linear elastic orthotropic properties are:\n"
	  << "Ex " << Ex/1e9 << " GPa" << nl
	  << "Ey " << Ey/1e9 << " GPa" << nl
	  << "nuxy " << vxy << nl
	  << "Gxy " << Gxy/1e9 << " GPa" << endl;
     }
    else // 3D
    {
     Ex = readScalar(soilProperties.lookup("Ex"));
     Ey = readScalar(soilProperties.lookup("Ey"));
     Ez = readScalar(soilProperties.lookup("Ez"));
     vxy = readScalar(soilProperties.lookup("nuxy"));
     vyz = readScalar(soilProperties.lookup("nuyz"));
     vzx = readScalar(soilProperties.lookup("nuzx"));
     Gxy = readScalar(soilProperties.lookup("Gxy"));
     Gyz = readScalar(soilProperties.lookup("Gyz"));
     Gzx = readScalar(soilProperties.lookup("Gzx"));

     //- material contraints
     vyx = vxy*Ey/Ex;
     vxz = vzx*Ex/Ez;
     vzy = vyz*Ez/Ey;

     Info << "3D model" << nl
	  << "Linear elastic orthotropic properties are:\n"
	  << "Ex " << Ex/1e9 << " GPa" << nl
	  << "Ey " << Ey/1e9 << " GPa" << nl
	  << "Ez " << Ez/1e9 << " GPa" << nl
	  << "nuxy " << vxy << nl
	  << "nuyz " << vyz << nl
	  << "nuzx " << vzx << nl
	  << "Gxy " << Gxy/1e9 << " GPa" << nl
	  << "Gyz " << Gyz/1e9 << " GPa" << nl
	  << "Gzx " << Gzx/1e9 << " GPa" << endl;
    }

    //- components of C - fourth order elastic constants tensor
	scalar J = 0;
	scalar A11 = 0;
	scalar A22 = 0;
	scalar A33 = 0;
	scalar A12 = 0;
	scalar A31 = 0;
	scalar A23 = 0;
	scalar A44 = 0;
	scalar A55 = 0;
	scalar A66 = 0;

	scalar A21 = 0;

	if(model2d)
	  {
	    J = 1 / (1 - vxy*vyx);
	    A11 = J*Ex;
	    A22 = J*Ey;
	    A12 = J*vyx*Ex;
	    A21 = J*vxy*Ey;
	    A44 = 2*Gxy;

	    Info << "\n2D stiffness coefficients are:" << nl
		 << "A11 " << A11 << nl
		 << "A22 " << A22 << nl
		 << "A12 " << A12 << nl
		 << "A21 " << A21 << nl
		 << "A44 " << A44 << endl;
	  }
	 else
	   {
	      J = (1.0 - vxy*vyx - vyz*vzy - vzx*vxz - 2*vyx*vzy*vxz) / (Ex*Ey*Ez);
	      A11 = (1.0 - vyz*vzy)/(J*Ey*Ez);
	      A22 = (1.0 - vxz*vzx)/(J*Ex*Ez);
	      A33 = (1.0 - vyx*vxy)/(J*Ey*Ex);
	      A12 = (vxy + vzy*vxz)/(J*Ex*Ez);
	      A31 = (vzx + vyx*vzy)/(J*Ey*Ez);
	      A23 = (vyz + vyx*vxz)/(J*Ex*Ey);
	      A44 = 2*Gxy;
	      A55 = 2*Gyz;
	      A66 = 2*Gzx;

	      Info << "\n3D stiffness coefficients:" << nl
		   << "A11 " << A11 << nl
		   << "A22 " << A22 << nl
		   << "A33 " << A33 << nl
		   << "A12 " << A12 << nl
		   << "A31 " << A31 << nl
		   << "A23 " << A23 << endl;
	   }

	   tensor Ku(A11, 0,   0,
		  0,   A22, 0,
		  0,   0,   A33);

	Info << "\nThe implicit stiffness tensor K is " << Ku << endl;

	volTensorField K
	(
	 IOobject
	 (
	  "K",
	  runTime.timeName(),
	  mesh,
	  IOobject::NO_READ,
	  IOobject::NO_WRITE
	  ),
	 mesh,
	 dimensionedTensor
	 (
	  "zero",
	  dimensionSet(1,-1,-2,0,0,0,0),
	  Ku
	 ),
	 zeroGradientFvPatchTensorField::typeName    
	 );

    K.correctBoundaryConditions();

    
