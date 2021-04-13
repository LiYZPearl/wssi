p.storePrevIter();

volVectorField d2dt2U(fvc::d2dt2(U));

volVectorField UPvector (rho_w * d2dt2U /* - rho_w * g */);


fvScalarMatrix pEqn
(
fvm::ddt(p) == fvm::laplacian(Dp, p) - fvc::div(fvc::ddt(Dp2,U))  + fvc::div(Dp & UPvector) //- fvm::div(Dp*rhoW,g)   
);

pResidual = pEqn.solve().initialResidual();
p.relax(); 

