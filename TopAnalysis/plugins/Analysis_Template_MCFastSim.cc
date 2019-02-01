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
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"

#include "Analysis_Template_MCFastSim.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"



using namespace std;

//---------------------------- Constructor Of The Class TriggerTurnOn -------------------------- //
Analysis_Template_MCFastSim::Analysis_Template_MCFastSim(edm::ParameterSet const& cfg)
{
  mFileName       = cfg.getParameter<std::string>("filename");
  mTreeName       = cfg.getParameter<std::string>("treename");
  mDirName        = cfg.getParameter<std::string>("dirname");

  mIsMCarlo       = cfg.getUntrackedParameter<bool>("isMCarlo");

  mElSelection    = cfg.getUntrackedParameter<bool>("ElSelection");
  mMuSelection    = cfg.getUntrackedParameter<bool>("MuSelection");
  mHadSelection   = cfg.getUntrackedParameter<bool>("HadSelection");

  mCrossSection   = cfg.getUntrackedParameter<double>("CrossSection");
  mIntLumi        = cfg.getUntrackedParameter<double>("IntLumi");

  mTriggers       = cfg.getUntrackedParameter<std::vector<std::string>>("Triggers");
}

//------------------------------ Declaration Of The Function beginjob() ------------------------//
void Analysis_Template_MCFastSim::beginJob()
{
  mInf = TFile::Open(mFileName.c_str());
  mDir = (TDirectoryFile*) mInf->Get(mDirName.c_str());
  mTree = (TTree*) mInf->Get(mTreeName.c_str());

  //------------------ Histogram Booking --------------------------- //
  //DET Jets
  nJets                              = fs->make<TH1F>("nJets","nJets",20,0.,20.);
  jetPt                              = fs->make<TH1F>("jetPt","jetPt",200,0.,2000.);                   jetPt->Sumw2();
  jetPt_hadronFlavorBtag_passed      = fs->make<TH1F>("jetPt_hadronFlavorBtag_passed","jetPt_hadronFlavorBtag_passed"        ,25,0.,1700.); jetPt_hadronFlavorBtag_passed    ->Sumw2();
  jetPt_hadronFlavorBtagAlgo_passed  = fs->make<TH1F>("jetPt_hadronFlavorBtagAlgo_passed","jetPt_hadronFlavorBtagAlgo_passed",25,0.,1700.); jetPt_hadronFlavorBtagAlgo_passed->Sumw2();
  jetPt_hadronFlavor_total           = fs->make<TH1F>("jetPt_hadronFlavor_total","jetPt_hadronFlavor_total"                  ,25,0.,1700.); jetPt_hadronFlavor_total         ->Sumw2();
  jetPt_Btag_total                   = fs->make<TH1F>("jetPt_Btag_total","jetPt_Btag_total"                                  ,25,0.,1700.); jetPt_Btag_total                 ->Sumw2();
  jetPt_BtagAlgo_total               = fs->make<TH1F>("jetPt_BtagAlgo_total","jetPt_BtagAlgo_total"                          ,25,0.,1700.); jetPt_BtagAlgo_total             ->Sumw2();
  jetEta                             = fs->make<TH1F>("jetEta","jetEta",60,-3.,3.);                    jetEta->Sumw2();
  jetEta_hadronFlavorBtag_passed     = fs->make<TH1F>("jetEta_hadronFlavorBtag_passed","jetEta_hadronFlavorBtag_passed"        ,30,-3.,3.);
  jetEta_hadronFlavorBtagAlgo_passed = fs->make<TH1F>("jetEta_hadronFlavorBtagAlgo_passed","jetEta_hadronFlavorBtagAlgo_passed",30,-3.,3.);
  jetEta_hadronFlavor_total          = fs->make<TH1F>("jetEta_hadronFlavor_total","jetEta_hadronFlavor_total"                  ,30,-3.,3.);
  jetEta_Btag_total                  = fs->make<TH1F>("jetEta_Btag_total","jetEta_Btag_total"                                  ,30,-3.,3.);
  jetEta_BtagAlgo_total              = fs->make<TH1F>("jetEta_BtagAlgo_total","jetEta_BtagAlgo_total"                          ,30,-3.,3.);
  jetPhi                             = fs->make<TH1F>("jetPhi","jetPhi",60, -TMath::Pi(),TMath::Pi()); jetPhi->Sumw2();
  jetBtag                            = fs->make<TH1F>("jetBtag"    ,"jetBtag"    ,10,0.,10.);
  jetBtagAlgo                        = fs->make<TH1F>("jetBtagAlgo","jetBtagAlgo",10,0.,10.);
  //GEN JETS
  nGenJets             = fs->make<TH1F>("nGenJets","nGenJets",15,0.,15.);
  GenJetPt             = fs->make<TH1F>("GenJetPt","GenJetPt",200,0.,2000.);                   GenJetPt->Sumw2();
  GenJetPt_passed      = fs->make<TH1F>("GenJetPt_passed","GenJetPt_passed",50,0.,1700.);      GenJetPt_passed->Sumw2();
  GenJetPt_total       = fs->make<TH1F>("GenJetPt_total" ,"GenJetPt_total" ,50,0.,1700.);      GenJetPt_total->Sumw2();
  GenJetEta            = fs->make<TH1F>("GenJetEta"       ,"GenJetEta"       ,60,-3.,3.);      GenJetEta->Sumw2();
  GenJetEta_passed     = fs->make<TH1F>("GenJetEta_passed","GenJetEta_passed",30,-3.,3.);      GenJetEta_passed->Sumw2();
  GenJetEta_total      = fs->make<TH1F>("GenJetEta_total" ,"GenJetEta_total" ,30,-3.,3.);      GenJetEta_total->Sumw2();
  GenJetPhi            = fs->make<TH1F>("GenJetPhi","GenJetPhi",60, -TMath::Pi(),TMath::Pi()); GenJetPhi->Sumw2();
  dEta_genJetdetJet    = fs->make<TH1F>("dEta_genJetdetJet","dEta_genJetdetJet",50,-0.2,0.2);  dEta_genJetdetJet->Sumw2();
  PtResolution_jet     = fs->make<TH1F>("PtResolution_jet","PtResolution_jet",50,-2.,2.);      PtResolution_jet->Sumw2();

  //DET TOPS
  nTopParticles   = fs->make<TH1F>("nTopParticles","nTopParticles",10,0.,10.);
  TopParticlePt   = fs->make<TH1F>("TopParticlePt","TopParticlePt",200,0.,2000.);                  TopParticlePt->Sumw2();
  TopParticleEta  = fs->make<TH1F>("TopParticleEta","TopParticleEta",60,-3.,3);                    TopParticleEta->Sumw2();
  TopParticlePhi  = fs->make<TH1F>("TopParticlePhi","TopParticlePhi",60,-TMath::Pi(),TMath::Pi()); TopParticlePhi->Sumw2();
  TopParticleMass = fs->make<TH1F>("TopParticleMass","TopParticleMass",200,0.,2000.);              TopParticleMass->Sumw2();

  //GEN LQ
  nLeptoQuarkParticles   = fs->make<TH1F>("nLeptoQuarkParticles","nLeptoQuarkParticles",30,0.,30);
  LeptoQuarkParticlePt   = fs->make<TH1F>("LeptoQuarkParticlePt","LeptoQuarkParticlePt",200,0.,2000.);                  LeptoQuarkParticlePt->Sumw2();
  LeptoQuarkParticlePhi  = fs->make<TH1F>("LeptoQuarkParticlePhi","LeptoQuarkParticlePhi",60,-TMath::Pi(),TMath::Pi()); LeptoQuarkParticlePhi->Sumw2();
  LeptoQuarkParticleEta  = fs->make<TH1F>("LeptoQuarkParticleEta","LeptoQuarkParticleEta",60,-3.,3);                    LeptoQuarkParticleEta->Sumw2();
  LeptoQuarkParticleMass = fs->make<TH1F>("LeptoQuarkParticleMass","LeptoQuarkParticleMass",200,0.,2000.);              LeptoQuarkParticleMass->Sumw2();

  //DET Muons
  nMuons  = fs->make<TH1F>("nMuons","nMuons",30,0.,30);
  muonPt  = fs->make<TH1F>("muonPt","muonPt",200,0.,2000.);                  muonPt->Sumw2();
  muonPhi = fs->make<TH1F>("muonPhi","muonPhi",60,-TMath::Pi(),TMath::Pi()); muonPhi->Sumw2();
  muonEta = fs->make<TH1F>("muonEta","muonEta",60,-3.,3);                    muonEta->Sumw2();
  //GEN MUONS
  nMuonParticles         = fs->make<TH1F>("nMuonParticles","nMuonParticles",30,0.,30);
  MuonParticlePt         = fs->make<TH1F>("MuonParticlePt","MuonParticlePt",200,0.,2000.);                  MuonParticlePt->Sumw2();
  MuonParticlePt_passed  = fs->make<TH1F>("MuonParticlePt_passed","MuonParticlePt_passed",25,0.,1700.);     MuonParticlePt_passed->Sumw2();
  MuonParticlePt_total   = fs->make<TH1F>("MuonParticlePt_total","MuonParticlePt_total"  ,25,0.,1700.);     MuonParticlePt_total->Sumw2();
  MuonParticlePhi        = fs->make<TH1F>("MuonParticlePhi","MuonParticlePhi",60,-TMath::Pi(),TMath::Pi()); MuonParticlePhi->Sumw2();
  MuonParticleEta        = fs->make<TH1F>("MuonParticleEta","MuonParticleEta",60,-3.,3);                    MuonParticleEta->Sumw2();
  MuonParticleEta_passed = fs->make<TH1F>("MuonParticleEta_passed","MuonParticleEta_passed",30,-3.,3);      MuonParticleEta_passed->Sumw2();
  MuonParticleEta_total  = fs->make<TH1F>("MuonParticleEta_total","MuonParticleEta_total"  ,30,-3.,3);      MuonParticleEta_total->Sumw2();
  dEta_genMudetMu        = fs->make<TH1F>("dEta_genMudetMu","dEta_genMudetMu",50,-0.2,0.2);                 dEta_genMudetMu->Sumw2();
  PtResolution_muon      = fs->make<TH1F>("PtResolution_muon","PtResolution_muon",50,-2.,2.);               PtResolution_muon->Sumw2();

  MLQreco_detMu = fs->make<TH1F>("MLQreco_detMu","MLQreco_detMu",200,0.,2000.); MLQreco_detMu->Sumw2();
  MLQreco_genMu = fs->make<TH1F>("MLQreco_genMu","MLQreco_genMu",200,0.,2000.); MLQreco_genMu->Sumw2();
  ST            = fs->make<TH1F>("ST","ST",200,1000.,5000.);                    ST->Sumw2();

  //DET ELECTRONS
  nElecs  = fs->make<TH1F>("nElecs","nElecs",10,0.,10);
  elecPt  = fs->make<TH1F>("elecPt","elecPt",200,0.,2000.);                  elecPt->Sumw2();
  elecPhi = fs->make<TH1F>("elecPhi","elecPhi",60,-TMath::Pi(),TMath::Pi()); elecPhi->Sumw2();
  elecEta = fs->make<TH1F>("elecEta","elecEta",60,-3.,3);                    elecEta->Sumw2();
  //GEN ELECTRONS
  nElecParticles         = fs->make<TH1F>("nElecParticles","nElecParticles",10,0.,10);
  ElecParticlePt         = fs->make<TH1F>("ElecParticlePt","ElecParticlePt",200,0.,2000.);                  ElecParticlePt->Sumw2();
  ElecParticlePt_passed  = fs->make<TH1F>("ElecParticlePt_passed","ElecParticlePt_passed",25,0.,700.);      ElecParticlePt_passed->Sumw2();
  ElecParticlePt_total   = fs->make<TH1F>("ElecParticlePt_total","ElecParticlePt_total"  ,25,0.,700.);      ElecParticlePt_total->Sumw2();
  ElecParticlePhi        = fs->make<TH1F>("ElecParticlePhi","ElecParticlePhi",60,-TMath::Pi(),TMath::Pi()); ElecParticlePhi->Sumw2();
  ElecParticleEta        = fs->make<TH1F>("ElecParticleEta","ElecParticleEta",60,-3.,3);                    ElecParticleEta->Sumw2();
  ElecParticleEta_passed = fs->make<TH1F>("ElecParticleEta_passed","ElecParticleEta_passed",20,-3.,3);      ElecParticleEta_passed->Sumw2();
  ElecParticleEta_total  = fs->make<TH1F>("ElecParticleEta_total","ElecParticleEta_total"  ,20,-3.,3);      ElecParticleEta_total->Sumw2();
  dEta_genEldetEl        = fs->make<TH1F>("dEta_genEldetEl","dEta_genEldetEl",50,-0.2,0.2);                 dEta_genEldetEl->Sumw2();
  PtResolution_elec      = fs->make<TH1F>("PtResolution_elec","PtResolution_elec",50,-2.,2.);               PtResolution_elec->Sumw2();

  //ADDED
  WbosonMass = fs->make<TH1F>("WbosonMass","WbosonMass",200,0.,200.); WbosonMass->Sumw2();
  MLQfullreco_detMu = fs->make<TH1F>("MLQfullreco_detMu","MLQfullreco_detMu",200,0.,4000.); MLQfullreco_detMu->Sumw2();

  LeptTopfullreco = fs->make<TH1F>("LeptTopfullreco","LeptTopfullreco",100,0.,1000.); LeptTopfullreco->Sumw2();
  HadrTopfullreco = fs->make<TH1F>("HadrTopfullreco","HadrTopfullreco",100,0.,1000.); HadrTopfullreco->Sumw2();
  chi2            = fs->make<TH1F>("chi2","chi2",150,0.,1500.); chi2->Sumw2();
  LQHadrMassreco  = fs->make<TH1F>("LQHadrMassreco","LQHadrMassreco",100,0.,4000.); LQHadrMassreco->Sumw2();
  LQLeptMassreco  = fs->make<TH1F>("LQLeptMassreco","LQLeptMassreco",100,0.,4000.); LQLeptMassreco->Sumw2();

  //RESOLUTION
  JetRes      = fs->make<TH1F>("JetRes","JetRes",50,-1.,1.); JetRes->Sumw2();
  JetRes2D    = fs->make<TH2F>("JetRes2D","JetRes2D",200,0.,2000.,200,0.,2000.); JetRes2D->Sumw2();
  JetResponse = fs->make<TH1F>("JetResponse","JetResponse",50,0.,2.); JetResponse->Sumw2();
}


//------------------------ endjob() function declaration ---------------------- //
void Analysis_Template_MCFastSim::endJob()
{
  mInf->Close();
}

//--------------------------- analyze() fuction declaration ------------------ //
void Analysis_Template_MCFastSim::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup)
{
  unsigned NEntries = mTree->GetEntries();
  cout << "Reading TREE: " << NEntries << " events" <<endl;

  int decade = 0 ;

  float hweight = 1.;  //Initial value set to one

  //GEN JETS
  std::vector<float>* GenJetPt_ = 0;
  std::vector<float>* GenJetEta_ = 0;
  std::vector<float>* GenJetPhi_ = 0;
  std::vector<float>* GenJetMass_ = 0;
  mTree->SetBranchAddress("GenJetPt",&GenJetPt_);
  mTree->SetBranchAddress("GenJetEta",&GenJetEta_);
  mTree->SetBranchAddress("GenJetPhi",&GenJetPhi_);
  mTree->SetBranchAddress("GenJetMass",&GenJetMass_);
  //DET JETS
  std::vector<float>* jetPt_           = 0;
  std::vector<float>* jetEta_          = 0;
  std::vector<float>* jetPhi_          = 0;
  std::vector<float>* jetMass_         = 0;
  std::vector<int>*   jetBtag_         = 0;
  std::vector<int>*   jetBtagAlgo_     = 0;
  std::vector<int>*   jetFlavorHadron_ = 0;
  mTree->SetBranchAddress("jetPt",  &jetPt_);
  mTree->SetBranchAddress("jetEta", &jetEta_);
  mTree->SetBranchAddress("jetPhi", &jetPhi_);
  mTree->SetBranchAddress("jetMass",&jetMass_);
  mTree->SetBranchAddress("jetBtag",&jetBtag_);
  mTree->SetBranchAddress("jetBtagAlgo",&jetBtagAlgo_);
  mTree->SetBranchAddress("jetFlavorHadron",&jetFlavorHadron_);

  //DET TOPS
  std::vector<float>* TopParticlePt_   = 0;
  std::vector<float>* TopParticleEta_  = 0;
  std::vector<float>* TopParticlePhi_  = 0;
  std::vector<float>* TopParticleId_   = 0;
  std::vector<float>* TopParticleMass_ = 0;
  mTree->SetBranchAddress("TopParticlePt",  &TopParticlePt_);
  mTree->SetBranchAddress("TopParticleEta", &TopParticleEta_);
  mTree->SetBranchAddress("TopParticlePhi", &TopParticlePhi_);
  mTree->SetBranchAddress("TopParticleId",  &TopParticleId_);
  mTree->SetBranchAddress("TopParticleMass",&TopParticleMass_);

  //GEN LQ
  std::vector<int>*   LeptoQuarkParticleId_   = 0;
  std::vector<float>* LeptoQuarkParticlePt_   = 0;
  std::vector<float>* LeptoQuarkParticlePhi_  = 0;
  std::vector<float>* LeptoQuarkParticleEta_  = 0;
  std::vector<float>* LeptoQuarkParticleMass_ = 0;
  mTree->SetBranchAddress("LeptoQuarkParticleId",  &LeptoQuarkParticleId_);
  mTree->SetBranchAddress("LeptoQuarkParticlePt",  &LeptoQuarkParticlePt_);
  mTree->SetBranchAddress("LeptoQuarkParticlePhi", &LeptoQuarkParticlePhi_);
  mTree->SetBranchAddress("LeptoQuarkParticleEta", &LeptoQuarkParticleEta_);
  mTree->SetBranchAddress("LeptoQuarkParticleMass",&LeptoQuarkParticleMass_);

  //GEN MUONS
  std::vector<int>*   MuonParticleId_     = 0;
  std::vector<int>*   MuonParticleStatus_ = 0;
  std::vector<float>* MuonParticlePt_     = 0;
  std::vector<float>* MuonParticlePhi_    = 0;
  std::vector<float>* MuonParticleEta_    = 0;
  std::vector<float>* MuonParticleMass_   = 0;
  mTree->SetBranchAddress("MuonParticleId",    &MuonParticleId_);
  mTree->SetBranchAddress("MuonParticleStatus",&MuonParticleStatus_);
  mTree->SetBranchAddress("MuonParticlePt",    &MuonParticlePt_);
  mTree->SetBranchAddress("MuonParticlePhi",   &MuonParticlePhi_);
  mTree->SetBranchAddress("MuonParticleEta",   &MuonParticleEta_);
  mTree->SetBranchAddress("MuonParticleMass",  &MuonParticleMass_);
  //DET MUONS
  std::vector<float>* muonPt_     = 0;
  std::vector<float>* muonEta_    = 0;
  std::vector<float>* muonPhi_    = 0;
  std::vector<int>*   muonCharge_ = 0;
  mTree->SetBranchAddress("muonPt",    &muonPt_);
  mTree->SetBranchAddress("muonEta",   &muonEta_);
  mTree->SetBranchAddress("muonPhi",   &muonPhi_);
  mTree->SetBranchAddress("muonCharge",&muonCharge_);
  const double muonMass = 0.1056583715; //in GeV

  //GEN ELECTRONS: are not implemented as branches -> select via abs(GenParticleId) == 11
  std::vector<int>*   GenParticleId_   = 0;
  std::vector<float>* GenParticlePt_   = 0;
  std::vector<float>* GenParticlePhi_  = 0;
  std::vector<float>* GenParticleEta_  = 0;
  std::vector<float>* GenParticleMass_ = 0;
  mTree->SetBranchAddress("GenParticleId",    &GenParticleId_);
  mTree->SetBranchAddress("GenParticlePt",    &GenParticlePt_);
  mTree->SetBranchAddress("GenParticlePhi",   &GenParticlePhi_);
  mTree->SetBranchAddress("GenParticleEta",   &GenParticleEta_);
  mTree->SetBranchAddress("GenParticleMass",  &GenParticleMass_);
  //DET ELECTRONS
  std::vector<float>* elecPt_  = 0;
  std::vector<float>* elecEta_ = 0;
  std::vector<float>* elecPhi_ = 0;
  std::vector<int>* elecCharge_ = 0;
  mTree->SetBranchAddress("elecPt", &elecPt_);
  mTree->SetBranchAddress("elecEta",&elecEta_);
  mTree->SetBranchAddress("elecPhi",&elecPhi_);
  mTree->SetBranchAddress("elecCharge",&elecCharge_);
  const double elecMass = 0.000510998928;

  //MET
  float MET;
  float METeta;
  float METphi;
  mTree->SetBranchAddress("MET",&MET);
  mTree->SetBranchAddress("METphi",&METphi);
  mTree->SetBranchAddress("METeta",&METeta);

  //DET SCALAR HT
  float ScalarHT    = 0;
  mTree->SetBranchAddress("ScalarHT",   &ScalarHT);

  //W-MASS
  const double massW = 80.385;

  //counter for events
  int numberOfEvents = 0;

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


    //NUMBER OF PARTICLES
    const int nMuons_               = muonPt_              ->size();
    const int nMuonParticles_       = MuonParticlePt_      ->size();
    const int nElecs_               = elecPt_              ->size();
    const int nGenParticles_        = GenParticlePt_       ->size();
    const int nJets_                = jetPt_               ->size();
    const int nGenJets_             = GenJetPt_            ->size();
    const int nTopParticles_        = TopParticlePt_       ->size();
    const int nLeptoQuarkParticles_ = LeptoQuarkParticlePt_->size();

    //SETUP FOR EVENT SELECTION
    //DET JETS
    int counterJet = 0;
    for(int i=0; i<nJets_; i++)
    {
      if(jetPt_->at(i) > 30)
      {
        if(abs(jetEta_->at(i)) < 2.4)  //pT, eta selection for jets
        {
          counterJet++;
        }

        jetEta_Btag_total    ->Fill(jetEta_->at(i));
        jetEta_BtagAlgo_total->Fill(jetEta_->at(i));
        if(abs(jetFlavorHadron_->at(i)) == 5)
        {
          jetEta_hadronFlavor_total->Fill(jetEta_->at(i));
          if(jetBtag_->at(i) >= 1)
          {
            jetEta_hadronFlavorBtag_passed->Fill(jetEta_->at(i));
          }
          if(jetBtagAlgo_->at(i) >= 1)
          {
            jetEta_hadronFlavorBtagAlgo_passed->Fill(jetEta_->at(i));
          }
        }
      }

      if(jetBtag_->at(i) >= 1)
      {
        jetPt_Btag_total->Fill(jetPt_->at(i));
      }
      if(jetBtagAlgo_->at(i) >= 1)
      {
        jetPt_BtagAlgo_total->Fill(jetPt_->at(i));
      }
      if(abs(jetFlavorHadron_->at(i)) == 5)
      {
        jetPt_hadronFlavor_total->Fill(jetPt_->at(i));
        if(jetBtag_->at(i) >= 1)
        {
          jetPt_hadronFlavorBtag_passed->Fill(jetPt_->at(i));
        }
        if(jetBtagAlgo_->at(i) >= 1)
        {
          jetPt_hadronFlavorBtagAlgo_passed->Fill(jetPt_->at(i));
        }
      }
    }
    //GEN JETS
    int counterGenJet = 0;

    for(int i=0; i<nGenJets_; i++)
    {
      if(GenJetPt_->at(i) > 30 && abs(GenJetEta_->at(i)) < 2.4)  //pT, eta selection for jets
      {
        counterGenJet++;
      }
    }

    //DET MUONS
    double STmu = 0.0;
    int counterSelMu      = 0;
    int counterSelMuPlus  = 0;
    int counterSelMuMinus = 0;
    TLorentzVector leadingMuMinus;
    TLorentzVector leadingMuPlus;
    for(int j=0; j<nMuons_; j++)
    {
      if(muonPt_->at(j) > 30. && abs(muonEta_->at(j)) < 2.4)   //pT, eta selection for muons
      {
        counterSelMu++;
        STmu += muonPt_->at(j);
        if(muonCharge_->at(j) == -1)
        {
          counterSelMuMinus++;
          if(counterSelMuMinus == 1)
          {
            leadingMuMinus.SetPtEtaPhiM(muonPt_->at(j),muonEta_->at(j),muonPhi_->at(j),muonMass);
          }
        }
        else if(muonCharge_->at(j) == +1)
        {
          counterSelMuPlus++;
          if(counterSelMuPlus == 1)
          {
            leadingMuPlus.SetPtEtaPhiM(muonPt_->at(j),muonEta_->at(j),muonPhi_->at(j),muonMass);
          }
        }
      }
    }
    //GEN MUONS
    double STmuPart = 0.0;
    int counterSelMuPart      = 0;
    int counterSelMuPartPlus  = 0;
    int counterSelMuPartMinus = 0;
    TLorentzVector leadingMuPartMinus;
    TLorentzVector leadingMuPartPlus;
    bool passMuonPtMatching;
    bool passMuonEtaMatching;
    float dEta_gMudMu;
    float dPtnorm_gMudMu;
    for(int j=0; j<nMuonParticles_; j++)
    {
      MuonParticlePt_total ->Fill(MuonParticlePt_ ->at(j)); //no weight for efficiency calculation
      if(MuonParticlePt_ ->at(j) > 30.)
      {
        MuonParticleEta_total->Fill(MuonParticleEta_->at(j));
      }
      passMuonPtMatching  = false;
      passMuonEtaMatching = false;
      for(int k=0; k<nMuons_; k++)
      {
        if(DeltaRFS(MuonParticleEta_->at(j),MuonParticlePhi_->at(j),muonEta_->at(k),muonPhi_->at(k)) < 0.2)
        {
          passMuonPtMatching = true;
          if(MuonParticlePt_ ->at(j) > 30.)
          {
            passMuonEtaMatching = true;
          }
          dEta_gMudMu = DeltaEtaFS(MuonParticleEta_->at(j),muonEta_->at(k));
          dEta_genMudetMu->Fill(dEta_gMudMu,hweight);
          dPtnorm_gMudMu = (MuonParticlePt_ ->at(j) - muonPt_->at(k)) / MuonParticlePt_ ->at(j);
          PtResolution_muon->Fill(dPtnorm_gMudMu,hweight);
        }
      }
      if(passMuonPtMatching == true)
      {
        MuonParticlePt_passed ->Fill(MuonParticlePt_ ->at(j));
        if(passMuonEtaMatching == true)
        {
          MuonParticleEta_passed->Fill(MuonParticleEta_->at(j));
        }
      }

      if(MuonParticlePt_->at(j) > 30. && abs(MuonParticleEta_->at(j)) < 2.4  && MuonParticleStatus_->at(j) == 23)   //pT, eta selection for muons
      {
        counterSelMuPart++;
        STmuPart += MuonParticlePt_->at(j);
        if(MuonParticleId_->at(j) == 13)
        {
          counterSelMuPartMinus++;
          if(counterSelMuPartMinus == 1)
          {
            leadingMuPartMinus.SetPtEtaPhiM(MuonParticlePt_->at(j),MuonParticleEta_->at(j),MuonParticlePhi_->at(j),MuonParticleMass_->at(j));
          }
        }
        else if(MuonParticleId_->at(j) == -13)
        {
          counterSelMuPartPlus++;
          if(counterSelMuPartPlus == 1)
          {
            leadingMuPartPlus.SetPtEtaPhiM(MuonParticlePt_->at(j),MuonParticleEta_->at(j),MuonParticlePhi_->at(j),MuonParticleMass_->at(j));
          }
        }
      }
    }

    //DET ELECTRONS
    double STel = 0.0;
    int counterSelEl = 0;
    for(int j=0; j<nElecs_; j++)
    {
      if(elecPt_->at(j) > 30. && abs(elecEta_->at(j)) < 2.4)          //pT, eta selection for electrons
      {
        counterSelEl++;
        STel += elecPt_->at(j);
      }
    }
    //GEN ELECTRONS
    double STelPart = 0.0;
    int counterSelElPart = 0;
    bool passElecPtMatching;
    bool passElecEtaMatching;
    float dEta_gEldEl;
    float dPtres_gEldEl;
    for(int i=0; i<nGenParticles_; i++)
    {
      if(abs(GenParticleId_->at(i)) == 11)  //select the electrons
      {
        ElecParticlePt_total ->Fill(GenParticlePt_ ->at(i)); //no weight for efficiency calculation
        if(GenParticlePt_->at(i) > 30.)
        {
          ElecParticleEta_total->Fill(GenParticleEta_->at(i));
        }
        passElecPtMatching  = false;
        passElecEtaMatching = false;
        for(int k=0; k<nElecs_; k++)
        {
          if(DeltaRFS(GenParticleEta_->at(i),GenParticlePhi_->at(i),elecEta_->at(k),elecPhi_->at(k)) < 0.2)
          {
            passElecPtMatching = true;
            if(GenParticlePt_->at(i) > 30.)
            {
              passElecEtaMatching = true;
            }

            dEta_gEldEl = DeltaEtaFS(GenParticleEta_->at(i),elecEta_->at(k));
            dEta_genEldetEl->Fill(dEta_gEldEl,hweight);
            dPtres_gEldEl = (GenParticlePt_ ->at(i) - elecPt_->at(k)) / GenParticlePt_ ->at(i);
            PtResolution_elec->Fill(dPtres_gEldEl,hweight);
          }
        }
        if(passElecPtMatching == true)
        {
          ElecParticlePt_passed ->Fill(GenParticlePt_ ->at(i));
          if(passElecEtaMatching == true)
          {
            ElecParticleEta_passed->Fill(GenParticleEta_->at(i));
          }
        }
        if(GenParticlePt_->at(i) > 30. && abs(GenParticleEta_->at(i)) < 2.4)
        {
          counterSelElPart++;
          STelPart += GenParticlePt_->at(i);
        }
      }
    }


    //LEPTOQUARK MASS RECONSTUCTION FROM TOP AND DET MUONS: always pair production -> always exactly 2 tops (t + tbar)
    TLorentzVector top;
    TLorentzVector topBar;
    double recoMLQ_top    = 0.0;
    double recoMLQ_topBar = 0.0;
    //double recoMLQ        = 0.0;
    for(int i=0; i<nTopParticles_; i++)
    {
      if(TopParticleId_->at(i) == 6)         //t + mu-
      {
        top.SetPtEtaPhiM(TopParticlePt_->at(i),TopParticleEta_->at(i),TopParticlePhi_->at(i),TopParticleMass_->at(i));
        recoMLQ_top = (top + leadingMuMinus).M();

      }
      else if(TopParticleId_->at(i) == -6)   //tbar + mu+
      {
        topBar.SetPtEtaPhiM(TopParticlePt_->at(i),TopParticleEta_->at(i),TopParticlePhi_->at(i),TopParticleMass_->at(i));
        recoMLQ_topBar = (topBar + leadingMuPlus).M();
      }
    }
    //recoMLQ = (recoMLQ_top + recoMLQ_topBar) / 2.;  //averaged

    //GEN MUONS RECONSTRUCTION
    double recoMLQ_top_GenMu    = 0.0;
    double recoMLQ_topBar_GenMu = 0.0;
    //double recoMLQ_GenMu        = 0.0;
    for(int i=0; i<nTopParticles_; i++)
    {
      if(TopParticleId_->at(i) == 6)         //t + mu^minus
      {
        top.SetPtEtaPhiM(TopParticlePt_->at(i),TopParticleEta_->at(i),TopParticlePhi_->at(i),TopParticleMass_->at(i));
        recoMLQ_top_GenMu = (top + leadingMuPartMinus).M();
      }
      else if(TopParticleId_->at(i) == -6)   //t^bar + mu^plus
      {
        topBar.SetPtEtaPhiM(TopParticlePt_->at(i),TopParticleEta_->at(i),TopParticlePhi_->at(i),TopParticleMass_->at(i));
        recoMLQ_topBar_GenMu = (topBar + leadingMuPartPlus).M();
      }
    }
    //recoMLQ_GenMu = (recoMLQ_top_GenMu + recoMLQ_topBar_GenMu) / 2.;  //averaged

    bool selectionPass = false;

    //FULL SELECTION: DETECTOR LEVEL
    if(counterJet >= 2)    // >= 2 jets
    {
      if(counterSelMuPlus >= 1 && counterSelMuMinus >= 1)     // >=1 selected mu+, mu- each
      {
        if(STmu+STel > 200.)     // STlep > 200 GeV
        {
          if(ScalarHT > 350.)     // ST > 350 GeV
          {
            selectionPass = true;
            numberOfEvents++;
            //FILL DET MU HISTOGRAMS
            nMuons    ->Fill(counterSelMu,hweight);
            for(int i=0; i<nMuons_; i++)
            {
              if(muonPt_->at(i) > 30. && abs(muonEta_->at(i)) < 2.4)
              {
                muonPt ->Fill(muonPt_ ->at(i),hweight);
                muonPhi->Fill(muonPhi_->at(i),hweight);
                muonEta->Fill(muonEta_->at(i),hweight);
              }
            }
            //Fill DET ELEC HISTOGRAMS
            nElecs-> Fill(counterSelEl,hweight);
            for(int i=0; i<nElecs_; i++)
            {
              if(elecPt_->at(i) > 30. && abs(elecEta_->at(i)) < 2.4)
              {
                elecPt ->Fill(elecPt_ ->at(i),hweight);
                elecPhi->Fill(elecPhi_->at(i),hweight);
                elecEta->Fill(elecEta_->at(i),hweight);
              }
            }
            //FILL JET HISTOGRAMS
            nJets->Fill(nJets_,hweight);
            for(int i=0; i<nJets_; i++)
            {
              if(jetPt_->at(i) > 30 && abs(jetEta_->at(i)) < 2.4)
              {
                jetPt      ->Fill(jetPt_->at(i));                 // NOTE: hweight excluded for test
                jetEta     ->Fill(jetEta_->at(i)     ,hweight);
                jetPhi     ->Fill(jetPhi_->at(i)     ,hweight);
                jetBtag    ->Fill(jetBtag_->at(i)    ,hweight);
                jetBtagAlgo->Fill(jetBtagAlgo_->at(i),hweight);
              }
            }
            //FILL TOP HISTOGRAMS
            nTopParticles->Fill(nTopParticles_, hweight);
            for(int i=0; i<nTopParticles_; i++)
            {
              TopParticlePt  ->Fill(TopParticlePt_->at(i)  ,hweight);
              TopParticlePhi ->Fill(TopParticlePhi_->at(i) ,hweight);
              TopParticleEta ->Fill(TopParticleEta_->at(i) ,hweight);
              TopParticleMass->Fill(TopParticleMass_->at(i),hweight);
            }

            //FILL LQ HISTOGRAMS
            nLeptoQuarkParticles->Fill(nLeptoQuarkParticles_,hweight);
            for(int i=0; i<nLeptoQuarkParticles_; i++)
            {
              LeptoQuarkParticlePt->  Fill(LeptoQuarkParticlePt_->at(i)  ,hweight);
              LeptoQuarkParticlePhi-> Fill(LeptoQuarkParticlePhi_->at(i) ,hweight);
              LeptoQuarkParticleEta-> Fill(LeptoQuarkParticleEta_->at(i) ,hweight);
              LeptoQuarkParticleMass->Fill(LeptoQuarkParticleMass_->at(i),hweight);
            }

            //LQ RECO MASS & S_T
            MLQreco_detMu->Fill(recoMLQ_top,hweight);
            MLQreco_detMu->Fill(recoMLQ_topBar,hweight);
            ST           ->Fill(ScalarHT,hweight);
          }
        }
      }
    }


    //FULL SELECTION: GENERATOR LEVEL
    if(counterGenJet >= 2)    // >= 2 jets
    {
      if(counterSelMuPartPlus >= 1 && counterSelMuPartMinus >= 1)     // >=2 selected muons
      {
        if(STmuPart+STelPart > 200.)     // STlep > 200 GeV
        {
          if(ScalarHT > 350.)     // ST > 350 GeV
          {
            //FILL GEN MU HISTOGRAMS
            nMuonParticles->Fill(counterSelMuPart,hweight);
            for(int j=0; j<nMuonParticles_; j++)
            {
              if(MuonParticlePt_->at(j) > 30. && abs(MuonParticleEta_->at(j)) < 2.4)
              {
                MuonParticlePt ->Fill(MuonParticlePt_ ->at(j),hweight);
                MuonParticlePhi->Fill(MuonParticlePhi_->at(j),hweight);
                MuonParticleEta->Fill(MuonParticleEta_->at(j),hweight);
              }
            }

            //FILL GEN ELEC HISTOGRAMS
            nElecParticles->Fill(counterSelElPart,hweight);
            for(int i=0; i<nGenParticles_; i++)
            {
              if(abs(GenParticleId_->at(i)) == 11 && GenParticlePt_->at(i) > 30. && abs(GenParticleEta_->at(i)) < 2.4)
              {
                ElecParticlePt ->Fill(GenParticlePt_ ->at(i),hweight);
                ElecParticlePhi->Fill(GenParticlePhi_->at(i),hweight);
                ElecParticleEta->Fill(GenParticleEta_->at(i),hweight);
              }
            }

            if(counterSelMuPartMinus >= 1 && counterSelMuPartPlus >= 1)
            {
              MLQreco_genMu->Fill(recoMLQ_top_GenMu   ,hweight);
              MLQreco_genMu->Fill(recoMLQ_topBar_GenMu,hweight);
            }
          }
        }
      }
    }

    //JET MACHTING EFFICIENCY
    nGenJets->Fill(nGenJets_,hweight);
    bool passJetPtMatching;
    bool passJetEtaMatching;
    for(int i=0; i<nGenJets_; i++)  //GEN JETS
    {
      bool overlaps = false; //for jet muon overlap
      for(int k=0; k<nMuonParticles_; k++)
      {
        if(DeltaRFS(GenJetEta_->at(i),GenJetPhi_->at(i),MuonParticleEta_->at(k),MuonParticlePhi_->at(k)) < 0.2)
        {
          overlaps = true;
        }
      }
      if(overlaps) continue;
      if(GenJetPt_->at(i) < 100) continue;  //rejects GenJets with pT < 100 GeV

      //FILL GENJET HISTOGRAMS
      GenJetPt       ->Fill(GenJetPt_ ->at(i),hweight);
      GenJetPt_total ->Fill(GenJetPt_ ->at(i));         //no weight for efficiency calculation
      GenJetEta      ->Fill(GenJetEta_->at(i),hweight);
      if(GenJetPt_->at(i) > 30.) GenJetEta_total->Fill(GenJetEta_->at(i));  //no weight for efficiency calculation
      GenJetPhi->Fill(GenJetPhi_->at(i),hweight);

      passJetPtMatching  = false;
      passJetEtaMatching = false;
      for(int k=0; k<nJets_; k++) //DET JETS
      {
        // if(jetPt_->at(k)<100) continue;
        if(DeltaRFS(GenJetEta_->at(i),GenJetPhi_->at(i),jetEta_->at(k),jetPhi_->at(k)) < 0.2)
        {
          passJetPtMatching = true;
          if(GenJetPt_->at(i) > 30. && jetPt_->at(k) > 30.)
          {
            passJetEtaMatching = true;
            double deltaEta = DeltaEtaFS(GenJetEta_->at(i),jetEta_->at(k));
            dEta_genJetdetJet->Fill(deltaEta,hweight);
            JetRes2D->Fill(GenJetPt_->at(i),jetPt_->at(k),hweight);
            double resolution = (GenJetPt_->at(i) - jetPt_->at(k)) / GenJetPt_->at(i);
            JetRes->Fill(resolution,hweight);
            double response = jetPt_->at(k) / GenJetPt_->at(i);
            JetResponse->Fill(response,hweight);
          }
        }
      }
      if(passJetPtMatching == true)
      {
        GenJetPt_passed ->Fill(GenJetPt_ ->at(i));
        if(passJetEtaMatching == true) GenJetEta_passed->Fill(GenJetEta_->at(i));
      }
    }



    //TOP & LQ MASS RECONSTRUCTION
    vector <TLorentzVector> Jet_v4;
    for(int j=0; j<nGenJets_; j++)
    {
      if(j == 7) break; //check the 7 leading jets
      if(GenJetPt_->at(j) > 30. && fabs(GenJetEta_->at(j)) < 2.4)
      {
        TLorentzVector jet_v4_temp;
        jet_v4_temp.SetPtEtaPhiM(GenJetPt_->at(j),GenJetEta_->at(j),GenJetPhi_->at(j),GenJetMass_->at(j));
        Jet_v4.push_back(jet_v4_temp);  //all selected jets
      }
    }

    // // changed to GenJets above -> here: for DetJets
    //
    // vector <TLorentzVector> Jet_v4_bflavour;
    // vector <TLorentzVector> Jet_v4_otherflavour;
    // for(int j=0; j<nJets_; j++)
    // {
    //   if(j == 7) break; //take the 7 leading jets
    //   if(jetPt_->at(j) > 30. && fabs(jetEta_->at(j)) < 2.4)
    //   {
    //     if(fabs(jetFlavorHadron_->at(j)) == 5)  //if()if() changed to if(if()else())
    //     {
    //       TLorentzVector jet_v4_temp;
    //       jet_v4_temp.SetPtEtaPhiM(jetPt_->at(j),jetEta_->at(j),jetPhi_->at(j),jetMass_->at(j));
    //       Jet_v4_bflavour.push_back(jet_v4_temp); //all selected b-jets
    //     }
    //     else
    //     {
    //       TLorentzVector jet_v4_temp;
    //       jet_v4_temp.SetPtEtaPhiM(jetPt_->at(j),jetEta_->at(j),jetPhi_->at(j),jetMass_->at(j));
    //       Jet_v4_otherflavour.push_back(jet_v4_temp); //all other selected jets
    //     }
    //   }
    // }

    if(Jet_v4.size() < 4) continue; //if true -> continue with next event in the for-loop

    if(!selectionPass) continue;

    vector <TLorentzVector> Tops_Lept_Reco_v4;
    vector <TLorentzVector> Tops_Hadr_Reco_v4;

    vector <TLorentzVector> LQRecos_Hadr_v4;
    vector <TLorentzVector> LQRecos_Lept_v4;

    // // not reconstructed in Arnes analysis
    //
    // //calculate the best combination for having the two reco-top (two hadronic)
    // if(counterSelMu == 2 && counterSelEl == 0 && selectionPass && mHadSelection)
    // {
    //   // cout << "started full hadronic top reconstruction..." << endl;
    //   // perhaps here one can use the b-hadron flavour
    //   // cout << "size " << Jet_v4_bflavour.size() << " " << Jet_v4_otherflavour.size() << endl;
    //   for(unsigned int first=0; first<Jet_v4.size(); first++)
    //   {
    //     for(unsigned int second=first+1; second<Jet_v4.size(); second++)
    //     {
    //       for(unsigned int third=second+1; third<Jet_v4.size(); third++)
    //       {
    //         Tops_Hadr_Reco_v4.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third));  //for three jets
    //         Tops_Lept_Reco_v4.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third));  //for three jets
    //
    //         for(unsigned int fourth=third+1; fourth<Jet_v4.size(); fourth++) //for gluon radiation
    //         {
    //           Tops_Hadr_Reco_v4.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third) + Jet_v4.at(fourth)); //for four jets
    //           Tops_Lept_Reco_v4.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third) + Jet_v4.at(fourth)); //for four jets
    //         } //NOTE: here Tops_Hadr_Reco_v4 == Tops_Lept_Reco_v4
    //       }
    //     }
    //   }
    //   //we have now all possible tops and we can calculate the reconstructed LQ mass
    //   //the constraint is that the muon and the electron needs to be oppositely charged -> ensures that the electron comes from top decay
    //   //LQ from leptonic top
    //   for(unsigned int j = 0; j < Tops_Lept_Reco_v4.size(); j++)
    //   {
    //     TLorentzVector muon_to_associate_v4_temp_1; //leading muon
    //     muon_to_associate_v4_temp_1.SetPtEtaPhiM(muonPt_->at(0),muonEta_->at(0),muonPhi_->at(0),muonMass);  //NOTE: are the detector muons really ordered in pt?
    //     TLorentzVector LQRecos_v4_temp_1 = Tops_Lept_Reco_v4.at(j) + muon_to_associate_v4_temp_1;
    //     LQRecos_Lept_v4.push_back(LQRecos_v4_temp_1); //fill with first possible combination
    //
    //     TLorentzVector muon_to_associate_v4_temp_2; //2nd leading muon
    //     muon_to_associate_v4_temp_2.SetPtEtaPhiM(muonPt_->at(1),muonEta_->at(1),muonPhi_->at(1),muonMass);
    //     TLorentzVector LQRecos_v4_temp_2 = Tops_Lept_Reco_v4.at(j) + muon_to_associate_v4_temp_2;
    //     LQRecos_Lept_v4.push_back(LQRecos_v4_temp_2); //fill with second possible combination
    //
    //     TLorentzVector LQRecos_v4_temp_3 = Tops_Hadr_Reco_v4.at(j) + muon_to_associate_v4_temp_1;
    //     LQRecos_Hadr_v4.push_back(LQRecos_v4_temp_1);
    //
    //     TLorentzVector LQRecos_v4_temp_4 = Tops_Hadr_Reco_v4.at(j) + muon_to_associate_v4_temp_2;
    //     LQRecos_Hadr_v4.push_back(LQRecos_v4_temp_2);
    //   } //NOTE: still LQRecos_Lept_v4 == LQRecos_Hadr_v4
    // } //END OF HADRONIC PART


    //LEPTONIC PART
    bool electronChannel = false;
    vector <TLorentzVector> wboson_v4;
    vector <TLorentzVector> neutrino_v4;
    TLorentzVector electron_v4;

    if(counterSelMu == 2 && counterSelEl >= 1 && selectionPass && mElSelection)
    {
      // cout << "started leptonic top reconstruction..." << endl;
      //if(!selectionPass || nElecs_<1) continue;
      electronChannel = true;

      //Top mass reconstruction
      //simple case: electron in the final state
      //select an electron and you have the four momentum
      if(elecPt_->at(0) < 30. || fabs(elecEta_->at(0)) > 2.4) continue;
      electron_v4.SetPtEtaPhiM(elecPt_->at(0),elecEta_->at(0),elecPhi_->at(0),elecMass);  //leading electron

      //define the neutrino from the MET
      float metPx = MET * cos(METphi);
      float metPy = MET * sin(METphi);

      float mu = massW * massW / 2 + electron_v4.Px() * metPx + electron_v4.Py() * metPy; //scalar product between lepton and neutrino
      float A = - (electron_v4.E() * electron_v4.E());
      float B = mu * electron_v4.Pz();
      float C = mu * mu - electron_v4.E() * electron_v4.E() * (MET * MET);
      float discriminant = B * B - A * C;     //NOTE: why is E_electron = p_T,electron?

      if(0 >= discriminant)
      {
        //take only real part of the solution for pz
        TLorentzVector solution;
        solution.SetPxPyPzE(metPx,metPy,-B/A,0);
        solution.SetE(solution.P());
        solution.SetPxPyPzE(metPx,metPy,-B/A,solution.E());
        neutrino_v4.push_back(solution);
      }
      else
      {
        discriminant = sqrt(discriminant);
        TLorentzVector solution;
        solution.SetPxPyPzE(metPx,metPy,(-B-discriminant)/A,0);
        solution.SetE(solution.P());
        solution.SetPxPyPzE(metPx,metPy,(-B-discriminant)/A,solution.E());
        neutrino_v4.push_back(solution);

        TLorentzVector solution2;
        solution2.SetPxPyPzE(metPx,metPy,(-B+discriminant)/A,0);
        solution2.SetE(solution2.P());
        solution2.SetPxPyPzE(metPx,metPy,(-B+discriminant)/A,solution2.E());
        neutrino_v4.push_back(solution2);
      }

      //neutrino_v4.SetPtEtaPhiM(MET,METeta,METphi,0.);

      //define the W system
      for(unsigned int j=0; j<neutrino_v4.size(); j++)
      {
        wboson_v4.push_back(electron_v4 + neutrino_v4.at(j));
      }

      //cout<<wboson_v4.M()<<endl;

      //now you need to associate the W system to the different jets in the system
      //define the four vectors of all jets

      //calculate the best combination for having the two reco-top (one leptonic and one hadronic)

      //for(unsigned int i=0; i<wboson_v4.size(); i++){
      //cout<<"wmass "<<i<<" "<<wboson_v4.at(i).M()<<endl;
      //}

      for(unsigned int first=0; first<Jet_v4.size(); first++)
      {
        //Leptonic top
        for(unsigned int i=0; i<wboson_v4.size(); i++)
        {
          TLorentzVector top_v4_temp = wboson_v4.at(i) + Jet_v4.at(first);  //for single jets
          Tops_Lept_Reco_v4.push_back(top_v4_temp);
        }
        for(unsigned int second=first+1; second<Jet_v4.size(); second++)
        {
          for(unsigned int i=0; i<wboson_v4.size(); i++)
          { //includes gluon radiation
            Tops_Lept_Reco_v4.push_back(wboson_v4.at(i) + Jet_v4.at(first) + Jet_v4.at(second));  //for dijets
          }
          //Hadronic top
          for(unsigned int third=second+1; third<Jet_v4.size(); third++)
          {
            Tops_Hadr_Reco_v4.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third)); //for three jets

            for(unsigned int fourth=third+1; fourth<Jet_v4.size(); fourth++)
            {
              Tops_Hadr_Reco_v4.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third) + Jet_v4.at(fourth)); //for fourth jets
            }
          }
        }
      }
      //we have now all possible tops and we can calculate the reconstructed LQ mass
      //the constraint is that the muon and the electron needs to be oppositely charged
      for(int i=0; i<2; i++)  //two leading muons
      {
        //LQ from leptonic top
        if(muonCharge_->at(i) != elecCharge_->at(0))  //OS of mu & e
        {
          for(unsigned int j=0; j<Tops_Lept_Reco_v4.size(); j++)
          {
            TLorentzVector muon_to_associate_v4_temp;
            muon_to_associate_v4_temp.SetPtEtaPhiM(muonPt_->at(i),muonEta_->at(i),muonPhi_->at(i),muonMass);
            TLorentzVector LQRecos_v4_temp = Tops_Lept_Reco_v4.at(j) + muon_to_associate_v4_temp;
            LQRecos_Lept_v4.push_back(LQRecos_v4_temp);
          }
        }
        //LQ from hadronic top
        else  //SS of mu & e
        {
          for(unsigned int j=0; j<Tops_Hadr_Reco_v4.size(); j++)
          {
            TLorentzVector muon_to_associate_v4_temp;
            muon_to_associate_v4_temp.SetPtEtaPhiM(muonPt_->at(i),muonEta_->at(i),muonPhi_->at(i),muonMass);
            TLorentzVector LQRecos_v4_temp = Tops_Hadr_Reco_v4.at(j) + muon_to_associate_v4_temp;
            LQRecos_Hadr_v4.push_back(LQRecos_v4_temp);
          }
        }
      }
    }
    //END OF LEPTONIC PART


    //CASE OF THREE MUONS (muonic decay of one of the tops)
    bool muonChannel = false;

    //CASE OF THREE MUONS (muonic decay of one of the tops)
    if(counterSelMu >= 3 && counterSelEl == 0 && selectionPass && mMuSelection)
    {
      //if(!selectionPass || nElecs_<1) continue;
      muonChannel = true;

      //Top mass reconstruction
      //simple case: additional muon in the final state -> select this muon and you have the four momentum
      if(muonPt_->at(2) < 30 || fabs(muonEta_->at(2)) > 2.4) continue;

      for(int l1 = 0; l1 < 3; l1++)
      {
        //we call the electron that is used to reconstruct a W (in this case it's a muon)
        electron_v4.SetPtEtaPhiM(muonPt_->at(l1),muonEta_->at(l1),muonPhi_->at(l1),muonMass);

        //define the neutrino from the MET
        float metPx = MET * cos(METphi);
        float metPy = MET * sin(METphi);

        float mu = massW * massW / 2. + electron_v4.Px() * metPx + electron_v4.Py() * metPy;  //scalar product between lepton and neutrino
        float A = - (electron_v4.E() * electron_v4.E());
        float B = mu * electron_v4.Pz();
        float C = mu * mu - electron_v4.E() * electron_v4.E() * (MET * MET);
        float discriminant = B * B - A * C;

        if(0 >= discriminant)
        { // Take only real part of the solution for pz:
          TLorentzVector solution;
          solution.SetPxPyPzE(metPx,metPy,-B/A,0);
          solution.SetE(solution.P());
          solution.SetPxPyPzE(metPx,metPy,-B/A,solution.E());
          neutrino_v4.push_back(solution);
        }
        else
        {
          discriminant = sqrt(discriminant);
          TLorentzVector solution;
          solution.SetPxPyPzE(metPx,metPy,(-B-discriminant)/A,0);
          solution.SetE(solution.P());
          solution.SetPxPyPzE(metPx,metPy,(-B-discriminant)/A,solution.E());
          neutrino_v4.push_back(solution);

          TLorentzVector solution2;
          solution2.SetPxPyPzE(metPx,metPy,(-B+discriminant)/A,0);
          solution2.SetE(solution2.P());
          solution2.SetPxPyPzE(metPx,metPy,(-B+discriminant)/A,solution2.E());
          neutrino_v4.push_back(solution2);
        }

        //neutrino_v4.SetPtEtaPhiM(MET,METeta,METphi,0.);

        //define the W system
        for(unsigned int j=0; j<neutrino_v4.size(); j++)
        {
          wboson_v4.push_back(electron_v4 + neutrino_v4.at(j));
        }

        //now you need to associate the W system to the different jets in the system
        //define the four vectors of all jets
        //calculate the best combination for having the two reco-top (one leptonic and one hadronic)

        for (unsigned int first=0; first<Jet_v4.size(); first++)
        { //Leptonic top
          for(unsigned int i=0; i<wboson_v4.size(); i++)
          {
            TLorentzVector top_v4_temp = wboson_v4.at(i) + Jet_v4.at(first); //for single jets
            Tops_Lept_Reco_v4.push_back(top_v4_temp);
          }
          for(unsigned int second=first+1; second<Jet_v4.size(); second++)
          {
            for(unsigned int i=0; i<wboson_v4.size(); i++)
            {
              Tops_Lept_Reco_v4.push_back(wboson_v4.at(i) + Jet_v4.at(first) + Jet_v4.at(second)); //for dijets
            } //Hadronic top
            for (unsigned int third=second+1; third<Jet_v4.size(); third++)
            {
              Tops_Hadr_Reco_v4.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third)); //for three jets

              for (unsigned int fourth=third+1; fourth<Jet_v4.size(); fourth++)
              {
                Tops_Hadr_Reco_v4.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third) + Jet_v4.at(fourth)); //for fourth jets
              }
            }
          }
        }

        //we have now all possible tops and we can calculate the reconstructed LQ mass
        //the constraint is that the muon and the electron needs to be oppositely charged
        for (int l2 = 0; l2<3; l2++)
        {
          if(l1 == l2) continue;
          if(muonCharge_->at(l2) != muonCharge_->at(l1)) //LQ from leptonic top
          {
            for(unsigned int j=0; j<Tops_Lept_Reco_v4.size(); j++)
            {
              TLorentzVector muon_to_associate_v4_temp;
              muon_to_associate_v4_temp.SetPtEtaPhiM(muonPt_->at(l2),muonEta_->at(l2),muonPhi_->at(l2),muonMass);
              TLorentzVector LQRecos_v4_temp = Tops_Lept_Reco_v4.at(j) + muon_to_associate_v4_temp;
              LQRecos_Lept_v4.push_back(LQRecos_v4_temp);
            }
          }
          else //LQ from hadronic top
          {
            for (unsigned int j=0; j<Tops_Hadr_Reco_v4.size(); j++)
            {
              TLorentzVector muon_to_associate_v4_temp;
              muon_to_associate_v4_temp.SetPtEtaPhiM(muonPt_->at(l2),muonEta_->at(l2),muonPhi_->at(l2),muonMass);
              TLorentzVector LQRecos_v4_temp = Tops_Hadr_Reco_v4.at(j) + muon_to_associate_v4_temp;
              LQRecos_Hadr_v4.push_back(LQRecos_v4_temp);
            }
          }
        }
      }
    } //END OF THREE MUONS PART


    //defintion of the chi2
    const double mass_thad = 174.;  //NOTE: these are not exactly the same values as in the paper! changed values!
    const double mass_thad_sigma = 17.;
    const double mass_tlep = 174.;
    const double mass_tlep_sigma = 23.;
    const double mass_LQ_diff_rel = -0.00132;
    const double mass_LQ_diff_rel_sigma = 0.089;
    // const double pt_LQ_diff = 0.65;
    // const double pt_LQ_diff_sigma = 46.;
    // const double pt_ratio = 1;
    // const double pt_ratio_sigma = 0.15;
    // const double dphi_LQ = 3.14;
    // const double dphi_LQ_sigma = 0.09;
    double chi2_total = 100000.;
    const double mass_LQ_mean_rec = 1200.;  //NOTE: why not calculated?

    double LQRecos_Hadr_rec_mass = -10;
    double LQRecos_Lept_rec_mass = -10;

    double Top_Hadr_rec_mass = -10;
    double Top_Lept_rec_mass = -10;

    double LQHadrMass = -10;
    double LQLeptMass = -10;

    for(unsigned int j=0; j<Tops_Lept_Reco_v4.size(); j++)
    {
      double chi2_top_lept = pow((Tops_Lept_Reco_v4.at(j).M() - mass_tlep) / mass_tlep_sigma, 2);
      if(fabs(Tops_Lept_Reco_v4.at(j).M() - mass_tlep) > 1000) continue;
      for(unsigned int i=0; i<Tops_Hadr_Reco_v4.size(); i++)
      {
        double chi2_thad = pow((Tops_Hadr_Reco_v4.at(i).M() - mass_thad) / mass_thad_sigma, 2);
        if(fabs(Tops_Hadr_Reco_v4.at(i).M() - mass_thad) > 1000) continue;
        for(unsigned int t=0; t<LQRecos_Hadr_v4.size(); t++)
        {
          for(unsigned int g=0; g<LQRecos_Lept_v4.size(); g++)
          {
            double chi2_MLQdiff_rel = pow(((LQRecos_Hadr_v4.at(t).M() - LQRecos_Lept_v4.at(g).M())/mass_LQ_mean_rec - mass_LQ_diff_rel) / mass_LQ_diff_rel_sigma, 2);
            double chi2_total_temp = chi2_thad + chi2_MLQdiff_rel + chi2_top_lept;
            if(chi2_total_temp < chi2_total)
            {
              chi2_total = chi2_total_temp;
              LQHadrMass = LQRecos_Hadr_v4.at(t).M();
              LQLeptMass = LQRecos_Lept_v4.at(g).M();
              LQRecos_Hadr_rec_mass = LQRecos_Hadr_v4.at(t).M();
              LQRecos_Lept_rec_mass = LQRecos_Lept_v4.at(g).M();
              Top_Hadr_rec_mass = Tops_Hadr_Reco_v4.at(i).M();
              Top_Lept_rec_mass = Tops_Lept_Reco_v4.at(j).M();
            }
          }
        }
      }
    }

    //plot top mass and chi2
    double AverageMass = (LQRecos_Hadr_rec_mass + LQRecos_Lept_rec_mass) / 2.;
    MLQfullreco_detMu->Fill(AverageMass,hweight);
    LQHadrMassreco   ->Fill(LQHadrMass ,hweight);
    LQLeptMassreco   ->Fill(LQLeptMass ,hweight);

    if(electronChannel || muonChannel)
    {
      double Wmass = wboson_v4.at(0).M();
      if(wboson_v4.size() > 1)
      {
        if(fabs(Wmass - 80.385) > fabs(wboson_v4.at(1).M() - 80.385)) Wmass = wboson_v4.at(1).M();
      }
      WbosonMass->Fill(Wmass,hweight);
    }

    HadrTopfullreco->Fill(Top_Hadr_rec_mass,hweight);
    LeptTopfullreco->Fill(Top_Lept_rec_mass,hweight);
    chi2           ->Fill(chi2_total       ,hweight);

    //clear all vectors
    LQRecos_Hadr_v4  .clear();
    LQRecos_Lept_v4  .clear();
    Tops_Hadr_Reco_v4.clear();
    Tops_Lept_Reco_v4.clear();
    Jet_v4           .clear();
    neutrino_v4      .clear();
    wboson_v4        .clear();

    // cout << endl;
  } // end of event loop
  cout << "numberOfEventsAfterSelection: " << numberOfEvents << endl;

  //EFFICIENCY PLOTS
  //If the denominator becomes 0 or pass > total, the corresponding bin is skipped -> change plot limits or binning!
  //jet matching efficiency
  TGraphAsymmErrors jetMatchEff_pt = TGraphAsymmErrors(GenJetPt_passed,GenJetPt_total);
  jetMatchEff_pt.Write("jetMatchEff_pt");
  TGraphAsymmErrors jetMatchEff_eta = TGraphAsymmErrors(GenJetEta_passed,GenJetEta_total);
  jetMatchEff_eta.Write("jetMatchEff_eta");
  //b-tag(algo) efficiency
  TGraphAsymmErrors jetBtagEff_pt = TGraphAsymmErrors(jetPt_hadronFlavorBtag_passed,jetPt_hadronFlavor_total);
  jetBtagEff_pt.Write("jetBtagEff_pt");
  TGraphAsymmErrors jetBtagAlgoEff_pt = TGraphAsymmErrors(jetPt_hadronFlavorBtagAlgo_passed,jetPt_hadronFlavor_total);
  jetBtagAlgoEff_pt.Write("jetBtagAlgoEff_pt");
  TGraphAsymmErrors jetBtagEff_Eta = TGraphAsymmErrors(jetEta_hadronFlavorBtag_passed,jetEta_hadronFlavor_total);
  jetBtagEff_Eta.Write("jetBtagEff_Eta");
  TGraphAsymmErrors jetBtagAlgoEff_Eta = TGraphAsymmErrors(jetEta_hadronFlavorBtagAlgo_passed,jetEta_hadronFlavor_total);
  jetBtagAlgoEff_Eta.Write("jetBtagAlgoEff_Eta");
  //b-tag(algo) purity
  TGraphAsymmErrors jetBtagPurity_pt = TGraphAsymmErrors(jetPt_hadronFlavorBtag_passed,jetPt_Btag_total);
  jetBtagPurity_pt.Write("jetBtagPurity_pt");
  TGraphAsymmErrors jetBtagAlgoPurity_pt = TGraphAsymmErrors(jetPt_hadronFlavorBtagAlgo_passed,jetPt_BtagAlgo_total);
  jetBtagAlgoPurity_pt.Write("jetBtagAlgoPurity_pt");
  TGraphAsymmErrors jetBtagPurity_Eta = TGraphAsymmErrors(jetEta_hadronFlavorBtag_passed,jetEta_Btag_total);
  jetBtagPurity_Eta.Write("jetBtagPurity_Eta");
  TGraphAsymmErrors jetBtagAlgoPurity_Eta = TGraphAsymmErrors(jetEta_hadronFlavorBtagAlgo_passed,jetEta_BtagAlgo_total);
  jetBtagAlgoPurity_Eta.Write("jetBtagAlgoPurity_Eta");
  //muon matching efficiency
  TGraphAsymmErrors muonMatchEff_pt = TGraphAsymmErrors(MuonParticlePt_passed,MuonParticlePt_total);
  muonMatchEff_pt.Write("muonMatchEff_pt");
  TGraphAsymmErrors muonMatchEff_eta = TGraphAsymmErrors(MuonParticleEta_passed,MuonParticleEta_total);
  muonMatchEff_eta.Write("muonMatchEff_eta");
  //electron matching efficiency
  TGraphAsymmErrors elecMatchEff_pt = TGraphAsymmErrors(ElecParticlePt_passed,ElecParticlePt_total);
  elecMatchEff_pt.Write("elecMatchEff_pt");
  TGraphAsymmErrors elecMatchEff_eta = TGraphAsymmErrors(ElecParticleEta_passed,ElecParticleEta_total);
  elecMatchEff_eta.Write("elecMatchEff_eta");





}  // closing analyze() function

Analysis_Template_MCFastSim::~Analysis_Template_MCFastSim()
{
}

DEFINE_FWK_MODULE(Analysis_Template_MCFastSim);
