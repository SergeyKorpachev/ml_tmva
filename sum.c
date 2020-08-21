void sum() {
  
    char fname[ 120 ];
    int nfiles = 16;
    int mass_energy[] = { 1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90 };
    unsigned int nEvents[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  /*  std::cout << "Trying to create output file... ";
    TFile *out = new TFile("gun_k0L_allgev_FTFP_BERT_90000evt_ILD_l5_v02steel.root", "RECREATE");
    if (!out) {
        out->Close();
        std::cout << " [FAIL]" << std::endl;
        return;
    }
    std::cout << "[OK]" << std::endl;
  */
    TFile* files[ nfiles ];

    std::cout << "Trying to open files... " << endl;
    for( unsigned int i = 0; i < nfiles; i++ ) {
        sprintf( fname, "gun_k0L_%dgev_FTFP_BERT_10000evt_ILD_l5_v02steel.root", mass_energy[ i ] );
        files[i] = new TFile( fname, "READ" );
        if (!files[i]) { // if error occure then exit
            std::cout << fname << " [FAIL]" << std::endl;
            return;
        }
        std::cout << fname << " [OK]" << std::endl;
    }

    TTree* trees[ nfiles ];

    std::cout << "Setup trees... " << endl;
    for( unsigned int i = 0; i < nfiles; i++ ) {
        sprintf( fname, "gun_k0L_%dgev_FTFP_BERT_10000evt_ILD_l5_v02steel.root", mass_energy[ i ] );
        trees[i] = (TTree *)files[i]->Get("tree");
        if ( !trees[i] ) {
            std::cout << fname << " [FAIL]" << std::endl;
            files[i]->Close();
            return;
        }
        std::cout << fname << " [OK]" << std::endl;
    }
    //unsigned int nEvents = trees[0]->GetEntries();

    int sumEvents = 0;
    for( unsigned int i = 0; i < nfiles; i++ ) {
        nEvents[i] = trees[i]->GetEntries();
        sumEvents = sumEvents + nEvents[i];
    }
 /*
    float temp_energy[ nfiles ];
    float temp_eecal[ nfiles ];
    float temp_ehcal[ nfiles ];

    float temp_mc_energy[ nfiles ];

    float temp_nhits[ nfiles ];
    float temp_nhits_ecal[ nfiles ];
    float temp_nhits_hcal[ nfiles ];

    float temp_time[ nfiles ];
    float temp_etime[ nfiles ];
    float temp_htime[ nfiles ];
    float temp_radius[ nfiles ];
    float temp_eradius[ nfiles ];
    float temp_hradius[ nfiles ];

    float temp_elayer[ nfiles ];
    float temp_hlayer[ nfiles ];

    float temp_energy_hit[ nfiles ];
    float temp_energy_hit_ecal[ nfiles ];
    float temp_energy_hit_hcal[ nfiles ];

    float temp_muon_energy[ nfiles ];
    float temp_muon_energy_hit[ nfiles ];
    float temp_muon_nhits[ nfiles ];
    float temp_muon_time[ nfiles ];
    
    for( unsigned int i = 0; i < nfiles; i++ ) {
        trees[i]->SetBranchAddress("energy", &temp_energy[i]);
        trees[i]->SetBranchAddress("eecal", &temp_eecal[i]);
        trees[i]->SetBranchAddress("ehcal", &temp_ehcal[i]);

        trees[i]->SetBranchAddress("mc_energy", &temp_mc_energy[i]);

        trees[i]->SetBranchAddress("nhits", &temp_nhits[i]);
        trees[i]->SetBranchAddress("nhits_ecal", &temp_nhits_ecal[i]);
        trees[i]->SetBranchAddress("nhits_hcal", &temp_nhits_hcal[i]);

        trees[i]->SetBranchAddress("time", &temp_time[i]);
        trees[i]->SetBranchAddress("etime", &temp_etime[i]);
        trees[i]->SetBranchAddress("htime", &temp_htime[i]);
        trees[i]->SetBranchAddress("radius", &temp_radius[i]);
        trees[i]->SetBranchAddress("eradius", &temp_eradius[i]);
        trees[i]->SetBranchAddress("hradius", &temp_hradius[i]);

        trees[i]->SetBranchAddress("elayer", &temp_elayer[i]);
        trees[i]->SetBranchAddress("hlayer", &temp_hlayer[i]);

        trees[i]->SetBranchAddress("energy_hit", &temp_energy_hit[i]);
        trees[i]->SetBranchAddress("energy_hit_ecal", &temp_energy_hit_ecal[i]);
        trees[i]->SetBranchAddress("energy_hit_hcal", &temp_energy_hit_hcal[i]);

        trees[i]->SetBranchAddress("muon_energy", &temp_muon_energy[i]);
        trees[i]->SetBranchAddress("muon_energy_hit", &temp_muon_energy_hit[i]);
        trees[i]->SetBranchAddress("muon_nhits", &temp_muon_nhits[i]);
        trees[i]->SetBranchAddress("muon_time", &temp_muon_time[i]);


    }
   
    float energy = 0;
    float eecal = 0;
    float ehcal = 0;

    float mc_energy = 0;

    float nhits = 0;
    float nhits_ecal = 0;
    float nhits_hcal = 0;

    float time = 0;
    float etime = 0;
    float htime = 0;
    float radius = 0;
    float eradius = 0;
    float hradius = 0;

    float elayer = 0;
    float hlayer = 0;

    float energy_hit = 0;
    float energy_hit_ecal = 0;
    float energy_hit_hcal = 0;

    float muon_energy = 0;
    float muon_energy_hit = 0;
    float muon_nhits = 0;
    float muon_time = 0;


    TTree* tree = new TTree("tree", "tree");
    tree->Branch("energy", &energy, "energy");
    tree->Branch("eecal", &eecal, "eecal");
    tree->Branch("ehcal", &ehcal, "ehcal");

    tree->Branch("mc_energy", &mc_energy, "mc_energy");

    tree->Branch("nhits", &nhits, "nhits" );
    tree->Branch("nhits_ecal", &nhits_ecal, "nhits_ecal" );
    tree->Branch("nhits_hcal", &nhits_hcal, "nhits_hcal" );

    tree->Branch("time", &time, "time" );
    tree->Branch("etime", &etime, "etime" );
    tree->Branch("htime", &htime, "htime" );
    tree->Branch("radius", &radius, "radius" );
    tree->Branch("eradius", &eradius, "eradius" );
    tree->Branch("hradius", &hradius, "hradius" );

    tree->Branch("elayer", &elayer, "elayer" );
    tree->Branch("hlayer", &hlayer, "hlayer" );

    tree->Branch("energy_hit", &energy_hit, "energy_hit" );
    tree->Branch("energy_hit_ecal", &energy_hit_ecal, "energy_hit_ecal" );
    tree->Branch("energy_hit_hcal", &energy_hit_hcal, "energy_hit_hcal" );

    tree->Branch("muon_energy", &muon_energy, "muon_energy" );
    tree->Branch("muon_energy_hit", &muon_energy_hit, "muon_energy_hit" );
    tree->Branch("muon_nhits", &muon_nhits, "muon_nhits" );
    tree->Branch("muon_time", &muon_time, "muon_time" );

    int chet = 0;
    
    for ( unsigned int j = 0; j < nfiles; j++ ) {
        for ( unsigned int i = 0; i < nEvents[ j ]; i++ ) {
        
            trees[ j ]->GetEntry( i );
    
            energy = temp_energy[ j ];

            eecal = temp_eecal[ j ];
            ehcal = temp_ehcal[ j ];

            mc_energy = temp_mc_energy[ j ];

            nhits = temp_nhits[ j ];
            nhits_ecal = temp_nhits_ecal[ j ];
            nhits_hcal = temp_nhits_hcal[ j ];

            time = temp_time[ j ];
            etime = temp_etime[ j ];
            htime = temp_htime[ j ];
            radius = temp_radius[ j ];
            eradius = temp_eradius[ j ];
            hradius = temp_hradius[ j ];

            elayer = temp_elayer[ j ];
            hlayer = temp_hlayer[ j ];

            energy_hit = temp_energy_hit[ j ];
            energy_hit_ecal = temp_energy_hit_ecal[ j ];
            energy_hit_hcal = temp_energy_hit_hcal[ j ];

            muon_energy = temp_muon_energy[ j ];
            muon_energy_hit = temp_muon_energy_hit[ j ];
            muon_nhits = temp_muon_nhits[ j ];
            muon_time = temp_muon_time[ j ];

            tree->Fill();
            chet++;
            std::cout << "chet === " << chet << std::endl;
    
        }
    }
    */  
    std::cout << "sumEvents === " << sumEvents << std::endl;

    //for ( unsigned int i = 0; i < nfiles; i++ ) std::cout << "Energy === " << mass_energy[i] << " and energy_count === " << energy_count[i] << std::endl;
    
    TChain ch( "tree" );
//    for ( int i = 0; i < nfiles; i++ ) ch.Add( files[ i ] );
    ch.Add( "gun_k0L_1gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_2gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_3gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_4gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_5gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_10gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_15gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_20gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_25gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_30gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_40gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_50gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_60gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_70gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_80gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Add( "gun_k0L_90gev_FTFP_BERT_10000evt_ILD_l5_v02steel.root" );
    ch.Merge( "gun_k0L_allgev_FTFP_BERT_160000evt_ILD_l5_v02steel.root" );
    
//    out->cd();
//    tree->Write();
//    out->Write();
//    out->Close();

//    delete out;

    for( unsigned int i = 0; i < nfiles; i++ ) files[i]->Close();
      
    //for( unsigned int i = 0; i < nfiles; i++ ) delete trees[i];
    
    std::cout << "That's all... " << endl;

}
