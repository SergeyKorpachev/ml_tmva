void graph1() {
    TCanvas *c1 = new TCanvas("graph","graph",200,10,700,500);
    TCanvas *c2 = new TCanvas("graph2","graph2",200,10,700,500);
    TCanvas *c3 = new TCanvas("graph3","graph3",200,10,700,500);
    TCanvas *c4 = new TCanvas("graph4","graph4",200,10,700,500);
    
    //c1->SetFillColor(42);
    //gStyle->SetPalette(52);
    c1->SetGrid();
    c2->SetGrid();
    c3->SetGrid();
    c4->SetGrid();
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
    Float_t lin[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t lin_error[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    Float_t energy2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t energyerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t mean2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t meanerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t sigma2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t sigmaerror2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t value2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t error2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t lin2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t lin_error2[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    Float_t mean3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t lin3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Float_t lin_error3[n] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    float temp11 = 0;
    float temp12 = 0;
    float temp21 = 0;
    float temp22 = 0;

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
        printf( " %f ", lin[i] );
        printf( " %f ", lin_error[i] );
        printf( "\n" );
    }
*/
    FILE *file = fopen("out_1.txt", "r");
    if ( !(long)file ) return;

    FILE *file2 = fopen("out_2.txt", "r");
    if ( !(long)file2 ) return;

    for ( int i = 0; i < n; i++ ) {
        fscanf( file, "%f %E %E %E %E %E %E\n", &energy[i], &mean[i], &meanerror[i], &sigma[i], &sigmaerror[i], &temp11, &temp12 );
        if ( feof( file ) ) break;
    }

    for ( int i = 0; i < n; i++ ) {
        fscanf( file2, "%f %E %E %E %E %E %E\n", &energy2[i], &mean2[i], &meanerror2[i], &sigma2[i], &sigmaerror2[i], &temp21, &temp22 );
        if ( feof( file2 ) ) break;
    }
    
    float a1 = -0.0258227; // 0.0416539;
    float a2 = 0.00489689; // 0.00383733;
    float a3 = -6.1357e-05;// -5.49995e-05;
    
   // float a1 = -0.000810916;
   // float a2 = 0.0106352;
   // float a3 = -0.000316043;
   // float a4 = 2.72191e-06;

    for ( int i = 0; i < n; i++ ) {
        value[ i ] = sigma[i] / mean[i];
        error[ i ] = sqrt( pow( (sigmaerror[i])/(mean[i]) ,2 ) + pow( (sigma[i] * meanerror[i])/(mean[i] * mean[i]) ,2 ) );
        lin[ i ] = ( mean[ i ] - energy[ i ] ) / energy[ i ];
    }

    for ( int i = 0; i < n; i++ ) {
        value2[ i ] = sigma2[i] / mean2[i];
        error2[ i ] = sqrt( pow( (sigmaerror2[i])/(mean2[i]) ,2 ) + pow( (sigma2[i] * meanerror2[i])/(mean2[i] * mean2[i]) ,2 ) );
        lin2[ i ] = ( mean2[ i ] - energy2[ i ] ) / energy2[ i ];
        
        mean3[ i ] = mean2[ i ] * ( a1 + a2 * mean2[ i ] + a3 * ( mean2[ i ] * mean2[ i ] ) );
        //mean3[ i ] = mean2[ i ] * ( a1 + a2 * mean2[ i ] + a3 * ( mean2[ i ] * mean2[ i ] ) + a4 * ( mean2[ i ] * mean2[ i ] * mean2[ i ]));
        lin3[ i ] = ( mean3[ i ] - energy2[ i ] ) / energy2[ i ];
    }

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
        printf( " %f ", lin[i] );
        printf( " %f ", lin_error[i] );
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
        printf( " %f ", lin2[i] );
        printf( " %f ", lin3[i] );
        printf( " %f ", lin_error2[i] );
        printf( "\n" );
    }

    TGraphErrors *agr;
    TGraphErrors *bgr;
    TGraphErrors *cgr;
    
    char fname[ 100 ];
    for ( int i = 0; i < 100; i++ ) fname[ i ] = 0;

    c1->cd();
    agr = new TGraphErrors( n, energy, mean, energyerror, meanerror );
    agr->GetYaxis()->SetTitle("Mean, GeV");
    agr->GetXaxis()->SetTitle("Energy, GeV");
    bgr = new TGraphErrors( n, energy2, mean2, energyerror2, meanerror2 );
    bgr->GetYaxis()->SetTitle("Mean, GeV");
    bgr->GetXaxis()->SetTitle("Energy, GeV");
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

    c2->cd();
    agr = new TGraphErrors( n, energy, sigma, energyerror, sigmaerror );
    agr->GetYaxis()->SetTitle("Sigma, GeV");
    agr->GetXaxis()->SetTitle("Energy, GeV");
    bgr = new TGraphErrors( n, energy2, sigma2, energyerror2, sigmaerror2 );
    bgr->GetYaxis()->SetTitle("Sigma, GeV");
    bgr->GetXaxis()->SetTitle("Energy, GeV");
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
    c2->Update();

    c3->cd();
    agr = new TGraphErrors( n, energy, value, energyerror, error );
    agr->GetYaxis()->SetTitle("Sigma / Mean");
    agr->GetXaxis()->SetTitle("Energy, GeV");
    bgr = new TGraphErrors( n, energy2, value2, energyerror2, error2 );
    bgr->GetYaxis()->SetTitle("Sigma / Mean");
    bgr->GetXaxis()->SetTitle("Energy, GeV");
    sprintf( fname, "Relative energy resolution" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
    agr->GetYaxis()->SetRangeUser(0.03,0.45);
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
    agr = new TGraphErrors( n, energy, lin, energyerror, lin_error );
    agr->GetYaxis()->SetTitle("");
    agr->GetXaxis()->SetTitle("Energy, GeV");
    bgr = new TGraphErrors( n, energy2, lin2, energyerror2, lin_error2 );
    bgr->GetYaxis()->SetTitle("");
    bgr->GetXaxis()->SetTitle("Energy, GeV");
    cgr = new TGraphErrors( n, energy2, lin3, energyerror2, lin_error2 );
    cgr->GetYaxis()->SetTitle("");
    cgr->GetXaxis()->SetTitle("Energy, GeV");
    sprintf( fname, "Residuals to linearity" ); // Linearity energy resolution // Absolute energy resolution // Relative energy resolution
    agr->GetYaxis()->SetRangeUser(-1.0,1.0);
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
    cgr->SetMarkerColor(kGreen); // kGreen // 17
    cgr->SetLineColor(kGreen);
    cgr->SetLineWidth(3);
    cgr->SetMarkerStyle(20); // 21
    //   cgr->SetMarkerSize(2);
    cgr->Draw("LPSAME"); // LPSAME  // ALP
    c4->Update();

    TLegend *lsc = new TLegend(0.55,0.62,0.90,0.92);
    lsc->AddEntry(agr,"no_corr","pl");
    lsc->AddEntry(bgr,"corr","pl");
    lsc->AddEntry(cgr,"new_corr","pl");

    c1->cd();
    lsc->Draw();
    c2->cd();
    lsc->Draw();
    c3->cd();
    lsc->Draw();
    c4->cd();
    lsc->Draw();

}
