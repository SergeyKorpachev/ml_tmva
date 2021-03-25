#include "TROOT.h"
#include <cstdio>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TLatex.h"

void evaluation() {
    TFile *noPU;
    TFile *regr;
    TFile *regrNoPU;
    TFile *corr;
    
    TString noPUname = "data/pionNoPU_test.root";
    TString regrName = "data/pionPU_regr.root";
    TString regrNoPUname = "data/pionNoPU_regr.root";
    TString corrName = "data/pionPU_corr.root";
    
    
    noPU = TFile::Open(noPUname);
    regr = TFile::Open(regrName);
    regrNoPU = TFile::Open(regrNoPUname);
    corr = TFile::Open(corrName);
    
    TTree *noPUTree = (TTree*)noPU->Get("CalibTree");
    TTree *regrTree = (TTree*)regr->Get("CalibTree");
    TTree *regrNoPUtree = (TTree*)regrNoPU->Get("CalibTree");
    TTree *corrTree = (TTree*)corr->Get("CalibTree");
    
    double r_true;
    int ieta;
    
    noPUTree->SetBranchAddress("R_true_fit", &r_true);
    noPUTree->SetBranchAddress("t_ieta", &ieta);
    
    long i = 0, j = 0;
    double r_noPU[60] = {0};
    
    for(i = 0; i < noPUTree->GetEntries(); i++){
        noPUTree->GetEntry(i);
        if(r_noPU[30 + ieta] == 0) {
            r_noPU[30 + ieta] = r_true;
            j++;
            }
        if(j == 54) break;
    }
    
    RooRealVar x("R_true_regr","R_true_regr",0,2) ;
    RooRealVar y("t_ieta","t_ieta", -30, 30) ;
    RooRealVar z("R","R",0,2) ;
    RooRealVar w("R_true_corr","R_true_corr",0,2) ;
    RooDataSet dataset = RooDataSet("data", "data", regrTree,  RooArgSet(x, y, z));
    RooRealVar meanR1("mean","mean of gaussian",1,0,2) ;
    RooRealVar sigmaR1("sigma","width of gaussian",0.2,0.00001,1) ;
    RooGaussian gaussR1("gauss","gaussian PDF",x,meanR1,sigmaR1) ;
    
    RooRealVar meanR2("mean","mean of gaussian",1,0,2) ;
    RooRealVar sigmaR2("sigma","width of gaussian",0.2,0.00001,1) ;
    RooGaussian gaussR2("gauss","gaussian PDF",z,meanR2,sigmaR2) ;
    
    char* ccut = new char [128];
    double R_regr_fit[60];
    double R_PU_fit[60];
    double R_regr_noPU[60];
    double R_corr[60];
    
    RooDataSet **data = (RooDataSet**)operator new (sizeof(RooDataSet)*60);
    
    for(i = -30; i < 30; i++){
        sprintf(ccut, "abs(t_ieta - %ld) < 0.5", i);
        data[30 + i] = (RooDataSet*)dataset.reduce(ccut); 
        gaussR1.fitTo(*data[30 + i]) ;
        gaussR2.fitTo(*data[30 + i]) ;
        R_regr_fit[30 + i] = meanR1.getValV();
        R_PU_fit[30 + i] = meanR2.getValV();
        (*data[30 + i]).~RooDataSet();
    }
    
    RooDataSet dataset2 = RooDataSet("data2", "data2", regrNoPUtree,  RooArgSet(x, y));
    RooDataSet **data2 = (RooDataSet**)operator new (sizeof(RooDataSet)*60);
    
    RooRealVar meanR3("mean","mean of gaussian",1,0,2) ;
    RooRealVar sigmaR3("sigma","width of gaussian",0.2,0.00001,1) ;
    RooGaussian gaussR3("gauss","gaussian PDF",x,meanR3,sigmaR3) ;
    
    for(i = -30; i < 30; i++){
        sprintf(ccut, "abs(t_ieta - %ld) < 0.5", i);
        data2[30 + i] = (RooDataSet*)dataset2.reduce(ccut); 
        gaussR3.fitTo(*data2[30 + i]) ;
        R_regr_noPU[30 + i] = meanR3.getValV();
        (*data2[30 + i]).~RooDataSet();
    }
    
    RooDataSet dataset3 = RooDataSet("data3", "data3", corrTree,  RooArgSet(w, y));
    RooDataSet **data3 = (RooDataSet**)operator new (sizeof(RooDataSet)*60);
    
    RooRealVar meanR4("mean","mean of gaussian",1,0,2) ;
    RooRealVar sigmaR4("sigma","width of gaussian",0.2,0.00001,1) ;
    RooGaussian gaussR4("gauss","gaussian PDF",w,meanR4,sigmaR4) ;
    
    for(i = -30; i < 30; i++){
        sprintf(ccut, "abs(t_ieta - %ld) < 0.5", i);
        data3[30 + i] = (RooDataSet*)dataset3.reduce(ccut); 
        gaussR4.fitTo(*data3[30 + i]) ;
        R_corr[30 + i] = meanR4.getValV();
        (*data3[30 + i]).~RooDataSet();
    }
    
    double num[60];
    for(i = 0; i < 60; i ++)
        num[i] = i - 30;
    
    TMultiGraph *mg1 = new TMultiGraph();
    
    TCanvas *cEval1 = new TCanvas("cEval1","Graph1",800,400);
    
    TH2F *hpx1 = new TH2F("hpx","MPV of response vs. i#eta",10,-26.5,26.5,10,0.9,1.61);
    hpx1->SetStats(kFALSE);   // no statistics
    hpx1->SetTitleSize(0.05, "XY");
    hpx1->GetXaxis()->SetTitle("i#eta");
    hpx1->GetYaxis()->SetTitle("#frac{E_{HCAL}}{p - E_{ECAL}}");
    hpx1->Draw();
    
    TGraph* grNoPU1 = new TGraph(60,num,r_noPU);
    grNoPU1->SetMarkerColor(kBlack);
    grNoPU1->SetMarkerSize(0.8);
    grNoPU1->SetMarkerStyle(20);
    grNoPU1->SetPoint(0, -5, 1.54);
    mg1->Add(grNoPU1);
    
    /*TGraph* grRegr1 = new TGraph(60,num,R_regr_fit);
    grRegr1->SetMarkerColor(kRed);
    grRegr1->SetMarkerSize(0.8);
    grRegr1->SetMarkerStyle(21);
    grRegr1->SetPoint(0, -5, 1.49);
    mg1->Add(grRegr1);*/
    
    /*TGraph* grRegrNoPU = new TGraph(60,num,R_regr_noPU);
    grRegrNoPU->SetMarkerColor(kBlue);
    grRegrNoPU->SetMarkerSize(0.8);
    grRegrNoPU->SetMarkerStyle(23);
    grRegrNoPU->SetPoint(0, -5, 1.39);
    mg1->Add(grRegrNoPU);*/
    
    TGraph* grPU1 = new TGraph(60,num,R_PU_fit);
    grPU1->SetMarkerColor(kRed);
    grPU1->SetMarkerSize(0.8);
    grPU1->SetMarkerStyle(22);
    grPU1->SetPoint(0, -5, 1.44);
    mg1->Add(grPU1);
    
    mg1->Draw("P");
    
    TLatex *t1 = new TLatex();
    
    t1->SetTextFont(62);
    t1->SetTextSize(0.05);
    t1->SetTextAlign(12);
    
    t1->SetTextColor(kBlack);
    t1->DrawLatex(-4, 1.54, "#pi^{#pm} w/o PU");
    
    //t1->SetTextColor(kRed);
    //t1->DrawLatex(-4, 1.49, "#pi^{#pm} w/ PU corrected");
    
    t1->SetTextColor(kRed);
    t1->DrawLatex(-4, 1.44, "#pi^{#pm} w/ PU");
    
    //t1->SetTextColor(kBlue);
    //t1->DrawLatex(-4, 1.39, "noPU regr");
    
    cEval1->SaveAs("graphs/pileup2.png");
    
    /*TMultiGraph *mg2 = new TMultiGraph();
    
    TCanvas *cEval2 = new TCanvas("cEval2","Graph2",800,400);
    
    TH2F *hpx2 = new TH2F("hpx","MPV of response vs. ieta",10,-26.5,26.5,10,0.9,1.61);
    hpx2->SetStats(kFALSE);   // no statistics
    hpx2->GetXaxis()->SetTitle("ieta");
    hpx2->GetYaxis()->SetTitle("eHcal/(p - eEcal)");
    hpx2->Draw();
    
    TGraph* grNoPU2 = new TGraph(60,num,r_noPU);
    grNoPU2->SetMarkerColor(kBlack);
    grNoPU2->SetMarkerSize(0.75);
    grNoPU2->SetMarkerStyle(20);
    grNoPU2->SetPoint(0, -5, 1.54);
    mg2->Add(grNoPU2);
    
    TGraph* grRegr2 = new TGraph(60,num,R_regr_fit);
    grRegr2->SetMarkerColor(kRed);
    grRegr2->SetMarkerSize(0.75);
    grRegr2->SetMarkerStyle(21);
    grRegr2->SetPoint(0, -5, 1.49);
    mg2->Add(grRegr2);
    
    TGraph* grPU2 = new TGraph(60,num,R_PU_fit);
    grPU2->SetMarkerColor(kSpring);
    grPU2->SetMarkerSize(0.75);
    grPU2->SetMarkerStyle(22);
    grPU2->SetPoint(0, -5, 1.44);
    mg2->Add(grPU2);
    
    TGraph* grCorr = new TGraph(60,num,R_corr);
    grCorr->SetMarkerColor(kBlue);
    grCorr->SetMarkerSize(0.75);
    grCorr->SetMarkerStyle(23);
    grCorr->SetPoint(0, -5, 1.39);
    mg2->Add(grCorr);
    
    TLatex *t2 = new TLatex();
    
    t2->SetTextFont(62);
    t2->SetTextSize(0.04);
    t2->SetTextAlign(12);
    
    t2->SetTextColor(kBlack);
    t2->DrawLatex(-4, 1.54, "noPU");
    
    t2->SetTextColor(kRed);
    t2->DrawLatex(-4, 1.49, "PU regr");
    
    t2->SetTextColor(kSpring);
    t2->DrawLatex(-4, 1.44, "PU");
    
    t2->SetTextColor(kBlue);
    t2->DrawLatex(-4, 1.39, "PU corr");
    
    mg2->Draw("P");
    
    cEval2->SaveAs("graphs/evaluationGraphSigDifN3_2.gif");*/
}
