//initEffSigmazz < dynamicEffsigmazz
//Criteria extended from Okusa(1985)

scalarField& liqueFlagOkusaI = liqueFlagOkusa.internalField();

scalarField effSigmazzI = sigma.component(symmTensor::ZZ);

forAll (liqueFlagOkusaI,cellI)
{
   scalar lq = -(initEffSigmazzI[cellI]) - effSigmazzI[cellI];
   if (lq <= 0)
    {
     liqueFlagOkusaI[cellI] = 1;
    }
   else
    {
     liqueFlagOkusaI[cellI] = 0;
    }   
}



