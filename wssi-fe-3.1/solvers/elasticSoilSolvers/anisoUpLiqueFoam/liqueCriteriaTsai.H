//const scalarField& pI = p.internalField();
//scalarField& InitEffSigmaMeanI = InitEffSigmaMean.internalField();
scalarField sigmaMeanI = (sigma.component(symmTensor::XX) + sigma.component(symmTensor::YY) + sigma.component(symmTensor::ZZ))/3.0;
scalarField& liqueFlagTsaiI = liqueFlagTsai.internalField();

//label patchID = mesh.boundaryMesh().findPatchID("seabed");
//const scalarField& pPatch = p.boundaryField()[patchID];
//const vectorField& bc = mesh.C().boundaryField()[patchID];

forAll (liqueFlagTsaiI,cellI)
{
/*
  scalar zpos = mesh.C()[cellI].z();
  scalar xpos = mesh.C()[cellI].x();
  scalar ypos = mesh.C()[cellI].y();

  //calculate 1q
  // if the z=0 is at the free surface, water depth needs to be input
  scalar lq = - (zpos + waterdepth.value()) *(gamma_s.value()-gamma_w.value())*2.0/3.0; //gamma_s=26500, gamma_w=10000  p-pb>=lq
  
  //get pb at the boundary patch with the same x,y

  scalar pb(10000.0);

  forAll(pPatch,faceI)
 // forAll(faceI)
   {
     scalar xfpos = bc[faceI].x();
     scalar yfpos = bc[faceI].y();
     //if (abs(xpos-xfpos)<=SMALL && abs(ypos-yfpos)<=SMALL)
      if (fabs(xpos-xfpos)<=0.0001 && fabs(ypos-yfpos)<=0.0001)
      {pb=pPatch[faceI]; //  
	//Info<< "xpos-xfpos, abs=" << xpos-xfpos<<','<<abs(xpos-xfpos)<< nl
	//<< "ypos-yfpos,abs=" << ypos-yfpos<<','<< abs(ypos-yfpos)<<endl; 
	} 
   } 
*/ 
  scalar lq = 0.0;
  if ((sigmaMeanI[cellI] - lq)>= -initEffSigmaMeanI[cellI]) 
    {
      liqueFlagTsaiI[cellI] = 1;
    }
   else
   {
      liqueFlagTsaiI[cellI] = 0;
    }
}


