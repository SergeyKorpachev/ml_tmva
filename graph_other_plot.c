void graph_other_plot() {
   TCanvas *c = new TCanvas("graph","graph",200,10,700,500);

   //c1->SetFillColor(42);
   //gStyle->SetPalette(52);
   c->Divide(2,2);
   c->SetGrid();
   //c1->GetFrame()->SetFillColor(21);
   //c1->GetFrame()->SetBorderSize(12);

   const Int_t n = 9;

   Float_t energy[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t energyerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t meanerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigma[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigmaerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t value[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t error[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   Float_t energy2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t energyerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t meanerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigma2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigmaerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t value2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t error2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   Float_t energy3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t energyerror3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t meanerror3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigma3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigmaerror3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t value3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t error3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   Float_t energy4[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t energyerror4[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean4[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t meanerror4[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigma4[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigmaerror4[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t value4[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t error4[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   Float_t energy5[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t energyerror5[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean5[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t meanerror5[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigma5[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t sigmaerror5[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t value5[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t error5[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   float temp11 = 0;
   float temp12 = 0;
   float temp21 = 0;
   float temp22 = 0;
   float temp31 = 0;
   float temp32 = 0;
   float temp41 = 0;
   float temp42 = 0;
   float temp51 = 0;
   float temp52 = 0;

/*
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy[i] );
     printf( " %f ", energyerror[i] );
     printf( " %f ", mean[i] );
     printf( " %f ", meanerror[i] );
     printf( " %f ", sigma[i] );
     printf( " %f ", sigmaerror[i] );
     printf( " %f ", value[i] );
     printf( " %f ", error[i] );
     printf( "\n" );
   }
*/
   FILE *file = fopen("out_1.txt", "r");
   if ( !(long)file ) return;

   FILE *file2 = fopen("out_2.txt", "r");
   if ( !(long)file2 ) return;

   FILE *file3 = fopen("out_3.txt", "r");
   if ( !(long)file3 ) return;

   FILE *file4 = fopen("out_4.txt", "r");
   if ( !(long)file4 ) return;

   FILE *file5 = fopen("out_5.txt", "r");
   if ( !(long)file5 ) return;


  for ( int i = 0; i < n; i++ ) {
    fscanf( file, "%f %E %E %E %E %E %E\n", &energy[i], &mean[i], &meanerror[i], &sigma[i], &sigmaerror[i], &temp11, &temp12 );
    if ( feof( file ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    fscanf( file2, "%f %E %E %E %E %E %E\n", &energy2[i], &mean2[i], &meanerror2[i], &sigma2[i], &sigmaerror2[i], &temp21, &temp22 );
    if ( feof( file2 ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    fscanf( file3, "%f %E %E %E %E %E %E\n", &energy3[i], &mean3[i], &meanerror3[i], &sigma3[i], &sigmaerror3[i], &temp31, &temp32 );
    if ( feof( file3 ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    fscanf( file4, "%f %E %E %E %E %E %E\n", &energy4[i], &mean4[i], &meanerror4[i], &sigma4[i], &sigmaerror4[i], &temp41, &temp42 );
    if ( feof( file4 ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    fscanf( file5, "%f %E %E %E %E %E %E\n", &energy5[i], &mean5[i], &meanerror5[i], &sigma5[i], &sigmaerror5[i], &temp51, &temp52 );
    if ( feof( file5 ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    value[ i ] = sigma[i] / mean[i];
    error[ i ] = sqrt( pow( (sigmaerror[i])/(mean[i]) ,2 ) + pow( (sigma[i] * meanerror[i])/(mean[i] * mean[i]) ,2 ) );

  }

  for ( int i = 0; i < n; i++ ) {
    value2[ i ] = sigma2[i] / mean2[i];
    error2[ i ] = sqrt( pow( (sigmaerror2[i])/(mean2[i]) ,2 ) + pow( (sigma2[i] * meanerror2[i])/(mean2[i] * mean2[i]) ,2 ) );

  }

  for ( int i = 0; i < n; i++ ) {
    value3[ i ] = sigma3[i] / mean3[i];
    error3[ i ] = sqrt( pow( (sigmaerror3[i])/(mean3[i]) ,2 ) + pow( (sigma3[i] * meanerror3[i])/(mean3[i] * mean3[i]) ,2 ) );

  }

  for ( int i = 0; i < n; i++ ) {
    value4[ i ] = sigma4[i] / mean4[i];
    error4[ i ] = sqrt( pow( (sigmaerror4[i])/(mean4[i]) ,2 ) + pow( (sigma4[i] * meanerror4[i])/(mean4[i] * mean4[i]) ,2 ) );

  }

  for ( int i = 0; i < n; i++ ) {
    value5[ i ] = sigma5[i] / mean5[i];
    error5[ i ] = sqrt( pow( (sigmaerror5[i])/(mean5[i]) ,2 ) + pow( (sigma5[i] * meanerror5[i])/(mean5[i] * mean5[i]) ,2 ) );

  }
/*
   printf( "\n" );
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy[i] );
     printf( " %f ", energyerror[i] );
     printf( " %f ", mean[i] );
     printf( " %f ", meanerror[i] );
     printf( " %f ", sigma[i] );
     printf( " %f ", sigmaerror[i] );
     printf( " %f ", value[i] );
     printf( " %f ", error[i] );
     printf( "\n" );
   }

   printf( "\n" );
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy2[i] );
     printf( " %f ", energyerror2[i] );
     printf( " %f ", mean2[i] );
     printf( " %f ", meanerror2[i] );
     printf( " %f ", sigma2[i] );
     printf( " %f ", sigmaerror2[i] );
     printf( " %f ", value2[i] );
     printf( " %f ", error2[i] );
     printf( "\n" );
   }

   printf( "\n" );
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy3[i] );
     printf( " %f ", energyerror3[i] );
     printf( " %f ", mean3[i] );
     printf( " %f ", meanerror3[i] );
     printf( " %f ", sigma3[i] );
     printf( " %f ", sigmaerror3[i] );
     printf( " %f ", value3[i] );
     printf( " %f ", error3[i] );
     printf( "\n" );
   }

   printf( "\n" );
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy4[i] );
     printf( " %f ", energyerror4[i] );
     printf( " %f ", mean4[i] );
     printf( " %f ", meanerror4[i] );
     printf( " %f ", sigma4[i] );
     printf( " %f ", sigmaerror4[i] );
     printf( " %f ", value4[i] );
     printf( " %f ", error4[i] );
     printf( "\n" );
   }

   printf( "\n" );
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy5[i] );
     printf( " %f ", energyerror5[i] );
     printf( " %f ", mean5[i] );
     printf( " %f ", meanerror5[i] );
     printf( " %f ", sigma5[i] );
     printf( " %f ", sigmaerror5[i] );
     printf( " %f ", value5[i] );
     printf( " %f ", error5[i] );
     printf( "\n" );
   }
*/
/*   printf( "Here is difference:\n" );

   Float_t v1 = 0;
   Float_t v2 = 0;
   Float_t v3 = 0;
  
   for ( int i = 0; i < n; i++ ) {
       printf( " %f, %f, %f, %f \n", energy[i], value[i], value2[i], value3[i] );
       printf( " Difference between nodigi and digi20: %f \n", value2[i] - value[i] );
       v1 = v1 + ( value2[i] - value[i] );
       printf( " Difference between digi20 and digi60: %f \n", value3[i] - value2[i] );
       v2 = v2 + ( value3[i] - value2[i] );
       printf( " Difference between nodigi and digi60: %f \n", value3[i] - value[i] );
       v3 = v3 + ( value3[i] - value[i] );
   } 

   printf( "Average values: %f, %f, %f \n", v1/n, v2/n, v3/n );
*/
   TGraphErrors *agr;
   TGraphErrors *bgr;
   TGraphErrors *cgr;
   TGraphErrors *dgr;
   TGraphErrors *egr;

   char fname[ 100 ];
   for ( int i = 0; i < 100; i++ ) fname[ i ] = 0;

   TLegend *lsc = new TLegend(0.55,0.62,0.90,0.92);

   for ( int i = 1; i < 4; i++ ) {

   c->cd(i);
   if ( i == 1 ) {
      agr = new TGraphErrors( n, energy, mean, energyerror, meanerror );
      agr->GetYaxis()->SetTitle("Mean, GeV");
      agr->GetXaxis()->SetTitle("Energy, GeV");
      bgr = new TGraphErrors( n, energy2, mean2, energyerror2, meanerror2 );
      bgr->GetYaxis()->SetTitle("Mean, GeV");
      bgr->GetXaxis()->SetTitle("Energy, GeV");
      cgr = new TGraphErrors( n, energy3, mean3, energyerror3, meanerror3 );
      cgr->GetYaxis()->SetTitle("Mean, GeV");
      cgr->GetXaxis()->SetTitle("Energy, GeV");
      dgr = new TGraphErrors( n, energy4, mean4, energyerror4, meanerror4 );
      dgr->GetYaxis()->SetTitle("Mean, GeV");
      dgr->GetXaxis()->SetTitle("Energy, GeV");
      egr = new TGraphErrors( n, energy5, mean5, energyerror5, meanerror5 );
      egr->GetYaxis()->SetTitle("Mean, GeV");
      egr->GetXaxis()->SetTitle("Energy, GeV");
      sprintf( fname, "Linearity" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
      agr->SetTitle(fname);
   }

   if ( i == 2 ) {
      agr = new TGraphErrors( n, energy, sigma, energyerror, sigmaerror );
      agr->GetYaxis()->SetTitle("Sigma, GeV");
      agr->GetXaxis()->SetTitle("Energy, GeV");
      bgr = new TGraphErrors( n, energy2, sigma2, energyerror2, sigmaerror2 );
      bgr->GetYaxis()->SetTitle("Sigma, GeV");
      bgr->GetXaxis()->SetTitle("Energy, GeV");
      cgr = new TGraphErrors( n, energy2, sigma2, energyerror3, sigmaerror3 );
      cgr->GetYaxis()->SetTitle("Sigma, GeV");
      cgr->GetXaxis()->SetTitle("Energy, GeV");
      dgr = new TGraphErrors( n, energy2, sigma2, energyerror4, sigmaerror4 );
      dgr->GetYaxis()->SetTitle("Sigma, GeV");
      dgr->GetXaxis()->SetTitle("Energy, GeV");
      egr = new TGraphErrors( n, energy2, sigma2, energyerror5, sigmaerror5 );
      egr->GetYaxis()->SetTitle("Sigma, GeV");
      egr->GetXaxis()->SetTitle("Energy, GeV");
      sprintf( fname, "Absolute energy resolution" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
      agr->SetTitle(fname);
   }

   if ( i == 3 ) {
      agr = new TGraphErrors( n, energy, value, energyerror, error );
      agr->GetYaxis()->SetTitle("Sigma / Mean");
      agr->GetXaxis()->SetTitle("Energy, GeV");
      bgr = new TGraphErrors( n, energy2, value2, energyerror2, error2 );
      bgr->GetYaxis()->SetTitle("Sigma / Mean");
      bgr->GetXaxis()->SetTitle("Energy, GeV");
      cgr = new TGraphErrors( n, energy2, value2, energyerror3, error3 );
      cgr->GetYaxis()->SetTitle("Sigma / Mean");
      cgr->GetXaxis()->SetTitle("Energy, GeV");
      dgr = new TGraphErrors( n, energy2, value2, energyerror4, error4 );
      dgr->GetYaxis()->SetTitle("Sigma / Mean");
      dgr->GetXaxis()->SetTitle("Energy, GeV");
      egr = new TGraphErrors( n, energy2, value2, energyerror5, error5 );
      egr->GetYaxis()->SetTitle("Sigma / Mean");
      egr->GetXaxis()->SetTitle("Energy, GeV");
      sprintf( fname, "Relative energy resolution" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
      agr->GetYaxis()->SetRangeUser(0.03,0.3);
      agr->SetTitle(fname);
   }

   agr->SetMarkerColor(kBlue); // kBlue // 12
   agr->SetLineColor(kBlue);
   agr->SetLineWidth(3);
   agr->SetMarkerStyle(34); // 21
//   agr->SetMarkerSize(2);
   agr->Draw("ALP");
   bgr->SetMarkerColor(kRed); // kRed  // 15
   bgr->SetLineColor(kRed);
   bgr->SetLineWidth(3);
   bgr->SetMarkerStyle(29); // 21
//   bgr->SetMarkerSize(2);
   bgr->Draw("LPSAME");  // LPSAME
   cgr->SetMarkerColor(kGreen); // kGreen // 17
   cgr->SetLineColor(kGreen);
   cgr->SetLineWidth(3);
   cgr->SetMarkerStyle(20); // 21
//   cgr->SetMarkerSize(2);
   cgr->Draw("LPSAME"); // LPSAME  // ALP
   dgr->SetMarkerColor(kCyan); // kGreen // 17
   dgr->SetLineColor(kCyan);
   dgr->SetLineWidth(3);
   dgr->SetMarkerStyle(21); // 21
//   dgr->SetMarkerSize(2);
   dgr->Draw("LPSAME"); // LPSAME  // ALP
   egr->SetMarkerColor(kViolet); // kGreen // 17
   egr->SetLineColor(kViolet);
   egr->SetLineWidth(3);
   egr->SetMarkerStyle(23); // 21
//   egr->SetMarkerSize(2);
   egr->Draw("LPSAME"); // LPSAME  // ALP
   c->Update();

   }

   lsc->AddEntry(agr,"without ANN","pl");
   lsc->AddEntry(bgr,"with ANN 1","pl");
   lsc->AddEntry(cgr,"with ANN 2","pl");
   lsc->AddEntry(dgr,"with ANN 3","pl");
   lsc->AddEntry(egr,"with ANN 4","pl");

   for ( int i = 1; i < 4; i++ ) {
      c->cd(i);
      lsc->Draw();
   }

}



