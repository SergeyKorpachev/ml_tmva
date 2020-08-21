void fitres( const int fenergy = 5, const int nBins = 1000 ) {

    float elim = 0;
    float eav = 0;
    float number_elim = 0;
    float number_eav = 0;
    float number_hits = 0;
    float c_lim = 0;
    float c_av = 0;
    float c_final = 0;
    float c_final2 = 0;
    
    char fname[ 200 ];
    char ftempname[ 200 ];
    char fname2[ 200 ];

    for ( int i = 0; i < 200; i++ ) fname[ i ] = 0;
    for ( int i = 0; i < 200; i++ ) ftempname[ i ] = 0;
    for ( int i = 0; i < 200; i++ ) fname2[ i ] = 0;

    sprintf( ftempname, "gun_k0L_%dgev_FTFP_BERT_10000evt_ILD_l5_v02steel", fenergy );
    sprintf( fname, "%s.root", ftempname );

    TH1F *hist;
    TH1F *temp_hist;

    TCanvas *c1 = new TCanvas("c1", "c1", 1);
    gStyle->SetOptStat(0);

    const char *treeName = "tree2";
    const float binLo = 0.0;
    const float binHi = 400.0;

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
    FILE *out = fopen("gc_out.txt", "a+");
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
    Float_t energy_hit_hcal_mip2 = 0;
    tree->SetBranchAddress("energy_hit_hcal_mip2", &energy_hit_hcal_mip2);

    //
    // Create a histogram and random generator
    //
    hist = new TH1F("hist", "hist", nBins, binLo, binHi);
    for ( int i = 0; i <nEvents; i++ ) {
        tree->GetEntry(i);
        hist->Fill( energy_hit_hcal_mip2 );
        number_hits++;
    }
    float mean = hist->GetMean();
    float rms = hist->GetRMS();

    cout << " 0:"
        << "  Mean: " << mean
        << "  RMS: " << rms
        << endl;
    
    hist->Draw();
    
    elim = 5.0;
    eav = mean;
  //  if ( nEvents == number_hits ) cout << "!!!nEvents == number_hits!!!" << endl;
    
    temp_hist = new TH1F("temp_hist", "temp_hist", nBins, binLo, binHi);
    for ( int i = 0; i <nEvents; i++ ) {
        tree->GetEntry(i);
        temp_hist->Fill( energy_hit_hcal_mip2 );
        if ( energy_hit_hcal_mip2 <= elim ) number_elim++;
        if ( energy_hit_hcal_mip2 <= eav ) number_eav++;
    }
    
    c_lim = number_elim / number_hits;
    c_av = number_eav / number_hits;
    
    c_final = c_lim / c_av;
    c_final2 = number_elim / number_eav;
    
    fprintf( out, "%d %E %E %E %E %E %E %E %E %E\n", fenergy, elim, eav, number_elim, number_eav, number_hits, c_lim, c_av, c_final, c_final2 );

    sprintf( fname2, "gc_%s.jpg", ftempname );
    //  c1->SaveAs( fname2 );
    
    //  delete hist;
    //  fclose( out );
    //  file->Close();
    
}

void global_comp( const int nBins = 1000 ) {

    fitres( 5, nBins );
    fitres( 10, nBins );
    fitres( 15, nBins );
    fitres( 20, nBins );
    fitres( 25, nBins );
    fitres( 30, nBins );
    fitres( 40, nBins );
    fitres( 50, nBins );
    fitres( 60, nBins );

}

