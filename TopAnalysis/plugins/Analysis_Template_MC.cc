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
#include "TLorentzVector.h"

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

  //Muons
  num_of_Mu = fs->make<TH1F>("num_of_Mu","num_of_Mu",30,0.,30);
  ptMu      = fs->make<TH1F>("ptMu","ptMu",200,0.,2000.);                   ptMu->Sumw2();
  phiMu     = fs->make<TH1F>("phiMu","phiMu",60,-TMath::Pi(),TMath::Pi()); phiMu->Sumw2();
  etaMu     = fs->make<TH1F>("etaMu","etaMu",60,-3.,3);                    etaMu->Sumw2();
  massMu    = fs->make<TH1F>("massMu","massMu",200,0.,2000.);             massMu->Sumw2();
  energyMu  = fs->make<TH1F>("energyMu","energyMu",200,0.,3000.);       energyMu->Sumw2();

  //deltaR measurements
  deltaRMuJet = fs->make<TH1F>("deltaRMuJet","deltaRMuJet",50,0.,5.);


  const int nBinsMLQ = 6;
  double binEdgesMLQ[7] = {0,250,350,450,600,750,1000};
  CatA_MLQreco_Arne = fs->make<TH1F>("CatA_MLQreco_Arne","CatA_MLQreco_Arne",nBinsMLQ,binEdgesMLQ); CatA_MLQreco_Arne->Sumw2();
  //CatB_MLQreco = fs->make<TH1F>("CatB_MLQreco","CatB_MLQreco",nBinsMLQ,binEdgesMLQ); CatB_MLQreco->Sumw2();
  const int nBinsST = 15;
  double binEdgesST[16] = {0,175,350,525,700,875,1050,1225,1400,1575,1750,1925,2100,2450,2800,3000};
  CatA_ST_Arne      = fs->make<TH1F>("CatA_ST_Arne","CatA_ST_Arne",nBinsST,binEdgesST);             CatA_ST_Arne->Sumw2();
  //CatB_ST      = fs->make<TH1F>("CatB_ST","CatB_ST",nBinsST,binEdgesST);             CatB_ST->Sumw2();


  CatA_MLQreco = fs->make<TH1F>("CatA_MLQreco","CatA_MLQreco",200,0.,2000.); CatA_MLQreco->Sumw2();
  //CatB_MLQreco = fs->make<TH1F>("CatB_MLQreco","CatB_MLQreco",200,0.,2000.); CatB_MLQreco->Sumw2();
  CatA_ST      = fs->make<TH1F>("CatA_ST","CatA_ST",200,1000.,5000.);             CatA_ST->Sumw2();
  //CatB_ST      = fs->make<TH1F>("CatB_ST","CatB_ST",200,1000.,5000.);             CatB_ST->Sumw2();


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
  std::vector<float>* GenJetPt_ = 0;
  std::vector<float>* GenJetEta_ = 0;
  std::vector<float>* GenJetPhi_ = 0;
  std::vector<float>* GenJetE_ = 0;
  mTree->SetBranchAddress("nGenJets",&nGenJets_);
  mTree->SetBranchAddress("GenJetpt",&GenJetPt_);
  mTree->SetBranchAddress("GenJeteta",&GenJetEta_);
  mTree->SetBranchAddress("GenJetphi",&GenJetPhi_);
  mTree->SetBranchAddress("GenJetenergy",&GenJetE_);

  //LQ
  int nS3LQs_ = 0;   //default value
  std::vector<int>* S3LQId_ = 0;
  std::vector<int>* S3LQSt_ = 0;
  std::vector<float>* S3LQPt_ = 0;
  std::vector<float>* S3LQPhi_ = 0;
  std::vector<float>* S3LQEta_ = 0;
  std::vector<float>* S3LQE_ = 0;
  std::vector<float>* S3LQM_ = 0;
  mTree->SetBranchAddress("nS3LQs",&nS3LQs_);
  mTree->SetBranchAddress("S3LQId",&S3LQId_);
  mTree->SetBranchAddress("S3LQSt",&S3LQSt_);
  mTree->SetBranchAddress("S3LQPt",&S3LQPt_);
  mTree->SetBranchAddress("S3LQPhi",&S3LQPhi_);
  mTree->SetBranchAddress("S3LQEta",&S3LQEta_);
  mTree->SetBranchAddress("S3LQE",&S3LQE_);
  mTree->SetBranchAddress("S3LQM",&S3LQM_);

  //MUONS
  int nMus_    = 0;   //default value
  std::vector<int>* MuId_ = 0;
  std::vector<int>* MuSt_ = 0;
  std::vector<float>* MuPt_ = 0;
  std::vector<float>* MuPhi_ = 0;
  std::vector<float>* MuEta_ = 0;
  std::vector<float>* MuE_ = 0;
  std::vector<float>* MuM_ = 0;
  mTree->SetBranchAddress("nMus",&nMus_);
  mTree->SetBranchAddress("MuId",&MuId_);
  mTree->SetBranchAddress("MuSt",&MuSt_);
  mTree->SetBranchAddress("MuPt",&MuPt_);
  mTree->SetBranchAddress("MuPhi",&MuPhi_);
  mTree->SetBranchAddress("MuEta",&MuEta_);
  mTree->SetBranchAddress("MuE",&MuE_);
  mTree->SetBranchAddress("MuM",&MuM_);

  //ELECTRONS
  int nEls_    = 0;
  std::vector<float>* ElPt_ = 0;
  std::vector<float>* ElPhi_ = 0;
  std::vector<float>* ElEta_ = 0;
  std::vector<float>* ElE_ = 0;
  std::vector<float>* ElM_ = 0;
  mTree->SetBranchAddress("nEls",&nEls_);
  mTree->SetBranchAddress("ElPt",&ElPt_);
  mTree->SetBranchAddress("ElPhi",&ElPhi_);
  mTree->SetBranchAddress("ElEta",&ElEta_);
  mTree->SetBranchAddress("ElE",&ElE_);
  mTree->SetBranchAddress("ElM",&ElM_);

  //MET
  int nNus_ = 0;
  std::vector<float>* NuPt_ = 0;
  mTree->SetBranchAddress("NuPt",&NuPt_);


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

    //SETUP FOR EVENT SELECTION
    //JETS
    double STjet = 0.0;
    int counterJet = 0;
    TLorentzVector recoMLQ_leadingJet;
    TLorentzVector recoMLQ_secondJet;


    for(int i=0; i<nGenJets_; i++)
    {
      if(GenJetPt_->at(i) > 30 && abs(GenJetEta_->at(i)) < 2.4)  //pT, eta selection for jets
      {
        counterJet++;
        STjet += GenJetPt_->at(i);
      }
    }

    //cout << " pt of jet: " << GenJetPt_->front() << endl;
    //cout << "eta of jet: " << GenJetEta_->front() << endl;
    //cout << "phi of jet: " << GenJetPhi_->front() << endl;
    //cout << "  E of jet: " << GenJetE_->front() << endl;
    double dRleadingMuleadingJet = DeltaR(GenJetEta_->front(), GenJetPhi_->front(), MuEta_->front(), MuPhi_->front()); //between leading jet and leading muon
    recoMLQ_leadingJet.SetPtEtaPhiE(GenJetPt_->front(),GenJetEta_->front(),GenJetPhi_->front(),GenJetE_->front());     //leading jet
    //cout << "nGenJets_: " << nGenJets_ << endl;

    if(nGenJets_ > 1)
    {
      recoMLQ_secondJet.SetPtEtaPhiE(GenJetPt_->at(1),GenJetEta_->at(1),GenJetPhi_->at(1),GenJetE_->at(1));            //second leading jet
    }



    //MUONS
    double dRMuVeto = 0.4;
    double dRMuJet = 0.0;
    double invM_mumu = 0.0;
    double STmu      = 0.0;
    int counterSelMu      = 0;
    int counterSelMuPlus  = 0;
    int counterSelMuMinus = 0;
    bool passInvM_mumu = true;
    TLorentzVector recoMLQmuminus;
    TLorentzVector recoMLQmuplus;

    for(int j=0; j<nMus_; j++)
    {
      dRMuJet = DeltaR(GenJetEta_->front(), GenJetPhi_->front(), MuEta_->at(j), MuPhi_->at(j));        //between leading jet and muon
      if(MuPt_->at(j) > 30. && abs(MuEta_->at(j)) < 2.4 && dRMuJet > dRMuVeto && MuSt_->at(j) == 23)   //pT, eta selection + isolation for hard scattering muons
      {
        counterSelMu++;
        STmu += MuPt_->at(j);
        if(MuId_->at(j) == 13)
        {
          counterSelMuMinus++;
          //cout << " pt of mu-: " << MuPt_->at(j) << endl;
          //cout << "eta of mu-: " << MuEta_->at(j) << endl;
          //cout << "phi of mu-: " << MuPhi_->at(j) << endl;
          //cout << "  E of mu-: " << MuE_->at(j) << endl;
          recoMLQmuminus.SetPtEtaPhiE(MuPt_->at(j),MuEta_->at(j),MuPhi_->at(j),MuE_->at(j));
        }
        else if(MuId_->at(j) == -13)
        {
          counterSelMuPlus++;
          //cout << " pt of mu+: " << MuPt_->at(j) << endl;
          //cout << "eta of mu+: " << MuEta_->at(j) << endl;
          //cout << "phi of mu+: " << MuPhi_->at(j) << endl;
          //cout << "  E of mu+: " << MuE_->at(j) << endl;
          recoMLQmuplus.SetPtEtaPhiE(MuPt_->at(j),MuEta_->at(j),MuPhi_->at(j),MuE_->at(j));
        }

        for(int k=0; k<nMus_; k++)
        {
          if(k > j)
          {
            TLorentzVector muonj(MuPt_->at(j),MuEta_->at(j),MuPhi_->at(j),MuE_->at(j));
            TLorentzVector muonk(MuPt_->at(k),MuEta_->at(k),MuPhi_->at(k),MuE_->at(k));
            invM_mumu = (muonj + muonk).M();
            if(invM_mumu <= 111.)                                     //invariant mass selection
            {
              passInvM_mumu = false;
            }
          }
        }
      }
    }
    //cout << "counterSelMu: " << counterSelMu << endl;

    /*
    //ELECTRONS
    double STel = 0.0;
    int counterSelEl = 0;
    for(int j=0; j<nEls_; j++)
    {
      if(ElPt_->at(j) > 30. && abs(ElEta_->at(j)) < 2.4)          //pT, eta selection for electrons
    {
    counterSelEl++;
    STel += ElPt_->at(j);
    }
    }
    */

//MET from neutrinos
double MET = 0.0;
for(int i=0; i<nNus_; i++)
{
  MET += NuPt_->at(i);
}

//ST: sum of all pt
double ST = STmu+STjet+MET;    //+STel

//LQ
double MLQreco_MinusLeading = 0.0;
double MLQreco_PlusLeading  = 0.0;
double MLQreco_MinusSecond  = 0.0;
double MLQreco_PlusSecond   = 0.0;
bool   isLQMinusPresent = false;
bool   isLQPlusPresent  = false;
cout << "nS3LQs_: " << nS3LQs_ << endl;
if(nS3LQs_ == 1)        //SINGLE PRODUCTION
{
  if(S3LQId_->front() == 9000005)
  {
    MLQreco_MinusLeading = (recoMLQ_leadingJet + recoMLQmuminus).M();
    isLQMinusPresent = true;
  }
  else if(S3LQId_->front() == -9000005)
  {
    MLQreco_PlusLeading  = (recoMLQ_leadingJet + recoMLQmuplus).M();
    isLQPlusPresent  = true;
  }
}
else if(nS3LQs_ == 2)   //PAIR PRODUCTION
{
  MLQreco_MinusLeading = (recoMLQ_leadingJet + recoMLQmuminus).M();
  MLQreco_PlusSecond   = (recoMLQ_secondJet  + recoMLQmuplus) .M();
  cout << "MLQreco_MinusLeading: " << MLQreco_MinusLeading << endl;
  cout << "  MLQreco_PlusSecond: " << MLQreco_PlusSecond << endl;
  cout << "or" << endl;
  MLQreco_PlusLeading  = (recoMLQ_leadingJet + recoMLQmuplus) .M();
  MLQreco_MinusSecond  = (recoMLQ_secondJet  + recoMLQmuminus).M();
  cout << " MLQreco_PlusLeading: " << MLQreco_PlusLeading << endl;
  cout << " MLQreco_MinusSecond: " << MLQreco_MinusSecond << endl;

  isLQMinusPresent = true;
  isLQPlusPresent  = true;
}
cout << endl;



//FULL SELECTION: no b-tag requested here!
double MLQreco = 0.0;
if(counterJet >= 2)    // >= 2 jets
{
  if(counterSelMu >= 2)     // >=2 selected muons
  {
    if(passInvM_mumu == true)      // all pairs of muons must have invariant mass > 111 GeV
    {
      if(STmu > 200.)     // STlep > 200 GeV , +STel
      {
        if(ST > 350.)     // ST > 350 GeV
        {
          //FILL MU HISTOGRAMS
          for(int j=0; j<nMus_; j++)
          {
            num_of_Mu    ->Fill(counterSelMu,hweight);
            dRMuJet = DeltaR(GenJetEta_->front(), GenJetPhi_->front(), MuEta_->at(j), MuPhi_->at(j));  //between leading jet and muon
            if(MuPt_->at(j) > 30. && abs(MuEta_->at(j)) < 2.4 && dRMuJet > dRMuVeto && MuSt_->at(j) == 23)
            {
              ptMu       ->Fill(MuPt_->at(j),hweight);
              phiMu      ->Fill(MuPhi_->at(j),hweight);
              etaMu      ->Fill(MuEta_->at(j),hweight);
              massMu     ->Fill(MuM_->at(j),hweight);
              energyMu   ->Fill(MuE_->at(j),hweight);
            }
          }

          //FILL JET HISTOGRAMS
          num_of_GenJets->Fill(nGenJets_,hweight);
          for(int i=0; i<nGenJets_; i++)
          {
            if(GenJetPt_->at(i) > 30 && abs(GenJetEta_->at(i)) < 2.4)
            {
              ptGENJet->   Fill(GenJetPt_->at(i),hweight);
              yGENJet->    Fill(GenJetEta_->at(i),hweight);
              phiGENJet->  Fill(GenJetPhi_->at(i),hweight);
            }
          }
          deltaRMuJet->Fill(dRleadingMuleadingJet,hweight);

          //FILL LQ HISTOGRAMS
          num_of_S3LQ->Fill(nS3LQs_,hweight);
          for(int i=0; i<nS3LQs_; i++)
          {
            ptS3LQ->     Fill(S3LQPt_->at(i),hweight);
            phiS3LQ->    Fill(S3LQPhi_->at(i),hweight);
            etaS3LQ->    Fill(S3LQEta_->at(i),hweight);
            massS3LQ->   Fill(S3LQM_->at(i),hweight);
            energyS3LQ-> Fill(S3LQE_->at(i),hweight);
          }


          //CATEGORY A
          if(counterSelMuMinus >= 1 && counterSelMuPlus >= 1)
          {
            if(isLQMinusPresent && isLQPlusPresent)         //pair production -> average masses
            {
              MLQreco = (MLQreco_MinusLeading + MLQreco_PlusLeading) / 2.;
              //cout << "MLQrecoPair: " << MLQreco << endl;
              //CatA_MLQreco->Fill(MLQreco,hweight);
              //CatA_MLQreco_Arne->Fill(MLQreco,hweight);
            }
            else if(isLQMinusPresent && !isLQPlusPresent)   //single LQ- production
            {
              MLQreco = MLQreco_MinusLeading;
              //cout << "MLQreco_MinusLeading: " << MLQreco << endl;
              CatA_MLQreco     ->Fill(MLQreco,hweight);
              CatA_MLQreco_Arne->Fill(MLQreco,hweight);
            }
            else if(!isLQMinusPresent && isLQPlusPresent)   //single LQ+ production
            {
              MLQreco = MLQreco_PlusLeading;
              //cout << " MLQreco_PlusLeading: " << MLQreco << endl;
              CatA_MLQreco     ->Fill(MLQreco,hweight);
              CatA_MLQreco_Arne->Fill(MLQreco,hweight);
            }
            CatA_ST     ->Fill(ST,hweight);
            CatA_ST_Arne->Fill(ST,hweight);
          }
        }
      }
    }
  }
}

//cout << endl;



}  // end of event loop
}    // closing analyze() function

Analysis_Template_MC::~Analysis_Template_MC()
{
}

DEFINE_FWK_MODULE(Analysis_Template_MC);
