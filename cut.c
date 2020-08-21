void cut() {

char fname[ 120 ];
char fname2[ 120 ];
int nfiles = 9;
int mass_energy[] = { 5, 10, 15, 20, 25, 30, 40, 50, 60 };

for( unsigned int i = 0; i < nfiles; i++ ) {
cout << "I === " << i << endl;

std::cout << "Trying to open file_in... " << endl;
sprintf( fname, "./backup/gun_k0L_%dgev_FTFP_BERT_5000evt_ILD_l5_v02steel.root", mass_energy[ i ] );
TFile* file_in = new TFile( fname, "READ" );
if (!file_in) {
   std::cout << " [FAIL] " << std::endl;
   return;
}
std::cout << " [OK] " << std::endl;
    
std::cout << "Trying to create file_out... ";
sprintf( fname2, "cut_gun_k0L_%dgev_FTFP_BERT_5000evt_ILD_l5_v02steel.root", mass_energy[ i ] );
TFile *file_out = new TFile( fname2, "RECREATE");
if (!file_out) {
  file_out->Close();
  std::cout << " [FAIL] " << std::endl;
  return;
}
std::cout << " [OK] " << std::endl;

std::cout << "Setup tree_in... " << endl;
TTree* tree_in = (TTree *)file_in->Get("tree");
if ( !tree_in ) {
   std::cout << " [FAIL] " << std::endl;
   file_in->Close();
   return;
}
std::cout << " [OK] " << std::endl;

unsigned int nEvents = tree_in->GetEntries();
  
float temp_energy;
float temp_eecal;
float temp_ehcal;

float temp_mc_energy;

float temp_cogx;
float temp_cogy;
float temp_cogz;

float temp_ecogx;
float temp_ecogy;
float temp_ecogz;
float temp_hcogx;
float temp_hcogy;
float temp_hcogz;

int temp_nhits;
int temp_nhits_ecal;
int temp_nhits_hcal;

float temp_time;
float temp_etime;
float temp_htime;
float temp_radius;
float temp_eradius;
float temp_hradius;

float temp_angle;
float temp_elayer;
float temp_hlayer;

float temp_energy_hit;
float temp_energy_hit_ecal;
float temp_energy_hit_hcal;

float temp_muon_energy;
float temp_muon_energy_hit;
int temp_muon_nhits;
float temp_muon_time;
    
tree_in->SetBranchAddress("energy", &temp_energy);
tree_in->SetBranchAddress("eecal", &temp_eecal);
tree_in->SetBranchAddress("ehcal", &temp_ehcal);

tree_in->SetBranchAddress("mc_energy", &temp_mc_energy);

tree_in->SetBranchAddress("cogx", &temp_cogx);
tree_in->SetBranchAddress("cogy", &temp_cogy);
tree_in->SetBranchAddress("cogz", &temp_cogz);

tree_in->SetBranchAddress("ecogx", &temp_ecogx);
tree_in->SetBranchAddress("ecogy", &temp_ecogy);
tree_in->SetBranchAddress("ecogz", &temp_ecogz);
tree_in->SetBranchAddress("hcogx", &temp_hcogx);
tree_in->SetBranchAddress("hcogy", &temp_hcogy);
tree_in->SetBranchAddress("hcogz", &temp_hcogz);

tree_in->SetBranchAddress("nhits", &temp_nhits);
tree_in->SetBranchAddress("nhits_ecal", &temp_nhits_ecal);
tree_in->SetBranchAddress("nhits_hcal", &temp_nhits_hcal);

tree_in->SetBranchAddress("time", &temp_time);
tree_in->SetBranchAddress("etime", &temp_etime);
tree_in->SetBranchAddress("htime", &temp_htime);
tree_in->SetBranchAddress("radius", &temp_radius);
tree_in->SetBranchAddress("eradius", &temp_eradius);
tree_in->SetBranchAddress("hradius", &temp_hradius);

tree_in->SetBranchAddress("angle", &temp_angle);
tree_in->SetBranchAddress("elayer", &temp_elayer);
tree_in->SetBranchAddress("hlayer", &temp_hlayer);

tree_in->SetBranchAddress("energy_hit", &temp_energy_hit);
tree_in->SetBranchAddress("energy_hit_ecal", &temp_energy_hit_ecal);
tree_in->SetBranchAddress("energy_hit_hcal", &temp_energy_hit_hcal);

tree_in->SetBranchAddress("muon_energy", &temp_muon_energy);
tree_in->SetBranchAddress("muon_energy_hit", &temp_muon_energy_hit);
tree_in->SetBranchAddress("muon_nhits", &temp_muon_nhits);
tree_in->SetBranchAddress("muon_time", &temp_muon_time);
   
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

int nhits = 0;
int nhits_ecal = 0;
int nhits_hcal = 0;

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
int muon_nhits = 0;
float muon_time = 0;

TTree* tree_out = new TTree("tree", "tree");
tree_out->Branch("energy", &energy, "energy");
tree_out->Branch("eecal", &eecal, "eecal");
tree_out->Branch("ehcal", &ehcal, "ehcal");

tree_out->Branch("mc_energy", &mc_energy, "mc_energy");

tree_out->Branch("cogx", &cogx, "cogx" );
tree_out->Branch("cogy", &cogy, "cogy" );
tree_out->Branch("cogz", &cogz, "cogz" );

tree_out->Branch("ecogx", &ecogx, "ecogx" );
tree_out->Branch("ecogy", &ecogy, "ecogy" );
tree_out->Branch("ecogz", &ecogz, "ecogz" );
tree_out->Branch("hcogx", &hcogx, "hcogx" );
tree_out->Branch("hcogy", &hcogy, "hcogy" );
tree_out->Branch("hcogz", &hcogz, "hcogz" );

tree_out->Branch("nhits", &nhits, "nhits" );
tree_out->Branch("nhits_ecal", &nhits_ecal, "nhits_ecal" );
tree_out->Branch("nhits_hcal", &nhits_hcal, "nhits_hcal" );

tree_out->Branch("time", &time, "time" );
tree_out->Branch("etime", &etime, "etime" );
tree_out->Branch("htime", &htime, "htime" );
tree_out->Branch("radius", &radius, "radius" );
tree_out->Branch("eradius", &eradius, "eradius" );
tree_out->Branch("hradius", &hradius, "hradius" );

tree_out->Branch("angle", &angle, "angle" );
tree_out->Branch("elayer", &elayer, "elayer" );
tree_out->Branch("hlayer", &hlayer, "hlayer" );

tree_out->Branch("energy_hit", &energy_hit, "energy_hit" );
tree_out->Branch("energy_hit_ecal", &energy_hit_ecal, "energy_hit_ecal" );
tree_out->Branch("energy_hit_hcal", &energy_hit_hcal, "energy_hit_hcal" );

tree_out->Branch("muon_energy", &muon_energy, "muon_energy" );
tree_out->Branch("muon_energy_hit", &muon_energy_hit, "muon_energy_hit" );
tree_out->Branch("muon_nhits", &muon_nhits, "muon_nhits" );
tree_out->Branch("muon_time", &muon_time, "muon_time" );

for ( unsigned int i = 0; i < nEvents; i++ ) {
        
    tree_in->GetEntry( i );
    
if ( temp_energy > sqrt( roundf( temp_mc_energy ) ) ) {

    energy = temp_energy;
    eecal = temp_eecal;
    ehcal = temp_ehcal;

    mc_energy = temp_mc_energy;

    cogx = temp_cogx;
    cogy = temp_cogy;
    cogz = temp_cogz;

    ecogx = temp_ecogx;
    ecogy = temp_ecogy;
    ecogz = temp_ecogz;
    hcogx = temp_hcogx;
    hcogy = temp_hcogy;
    hcogz = temp_hcogz;

    nhits = temp_nhits;
    nhits_ecal = temp_nhits_ecal;
    nhits_hcal = temp_nhits_hcal;

    time = temp_time;
    etime = temp_etime;
    htime = temp_htime;
    radius = temp_radius;
    eradius = temp_eradius;
    hradius = temp_hradius;

    angle = temp_angle;
    elayer = temp_elayer;
    hlayer = temp_hlayer;

    energy_hit = temp_energy_hit;
    energy_hit_ecal = temp_energy_hit_ecal;
    energy_hit_hcal = temp_energy_hit_hcal;

    muon_energy = temp_muon_energy;
    muon_energy_hit = temp_muon_energy_hit;
    muon_nhits = temp_muon_nhits;
    muon_time = temp_muon_time;

    tree_out->Fill();

}
}

file_out->cd();
tree_out->Write();
file_out->Write();
file_out->Close();

file_in->Close();

}

std::cout << "That's all... " << endl;

}
