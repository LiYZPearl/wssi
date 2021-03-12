    const dictionary& stressControl =
        mesh.solutionDict().subDict("elasticStructureFoam");

    int nCorr(readInt(stressControl.lookup("nCorrectors")));
    scalar convergenceTolerance(readScalar(stressControl.lookup("U")));
