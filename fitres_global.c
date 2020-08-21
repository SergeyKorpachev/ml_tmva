void fitres( const int fenergy = 5, const int nBins = 1000, const float range = 1.3, const float lr = 1.0, const float rr = 1.0 ) {
    
    int nfiles = 9;

    char fname[ 200 ];
    char ftempname[ 200 ];
    char fname2[ 200 ];

    for ( int i = 0; i < 200; i++ ) fname[ i ] = 0;
    for ( int i = 0; i < 200; i++ ) ftempname[ i ] = 0;
    for ( int i = 0; i < 200; i++ ) fname2[ i ] = 0;

    sprintf( ftempname, "gun_k0L_%dgev_FTFP_BERT_10000evt_ILD_l5_v02steel", fenergy );
    sprintf( fname, "%s.root", ftempname );

    TF1 *fitFunc;
    TF1 *fitFunc2;
    TH1F *hist;
    
    TCanvas *c1 = new TCanvas("c1", "c1", 1);
    gStyle->SetOptStat(0);

    const char *treeName = "tree";
    const float binLo = 0.0;
    const float binHi = fenergy + 20.0;

    //  const float cut = 2.0; //0.6 * sqrt( energy );
    
    //
    // Open data file
    //
    std::cout << "Trying to open data file... ";
    TFile *file = new TFile(fname, "READ");
    if (!file) { // if error occure then exit
        std::cout << "[FAIL]" << std::endl;
        return;
    }
    std::cout << "[OK]" << std::endl;

    //
    // Open file for output
    //
    FILE *out = fopen("out.txt", "a+");
        printf("File open... ");
        if (!out) {
            printf("[FAIL]\n");
            return;
        } else printf("[OK]\n");

    //
    // Setup a TTree
    //
    std::cout << "Setup a tree... ";
    TTree *tree = (TTree *)file->Get(treeName);
    if (!tree) {
        std::cout << "[FAIL]" << std::endl;
        file->Close();
        return;
    }
    std::cout << "[OK]" << std::endl;

    unsigned int nEvents = tree->GetEntries();

    //
    // Setup a branch
    //
    Float_t energy = 0;
    Float_t eecal = 0;
    Float_t ehcal = 0;

    Int_t n302 = 0;
    Int_t n352 = 0;
    Int_t n402 = 0;
    Int_t n452 = 0;
    Int_t n502 = 0;
    Int_t n552 = 0;
    Int_t n602 = 0;
    Int_t n652 = 0;
    Int_t n702 = 0;
    Int_t n752 = 0;
    Int_t n802 = 0;
    Int_t nav2 = 0;

    tree->SetBranchAddress("energy", &energy);
    tree->SetBranchAddress("eecal", &eecal);
    tree->SetBranchAddress("ehcal", &ehcal);

    tree->SetBranchAddress("n302", &n302);
    tree->SetBranchAddress("n352", &n352);
    tree->SetBranchAddress("n402", &n402);
    tree->SetBranchAddress("n452", &n452);
    tree->SetBranchAddress("n502", &n502);
    tree->SetBranchAddress("n552", &n552);
    tree->SetBranchAddress("n602", &n602);
    tree->SetBranchAddress("n652", &n652);
    tree->SetBranchAddress("n702", &n702);
    tree->SetBranchAddress("n752", &n752);
    tree->SetBranchAddress("n802", &n802);
    tree->SetBranchAddress("nav2", &nav2);

    //
    // Create a histogram and random generator
    //
    hist = new TH1F("hist", "hist", nBins, binLo, binHi);

    for ( int i = 0; i <nEvents; i++ ) {
        tree -> GetEntry(i);
//        if ( energy > 0 ) hist -> Fill( eecal + ehcal );
//        cout << "n302 / nav2 === " << n302 << " / " << nav2 << " === " << float(n302) / float(nav2) << endl;
        if ( nav2 > 0 ) hist -> Fill( eecal + ( ehcal * ( float( n302 ) / float( nav2 ) ) ) );
    }

    float mean = hist -> GetMean();
    float rms = hist -> GetRMS();

    cout << " 0:"
        << "  Mean: " << mean
        << "  RMS: " << rms
        << endl;

    fitFunc = new TF1("fitFunc", "gaus", mean - range * rms, mean + range * rms);
    hist -> Fit( fitFunc, "R" );
    float fitmean = fitFunc -> GetParameter(1);
    float fitsigma = fitFunc -> GetParameter(2);
    float fitchi = fitFunc -> GetChisquare() / fitFunc -> GetNDF();
    float fiterrormean = fitFunc -> GetParError(1);
    float fiterrorsigma = fitFunc -> GetParError(2);

    cout << " 1:"
        << "  Mean: " << fitmean
        << " Mean error: " << fiterrormean
        << "  Sigma: " << fitsigma
        << " Sigma error: " << fiterrorsigma
        << "  Chi2/ndf: " << fitchi
        << endl;

    fitFunc2 = new TF1("fitFunc2", "gaus", fitmean - lr * range * fitsigma, fitmean + rr * range * fitsigma);
    hist -> Fit( fitFunc2, "R" );
    hist->GetYaxis()->SetTitle("Events");
    hist->GetXaxis()->SetTitle("Energy, GeV");
    float fitmean2 = fitFunc2 -> GetParameter(1);
    float fitsigma2 = fitFunc2 -> GetParameter(2);
    float fitchi2 = fitFunc2 -> GetChisquare() / fitFunc2 -> GetNDF();
    float fiterrormean2 = fitFunc2 -> GetParError(1);
    float fiterrorsigma2 = fitFunc2 -> GetParError(2);

    cout << " 2:"
        << "  Mean: " << fitmean2
        << " Mean error: " << fiterrormean2
        << "  Sigma: " << fitsigma2
        << " Sigma error: " << fiterrorsigma2
        << "  Chi2/ndf: " << fitchi2
        << endl;

    if ( fitchi < fitchi2 ) {
        fitmean2 = fitmean;
        fiterrormean2 = fiterrormean;
        fitsigma2 = fitsigma;
        fiterrorsigma2 = fiterrorsigma;
        fitchi2 = fitchi;
    }
    
    fprintf( out, "%d %E %E %E %E %E %E\n", fenergy, fitmean2, fiterrormean2, fitsigma2, fiterrorsigma2, fitchi, fitchi2 );
    
    c1->cd();
    hist -> Draw();
    c1->Update();
    sprintf( fname2, "%s.jpg", ftempname );
    c1->SaveAs( fname2 );
    
    //  delete hist;
    //  fclose(  out );
    //  file -> Close();

}

void fitres_global( const int nBins = 1000, const float range = 1.3, const float lr = 1.0, const float rr = 1.0 ) {

    fitres( 5, nBins, range );
    fitres( 10, nBins, range );
    fitres( 15, nBins, range );
    fitres( 20, nBins, range );
    fitres( 25, nBins, range );
    fitres( 30, nBins, range );
    fitres( 40, nBins, range );
    fitres( 50, nBins, range );
    fitres( 60, nBins, range );

}

