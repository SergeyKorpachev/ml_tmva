void fitres( const int fenergy = 5, const int nBins = 1000 ) {

  char fname[ 200 ];
  char ftempname[ 200 ];
  char fname2[ 200 ];

//  const float cut = sqrtf( float( fenergy ) );

//  cout << "Cut === " << cut << endl;

  for ( int i = 0; i < 200; i++ ) fname[ i ] = 0;
  for ( int i = 0; i < 200; i++ ) ftempname[ i ] = 0;
  for ( int i = 0; i < 200; i++ ) fname2[ i ] = 0;

  sprintf( ftempname, "application%d", fenergy );
//  sprintf( ftempname, "gun_k0L_%dgev_FTFP_BERT_5000evt_ILD_l5_v02steel", fenergy );
  sprintf( fname, "%s.root", ftempname );

  TH1F *hist;

  TH1F *hist_mean;
  TH1F *hist_sigma;
  TH1F *hist_chi_full;
  TH1F *hist_chi;
  TH1F *hist_meanerror;
  TH1F *hist_sigmaerror;

  TCanvas *c1 = new TCanvas("c1", "c1", 1);

  gStyle->SetOptStat(0);

  const char *treeName = "tree";
  const float binLo = 0.0;
  const float binHi = fenergy + 20.0;

  const int nBins_fit = 10;
  const float binHi_fit = ( binHi - fenergy ) / 2.0;
  const float binHi_fit_error = binHi_fit - 8.0;

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
//  Float_t energy = 0;
//  tree->SetBranchAddress("energy", &energy);
  Float_t MLP_method = 0;
  tree->SetBranchAddress("MLP_method", &MLP_method);

  //
  // Create a histogram and random generator
  //
  hist = new TH1F("hist", "hist", nBins, binLo, binHi);

  hist_mean = new TH1F("hist_mean", "hist_mean", nBins_fit, binLo, binHi);
  hist_sigma = new TH1F("hist_sigma", "hist_sigma", nBins_fit, binLo, binHi_fit);
  hist_chi_full = new TH1F("hist_chi_full", "hist_chi_full", nBins_fit, binLo, binHi_fit);
  hist_chi = new TH1F("hist_chi", "hist_chi", nBins_fit, binLo, binHi_fit);
  hist_meanerror = new TH1F("hist_meanerror", "hist_meanerror", nBins_fit, binLo, binHi_fit_error);
  hist_sigmaerror = new TH1F("hist_sigmaerror", "hist_sigmaerror", nBins_fit, binLo, binHi_fit_error);

  for ( int i = 0; i <nEvents; i++ ) {
    tree -> GetEntry(i);
    if ( MLP_method > 0 ) hist -> Fill( MLP_method );
//    if ( energy > 0 ) hist -> Fill( energy );
  }

  float mean = hist -> GetMean();
  float rms = hist -> GetRMS();
  cout << " 0:"
  	<< "  Mean: " << mean
	<< "  RMS: " << rms
	<< endl;

  float step = 0.1;

  float mass_chi_full[ 20 ];
  for ( int i = 0; i < 20; i++ ) mass_chi_full[ i ] = 0;

  float mass_chi[ 20 ];
  for ( int i = 0; i < 20; i++ ) mass_chi[ i ] = 0;

  float mass_mean[ 20 ];
  for ( int i = 0; i < 20; i++ ) mass_mean[ i ] = 0;
  float mass_sigma[ 20 ];
  for ( int i = 0; i < 20; i++ ) mass_sigma[ i ] = 0;
  float mass_meanerror[ 20 ];
  for ( int i = 0; i < 20; i++ ) mass_meanerror[ i ] = 0;
  float mass_sigmaerror[ 20 ];
  for ( int i = 0; i < 20; i++ ) mass_sigmaerror[ i ] = 0;

  int i_const = 10;

  for ( int i = 10; i <= 25; i++ ) {
     
     cout << "i === " << i << endl;
     float range = i * step;

     TF1 *fitFunc = new TF1("fitFunc", "gaus", mean - range * rms, mean + range * rms);
     hist -> Fit( fitFunc, "R" );
     float fitmean = fitFunc -> GetParameter(1);
     float fitsigma = fitFunc -> GetParameter(2);
     float fitchi = fitFunc -> GetChisquare() / fitFunc -> GetNDF();
     float fitmeanerror = fitFunc -> GetParError(1);
     float fitsigmaerror = fitFunc -> GetParError(2);

     hist_chi_full -> Fill( fitchi );
     mass_chi_full[ i - i_const ] = fitchi;

     if ( fitchi < 2.5 ) {
         hist_mean -> Fill( fitmean );
         mass_mean[ i - i_const ] = fitmean;

         hist_sigma -> Fill( fitsigma );
         mass_sigma[ i - i_const ] = fitsigma;

         hist_chi -> Fill( fitchi );
         mass_chi[ i - i_const ] = fitchi;

         hist_meanerror -> Fill( fitmeanerror );
         mass_meanerror[ i - i_const ] = fitmeanerror;

         hist_sigmaerror -> Fill( fitsigmaerror );
         mass_sigmaerror[ i - i_const ] = fitsigmaerror;
     }

     cout << " 1:"
     	  << "  Mean: " << fitmean
  	  << " Mean error: " << fitmeanerror
          << "  Sigma: " << fitsigma
          << " Sigma error: " << fitsigmaerror
	  << "  Chi2/ndf: " << fitchi
	  << endl;

     sprintf( fname2, "%d_%s.jpg", i, ftempname );
     c1->SaveAs( fname2 );
     for ( int j = 0; j < 200; j++ ) fname2[ j ] = 0;

     delete fitFunc;

  }

  float min_chi = 2.5;
  float min = 0.0;
  int i_min = 0;
  for ( int i = 0; i < 20; i++ ) {

      if ( mass_chi[ i ] > 0.0 ) {

          if ( mass_chi[ i ] < min_chi ) {
             min_chi = mass_chi[ i ];
             i_min = i;
          }

      }

  }

  float mean_mean = hist_mean -> GetMean();
  float rms_mean = hist_mean -> GetRMS();
  cout << " Mean:"
  	<< "  Mean_mean: " << mean_mean
	<< "  RMS_mean: " << rms_mean
	<< endl;

  float mean_sigma = hist_sigma -> GetMean();
  float rms_sigma = hist_sigma -> GetRMS();
  cout << " Sigma:"
  	<< "  Mean_sigma: " << mean_sigma
	<< "  RMS_sigma: " << rms_sigma
	<< endl;

//  float mean_chi = hist_chi -> GetMean();
//  float rms_chi = hist_chi -> GetRMS();
  float mean_chi = mass_chi[ i_min ];
  cout << " Chi:"
  	<< "  Mean_chi: " << mean_chi
//	<< "  RMS_chi: " << rms_chi
	<< endl;

//  float mean_meanerror = hist_meanerror -> GetMean();
//  float rms_meanerror = hist_meanerror -> GetRMS();
  float mean_meanerror = mass_meanerror[ i_min ];
  cout << " Meanerror:"
  	<< "  Mean_meanerror: " << mean_meanerror
//	<< "  RMS_meanerror: " << rms_meanerror
	<< endl;

//  float mean_sigmaerror = hist_sigmaerror -> GetMean();
//  float rms_sigmaerror = hist_sigmaerror -> GetRMS();
  float mean_sigmaerror = mass_sigmaerror[ i_min ];
  cout << " Sigmaerror:"
  	<< "  Mean_sigmaerror: " << mean_sigmaerror
//	<< "  RMS_sigmaerror: " << rms_sigmaerror
	<< endl;


  

//  fprintf( out, "%d %E %E %E %E %E %E %E %E %E %E\n", fenergy, mean_mean, rms_mean, mean_meanerror, rms_meanerror, mean_sigma, rms_sigma, mean_sigmaerror, rms_sigmaerror, mean_chi, rms_chi );
  fprintf( out, "%d %E %E %E %E %E %E %E\n", fenergy, mean_mean, rms_mean, mean_meanerror, mean_sigma, rms_sigma, mean_sigmaerror, mean_chi );
//  delete hist;
//  fclose(  out );
//  file -> Close();

  for ( int i = 0; i < 20; i++ ) printf( "%E\n", mass_chi[ i ] );
  printf("-------------------\n");
  printf( "%E\n", mass_chi[ i_min ] );
  printf( "%E\n", min_chi );
  printf("-------------------\n");
  for ( int i = 0; i < 20; i++ ) printf( "%E\n", mass_chi_full[ i ] );

}

void run_fitres( const int bins = 1000 ) {

  int mass[] = { 1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90 };
  int dim = 16;

  for (int i = 0; i < 16; i++ ) fitres( mass[ i ], bins );

}

