void graph_errors() {
   TCanvas *c1 = new TCanvas("graph1","graph1",200,10,700,500);
   TCanvas *c2 = new TCanvas("graph2","graph2",200,10,700,500);
//   TCanvas *c3 = new TCanvas("graph3","graph3",200,10,700,500);
//   TCanvas *c4 = new TCanvas("graph4","graph4",200,10,700,500);

   //c1->SetFillColor(42);
   //gStyle->SetPalette(52);
   c1->SetGrid();
   c2->SetGrid();
//   c3->SetGrid();
//   c4->SetGrid();
   //c1->GetFrame()->SetFillColor(21);
   //c1->GetFrame()->SetBorderSize(12);

   const Int_t n = 16;

   Float_t energy[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t energyerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_mean[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_mean[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_meanerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_meanerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_sigma[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_sigma[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_sigmaerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_sigmaerror[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_chi[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_chi[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t linearity_error[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t absolute_error[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t ratio[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t ratio_error_stat[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t ratio_error_sys[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t ratio_error[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t resolution[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t resolution_error_stat[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t resolution_error_sys[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t resolution_error[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

   Float_t energy2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t energyerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_mean2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_mean2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_meanerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_meanerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_sigma2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_sigma2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_sigmaerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_sigmaerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t mean_chi2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t rms_chi2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t linearity_error2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t absolute_error2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t ratio2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t ratio_error_stat2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t ratio_error_sys2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t ratio_error2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t resolution2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t resolution_error_stat2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t resolution_error_sys2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   Float_t resolution_error2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

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
   FILE *file1 = fopen("out0_5000.txt", "r");
   if ( !(long)file1 ) return;

   FILE *file2 = fopen("out1.txt", "r");
   if ( !(long)file2 ) return;

  for ( int i = 0; i < n; i++ ) {
    fscanf( file1, "%f %E %E %E %E %E %E %E\n", &energy[i], &mean_mean[i], &rms_mean[i], &mean_meanerror[i], &mean_sigma[i], &rms_sigma[i], &mean_sigmaerror[i], &mean_chi[i] );
    if ( feof( file1 ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {
    fscanf( file2, "%f %E %E %E %E %E %E %E\n", &energy2[i], &mean_mean2[i], &rms_mean2[i], &mean_meanerror2[i], &mean_sigma2[i], &rms_sigma2[i], &mean_sigmaerror2[i], &mean_chi2[i] );
    if ( feof( file2 ) ) break;
  }

  for ( int i = 0; i < n; i++ ) {

    linearity_error[ i ] = sqrt( ( pow( mean_meanerror[ i ], 2 ) ) + ( pow( rms_mean[ i ], 2 ) ) );
    absolute_error[ i ] = sqrt( ( pow( mean_sigmaerror[ i ], 2 ) ) + ( pow( rms_sigma[ i ], 2 ) ) );

    ratio[ i ] =  ( mean_mean[i] - energy[i] ) / energy[i];
    ratio_error_stat[ i ] = sqrt( pow( (mean_meanerror[i])/(energy[i]), 2 ) + pow( (mean_mean[i] * energyerror[i])/(energy[i] * energy[i]), 2 ) );
    ratio_error_sys[ i ] = sqrt( pow( (rms_mean[i])/(energy[i]), 2 ) + pow( (mean_mean[i] * energyerror[i])/(energy[i] * energy[i]), 2 ) );
    ratio_error[ i ] = sqrt( ( pow( ratio_error_stat[ i ], 2 ) ) + ( pow( ratio_error_sys[ i ], 2 ) ) );

    resolution[ i ] = mean_sigma[i] / mean_mean[i];
    resolution_error_stat[ i ] = sqrt( pow( (mean_sigmaerror[i])/(mean_mean[i]), 2 ) + pow( (mean_sigma[i] * mean_meanerror[i])/(mean_mean[i] * mean_mean[i]), 2 ) );
    resolution_error_sys[ i ] = sqrt( pow( (rms_sigma[i])/(mean_mean[i]), 2 ) + pow( (mean_sigma[i] * rms_mean[i])/(mean_mean[i] * mean_mean[i]), 2 ) );
    resolution_error[ i ] = sqrt( ( pow( resolution_error_stat[ i ], 2 ) ) + ( pow( resolution_error_sys[ i ], 2 ) ) );

  }

  for ( int i = 0; i < n; i++ ) {

    linearity_error2[ i ] = sqrt( ( pow( mean_meanerror2[ i ], 2 ) ) + ( pow( rms_mean2[ i ], 2 ) ) );
    absolute_error2[ i ] = sqrt( ( pow( mean_sigmaerror2[ i ], 2 ) ) + ( pow( rms_sigma2[ i ], 2 ) ) );

    ratio2[ i ] =  ( mean_mean2[i] - energy2[i] ) / energy2[i];
    ratio_error_stat2[ i ] = sqrt( pow( (mean_meanerror2[i])/(energy2[i]), 2 ) + pow( (mean_mean2[i] * energyerror2[i])/(energy2[i] * energy2[i]), 2 ) );
    ratio_error_sys2[ i ] = sqrt( pow( (rms_mean2[i])/(energy2[i]), 2 ) + pow( (mean_mean2[i] * energyerror2[i])/(energy2[i] * energy2[i]), 2 ) );
    ratio_error2[ i ] = sqrt( ( pow( ratio_error_stat2[ i ], 2 ) ) + ( pow( ratio_error_sys2[ i ], 2 ) ) );

    resolution2[ i ] = mean_sigma2[i] / mean_mean2[i];
    resolution_error_stat2[ i ] = sqrt( pow( (mean_sigmaerror2[i])/(mean_mean2[i]), 2 ) + pow( (mean_sigma2[i] * mean_meanerror2[i])/(mean_mean2[i] * mean_mean2[i]), 2 ) );
    resolution_error_sys2[ i ] = sqrt( pow( (rms_sigma2[i])/(mean_mean2[i]), 2 ) + pow( (mean_sigma2[i] * rms_mean2[i])/(mean_mean2[i] * mean_mean2[i]), 2 ) );
    resolution_error2[ i ] = sqrt( ( pow( resolution_error_stat2[ i ], 2 ) ) + ( pow( resolution_error_sys2[ i ], 2 ) ) );

  }

   printf( "\n" );
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy[i] );
     printf( " %f ", energyerror[i] );
     printf( " %f ", mean_mean[i] );
     printf( " %f ", rms_mean[i] );
     printf( " %f ", mean_meanerror[i] );
     printf( " %f ", rms_meanerror[i] );
     printf( " %f ", mean_sigma[i] );
     printf( " %f ", rms_sigma[i] );
     printf( " %f ", mean_sigmaerror[i] );
     printf( " %f ", rms_sigmaerror[i] );
     printf( " %f ", linearity_error[i] );
     printf( " %f ", absolute_error[i] );
     printf( " %f ", ratio[i] );
     printf( " %f ", ratio_error[i] );
     printf( " %f ", resolution[i] );
     printf( " %f ", resolution_error[i] );
     printf( "\n" );
   }

   printf( "\n" );
   for (int i = 0; i < n; i++) {
     printf( " %f ", energy2[i] );
     printf( " %f ", energyerror2[i] );
     printf( " %f ", mean_mean2[i] );
     printf( " %f ", rms_mean2[i] );
     printf( " %f ", mean_meanerror2[i] );
     printf( " %f ", rms_meanerror2[i] );
     printf( " %f ", mean_sigma2[i] );
     printf( " %f ", rms_sigma2[i] );
     printf( " %f ", mean_sigmaerror2[i] );
     printf( " %f ", rms_sigmaerror2[i] );
     printf( " %f ", linearity_error2[i] );
     printf( " %f ", absolute_error2[i] );
     printf( " %f ", ratio2[i] );
     printf( " %f ", ratio_error2[i] );
     printf( " %f ", resolution2[i] );
     printf( " %f ", resolution_error2[i] );
     printf( "\n" );
   }

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

   char fname[ 100 ];
   for ( int i = 0; i < 100; i++ ) fname[ i ] = 0;
/*
   c1->cd();
   agr = new TGraphErrors( n, energy, mean_mean, energyerror, linearity_error );
   agr->GetYaxis()->SetTitle("E_{reco}, GeV");
   agr->GetXaxis()->SetTitle("E_{true}, GeV");
   bgr = new TGraphErrors( n, energy2, mean_mean2, energyerror2, linearity_error2 );
   bgr->GetYaxis()->SetTitle("E_{reco}, GeV");
   bgr->GetXaxis()->SetTitle("E_{true}, GeV");
   sprintf( fname, "Linearity" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
   agr->SetTitle(fname);

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
   c1->Update();
*/

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------

   c1->cd();
   agr = new TGraphErrors( n, energy, ratio, energyerror, ratio_error_sys );
   agr->GetYaxis()->SetTitle("( E_{reco} - E_{true} ) / E_{true}");
   agr->GetXaxis()->SetTitle("E_{true}, GeV");
   bgr = new TGraphErrors( n, energy, ratio, energyerror, ratio_error_stat );
   bgr->GetYaxis()->SetTitle("( E_{reco} - E_{true} ) / E_{true}");
   bgr->GetXaxis()->SetTitle("E_{true}, GeV");
   cgr = new TGraphErrors( n, energy2, ratio2, energyerror2, ratio_error_stat2 );
   cgr->GetYaxis()->SetTitle("( E_{reco} - E_{true} ) / E_{true}");
   cgr->GetXaxis()->SetTitle("E_{true}, GeV");
   dgr = new TGraphErrors( n, energy2, ratio2, energyerror2, ratio_error_stat2 );
   dgr->GetYaxis()->SetTitle("( E_{reco} - E_{true} ) / E_{true}");
   dgr->GetXaxis()->SetTitle("E_{true}, GeV");
   sprintf( fname, "Linearity" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
//   agr->GetYaxis()->SetRangeUser(-0.25, 0.8);
   agr->SetTitle(fname);

   agr->SetFillColor(kCyan);
   agr->SetFillStyle(3001);
   agr->SetMarkerColor(kCyan); // kBlue // 12
   agr->SetLineColor(kCyan);
   agr->SetLineWidth(3);
   agr->SetMarkerStyle(34); // 21
//   agr->SetMarkerSize(2);
   agr->Draw("A 3"); // ALP
   bgr->SetMarkerColor(kBlue); // kRed  // 15
   bgr->SetLineColor(kBlue);
   bgr->SetLineWidth(3);
   bgr->SetFillColor(kCyan);
   bgr->SetMarkerStyle(20); // 21
//   bgr->SetMarkerSize(2);
   bgr->Draw("P SAME");  // LPSAME
   cgr->SetMarkerColor(kBlack); // kRed  // 15
   cgr->SetFillStyle(3001);
   cgr->SetLineColor(kYellow-6);
   cgr->SetLineWidth(3);
   cgr->SetFillColor(kYellow-6);
   cgr->SetMarkerStyle(20); // 21
//   bgr->SetMarkerSize(2);
   cgr->Draw("3 SAME");  // LPSAME
   dgr->SetMarkerColor(kRed); // kRed  // 15
   dgr->SetLineColor(kRed);
   dgr->SetLineWidth(3);
   dgr->SetFillColor(kYellow-6);
   dgr->SetMarkerStyle(20); // 21
//   bgr->SetMarkerSize(2);
   dgr->Draw("P SAME");  // LPSAME
   c1->Update();

   c2->cd();
   agr = new TGraphErrors( n, energy, mean_sigma, energyerror, rms_sigma );
   agr->GetYaxis()->SetTitle("#sigma_{reco}, GeV");
   agr->GetXaxis()->SetTitle("E_{true}, GeV");
   bgr = new TGraphErrors( n, energy, mean_sigma, energyerror, mean_sigmaerror );
   bgr->GetYaxis()->SetTitle("#sigma_{reco}, GeV");
   bgr->GetXaxis()->SetTitle("E_{true}, GeV");
   cgr = new TGraphErrors( n, energy2, mean_sigma2, energyerror2, rms_sigma2 );
   cgr->GetYaxis()->SetTitle("#sigma_{reco}, GeV");
   cgr->GetXaxis()->SetTitle("E_{true}, GeV");
   dgr = new TGraphErrors( n, energy2, mean_sigma2, energyerror2, mean_sigmaerror2 );
   dgr->GetYaxis()->SetTitle("#sigma_{reco}, GeV");
   dgr->GetXaxis()->SetTitle("E_{true}, GeV");
   sprintf( fname, "Absolute energy resolution" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
//   agr->GetYaxis()->SetRangeUser(-0.25, 1.0);
   agr->SetTitle(fname);

   agr->SetFillColor(kCyan);
   agr->SetFillStyle(3001);
   agr->SetMarkerColor(kCyan); // kBlue // 12
   agr->SetLineColor(kCyan);
   agr->SetLineWidth(3);
   agr->SetMarkerStyle(34); // 21
//   agr->SetMarkerSize(2);
   agr->Draw("A 3"); // ALP
   bgr->SetMarkerColor(kBlue); // kRed  // 15
   bgr->SetLineColor(kBlue);
   bgr->SetLineWidth(3);
   bgr->SetFillColor(kCyan);
   bgr->SetMarkerStyle(20); // 21
//   bgr->SetMarkerSize(2);
   bgr->Draw("P SAME");  // LPSAME
   cgr->SetMarkerColor(kBlack); // kRed  // 15
   cgr->SetFillStyle(3001);
   cgr->SetLineColor(kYellow-6);
   cgr->SetLineWidth(3);
   cgr->SetFillColor(kYellow-6);
   cgr->SetMarkerStyle(20); // 21
//   bgr->SetMarkerSize(2);
   cgr->Draw("3 SAME");  // LPSAME
   dgr->SetMarkerColor(kRed); // kRed  // 15
   dgr->SetLineColor(kRed);
   dgr->SetLineWidth(3);
   dgr->SetFillColor(kYellow-6);
   dgr->SetMarkerStyle(20); // 21
//   bgr->SetMarkerSize(2);
   dgr->Draw("P SAME");  // LPSAME
   c2->Update();





// ------------------------------------------------------------------------------------------------------------------------------------------------------------------


/*   c2->cd();
   agr = new TGraphErrors( n, energy, ratio, energyerror, ratio_error );
   agr->GetYaxis()->SetTitle("( E_{reco} - E_{true} ) / E_{true}");
   agr->GetXaxis()->SetTitle("E_{true}, GeV");
   bgr = new TGraphErrors( n, energy2, ratio2, energyerror2, ratio_error2 );
   bgr->GetYaxis()->SetTitle("( E_{reco} - E_{true} ) / E_{true}");
   bgr->GetXaxis()->SetTitle("E_{true}, GeV");
   sprintf( fname, "Linearity" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
   agr->GetYaxis()->SetRangeUser(-0.3,0.8);
   agr->SetTitle(fname);

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
   c2->Update();

   c3->cd();
   agr = new TGraphErrors( n, energy, mean_sigma, energyerror, absolute_error );
   agr->GetYaxis()->SetTitle("#sigma_{reco}, GeV");
   agr->GetXaxis()->SetTitle("E_{true}, GeV");
   bgr = new TGraphErrors( n, energy2, mean_sigma2, energyerror2, absolute_error2 );
   bgr->GetYaxis()->SetTitle("#sigma_{reco}, GeV");
   bgr->GetXaxis()->SetTitle("E_{true}, GeV");
   sprintf( fname, "Absolute energy resolution" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
   agr->SetTitle(fname);

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
   c3->Update();

   c4->cd();
   agr = new TGraphErrors( n, energy, resolution, energyerror, resolution_error );
   agr->GetYaxis()->SetTitle("#sigma_{reco} / E_{reco}");
   agr->GetXaxis()->SetTitle("E_{true}, GeV");
   bgr = new TGraphErrors( n, energy2, resolution2, energyerror2, resolution_error2 );
   bgr->GetYaxis()->SetTitle("#sigma_{reco} / E_{reco}");
   bgr->GetXaxis()->SetTitle("E_{true}, GeV");
   sprintf( fname, "Relative energy resolution" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
//   agr->GetYaxis()->SetRangeUser(0.03,0.45);
   agr->SetTitle(fname);

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
   c4->Update();
*/
   TLegend *lsc1 = new TLegend(0.55,0.62,0.90,0.92);
//   lsc1->AddEntry(agr,"without ANN","pl");
   lsc1->AddEntry(bgr,"without ANN","plf");
//   lsc1->AddEntry(cgr,"without ANN","plf");
   lsc1->AddEntry(dgr,"with ANN","plf");

   TLegend *lsc2 = new TLegend(0.55,0.62,0.90,0.92);
//   lsc2->AddEntry(agr,"without ANN","pl");
   lsc2->AddEntry(bgr,"without ANN","plf");
//   lsc2->AddEntry(cgr,"without ANN","plf");
   lsc2->AddEntry(dgr,"with ANN","plf");

//   TLegend *lsc3 = new TLegend(0.55,0.62,0.90,0.92);
//   lsc3->AddEntry(agr,"without ANN","pl");
//   lsc3->AddEntry(bgr,"with ANN","pl");

//   TLegend *lsc4 = new TLegend(0.55,0.62,0.90,0.92);
//   lsc4->AddEntry(agr,"without ANN","pl");
//   lsc4->AddEntry(bgr,"with ANN","pl");

   c1->cd();
   lsc1->Draw();
   c2->cd();
   lsc2->Draw();
//   c3->cd();
//   lsc3->Draw();
//   c4->cd();
//   lsc4->Draw();

}



