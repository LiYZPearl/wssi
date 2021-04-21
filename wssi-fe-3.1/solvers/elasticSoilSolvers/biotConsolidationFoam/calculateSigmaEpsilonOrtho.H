//- calculate epsilon and sigma for an orthotropic material

//- epsilon
epsilon = symm(gradU);

//- sigma = C:epsilon
forAll(sigma.internalField(), celli)
{
  const scalar& e11 = epsilon.internalField()[celli].component(symmTensor::XX);
  const scalar& e22 = epsilon.internalField()[celli].component(symmTensor::YY);
  const scalar& e33 = epsilon.internalField()[celli].component(symmTensor::ZZ);
  const scalar& e12 = epsilon.internalField()[celli].component(symmTensor::XY);
  const scalar& e23 = epsilon.internalField()[celli].component(symmTensor::YZ);
  const scalar& e31 = epsilon.internalField()[celli].component(symmTensor::XZ);

  if(model2d)
    {
      sigma.internalField()[celli].component(symmTensor::XX) = A11*e11 + A12*e22;
      sigma.internalField()[celli].component(symmTensor::YY) = A21*e11 + A22*e22;
      sigma.internalField()[celli].component(symmTensor::XY) = A44*e12;
    }
  else
    {
      sigma.internalField()[celli].component(symmTensor::XX) = A11*e11 + A12*e22 + A31*e33;
      sigma.internalField()[celli].component(symmTensor::YY) = A12*e11 + A22*e22 + A23*e33;
      sigma.internalField()[celli].component(symmTensor::ZZ) = A31*e11 + A23*e22 + A33*e33;
      sigma.internalField()[celli].component(symmTensor::XY) = A44*e12;
      sigma.internalField()[celli].component(symmTensor::YZ) = A55*e23;
      sigma.internalField()[celli].component(symmTensor::XZ) = A66*e31;
    }
}

forAll(mesh.boundary(), patchi)
{
  forAll(sigma.boundaryField()[patchi], facei)
    {
      const scalar& e11 = epsilon.boundaryField()[patchi][facei].component(symmTensor::XX);
      const scalar& e22 = epsilon.boundaryField()[patchi][facei].component(symmTensor::YY);
      const scalar& e33 = epsilon.boundaryField()[patchi][facei].component(symmTensor::ZZ);
      const scalar& e12 = epsilon.boundaryField()[patchi][facei].component(symmTensor::XY);
      const scalar& e23 = epsilon.boundaryField()[patchi][facei].component(symmTensor::YZ);
      const scalar& e31 = epsilon.boundaryField()[patchi][facei].component(symmTensor::XZ);
      
      if(model2d)
	{
	  sigma.boundaryField()[patchi][facei].component(symmTensor::XX) = A11*e11 + A12*e22;
	  sigma.boundaryField()[patchi][facei].component(symmTensor::YY) = A21*e11 + A22*e22;
	  sigma.boundaryField()[patchi][facei].component(symmTensor::XY) = A44*e12;
	}
      else
	{
	  sigma.boundaryField()[patchi][facei].component(symmTensor::XX) = A11*e11 + A12*e22 + A31*e33;
	  sigma.boundaryField()[patchi][facei].component(symmTensor::YY) = A12*e11 + A22*e22 + A23*e33;
	  sigma.boundaryField()[patchi][facei].component(symmTensor::ZZ) = A31*e11 + A23*e22 + A33*e33;
	  sigma.boundaryField()[patchi][facei].component(symmTensor::XY) = A44*e12;
	  sigma.boundaryField()[patchi][facei].component(symmTensor::YZ) = A55*e23;
	  sigma.boundaryField()[patchi][facei].component(symmTensor::XZ) = A66*e31;
	}
    }
}
