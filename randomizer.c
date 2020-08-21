void randomizer() {

using std::vector;
  
char fname[ 120 ];
int nfiles = 9;
int mass_energy[] = { 5, 10, 15, 20, 25, 30, 40, 50, 60 };
int energy_count[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned int nEvents[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int max = 7500;
    
std::cout << "Trying to create output file... ";
TFile *out = new TFile("gun_k0L_allgev_FTFP_BERT_10000evt_ILD_l5_v02steel.root", "RECREATE");
if (!out) {
  out->Close();
  std::cout << " [FAIL]" << std::endl;
  return;
}
std::cout << "[OK]" << std::endl;
  
TFile* files[ nfiles ];
TTree* trees[ nfiles ];

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

for( unsigned int i = 0; i < nfiles; i++ ) {
  nEvents[i] = trees[i]->GetEntries();
}
  
float temp_energy[ nfiles ];
float temp_eecal[ nfiles ];
float temp_ehcal[ nfiles ];

float temp_mc_energy[ nfiles ];

float temp_cogx[ nfiles ];
float temp_cogy[ nfiles ];
float temp_cogz[ nfiles ];

float temp_ecogx[ nfiles ];
float temp_ecogy[ nfiles ];
float temp_ecogz[ nfiles ];
float temp_hcogx[ nfiles ];
float temp_hcogy[ nfiles ];
float temp_hcogz[ nfiles ];

float temp_nhits[ nfiles ];
float temp_nhits_ecal[ nfiles ];
float temp_nhits_hcal[ nfiles ];

float temp_time[ nfiles ];
float temp_etime[ nfiles ];
float temp_htime[ nfiles ];
float temp_radius[ nfiles ];
float temp_eradius[ nfiles ];
float temp_hradius[ nfiles ];

float temp_angle[ nfiles ];
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

    trees[i]->SetBranchAddress("cogx", &temp_cogx[i]);
    trees[i]->SetBranchAddress("cogy", &temp_cogy[i]);
    trees[i]->SetBranchAddress("cogz", &temp_cogz[i]);

    trees[i]->SetBranchAddress("ecogx", &temp_ecogx[i]);
    trees[i]->SetBranchAddress("ecogy", &temp_ecogy[i]);
    trees[i]->SetBranchAddress("ecogz", &temp_ecogz[i]);
    trees[i]->SetBranchAddress("hcogx", &temp_hcogx[i]);
    trees[i]->SetBranchAddress("hcogy", &temp_hcogy[i]);
    trees[i]->SetBranchAddress("hcogz", &temp_hcogz[i]);

    trees[i]->SetBranchAddress("nhits", &temp_nhits[i]);
    trees[i]->SetBranchAddress("nhits_ecal", &temp_nhits_ecal[i]);
    trees[i]->SetBranchAddress("nhits_hcal", &temp_nhits_hcal[i]);

    trees[i]->SetBranchAddress("time", &temp_time[i]);
    trees[i]->SetBranchAddress("etime", &temp_etime[i]);
    trees[i]->SetBranchAddress("htime", &temp_htime[i]);
    trees[i]->SetBranchAddress("radius", &temp_radius[i]);
    trees[i]->SetBranchAddress("eradius", &temp_eradius[i]);
    trees[i]->SetBranchAddress("hradius", &temp_hradius[i]);

    trees[i]->SetBranchAddress("angle", &temp_angle[i]);
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

float cogx = 0;
float cogy = 0;
float cogz = 0;

float ecogx = 0;
float ecogy = 0;
float ecogz = 0;
float hcogx = 0;
float hcogy = 0;
float hcogz = 0;

float nhits = 0;
float nhits_ecal = 0;
float nhits_hcal = 0;

float time = 0;
float etime = 0;
float htime = 0;
float radius = 0;
float eradius = 0;
float hradius = 0;

float angle = 0;
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

tree->Branch("cogx", &cogx, "cogx" );
tree->Branch("cogy", &cogy, "cogy" );
tree->Branch("cogz", &cogz, "cogz" );

tree->Branch("ecogx", &ecogx, "ecogx" );
tree->Branch("ecogy", &ecogy, "ecogy" );
tree->Branch("ecogz", &ecogz, "ecogz" );
tree->Branch("hcogx", &hcogx, "hcogx" );
tree->Branch("hcogy", &hcogy, "hcogy" );
tree->Branch("hcogz", &hcogz, "hcogz" );

tree->Branch("nhits", &nhits, "nhits" );
tree->Branch("nhits_ecal", &nhits_ecal, "nhits_ecal" );
tree->Branch("nhits_hcal", &nhits_hcal, "nhits_hcal" );

tree->Branch("time", &time, "time" );
tree->Branch("etime", &etime, "etime" );
tree->Branch("htime", &htime, "htime" );
tree->Branch("radius", &radius, "radius" );
tree->Branch("eradius", &eradius, "eradius" );
tree->Branch("hradius", &hradius, "hradius" );

tree->Branch("angle", &angle, "angle" );
tree->Branch("elayer", &elayer, "elayer" );
tree->Branch("hlayer", &hlayer, "hlayer" );

tree->Branch("energy_hit", &energy_hit, "energy_hit" );
tree->Branch("energy_hit_ecal", &energy_hit_ecal, "energy_hit_ecal" );
tree->Branch("energy_hit_hcal", &energy_hit_hcal, "energy_hit_hcal" );

tree->Branch("muon_energy", &muon_energy, "muon_energy" );
tree->Branch("muon_energy_hit", &muon_energy_hit, "muon_energy_hit" );
tree->Branch("muon_nhits", &muon_nhits, "muon_nhits" );
tree->Branch("muon_time", &muon_time, "muon_time" );

//for ( unsigned int i = 0; i < nEvents; i++ ) {
for ( unsigned int i = 0; i < max; i++ ) {
        
    int per = rand() % nfiles;
    energy_count[ per ] = energy_count[ per ] + 1;
    trees[ per ]->GetEntry( rand() % nEvents[ per ] );
    
    energy = temp_energy[ per ];
    eecal = temp_eecal[ per ];
    ehcal = temp_ehcal[ per ];

    mc_energy = temp_mc_energy[ per ];

    cogx = temp_cogx[ per ];
    cogy = temp_cogy[ per ];
    cogz = temp_cogz[ per ];

    ecogx = temp_ecogx[ per ];
    ecogy = temp_ecogy[ per ];
    ecogz = temp_ecogz[ per ];
    hcogx = temp_hcogx[ per ];
    hcogy = temp_hcogy[ per ];
    hcogz = temp_hcogz[ per ];

    nhits = temp_nhits[ per ];
    nhits_ecal = temp_nhits_ecal[ per ];
    nhits_hcal = temp_nhits_hcal[ per ];

    time = temp_time[ per ];
    etime = temp_etime[ per ];
    htime = temp_htime[ per ];
    radius = temp_radius[ per ];
    eradius = temp_eradius[ per ];
    hradius = temp_hradius[ per ];

    angle = temp_angle[ per ];
    elayer = temp_elayer[ per ];
    hlayer = temp_hlayer[ per ];

    energy_hit = temp_energy_hit[ per ];
    energy_hit_ecal = temp_energy_hit_ecal[ per ];
    energy_hit_hcal = temp_energy_hit_hcal[ per ];

    muon_energy = temp_muon_energy[ per ];
    muon_energy_hit = temp_muon_energy_hit[ per ];
    muon_nhits = temp_muon_nhits[ per ];
    muon_time = temp_muon_time[ per ];

    tree->Fill();
}

//for ( unsigned int i = 0; i < nfiles; i++ ) std::cout << "Energy === " << mass_energy[i] << " and energy_count === " << energy_count[i] << std::endl;

out->cd();
tree->Write();
out->Write();
out->Close();

delete out;

for( unsigned int i = 0; i < nfiles; i++ ) files[i]->Close();
      
//delete tree_r;
//for( unsigned int i = 0; i < nfiles; i++ ) delete trees[i];
    
std::cout << "That's all... " << endl;

}
