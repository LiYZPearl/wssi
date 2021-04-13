    const dictionary& stressControl =
        mesh.solutionDict().subDict("anisotropicBiotLiqueFoam");

    int nCorr(readInt(stressControl.lookup("nCorrectors")));
    scalar convergenceTolerance(readScalar(stressControl.lookup("U")));
