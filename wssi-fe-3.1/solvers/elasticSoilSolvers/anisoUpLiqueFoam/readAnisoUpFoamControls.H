    const dictionary& stressControl =
        mesh.solutionDict().subDict("upFoam");

    int nCorr(readInt(stressControl.lookup("nCorrectors")));
    scalar convergenceTolerance(readScalar(stressControl.lookup("U")));
