//InitEffSigmazz < excess pore pressure
//criterion of Zen & Yamazaki (1990), extended by Jeng(1997)
//modified considering the presence of the structure



scalarField& liqueFlagZenI = liqueFlagZen.internalField();

forAll (liqueFlagZenI,cellI)
{
  //scalar zpos = mesh.C()[cellI].z();
  scalar xpos = mesh.C()[cellI].x();
  scalar ypos = mesh.C()[cellI].y();

  //get pb at the boundary patch with the same x,y

  scalar pb(0.0);

  forAll(pPatch,faceI)
   {
     scalar xfpos = bc[faceI].x();
     scalar yfpos = bc[faceI].y();
     //if (abs(xpos-xfpos)<=SMALL && abs(ypos-yfpos)<=SMALL)
	if (fabs(xpos-xfpos)<=0.0001 && fabs(ypos-yfpos)<=0.0001)
          {pb=pPatch[faceI];  
	} 
   } 

   scalar lq = (pI[cellI] - pb) - (-initEffSigmazzI[cellI]);  
   if (lq >= 0)
    {
     liqueFlagZenI[cellI] = 1;
    }
   else
    {
     liqueFlagZenI[cellI] = 0;
    }   
}
