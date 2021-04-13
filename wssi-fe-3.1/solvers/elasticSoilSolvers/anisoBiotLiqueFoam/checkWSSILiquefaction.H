//InitEffSigmazz < DynamicEffsigmazz

if(preConsolidationAnalysis)
{

	scalarField& initEffSigmazzI = initEffSigmazz.internalField();

	const scalarField& pI = p.internalField();
	scalarField& liqueFlagI = liqueFlag.internalField();

	label patchID = mesh.boundaryMesh().findPatchID("seabed");
	const scalarField& pPatch = p.boundaryField()[patchID];
	const vectorField& bc = mesh.C().boundaryField()[patchID];

	forAll (liqueFlagI,cellI)
	{
	  scalar zpos = mesh.C()[cellI].z();
	  scalar xpos = mesh.C()[cellI].x();
	  scalar ypos = mesh.C()[cellI].y();

	  //get pb at the boundary patch with the same x,y

	  scalar pb(0.0);

	  forAll(pPatch,faceI)
	   {
	     scalar xfpos = bc[faceI].x();
	     scalar yfpos = bc[faceI].y();
	     //if (abs(xpos-xfpos)<=SMALL && abs(ypos-yfpos)<=SMALL)
		if (fabs(xpos-xfpos)<=0.00001 && fabs(ypos-yfpos)<=0.00001)
		  {pb=pPatch[faceI]; //  
		} 
	   } 

	   scalar lq = (pI[cellI] - pb) - (-initEffSigmazzI[cellI]);  //when p is negative, it is drag
	   if (lq >= 0)
	    {
	     liqueFlagI[cellI] = 1;
	    }
	   else
	    {
	     liqueFlagI[cellI] = 0;
	    }   
	}
}
else
{
	const scalarField& pI = p.internalField();
	scalarField& liqueFlagI = liqueFlag.internalField();

	label patchID = mesh.boundaryMesh().findPatchID("seabed");
	const scalarField& pPatch = p.boundaryField()[patchID];
	const vectorField& bc = mesh.C().boundaryField()[patchID];

	forAll (liqueFlagI,cellI)
	{
	  scalar zpos = mesh.C()[cellI].z();
	  scalar xpos = mesh.C()[cellI].x();
	  scalar ypos = mesh.C()[cellI].y();

	  //calculate 1q
	  // eg. scalar waterdepth = 8.0 m;
	  scalar lq = - (zpos + waterdepth.value()) *(gamma_s.value()-gamma_w.value())*2.0/3.0; 
	  
	  //get pb at the boundary patch with the same x,y

	  scalar pb(0.0);

	  forAll(pPatch,faceI)

	   {
	     scalar xfpos = bc[faceI].x();
	     scalar yfpos = bc[faceI].y();

	if (fabs(xpos-xfpos)<=0.0001 && fabs(ypos-yfpos)<=0.0001)
	      {pb=pPatch[faceI]; //  

		} 

	   } 
	  
	  if ((pI[cellI]- pb)>=lq) 
	    {
	      liqueFlagI[cellI] = 1;

	    }
	   else
	   {
	      liqueFlagI[cellI] = 0;
	    }
	}
}
