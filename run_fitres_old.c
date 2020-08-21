
Double_t langaufun(Double_t *x, Double_t *par) {

   //Fit parameters:
   //par[0]=Width (scale) parameter of Landau density
   //par[1]=Most Probable (MP, location) parameter of Landau density
   //par[2]=Total area (integral -inf to inf, normalization constant)
   //par[3]=Width (sigma) of convoluted Gaussian function
   //
   //In the Landau distribution (represented by the CERNLIB approximation),
   //the maximum is located at x=-0.22278298 with the location parameter=0.
   //This shift is corrected within this function, so that the actual
   //maximum is identical to the MP parameter.

      // Numeric constants
      Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
      Double_t mpshift  = 0; //-0.22278298;       // Landau maximum location

      // Control constants
      Double_t np = 300; //nstp; //100.0;      // number of convolution steps
      Double_t sc = 5.0;      // convolution extends to +-sc Gaussian sigmas

      // Variables
      Double_t xx;
      Double_t mpc;
      Double_t fland;
      Double_t sum = 0.0;
      Double_t xlow,xupp;
      Double_t step;
      Double_t i;


      // MP shift correction
      mpc = par[1] - mpshift * par[0];

      // Range of convolution integral
      xlow = x[0] - sc * par[3];
      xupp = x[0] + sc * par[3];

      step = (xupp-xlow) / np;

      // Convolution integral of Landau and Gaussian by sum
      for(i=1.0; i<=np/2; i++) {
         xx = xlow + (i-.5) * step;
         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
         sum += fland * TMath::Gaus(x[0],xx,par[3]);

         xx = xupp - (i-.5) * step;
         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
         sum += fland * TMath::Gaus(x[0],xx,par[3]);
      }

      return (par[2] * step * sum * invsq2pi / par[3]);
}

void fitres( const int fenergy = 5, const int nBins = 500, const float range = 1.3, const float lr = 1.0, const float rr = 1.0 ) {

//  const float range = 1.3;

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

  TF1 *fitFunc;
  TF1 *fitFunc2;
  TH1F *hist;

  TCanvas *c1 = new TCanvas("c1", "c1", 1);

  gStyle->SetOptStat(0);

  const char *treeName = "tree";
//  const int nBins = 1000;
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
//  Float_t energy = 0;
//  tree->SetBranchAddress("energy", &energy);
  Float_t MLP_method = 0;
  tree->SetBranchAddress("MLP_method", &MLP_method);

  //
  // Create a histogram and random generator
  //
  hist = new TH1F("hist", "hist", nBins, binLo, binHi);

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
  	<< "  Mean2: " << fitmean2
        << " Mean error: " << fiterrormean2
	<< "  Sigma2: " << fitsigma2
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
    
/*    
      TF1 *ff1 = new TF1("ff1",langaufun,mean - lr * range * rms,mean - lr * range * rms,4);
      ff1->SetParameters(0.2*hist->GetMean(),
                hist->GetMean(),
                double(hist->GetEntries()),
                0.2*hist->GetMean());
      ff1->SetParNames("Width","MP","Area","GSigma");
      hist->Fit(ff1,"Q0R");
      std::cout << "Fit result for 1: " << std::endl
            << " MPV = " << ff1->GetParameter(1) << "+-" << ff1->GetParError(1) << std::endl
            << " Lwidth = " << ff1->GetParameter(0) << "+-" << ff1->GetParError(0) << std::endl
            << " Gwidth = " << ff1->GetParameter(3) << "+-" << ff1->GetParError(3) << std::endl
            << " Scale = " << ff1->GetParameter(2) << "+-" << ff1->GetParError(2) << std::endl
            << "    chi2/ndf = " << ff1->GetChisquare() << " / " << ff1->GetNDF()
            << " = " << ff1->GetChisquare()/ff1->GetNDF()
            << std::endl;

      //--- plot result
    //  gStyle->SetOptStat(1110);
    //  gStyle->SetOptFit(1111);

      TF1 *ff2 = new TF1("ff2",langaufun,ff1->GetParameter(1) - lr * range * ff1->GetParameter(0),ff1->GetParameter(1) - rr * range * ff1->GetParameter(0),4);
      ff2->SetParameters(0.2*hist->GetMean(),
                hist2->GetMean(),
                double(hist2->GetEntries()),
                0.2*hist2->GetMean());
      ff2->SetParNames("Width","MP","Area","GSigma");
      hist2->Fit(ff2,"Q0R");
      std::cout << "Fit result for 2: " << std::endl
            << " MPV = " << ff2->GetParameter(1) << "+-" << ff2->GetParError(1) << std::endl
            << " Lwidth = " << ff2->GetParameter(0) << "+-" << ff2->GetParError(0) << std::endl
            << " Gwidth = " << ff2->GetParameter(3) << "+-" << ff2->GetParError(3) << std::endl
            << " Scale = " << ff2->GetParameter(2) << "+-" << ff2->GetParError(2) << std::endl
            << "    chi2/ndf = " << ff2->GetChisquare() << " / " << ff2->GetNDF()
            << " = " << ff2->GetChisquare()/ff2->GetNDF()
            << std::endl;

      //--- plot result
    //  gStyle->SetOptStat(1110);
    //  gStyle->SetOptFit(1111);
    */


  fprintf( out, "%d %E %E %E %E %E %E\n", fenergy, fitmean2, fiterrormean2, fitsigma2, fiterrorsigma2, fitchi, fitchi2 );

  sprintf( fname2, "%s.jpg", ftempname );

  c1->SaveAs( fname2 );

//  delete hist;
//  fclose(  out );
//  file -> Close();

}

void run_fitres( const int nBins = 1000, const float range = 1.3, const float lr = 1.0, const float rr = 1.0 ) {

  fitres( 1, nBins, range );
  fitres( 2, nBins, range );
  fitres( 3, nBins, range );
  fitres( 4, nBins, range );
  fitres( 5, nBins, range );
  fitres( 10, nBins, range );
  fitres( 15, nBins, range );
  fitres( 20, nBins, range );
  fitres( 25, nBins, range );
  fitres( 30, nBins, range );
  fitres( 40, nBins, range );
  fitres( 50, nBins, range );
  fitres( 60, nBins, range );
  fitres( 70, nBins, range );
  fitres( 80, nBins, range );
  fitres( 90, nBins, range );

}

