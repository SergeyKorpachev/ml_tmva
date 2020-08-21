#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
using namespace TMVA;
void application( TString myMethodList = "" ) 
{

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
/*   Use["PDERS"]           = 0;
   Use["PDEFoam"]         = 0; 
   Use["KNN"]             = 0;
   // 
   // --- Linear Discriminant Analysis
   Use["LD"]              = 0;
   // 
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   // 
   // --- Neural Network
*/   Use["MLP"] = 1;
/*   Use["DNN_CPU"] = 0;
   // 
   // --- Support Vector Machine 
   Use["SVM"]             = 0;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 0;
   Use["BDTG"]            = 0;
*/   // ---------------------------------------------------------------
   std::cout << std::endl;
   std::cout << "==> Start TMVARegressionApplication" << std::endl;
   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);
         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   char fname1[ 120 ];
   char fname2[ 120 ];
   int nfiles = 16;
   int mass_energy[] = { 1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90 };

   for ( unsigned int i = 0; i < nfiles; i++ ) {
   cout << "I === " << i + 1 << endl;

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object
   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    
   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
//   Float_t var1, var2;
//   reader->AddVariable( "var1", &var1 );
//   reader->AddVariable( "var2", &var2 );

   Float_t energy, eecal, ehcal;
   Float_t nhits_t, nhits_ecal_t, nhits_hcal_t, muon_nhits_t;
   Float_t time, etime, htime, radius, eradius, hradius, elayer, hlayer, energy_hit, energy_hit_ecal, energy_hit_hcal;
   Float_t muon_energy, muon_energy_hit, muon_time, muon_layer;
   Float_t energy_hit_ecal_max, energy_hit_hcal_max;
   Float_t n30_t, n35_t, n40_t, n45_t, n50_t, n55_t, n60_t, n65_t, n70_t, n75_t, n80_t, nav_t;
   Float_t c30, c35, c40, c45, c50, c55, c60, c65, c70, c75, c80;
//   reader->AddVariable( "energy", &energy );
   reader->AddVariable( "eecal", &eecal );
   reader->AddVariable( "ehcal", &ehcal );

//   reader->AddVariable( "nhits_t", &nhits_t );
   reader->AddVariable( "nhits_ecal_t", &nhits_ecal_t );
   reader->AddVariable( "nhits_hcal_t", &nhits_hcal_t );

//   reader->AddVariable( "time", &time );
   reader->AddVariable( "etime", &etime );
   reader->AddVariable( "htime", &htime );
//   reader->AddVariable( "radius", &radius );
   reader->AddVariable( "eradius", &eradius );
   reader->AddVariable( "hradius", &hradius );

   reader->AddVariable( "elayer", &elayer );
   reader->AddVariable( "hlayer", &hlayer );

//   reader->AddVariable( "energy_hit", &energy_hit );
   reader->AddVariable( "energy_hit_ecal", &energy_hit_ecal );
   reader->AddVariable( "energy_hit_hcal", &energy_hit_hcal );

   reader->AddVariable( "energy_hit_ecal_max", &energy_hit_ecal_max );
   reader->AddVariable( "energy_hit_hcal_max", &energy_hit_hcal_max );

/*   reader->AddVariable( "n30_t", &n30_t );
   reader->AddVariable( "n35_t", &n35_t );
   reader->AddVariable( "n40_t", &n40_t );
   reader->AddVariable( "n45_t", &n45_t );
   reader->AddVariable( "n50_t", &n50_t );
   reader->AddVariable( "n55_t", &n55_t );
   reader->AddVariable( "n60_t", &n60_t );
   reader->AddVariable( "n65_t", &n65_t );
   reader->AddVariable( "n70_t", &n70_t );
   reader->AddVariable( "n75_t", &n75_t );
   reader->AddVariable( "n80_t", &n80_t );
   reader->AddVariable( "nav_t", &nav_t );

   reader->AddVariable( "c30", &c30 );
   reader->AddVariable( "c35", &c35 );
   reader->AddVariable( "c40", &c40 );
   reader->AddVariable( "c45", &c45 );
   reader->AddVariable( "c50", &c50 );
   reader->AddVariable( "c55", &c55 );
   reader->AddVariable( "c60", &c60 );
   reader->AddVariable( "c65", &c65 );
   reader->AddVariable( "c70", &c70 );
   reader->AddVariable( "c75", &c75 );
   reader->AddVariable( "c80", &c80 );
*/
//   reader->AddVariable( "muon_energy", &muon_energy );
//   reader->AddVariable( "muon_energy_hit", &muon_energy_hit );
//   reader->AddVariable( "muon_nhits_t", &muon_nhits_t );
//   reader->AddVariable( "muon_time", &muon_time );
//   reader->AddVariable( "muon_layer", &muon_layer );

   // Spectator variables declared in the training have to be added to the reader, too
//   Float_t spec1,spec2;
//   reader->AddSpectator( "spec1:=var1*2",  &spec1 );
//   reader->AddSpectator( "spec2:=var1*3",  &spec2 );
   // --- Book the MVA methods
   TString dir    = "dataset/weights/";
   TString prefix = "TMVARegression";
   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = it->first + " method";
         TString weightfile = dir + prefix + "_" + TString(it->first) + ".weights.xml";
         reader->BookMVA( methodName, weightfile ); 
      }
   }

   // Book output histograms
   TH1* hists[100];
   TTree* trees[100];
   Float_t per[100];
   Int_t nhists = -1;
   Int_t ntrees = -1;
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      TH1* h = new TH1F( it->first.c_str(), TString(it->first) + " method", 100, -100, 600 );
      if (it->second) hists[++nhists] = h;
      if (it->second) trees[++ntrees] = new TTree("tree", "tree");
      if (it->second) trees[ntrees]-> Branch( TString(it->first) + "_method", &( per[ntrees] ), "per" );
   }
   nhists++;
   ntrees++;
   
   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //
   TFile *input(0);
//   TString fname = "./tmva_reg_example.root";

   sprintf( fname1, "./gun_k0L_%dgev_FTFP_BERT_5000evt_ILD_l5_v02steel.root", mass_energy[ i ] );

   TString fname = fname1;
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }
   else {
      TFile::SetCacheFileDir(".");
      input = TFile::Open("http://root.cern.ch/files/tmva_reg_example.root", "CACHEREAD"); // if not: download from ROOT server
   }
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegressionApp        : Using input file: " << input->GetName() << std::endl;
   // --- Event loop
   // Prepare the tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
//   TTree* theTree = (TTree*)input->Get("TreeR");
   TTree* theTree = (TTree*)input->Get("tree");
   std::cout << "--- Select signal sample" << std::endl;
//   theTree->SetBranchAddress( "var1", &var1 );
//   theTree->SetBranchAddress( "var2", &var2 );

//   theTree->SetBranchAddress( "energy", &energy );
   theTree->SetBranchAddress( "eecal", &eecal );
   theTree->SetBranchAddress( "ehcal", &ehcal );

//   theTree->SetBranchAddress( "nhits_t", &nhits_t );
   theTree->SetBranchAddress( "nhits_ecal_t", &nhits_ecal_t );
   theTree->SetBranchAddress( "nhits_hcal_t", &nhits_hcal_t );

//   theTree->SetBranchAddress( "time", &time );
   theTree->SetBranchAddress( "etime", &etime );
   theTree->SetBranchAddress( "htime", &htime );
//   theTree->SetBranchAddress( "radius", &radius );
   theTree->SetBranchAddress( "eradius", &eradius );
   theTree->SetBranchAddress( "hradius", &hradius );

   theTree->SetBranchAddress( "elayer", &elayer );
   theTree->SetBranchAddress( "hlayer", &hlayer );

//   theTree->SetBranchAddress( "energy_hit", &energy_hit );
   theTree->SetBranchAddress( "energy_hit_ecal", &energy_hit_ecal );
   theTree->SetBranchAddress( "energy_hit_hcal", &energy_hit_hcal );

   theTree->SetBranchAddress( "energy_hit_ecal_max", &energy_hit_ecal_max );
   theTree->SetBranchAddress( "energy_hit_hcal_max", &energy_hit_hcal_max );

/*   theTree->SetBranchAddress( "n30_t", &n30_t );
   theTree->SetBranchAddress( "n35_t", &n35_t );
   theTree->SetBranchAddress( "n40_t", &n40_t );
   theTree->SetBranchAddress( "n45_t", &n45_t );
   theTree->SetBranchAddress( "n50_t", &n50_t );
   theTree->SetBranchAddress( "n55_t", &n55_t );
   theTree->SetBranchAddress( "n60_t", &n60_t );
   theTree->SetBranchAddress( "n65_t", &n65_t );
   theTree->SetBranchAddress( "n70_t", &n70_t );
   theTree->SetBranchAddress( "n75_t", &n75_t );
   theTree->SetBranchAddress( "n80_t", &n80_t );
   theTree->SetBranchAddress( "nav_t", &nav_t );

   theTree->SetBranchAddress( "c30", &c30 );
   theTree->SetBranchAddress( "c35", &c35 );
   theTree->SetBranchAddress( "c40", &c40 );
   theTree->SetBranchAddress( "c45", &c45 );
   theTree->SetBranchAddress( "c50", &c50 );
   theTree->SetBranchAddress( "c55", &c55 );
   theTree->SetBranchAddress( "c60", &c60 );
   theTree->SetBranchAddress( "c65", &c65 );
   theTree->SetBranchAddress( "c70", &c70 );
   theTree->SetBranchAddress( "c75", &c75 );
   theTree->SetBranchAddress( "c80", &c80 );
*/
//   theTree->SetBranchAddress( "muon_energy", &muon_energy );
//   theTree->SetBranchAddress( "muon_energy_hit", &muon_energy_hit );
//   theTree->SetBranchAddress( "muon_nhits_t", &muon_nhits_t );
//   theTree->SetBranchAddress( "muon_time", &muon_time );
//   theTree->SetBranchAddress( "muon_layer", &muon_layer );

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {
      if (ievt%1000 == 0) {
         std::cout << "--- ... Processing event: " << ievt << std::endl;
      }
      theTree->GetEntry(ievt);
      // Retrieve the MVA target values (regression outputs) and fill into histograms
      // NOTE: EvaluateRegression(..) returns a vector for multi-target regression
      for (Int_t ih=0; ih<nhists; ih++) {
         TString title = hists[ih]->GetTitle();
         Float_t val = (reader->EvaluateRegression( title ))[0];
         hists[ih]->Fill( val );
         per[ih] = val;
         trees[ih]->Fill();    
      }
   }
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();
   // --- Write histograms

   sprintf( fname2, "./application%d.root", mass_energy[ i ] );
   TFile *target  = new TFile( fname2, "RECREATE" );

   for (Int_t ih=0; ih<nhists; ih++) {
     hists[ih]->Write();
     trees[ih]->Write();
   }
   target->Close();
   std::cout << "--- Created root file: \"" << target->GetName() 
             << "\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVARegressionApplication is done!" << std::endl << std::endl;

   }

}
int main( int argc, char** argv )
{

   // Select methods (don't look at this code - not of interest)
   TString methodList; 
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(","); 
      methodList += regMethod;
   }
   application(methodList);
   return 0;
}


