    const dictionary& stressControl =
        mesh.solutionDict().subDict("biotConsolidationFoam");

    int nCorr(readInt(stressControl.lookup("nCorrectors")));
    scalar convergenceTolerance(readScalar(stressControl.lookup("U")));
