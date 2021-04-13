//three criteria are implemented
//Criterion extended from Okusa(1985)
//criterion of Zen & Yamazaki (1990), extended by Jeng(1997)
//criterion extended from Tsai (1995)
//all modified considering the presence of the structure

scalarField& initEffSigmazzI = initEffSigmazz.internalField();
scalarField& initEffSigmaMeanI = initEffSigmaMean.internalField();
const scalarField& pI = p.internalField();
label patchID = mesh.boundaryMesh().findPatchID("seabed");
const scalarField& pPatch = p.boundaryField()[patchID];
const vectorField& bc = mesh.C().boundaryField()[patchID];


#       include "liqueCriteriaOkusa.H"  
//#       include "liqueCriteriaTsai.H"  
#       include "liqueCriteriaZen.H"  
