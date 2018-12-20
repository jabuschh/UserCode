#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"

#include "Analysis_Template_MC.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"



using namespace std;

//---------------------------- Constructor Of The Class TriggerTurnOn -------------------------- //
Analysis_Template_MC::Analysis_Template_MC(edm::ParameterSet const& cfg)
{
     mFileName       = cfg.getParameter<std::string>               ("filename");
     mTreeName       = cfg.getParameter<std::string>               ("treename");
     mDirName        = cfg.getParameter<std::string>               ("dirname");

     mIsMCarlo       = cfg.getUntrackedParameter<bool>             ("isMCarlo");

     mCrossSection   = cfg.getUntrackedParameter<double>             ("CrossSection");
     mIntLumi        = cfg.getUntrackedParameter<double>             ("IntLumi");

     mTriggers       = cfg.getUntrackedParameter<std::vector<std::string>>     ("Triggers");
}

//------------------------------ Declaration Of The Function beginjob() ------------------------//
void Analysis_Template_MC::beginJob()
 {
     mInf = TFile::Open(mFileName.c_str());
     mDir = (TDirectoryFile*) mInf->Get(mDirName.c_str());
     mTree = (TTree*) mDir->Get(mTreeName.c_str());

     //------------------ Histogram Booking --------------------------- //

     //Jets
     num_of_GenJets = fs->make<TH1F>("num_of_GenJets","num_of_GenJets",10,0.,10.);
     ptGENJet       = fs->make<TH1F>("ptGENJet","ptGENJet",200,0.,2000.);                     ptGENJet->Sumw2();
     yGENJet        = fs->make<TH1F>("yGENJet","yGENJet",60,-3.,3.);                           yGENJet->Sumw2();
     phiGENJet      = fs->make<TH1F>("phiGENJet","phiGENJet",60, -TMath::Pi(),TMath::Pi());  phiGENJet->Sumw2();

     //LQ
     num_of_S3LQ = fs->make<TH1F>("num_of_S3LQ","num_of_S3LQ",30,0.,30);
     ptS3LQ      = fs->make<TH1F>("ptS3LQ","ptS3LQ",200,0.,2000.);                    ptS3LQ->Sumw2();
     phiS3LQ     = fs->make<TH1F>("phiS3LQ","phiS3LQ",60,-TMath::Pi(),TMath::Pi());  phiS3LQ->Sumw2();
     etaS3LQ     = fs->make<TH1F>("etaS3LQ","etaS3LQ",60,-3.,3);                     etaS3LQ->Sumw2();
     massS3LQ    = fs->make<TH1F>("massS3LQ","massS3LQ",200,0.,2000.);              massS3LQ->Sumw2();
     energyS3LQ  = fs->make<TH1F>("energyS3LQ","energyS3LQ",300,0.,3000.);        energyS3LQ->Sumw2();

     //muons from LQ decays
     num_of_Mu = fs->make<TH1F>("num_of_Mu","num_of_Mu",30,0.,30);
     ptMu      = fs->make<TH1F>("ptMu","ptMu",200,0.,2000.);                   ptMu->Sumw2();
     phiMu     = fs->make<TH1F>("phiMu","phiMu",60,-TMath::Pi(),TMath::Pi()); phiMu->Sumw2();
     etaMu     = fs->make<TH1F>("etaMu","etaMu",60,-3.,3);                    etaMu->Sumw2();
     massMu    = fs->make<TH1F>("massMu","massMu",200,0.,2000.);             massMu->Sumw2();
     energyMu  = fs->make<TH1F>("energyMu","energyMu",200,0.,3000.);       energyMu->Sumw2();


     //deltaR measurements
     deltaRMuJet = fs->make<TH1F>("deltaRMuJet","deltaRMuJet",50,0.,5.);

 } // end of function beginJob()


 //------------------------ endjob() function declaration ---------------------- //
 void Analysis_Template_MC::endJob()
 {
   mInf->Close();
 } // closing endJob()

 //--------------------------- analyze() fuction declaration ------------------ //
void Analysis_Template_MC::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup)
 {
   unsigned NEntries = mTree->GetEntries();
   cout << "Reading TREE: " << NEntries << " events" <<endl;

   int decade = 0 ;

   float hweight = 1.;  //Initial value set to one

   //JETS
   int nGenJets_ = 0;
   double STjet_ = 0.0;
   std::vector<float>* GenJetPt_ = 0;
   std::vector<float>* GenJetEta_ = 0;
   std::vector<float>* GenJetPhi_ = 0;
   mTree->SetBranchAddress("nGenJets",&nGenJets_);
   mTree->SetBranchAddress("STjet",&STjet_);
   mTree->SetBranchAddress("GenJetpt",&GenJetPt_);
   mTree->SetBranchAddress("GenJeteta",&GenJetEta_);
   mTree->SetBranchAddress("GenJetphi",&GenJetPhi_);

   //LQ
   int nS3LQs_ = 0;   //default value
   std::vector<float>* S3LQPt_ = 0;
   std::vector<float>* S3LQPhi_ = 0;
   std::vector<float>* S3LQEta_ = 0;
   std::vector<float>* S3LQE_ = 0;
   std::vector<float>* S3LQM_ = 0;
   mTree->SetBranchAddress("nS3LQs",&nS3LQs_);
   mTree->SetBranchAddress("S3LQPt",&S3LQPt_);
   mTree->SetBranchAddress("S3LQPhi",&S3LQPhi_);
   mTree->SetBranchAddress("S3LQEta",&S3LQEta_);
   mTree->SetBranchAddress("S3LQE",&S3LQE_);
   mTree->SetBranchAddress("S3LQM",&S3LQM_);

   //MUONS
   int nMus_    = 0;   //default value
   double STmu_ = 0.0;
   std::vector<float>* MuPt_ = 0;
   std::vector<float>* MuPhi_ = 0;
   std::vector<float>* MuEta_ = 0;
   std::vector<float>* MuE_ = 0;
   std::vector<float>* MuM_ = 0;
   mTree->SetBranchAddress("nMus",&nMus_);
   mTree->SetBranchAddress("STmu",&STmu_);
   mTree->SetBranchAddress("MuPt",&MuPt_);
   mTree->SetBranchAddress("MuPhi",&MuPhi_);
   mTree->SetBranchAddress("MuEta",&MuEta_);
   mTree->SetBranchAddress("MuE",&MuE_);
   mTree->SetBranchAddress("MuM",&MuM_);

   //ELECTRONS
   double STel_ = 0.0;
   mTree->SetBranchAddress("STel",&STel_);

   //MET
   double MET_  = 0.0;
   mTree->SetBranchAddress("MET",&MET_);

   //b QUARKS
   int nBs_ = 0;
   mTree->SetBranchAddress("nBs",&nBs_);

   for(unsigned  l=0; l<NEntries; l++)
   {
     //----------- progress report -------------
     double progress = 10.0*l/(1.0*NEntries);
     int k = TMath::FloorNint(progress);
     if(k > decade)
     {
       cout << 10*k << " %" << endl;
     }
     decade = k;

     //READ THE EVENT
     mTree->GetEntry(l);
     if(mIsMCarlo)
     {
       hweight=mCrossSection/NEntries;
     }

     //TOTAL NUMBERS
     num_of_GenJets->Fill(nGenJets_,hweight);
     num_of_S3LQ   ->Fill(nS3LQs_,hweight);
     num_of_Mu     ->Fill(nMus_,hweight);

     //SETUP FOR EVENT SELECTION
     double dRveto = 0.4;
     double dRMuJet = 0.0;
     int counterJet = 0;
     for(int i=0; i<nGenJets_; i++)
     {
       if(GenJetPt_->at(i) > 30 && abs(GenJetEta_->at(i)) < 2.4)  //pT, eta selection for jets
       {
         counterJet++;
       }
     }
     dRMuJet = DeltaR(GenJetEta_->front(), GenJetPhi_->front(), MuEta_->front(), MuPhi_->front());

     double invM_mumu = 0.0;
     int counterMu = 0;
     bool passInvM_mumu = false;
     for(int j=0; j<nMus_; j++)
     {
       if(MuPt_->at(j) > 30 && abs(MuEta_->at(j)) < 2.4)          //pT, eta selection for muons
       {
         counterMu++;
       }
       for(int k=0; k<nMus_; k++)
       {
         if(k > j)
         {
           invM_mumu = TMath::Sqrt(MuE_->at(j)*MuE_->at(j) + MuE_->at(k)*MuE_->at(k));
           if(invM_mumu > 91)                                     //invariant mass selection
           {
             passInvM_mumu = true;
           }
         }
       }
     }

     //FULL SELECTION: >= 2 jets with >= 1 b-jet & >= 2 isolated muons & invariant mass & STlep > 200 GeV & ST > 350 GeV
     // && nBs_ >= 1
     if(counterJet >= 2 && dRMuJet > dRveto && counterMu >= 2 && passInvM_mumu == true && STmu_+STel_ > 200 && STmu_+STel_+STjet_+MET_ > 350)
     {
       //FILL MU HISTOGRAMS
       for(int j=0; j<nMus_; j++)
       {
         ptMu       ->Fill(MuPt_->at(j),hweight);
         phiMu      ->Fill(MuPhi_->at(j),hweight);
         etaMu      ->Fill(MuEta_->at(j),hweight);
         massMu     ->Fill(MuM_->at(j),hweight);
         energyMu   ->Fill(MuE_->at(j),hweight);
       }
       //FILL JET HISTOGRAMS
       for(int i=0; i<nGenJets_; i++)
       {
         ptGENJet->   Fill(GenJetPt_->at(i),hweight);
         yGENJet->    Fill(GenJetEta_->at(i),hweight);
         phiGENJet->  Fill(GenJetPhi_->at(i),hweight);
         deltaRMuJet->Fill(dRMuJet,hweight);
       }
       //FILL LQ HISTOGRAMS
       ptS3LQ->     Fill(S3LQPt_->at(0),hweight);
       phiS3LQ->    Fill(S3LQPhi_->at(0),hweight);
       etaS3LQ->    Fill(S3LQEta_->at(0),hweight);
       massS3LQ->   Fill(S3LQM_->at(0),hweight);
       energyS3LQ-> Fill(S3LQE_->at(0),hweight);
     }
   }  // end of event loop
 }    // closing analyze() function

Analysis_Template_MC::~Analysis_Template_MC()
{
}

DEFINE_FWK_MODULE(Analysis_Template_MC);
