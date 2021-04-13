U.storePrevIter();

fvVectorMatrix UEqn
(
fvm::d2dt2(rho, U)
==
fvm::laplacian(K, U, "laplacian(DU,U)")

+ fvc::div(sigma)

- fvc::div(K & gradU)

- fvc::grad(p)
);

UResidual = UEqn.solve().initialResidual();
U.relax();
gradU = fvc::grad(U);

