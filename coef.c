void coef() {
    
std::cout << "Trying to create output file... ";
TFile *out = new TFile("out.root", "RECREATE");
if (!out) {
  out->Close();
  std::cout << " [FAIL] " << std::endl;
  return;
}
std::cout << "[OK]" << std::endl;

std::cout << "Trying to open file_in... ";
TFile* file_in = new TFile( "application.root", "READ" );
if (!file_in) { // if error occure then exit
    std::cout << " [FAIL] " << std::endl;
    return;
}
std::cout << " [OK] " << std::endl;

std::cout << "Trying to open file_gun... ";
TFile* file_gun = new TFile( "gun_k0L_5gev_FTFP_BERT_5000evt_ILD_l5_v02steel.root", "READ" );
if (!file_gun) { // if error occure then exit
    std::cout << " [FAIL] " << std::endl;
    return;
}
std::cout << " [OK] " << std::endl;
    
std::cout << "Setup tree_in... ";
TTree* tree_in = (TTree *)file_in->Get("tree");
if ( !tree_in ) {
    std::cout << " [FAIL] " << std::endl;
    file_in->Close();
    return;
}
std::cout << " [OK] " << std::endl;

std::cout << "Setup tree_gun... ";
TTree* tree_gun = (TTree *)file_gun->Get("tree");
if ( !tree_gun ) {
    std::cout << " [FAIL] " << std::endl;
    file_gun->Close();
    return;
}
std::cout << " [OK] " << std::endl;
    
unsigned int nEvents = tree_in->GetEntries();
unsigned int nEvents2 = tree_in->GetEntries();
    
if ( nEvents == nEvents2 ) cout << "nEvents == nEvents2, that's good :)" << endl;
    
float MLP_method = 0;
float energy = 0;
float mc_energy = 0;
tree_in->SetBranchAddress("MLP_method", &MLP_method);
tree_gun->SetBranchAddress("energy", &energy);
tree_gun->SetBranchAddress("mc_energy", &mc_energy);
    
float final = 0;

TTree* tree = new TTree("tree", "tree");
tree->Branch("final", &final, "final");

for ( unsigned int i = 0; i < nEvents; i++ ) {
    tree_in->GetEntry( i );
    tree_gun->GetEntry( i );
    
    final = MLP_method * ( ( energy * energy ) / ( mc_energy ) );
//    final = MLP_method * energy;//( ( energy * energy ) / ( mc_energy ) );

    
    tree->Fill();
}

out->cd();
tree->Write();
out->Write();
out->Close();

file_in -> Close();
file_gun -> Close();
    
std::cout << "That's all... " << endl;

}
