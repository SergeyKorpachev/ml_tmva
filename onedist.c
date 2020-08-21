TCanvas *c1;

void onedist() {

  TH1F *hist1;
  TH1F *hist2;
  TH1F *hist3;

  if ( gROOT->GetListOfCanvases()->FindObject("c1") == NULL ) c1 = new TCanvas("c1", "c1", 1);

  gStyle->SetOptStat(0);

  const char *treeName = "tree";
  const int nBins = 100;
  const float binLo = 0;  // -35 for 20 GeV // 0 for 60 GeV
  const float binHi = 125; // 70 for 20 GeV // 125 for 60 GeV

  //
  // Open data file 1
  //
  std::cout << "Trying to open data file 1 ... ";
  TFile *file1 = new TFile("/home/korpachev/Desktop/tmva/results/all_variables_5000/gun_k0L_60gev_FTFP_BERT_5000evt_ILD_l5_v02steel.root", "READ");
  if (!file1) { // if error occure then exit
    std::cout << "[FAIL]" << std::endl;
    return;
  }
  std::cout << "[OK]" << std::endl;

  //
  // Open data file 2
  //
  std::cout << "Trying to open data file 2 ... ";
  TFile *file2 = new TFile("/home/korpachev/Desktop/tmva/results/all_variables_5000/application60.root", "READ");
  if (!file2) { // if error occure then exit
    std::cout << "[FAIL]" << std::endl;
    return;
  }
  std::cout << "[OK]" << std::endl;

  //
  // Open data file 3
  //
  std::cout << "Trying to open data file 3 ... ";
  TFile *file3 = new TFile("/home/korpachev/Desktop/tmva/results/phys_variables_5000/application60.root", "READ");
  if (!file3) { // if error occure then exit
    std::cout << "[FAIL]" << std::endl;
    return;
  }
  std::cout << "[OK]" << std::endl;

  //
  // Setup a TTree 1
  //
  std::cout << "Setup a tree 1 ... ";
  TTree *tree1 = (TTree *)file1->Get(treeName);
  if (!tree1) {
    std::cout << "[FAIL]" << std::endl;
    file1->Close();
    return;
  }
  std::cout << "[OK]" << std::endl;

  //
  // Setup a TTree 2
  //
  std::cout << "Setup a tree 2 ... ";
  TTree *tree2 = (TTree *)file2->Get(treeName);
  if (!tree2) {
    std::cout << "[FAIL]" << std::endl;
    file2->Close();
    return;
  }
  std::cout << "[OK]" << std::endl;

  //
  // Setup a TTree 3
  //
  std::cout << "Setup a tree 3 ... ";
  TTree *tree3 = (TTree *)file3->Get(treeName);
  if (!tree3) {
    std::cout << "[FAIL]" << std::endl;
    file3->Close();
    return;
  }
  std::cout << "[OK]" << std::endl;

  unsigned int nEvents1 = tree1->GetEntries();
  unsigned int nEvents2 = tree2->GetEntries();
  unsigned int nEvents3 = tree3->GetEntries();

  //
  // Setup a branch 1
  //
  Float_t energy = 0;
  tree1->SetBranchAddress("energy", &energy);

  //
  // Setup a branch 2
  //
  Float_t MLP_method = 0;
  tree2->SetBranchAddress("MLP_method", &MLP_method);

  //
  // Setup a branch 3
  //
  Float_t MLP_method2 = 0;
  tree3->SetBranchAddress("MLP_method", &MLP_method2);

  //
  // Create a histograms
  //
  hist1 = new TH1F("hist1", "hist1", nBins, binLo, binHi);
  hist2 = new TH1F("hist2", "hist2", nBins, binLo, binHi);
  hist3 = new TH1F("hist3", "hist3", nBins, binLo, binHi);

  for ( int i = 0; i <nEvents1; i++ ) {
    tree1 -> GetEntry(i);
    hist1 -> Fill( energy );
  }

  for ( int i = 0; i <nEvents2; i++ ) {
    tree2 -> GetEntry(i);
    hist2 -> Fill( MLP_method );
  }

  for ( int i = 0; i <nEvents3; i++ ) {
    tree3 -> GetEntry(i);
    hist3 -> Fill( MLP_method2 );
  }

//  cout << "Entries1:   " << hist1->GetEntries() << endl;
//  cout << "Entries2:   " << hist2->GetEntries() << endl;
//  cout << "Entries3:   " << hist3->GetEntries() << endl;
  
//  hist1->Scale(1. / float( hist1->GetEntries() ) );
//  hist2->Scale(1. / float( hist2->GetEntries() ) );
//  hist3->Scale(1. / float( hist3->GetEntries() ) );

  c1->cd();

  hist1->SetTitle("Single K0L in ILD");
  hist1->GetYaxis()->SetTitle("Number of events");
  hist1->GetXaxis()->SetTitle("Energy, GeV");

  hist1->SetMarkerColor(kBlue);
  hist1->SetMarkerStyle(20);
  hist1->SetLineColor(kBlue);
  hist1->SetLineWidth(3);
  hist1->DrawCopy(""); // p e LP
//  hist1->SetMarkerSize(2);
//  hist1->Draw("ALP");
 
  hist2->SetMarkerColor(kRed);
  hist2->SetMarkerStyle(20);
  hist2->SetLineColor(kRed);
  hist2->SetLineWidth(3);
  hist2->DrawCopy("SAME");
//  hist2->SetMarkerSize(2);
//  hist2->Draw("LPSAME");  // LPSAME

  hist3->SetMarkerColor(kGreen);
  hist3->SetMarkerStyle(20);
  hist3->SetLineColor(kGreen);
  hist3->SetLineWidth(3);
  hist3->DrawCopy("SAME");
//  hist3->SetMarkerSize(2);
//  hist3->Draw("ALP");

  TLegend *lsc = new TLegend(0.55,0.62,0.90,0.92);
  lsc->AddEntry(hist1,"without ANN","pl");
  lsc->AddEntry(hist2,"with ANN 1","pl");
  lsc->AddEntry(hist3,"with ANN 2","pl");
  lsc->Draw();

//  delete hist;
//  file -> Close();

}
