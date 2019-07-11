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
#include "TRandom3.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "FastSimAnalysis_LQtoTopMu.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"

using namespace std;

//---------------------------- Constructor Of The Class TriggerTurnOn -------------------------- //
FastSimAnalysis_LQtoTopMu::FastSimAnalysis_LQtoTopMu(edm::ParameterSet const& cfg)
{
  mFileName     = cfg.getParameter<std::string>("filename"); // vector
  mTreeName     = cfg.getParameter<std::string>("treename");
  mDirName      = cfg.getParameter<std::string>("dirname");
  mIsMCarlo     = cfg.getUntrackedParameter<bool>("isMCarlo");
  mElSelection  = cfg.getUntrackedParameter<bool>("ElSelection");
  mMuSelection  = cfg.getUntrackedParameter<bool>("MuSelection");
  mCrossSection = cfg.getUntrackedParameter<double>("CrossSection");
  mIntLumi      = cfg.getUntrackedParameter<double>("IntLumi");
  mTriggers     = cfg.getUntrackedParameter<std::vector<std::string>>("Triggers");

  cout << "      input file: " << mFileName << endl;
  cout << "electron channel: " << mElSelection << endl;
  cout << "    muon channel: " << mMuSelection << endl;
  cout << "   cross section: " << mCrossSection << endl;
}

//------------------------------ Declaration Of The Function beginjob() ------------------------//
void FastSimAnalysis_LQtoTopMu::beginJob()
{
  mInf = TFile::Open(mFileName.c_str());
  mDir = (TDirectoryFile*) mInf->Get(mDirName.c_str());
  mTree = (TTree*) mInf->Get(mTreeName.c_str());

  /*
  ██████   ██████   ██████  ██   ██     ██   ██ ██ ███████ ████████  ██████   ██████  ██████   █████  ███    ███ ███████
  ██   ██ ██    ██ ██    ██ ██  ██      ██   ██ ██ ██         ██    ██    ██ ██       ██   ██ ██   ██ ████  ████ ██
  ██████  ██    ██ ██    ██ █████       ███████ ██ ███████    ██    ██    ██ ██   ███ ██████  ███████ ██ ████ ██ ███████
  ██   ██ ██    ██ ██    ██ ██  ██      ██   ██ ██      ██    ██    ██    ██ ██    ██ ██   ██ ██   ██ ██  ██  ██      ██
  ██████   ██████   ██████  ██   ██     ██   ██ ██ ███████    ██     ██████   ██████  ██   ██ ██   ██ ██      ██ ███████
  */
  // number of events after cuts
  N_noCuts    = fs->make<TH1D>("N_noCuts","N_noCuts",1,0.5,1.5);
  N_preSel    = fs->make<TH1D>("N_preSel","N_preSel",1,0.5,1.5);
  N_bTag      = fs->make<TH1D>("N_bTag","N_bTag",1,0.5,1.5);
  N_invMuMass = fs->make<TH1D>("N_invMuMass","N_invMuMass",1,0.5,1.5);
  N_STlep     = fs->make<TH1D>("N_STlep","N_STlep",1,0.5,1.5);
  N_catA      = fs->make<TH1D>("N_catA","N_catA",1,0.5,1.5);
  N_catAmu    = fs->make<TH1D>("N_catAmu","N_catAmu",1,0.5,1.5);
  N_catAel    = fs->make<TH1D>("N_catAel","N_catAel",1,0.5,1.5);
  N_catB      = fs->make<TH1D>("N_catB","N_catB",1,0.5,1.5);


  // RECO level
  // jets
  N_jets        = fs->make<TH1F>("N_jets","N_jets",20,0.,20.);
  pT_jets       = fs->make<TH1F>("pT_jets","pT_jets",50,20,1500.);                   pT_jets->Sumw2();
  eta_jets      = fs->make<TH1F>("eta_jets","eta_jets",25,-2.5,2.5);                 eta_jets->Sumw2();
  phi_jets      = fs->make<TH1F>("phi_jets","phi_jets",60,-TMath::Pi(),TMath::Pi()); phi_jets->Sumw2();
  m_jets        = fs->make<TH1F>("m_jets","m_jets",50,0.,500.);                      m_jets->Sumw2();
  bTag_jets     = fs->make<TH1F>("bTag_jets","bTag_jets",100,0.,10.);
  bTagAlgo_jets = fs->make<TH1F>("bTagAlgo_jets","bTagAlgo_jets",100,0.,10.);
  flavor_jets   = fs->make<TH1F>("flavor_jets","flavor_jets",250,0.,25.);
  // muons
  N_mus             = fs->make<TH1F>("N_mus","N_mus",10,0.,10.);
  pT_mus            = fs->make<TH1F>("pT_mus","pT_mus",50,0.,1500.);                      pT_mus->Sumw2();
  eta_mus           = fs->make<TH1F>("eta_mus","eta_mus",25,-2.5,2.5);                    eta_mus->Sumw2();
  phi_mus           = fs->make<TH1F>("phi_mus","phi_mus",60,-TMath::Pi(),TMath::Pi());    phi_mus->Sumw2();
  charge_mus        = fs->make<TH1F>("charge_mus","charge_mus",40,-2.,2.);                charge_mus->Sumw2();
  isoVar_mus        = fs->make<TH1F>("isoVar_mus","isoVar_mus",150,0.,0.15);               isoVar_mus->Sumw2();
  isoVarRhoCorr_mus = fs->make<TH1F>("isoVarRhoCorr_mus","isoVarRhoCorr_mus",150,0.,0.15); isoVarRhoCorr_mus->Sumw2();
  // electrons
  N_els             = fs->make<TH1F>("N_els","N_els",5,0.,5.);
  pT_els            = fs->make<TH1F>("pT_els","pT_els",100,0.,1000.);                     pT_els->Sumw2();
  eta_els           = fs->make<TH1F>("eta_els","eta_els",60,-3.,3);                       eta_els->Sumw2();
  phi_els           = fs->make<TH1F>("phi_els","phi_els",60,-TMath::Pi(),TMath::Pi());    phi_els->Sumw2();
  charge_els        = fs->make<TH1F>("charge_els","charge_els",40,-2.,2.);                charge_els->Sumw2();
  isoVar_els        = fs->make<TH1F>("isoVar_els","isoVar_els",150,0.,0.15);               isoVar_els->Sumw2();
  isoVarRhoCorr_els = fs->make<TH1F>("isoVarRhoCorr_els","isoVarRhoCorr_els",150,0.,0.15); isoVarRhoCorr_els->Sumw2();
  // MET
  ETmiss     = fs->make<TH1F>("ETmiss","ETmiss",50,0.,2000.);                         ETmiss->Sumw2();
  phi_ETmiss = fs->make<TH1F>("phi_ETmiss","phi_ETmiss",60,-TMath::Pi(),TMath::Pi()); phi_ETmiss->Sumw2();
  // CAT A
  M_Ws = fs->make<TH1F>("M_Ws","M_Ws",100,0.,200.); M_Ws->Sumw2();
  double binsMLQ[7] = {0,250,350,450,600,750,1000};
  M_LQs_binArne = fs->make<TH1F>("M_LQs_binArne","M_LQs_binArne",6,binsMLQ); M_LQs_binArne->Sumw2();
  M_LQs         = fs->make<TH1F>("M_LQs","M_LQs",60,0.,3000.);               M_LQs->Sumw2();
  M_LQs_had     = fs->make<TH1F>("M_LQs_had","M_LQs_had",60,0.,3000.);       M_LQs_had->Sumw2();
  M_LQs_lep     = fs->make<TH1F>("M_LQs_lep","M_LQs_lep",60,0.,3000.);       M_LQs_lep->Sumw2();
  pT_LQs        = fs->make<TH1F>("pT_LQs","pT_LQs",60,0.,3000.);             pT_LQs->Sumw2();
  eta_LQs       = fs->make<TH1F>("eta_LQs","eta_LQs",60,-3.,3);              eta_LQs->Sumw2();
  // TODO: add phi
  m_tops     = fs->make<TH1F>("m_tops","m_tops",50,0.,1000.);         m_tops->Sumw2();
  m_tops_lep = fs->make<TH1F>("m_tops_lep","m_tops_lep",50,0.,1000.); m_tops_lep->Sumw2();
  m_tops_had = fs->make<TH1F>("m_tops_had","m_tops_had",50,0.,1000.); m_tops_had->Sumw2();
  pT_tops    = fs->make<TH1F>("pT_tops","pT_tops",50,0.,2000.);       pT_tops->Sumw2();
  eta_tops   = fs->make<TH1F>("eta_tops","eta_tops",30,-3.,3.);       eta_tops->Sumw2();
  // TODO: add phi
  chiSquare = fs->make<TH1F>("chiSquare","chiSquare",200,0.,2000.); chiSquare->Sumw2();
  // CAT B
  double binsST[16] = {0,175,350,525,700,875,1050,1225,1400,1575,1750,1925,2100,2450,2800,3000};
  ST_binArne = fs->make<TH1F>("ST_binArne","ST_binArne",15,binsST); ST_binArne->Sumw2();
  ST         = fs->make<TH1F>("ST","ST",50,0.,7000.);               ST->Sumw2();

  // resolutions
  pTresolution_jets = fs->make<TH1F>("pTresolution_jets","pTresolution_jets",200,-1.,1.); pTresolution_jets->Sumw2();
  pTresolution_mus  = fs->make<TH1F>("pTresolution_mus","pTresolution_mus",200,-1.,1.);   pTresolution_mus->Sumw2();
  pTresolution_els  = fs->make<TH1F>("pTresolution_els","pTresolution_els",200,-1.,1.);   pTresolution_els->Sumw2();

  // isolation efficiencies
  N_mus_iso        = fs->make<TH1F>("N_mus_iso","N_mus_iso",1,0.,1.);
  double bins_pT_mu_iso[7] = {30,40,50,60,120,200,1000};
  pT_mus_iso       = fs->make<TH1F>("pT_mus_iso","pT_mus_iso",6,bins_pT_mu_iso);
  pT_mus_iso_total = fs->make<TH1F>("pT_mus_iso_total","pT_mus_iso_total",6,bins_pT_mu_iso);

  N_els_iso        = fs->make<TH1F>("N_els_iso","N_els_iso",1,0.,1.);
  double bins_pT_el_iso[3] = {0,200,2000};
  pT_els_iso       = fs->make<TH1F>("pT_els_iso","pT_els_iso",2,bins_pT_el_iso);
  pT_els_iso_total = fs->make<TH1F>("pT_els_iso_total","pT_els_iso_total",2,bins_pT_el_iso);

  // btag efficiencies
  double bins_pT_btag[5] = {0,50,200,500,1000};
  pT_btag1     = fs->make<TH1F>("pT_btag1","pT_btag1",4,bins_pT_btag);
  pT_btag2     = fs->make<TH1F>("pT_btag2","pT_btag2",4,bins_pT_btag);
  pT_btag3     = fs->make<TH1F>("pT_btag3","pT_btag3",4,bins_pT_btag);
  pT_btag4     = fs->make<TH1F>("pT_btag4","pT_btag4",4,bins_pT_btag);
  pT_btag5     = fs->make<TH1F>("pT_btag5","pT_btag5",4,bins_pT_btag);
  pT_btag6     = fs->make<TH1F>("pT_btag6","pT_btag6",4,bins_pT_btag);
  pT_btag7     = fs->make<TH1F>("pT_btag7","pT_btag7",4,bins_pT_btag);
  pT_btag_real = fs->make<TH1F>("pT_btag_real","pT_btag_real",4,bins_pT_btag);

  // GEN level
  // jets
  N_GENjets    = fs->make<TH1F>("N_GENjets","N_GENjets",20,0,20);
  pT_GENjets   = fs->make<TH1F>("pT_GENjets","pT_GENjets",500,0.,2000);                   pT_GENjets->Sumw2();
  eta_GENjets  = fs->make<TH1F>("eta_GENjets","eta_GENjets",100,-5,5);                    eta_GENjets->Sumw2();
  phi_GENjets  = fs->make<TH1F>("phi_GENjets","phi_GENjets",25,-TMath::Pi(),TMath::Pi()); phi_GENjets->Sumw2();
  m_GENjets    = fs->make<TH1F>("m_GENjets","m_GENjets",100,0,500);                       m_GENjets->Sumw2();

  // muons
  N_GENmus              = fs->make<TH1F>("N_GENmus","N_GENmus",10,0,10);
  pT_GENmus             = fs->make<TH1F>("pT_GENmus","pT_GENmus",250,0,1000);                         pT_GENmus->Sumw2();
  pT_GENmus_leadingMu   = fs->make<TH1F>("pT_GENmus_leadingMu","pT_GENmus_leadingMu",250,0,1000);     pT_GENmus_leadingMu->Sumw2();
  pT_GENmus_fromLQdecay = fs->make<TH1F>("pT_GENmus_fromLQdecay","pT_GENmus_fromLQdecay",250,0,1000); pT_GENmus_fromLQdecay->Sumw2();
  eta_GENmus            = fs->make<TH1F>("eta_GENmus","eta_GENmus",100,-5,5);                         eta_GENmus->Sumw2();
  phi_GENmus            = fs->make<TH1F>("phi_GENmus","phi_GENmus",25,-TMath::Pi(),TMath::Pi());      phi_GENmus->Sumw2();
  m_GENmus              = fs->make<TH1F>("m_GENmus","m_GENmus",100,0,1);                              m_GENmus->Sumw2();
  // electrons
  N_GENels   = fs->make<TH1F>("N_GENels","N_GENels",5,0,5);
  pT_GENels  = fs->make<TH1F>("pT_GENels","pT_GENels",250,0,1000);                    pT_GENels->Sumw2();
  eta_GENels = fs->make<TH1F>("eta_GENels","eta_GENels",100,-5,5);                    eta_GENels->Sumw2();
  phi_GENels = fs->make<TH1F>("phi_GENels","phi_GENels",25,-TMath::Pi(),TMath::Pi()); phi_GENels->Sumw2();
  m_GENels   = fs->make<TH1F>("m_GENels","m_GENels",100,0,.01);                       m_GENels->Sumw2();
  // tops
  N_GENtops   = fs->make<TH1F>("N_GENtops","N_GENtops",5,0.,5.);
  pT_GENtops  = fs->make<TH1F>("pT_GENtops","pT_GENtops",500,0,2000);                    pT_GENtops->Sumw2();
  eta_GENtops = fs->make<TH1F>("eta_GENtops","eta_GENtops",100,-5,5);                    eta_GENtops->Sumw2();
  phi_GENtops = fs->make<TH1F>("phi_GENtops","phi_GENtops",25,-TMath::Pi(),TMath::Pi()); phi_GENtops->Sumw2();
  m_GENtops   = fs->make<TH1F>("m_GENtops","m_GENtops",1000,150,200);                    m_GENtops->Sumw2();
  // LQs
  N_GENLQs   = fs->make<TH1F>("N_GENLQs","N_GENLQs",5,0.,5.);
  pT_GENLQs  = fs->make<TH1F>("pT_GENLQs","pT_GENLQs",1000,0,2000);                   pT_GENLQs->Sumw2();
  eta_GENLQs = fs->make<TH1F>("eta_GENLQs","eta_GENLQs",1000,-5,5);                   eta_GENLQs->Sumw2();
  phi_GENLQs = fs->make<TH1F>("phi_GENLQs","phi_GENLQs",25,-TMath::Pi(),TMath::Pi()); phi_GENLQs->Sumw2();
  M_GENLQs   = fs->make<TH1F>("M_GENLQs","M_GENLQs",30000,0,1650);                    M_GENLQs->Sumw2();
  // MET
  GENETmiss     = fs->make<TH1F>("GENETmiss","GENETmiss",50,0.,2000.);                         GENETmiss->Sumw2();
  phi_GENETmiss = fs->make<TH1F>("phi_GENETmiss","phi_GENETmiss",60,-TMath::Pi(),TMath::Pi()); phi_GENETmiss->Sumw2();
}


//------------------------ endjob() function declaration ---------------------- //
void FastSimAnalysis_LQtoTopMu::endJob()
{
  mInf->Close();
}

//--------------------------- analyze() fuction declaration ------------------ //
void FastSimAnalysis_LQtoTopMu::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup)
{
  /*
  ██████  ███████  █████  ██████      ██ ███    ██     ████████ ██████  ███████ ███████
  ██   ██ ██      ██   ██ ██   ██     ██ ████   ██        ██    ██   ██ ██      ██
  ██████  █████   ███████ ██   ██     ██ ██ ██  ██        ██    ██████  █████   █████
  ██   ██ ██      ██   ██ ██   ██     ██ ██  ██ ██        ██    ██   ██ ██      ██
  ██   ██ ███████ ██   ██ ██████      ██ ██   ████        ██    ██   ██ ███████ ███████
  */

  unsigned NEntries = mTree->GetEntries();
  int N_filesAdded = 10; // !
  cout << "Reading TREE: " << NEntries << " events" <<endl;
  int decade = 0;
  float hweight = 1.;  //Initial value set to one

  // RECO level
  // jets
  std::vector<float>* jetPt_       = 0;
  std::vector<float>* jetEta_      = 0;
  std::vector<float>* jetPhi_      = 0;
  std::vector<float>* jetMass_     = 0;
  std::vector<float>* jetBtag_     = 0;
  std::vector<float>* jetBtagAlgo_ = 0;
  std::vector<float>* jetFlavor_   = 0;
  mTree->SetBranchAddress("jetPt",  &jetPt_);
  mTree->SetBranchAddress("jetEta", &jetEta_);
  mTree->SetBranchAddress("jetPhi", &jetPhi_);
  mTree->SetBranchAddress("jetMass",&jetMass_);
  mTree->SetBranchAddress("jetBtag",&jetBtag_);
  mTree->SetBranchAddress("jetBtagAlgo",&jetBtagAlgo_);
  mTree->SetBranchAddress("jetFlavorHadron",&jetFlavor_);
  // muons
  std::vector<float>* muonPt_            = 0;
  std::vector<float>* muonEta_           = 0;
  std::vector<float>* muonPhi_           = 0;
  std::vector<int>*   muonCharge_        = 0;
  std::vector<float>* muonIsoVar_        = 0;
  std::vector<float>* muonIsoVarRhoCorr_ = 0;
  mTree->SetBranchAddress("muonPt",           &muonPt_);
  mTree->SetBranchAddress("muonEta",          &muonEta_);
  mTree->SetBranchAddress("muonPhi",          &muonPhi_);
  mTree->SetBranchAddress("muonCharge",       &muonCharge_);
  mTree->SetBranchAddress("muonIsoVar",       &muonIsoVar_);
  mTree->SetBranchAddress("muonIsoVarRhoCorr",&muonIsoVarRhoCorr_);

  const double M_muon = 0.1056583715; //in GeV
  // electrons
  std::vector<float>* elecPt_            = 0;
  std::vector<float>* elecEta_           = 0;
  std::vector<float>* elecPhi_           = 0;
  std::vector<int>*   elecCharge_        = 0;
  std::vector<float>* elecIsoVar_        = 0;
  std::vector<float>* elecIsoVarRhoCorr_ = 0;
  mTree->SetBranchAddress("elecPt",           &elecPt_);
  mTree->SetBranchAddress("elecEta",          &elecEta_);
  mTree->SetBranchAddress("elecPhi",          &elecPhi_);
  mTree->SetBranchAddress("elecCharge",       &elecCharge_);
  mTree->SetBranchAddress("elecIsoVar",       &elecIsoVar_);
  mTree->SetBranchAddress("elecIsoVarRhoCorr",&elecIsoVarRhoCorr_);
  const double elecMass = 0.000510998928;
  // MET (eta is not meaningful since it's boosted!)
  float MET;
  float METphi;
  mTree->SetBranchAddress("MET",&MET);
  mTree->SetBranchAddress("METphi",&METphi);
  // W mass
  const double massW = 80.385;

  // GEN level
  // jets
  std::vector<float>* GenJetPt_   = 0;
  std::vector<float>* GenJetEta_  = 0;
  std::vector<float>* GenJetPhi_  = 0;
  std::vector<float>* GenJetMass_ = 0;
  mTree->SetBranchAddress("GenJetPt",  &GenJetPt_);
  mTree->SetBranchAddress("GenJetEta", &GenJetEta_);
  mTree->SetBranchAddress("GenJetPhi", &GenJetPhi_);
  mTree->SetBranchAddress("GenJetMass",&GenJetMass_);
  // muons
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
  // electrons -> select via pdgID == +/- 11
  std::vector<float>* GenParticlePt_   = 0;
  std::vector<float>* GenParticleEta_  = 0;
  std::vector<float>* GenParticlePhi_  = 0;
  std::vector<int>*   GenParticleId_ = 0;
  std::vector<float>* GenParticleMass_ = 0;
  mTree->SetBranchAddress("GenParticlePt",  &GenParticlePt_);
  mTree->SetBranchAddress("GenParticleEta" ,&GenParticleEta_);
  mTree->SetBranchAddress("GenParticlePhi", &GenParticlePhi_);
  mTree->SetBranchAddress("GenParticleId",  &GenParticleId_);
  mTree->SetBranchAddress("GenParticleMass",&GenParticleMass_);
  // tops
  std::vector<float>* TopParticlePt_   = 0;
  std::vector<float>* TopParticleEta_  = 0;
  std::vector<float>* TopParticlePhi_  = 0;
  std::vector<int>*   TopParticleId_ = 0;
  std::vector<float>* TopParticleMass_ = 0;
  mTree->SetBranchAddress("TopParticlePt",  &TopParticlePt_);
  mTree->SetBranchAddress("TopParticleEta", &TopParticleEta_);
  mTree->SetBranchAddress("TopParticlePhi", &TopParticlePhi_);
  mTree->SetBranchAddress("TopParticleId",  &TopParticleId_);
  mTree->SetBranchAddress("TopParticleMass",&TopParticleMass_);
  // LQs
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
  // MET
  float GenMET    = 0;
  float GenMETphi = 0;
  mTree->SetBranchAddress("GenMET",  &GenMET);
  mTree->SetBranchAddress("GenMETphi",  &GenMETphi);

  // counter for isolation study
  int N_mu_total = 0;
  int N_mu_iso   = 0;
  int N_el_total = 0;
  int N_el_iso   = 0;

  for(unsigned  l=0; l<NEntries; l++)
  {
    //----------- progress report -------------
    double progress = 10.0 * l / (1.0 * NEntries);
    int k = TMath::FloorNint(progress);
    if(k > decade)
    {
      cout << 10*k << " %" << endl;
    }
    decade = k;

    // READ THE EVENT
    mTree->GetEntry(l);
    if(mIsMCarlo) hweight = (mCrossSection / (NEntries * N_filesAdded)) * 35867; // compute weighted # of events (L_int is 35867 pb-1 for 2016)
    N_noCuts->Fill(1.0);

    // NUMBER OF PARTICLES
    const int nJets_  = jetPt_ ->size();
    const int nMuons_ = muonPt_->size();
    const int nElecs_ = elecPt_->size();

    /*
    ██████  ██████  ███████     ███████ ███████ ██      ███████  ██████ ████████ ██  ██████  ███    ██
    ██   ██ ██   ██ ██          ██      ██      ██      ██      ██         ██    ██ ██    ██ ████   ██
    ██████  ██████  █████ █████ ███████ █████   ██      █████   ██         ██    ██ ██    ██ ██ ██  ██
    ██      ██   ██ ██               ██ ██      ██      ██      ██         ██    ██ ██    ██ ██  ██ ██
    ██      ██   ██ ███████     ███████ ███████ ███████ ███████  ██████    ██    ██  ██████  ██   ████
    */

    // cout << "2" << endl;
    // JETS
    vector<float> pT_jet;
    vector<float> eta_jet;
    vector<float> phi_jet;
    vector<float> M_jet;
    vector<float> bTag_jet;
    vector<float> bTagAlgo_jet;
    vector<float> flavor_jet;
    int nJets = 0;
    int counterBTag = 0;
    double STjet = 0.0;
    for(int i=0; i<nJets_; i++)
    {
      if(jetPt_->at(i) >= 30. && abs(jetEta_->at(i)) <= 2.4) // pT & eta cut
      {
        nJets++;
        pT_jet.push_back(jetPt_->at(i));
        eta_jet.push_back(jetEta_->at(i));
        phi_jet.push_back(jetPhi_->at(i));
        M_jet.push_back(jetMass_->at(i));
        bTag_jet.push_back(jetBtag_->at(i));
        bTagAlgo_jet.push_back(jetBtagAlgo_->at(i));
        flavor_jet.push_back(jetFlavor_->at(i));

        STjet += jetPt_->at(i);
        if(jetBtag_->at(i) >= 1) counterBTag++;

        // btag efficiencies
        if(jetBtag_->at(i) >= 1) pT_btag1->Fill(jetPt_->at(i));
        if(jetBtag_->at(i) >= 2) pT_btag2->Fill(jetPt_->at(i));
        if(jetBtag_->at(i) >= 3) pT_btag3->Fill(jetPt_->at(i));
        if(jetBtag_->at(i) >= 4) pT_btag4->Fill(jetPt_->at(i));
        if(jetBtag_->at(i) >= 5) pT_btag5->Fill(jetPt_->at(i));
        if(jetBtag_->at(i) >= 6) pT_btag6->Fill(jetPt_->at(i));
        if(jetBtag_->at(i) >= 7) pT_btag7->Fill(jetPt_->at(i));
        if(jetFlavor_->at(i) == 5) pT_btag_real->Fill(jetPt_->at(i));
      }
    }
    // cout << "3" << endl;
    // MUONS
    vector<float> pT_mu;
    vector<float> eta_mu;
    vector<float> phi_mu;
    vector<int>   charge_mu;

    double STmu = 0.0;
    int N_mu   = 0;
    int N_muPlus  = 0;
    int N_muMinus = 0;
    bool passInvM_mumu = true;
    // for tight muons (https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2)

    for(int i=0; i<nMuons_; i++)
    {
      if(muonPt_->at(i) >= 30. && abs(muonEta_->at(i)) <= 2.4) //pT & eta cut
      {
        bool isMuonIsolated = true;
        N_mu_total++;
        pT_mus_iso_total ->Fill(muonPt_->at(i));
        isoVar_mus       ->Fill(muonIsoVar_->at(i));
        isoVarRhoCorr_mus->Fill(muonIsoVarRhoCorr_->at(i));

        if(muonIsoVar_->at(i) > 0.02) isMuonIsolated = false;
        if(!isMuonIsolated) continue; // ensures muon isolation

        N_mu++;
        N_mu_iso++;
        pT_mus_iso->Fill(muonPt_->at(i));

        pT_mu.push_back(muonPt_->at(i));
        eta_mu.push_back(muonEta_->at(i));
        phi_mu.push_back(muonPhi_->at(i));
        charge_mu.push_back(muonCharge_->at(i));
      }
    }
    // cout << "4" << endl;
    for(int i=0; i<N_mu; i++)
    {
      STmu += pT_mu.at(i);

      if(charge_mu.at(i) == -1) N_muMinus++;
      else if(charge_mu.at(i) == +1) N_muPlus++;

      for(int j=0; j<N_mu; j++) // invariant mass selection of muon pairs
      {
        if(j > i)
        {
          TLorentzVector muoni;
          muoni.SetPtEtaPhiM(pT_mu.at(i),eta_mu.at(i),phi_mu.at(i),M_muon);
          TLorentzVector muonj;
          muonj.SetPtEtaPhiM(pT_mu.at(j),eta_mu.at(j),phi_mu.at(j),M_muon);
          double invM_mumu = (muoni + muonj).M();
          if(invM_mumu < 111.) passInvM_mumu = false;
        }
      }
    }
    // cout << "5" << endl;
    // ELECTRONS
    double STel = 0.0;
    int N_el = 0;
    vector<float> pT_el;
    vector<float> eta_el;
    vector<float> phi_el;
    vector<int>   charge_el;

    for(int i=0; i<nElecs_; i++)
    {
      if(elecPt_->at(i) >= 30. && abs(elecEta_->at(i)) <= 2.4) // pT & eta cut
      {
        bool isElecIsolated = true;
        N_el_total++;
        pT_els_iso_total ->Fill(elecPt_->at(i));
        isoVar_els       ->Fill(elecIsoVar_->at(i));
        isoVarRhoCorr_els->Fill(elecIsoVarRhoCorr_->at(i));

        if(elecIsoVar_->at(i) > 0.02) isElecIsolated = false;

        if(!isElecIsolated) continue; // ensures electron isolation

        N_el++;
        N_el_iso++;
        pT_els_iso->Fill(elecPt_->at(i));

        pT_el.push_back(elecPt_->at(i));
        eta_el.push_back(elecEta_->at(i));
        phi_el.push_back(elecPhi_->at(i));
        charge_el.push_back(elecCharge_->at(i));
        STel += elecPt_->at(i);
      }
    }
    // cout << "6" << endl;
    bool selectionPass = false;

    /*
    ███████ ██    ██ ██      ██          ███████ ███████ ██      ███████  ██████ ████████ ██  ██████  ███    ██
    ██      ██    ██ ██      ██          ██      ██      ██      ██      ██         ██    ██ ██    ██ ████   ██
    █████   ██    ██ ██      ██          ███████ █████   ██      █████   ██         ██    ██ ██    ██ ██ ██  ██
    ██      ██    ██ ██      ██               ██ ██      ██      ██      ██         ██    ██ ██    ██ ██  ██ ██
    ██       ██████  ███████ ███████     ███████ ███████ ███████ ███████  ██████    ██    ██  ██████  ██   ████
    */

    if(nJets >= 2 && N_mu >= 2 && STmu+STel+STjet+MET > 350.) // PRE-SELECTION
    {
      N_preSel->Fill(1.0);
      if(counterBTag >= 1) // >=1 b-tag
      {
        N_bTag->Fill(1.0);
        if(passInvM_mumu == true) // invariant mass selection of muon pairs -> reduces DY background
        {
          N_invMuMass->Fill(1.0);
          if(STmu+STel > 200.) // STlep > 200 GeV
          {
            N_STlep->Fill(1.0);
            selectionPass = true;

            //FILL DET MU HISTOGRAMS
            N_mus->Fill(N_mu);
            for(int i=0; i<N_mu; i++)
            {
              pT_mus        ->Fill(pT_mu .at(i),hweight);
              phi_mus       ->Fill(phi_mu.at(i),hweight);
              eta_mus       ->Fill(eta_mu.at(i),hweight);
              charge_mus    ->Fill(charge_mu.at(i),hweight);
            }
            //Fill DET ELEC HISTOGRAMS
            N_els->Fill(N_el);
            for(int i=0; i<N_el; i++)
            {
              pT_els ->Fill(pT_el .at(i),hweight);
              phi_els->Fill(phi_el.at(i),hweight);
              eta_els->Fill(eta_el.at(i),hweight);
              charge_els->Fill(charge_el.at(i),hweight);
            }
            //FILL JET HISTOGRAMS
            N_jets->Fill(nJets);
            for(int i=0; i<nJets; i++)
            {
              pT_jets      ->Fill(pT_jet.at(i),hweight);
              eta_jets     ->Fill(eta_jet.at(i),hweight);
              phi_jets     ->Fill(phi_jet.at(i),hweight);
              m_jets       ->Fill(M_jet.at(i),hweight);
              bTag_jets    ->Fill(bTag_jet.at(i),hweight);
              bTagAlgo_jets->Fill(bTagAlgo_jet.at(i),hweight);
              flavor_jets  ->Fill(flavor_jet.at(i),hweight);
            }
            // FILL MET HISTOGRAMS
            ETmiss->Fill(MET,hweight);
            phi_ETmiss->Fill(METphi,hweight);
          }
        }
      }
    }
    // cout << "7" << endl;
    /*
    ██████  ██       ██████  ████████ ███████
    ██   ██ ██      ██    ██    ██    ██
    ██████  ██      ██    ██    ██    ███████
    ██      ██      ██    ██    ██         ██
    ██      ███████  ██████     ██    ███████
    */
    // JETS
    N_GENjets->Fill(GenJetPt_->size());
    for(unsigned int i=0; i<GenJetPt_->size(); i++)
    {
      pT_GENjets ->Fill(GenJetPt_  ->at(i),hweight);
      eta_GENjets->Fill(GenJetEta_ ->at(i),hweight);
      phi_GENjets->Fill(GenJetPhi_ ->at(i),hweight);
      m_GENjets  ->Fill(GenJetMass_->at(i),hweight);

      for(unsigned int j=0; j<jetPt_->size(); j++)
      {
        if(DeltaRFSA(GenJetEta_->at(i),GenJetPhi_->at(i),jetEta_->at(j),jetPhi_->at(j)) < 0.1)
        {
          double resolution = (GenJetPt_->at(i) - jetPt_->at(j)) / GenJetPt_->at(i);
          pTresolution_jets->Fill(resolution);
        }
      }
    }
    // cout << "8" << endl;
    // MUONS
    N_GENmus->Fill(MuonParticlePt_->size());
    for(unsigned int i=0; i<MuonParticlePt_->size(); i++)
    {
      pT_GENmus->Fill(MuonParticlePt_->at(i),hweight);
      pT_GENmus_leadingMu->Fill(MuonParticlePt_->at(0),hweight);
      if(MuonParticleStatus_->at(i) == 23) pT_GENmus_fromLQdecay->Fill(MuonParticlePt_->at(i),hweight);
      eta_GENmus->Fill(MuonParticleEta_->at(i),hweight);
      phi_GENmus->Fill(MuonParticlePhi_->at(i),hweight);
      m_GENmus->Fill(MuonParticleMass_->at(i),hweight);

      for(unsigned int j=0; j<muonPt_->size(); j++)
      {
        if(DeltaRFSA(MuonParticleEta_->at(i),MuonParticlePhi_->at(i),muonEta_->at(j),muonPhi_->at(j)) < 0.1)
        {
          double resolution = (MuonParticlePt_->at(i) - muonPt_->at(j)) / MuonParticlePt_->at(i);
          pTresolution_mus->Fill(resolution);
        }
      }
    }
    // cout << "9" << endl;
    // electrons
    int nGENels = 0;
    for(unsigned int i=0; i<GenParticlePt_->size(); i++)
    {
      if(abs(GenParticleId_->at(i)) == 11)
      {
        nGENels++;
        pT_GENels ->Fill(GenParticlePt_  ->at(i),hweight);
        eta_GENels->Fill(GenParticleEta_ ->at(i),hweight);
        phi_GENels->Fill(GenParticlePhi_ ->at(i),hweight);
        m_GENels  ->Fill(GenParticleMass_->at(i),hweight);

        for(unsigned int j=0; j<elecPt_->size(); j++)
        {
          if(DeltaRFSA(GenParticleEta_->at(i),GenParticlePhi_->at(i),elecEta_->at(j),elecPhi_->at(j)) < 0.1)
          {
            double resolution = (GenParticlePt_->at(i) - elecPt_->at(j)) / GenParticlePt_->at(i);
            pTresolution_els->Fill(resolution);
          }
        }
      }
    }
    N_GENels->Fill(nGENels);
    // cout << "10" << endl;
    // tops
    N_GENtops->Fill(TopParticlePt_->size());
    for(unsigned int i=0; i<TopParticlePt_->size(); i++)
    {
      pT_GENtops ->Fill(TopParticlePt_  ->at(i),hweight);
      eta_GENtops->Fill(TopParticleEta_ ->at(i),hweight);
      phi_GENtops->Fill(TopParticlePhi_ ->at(i),hweight);
      m_GENtops  ->Fill(TopParticleMass_->at(i),hweight);
    }
    // cout << "11" << endl;
    // LQs
    N_GENLQs->Fill(LeptoQuarkParticlePt_->size());
    for(unsigned int i=0; i<LeptoQuarkParticleMass_->size(); i++)
    {
      pT_GENLQs ->Fill(LeptoQuarkParticlePt_  ->at(i),hweight);
      eta_GENLQs->Fill(LeptoQuarkParticleEta_ ->at(i),hweight);
      phi_GENLQs->Fill(LeptoQuarkParticlePhi_ ->at(i),hweight);
      M_GENLQs  ->Fill(LeptoQuarkParticleMass_->at(i),hweight);
    }
    // cout << "12" << endl;
    // MET
    GENETmiss    ->Fill(GenMET,hweight);
    phi_GENETmiss->Fill(GenMETphi,hweight);



    // ███    ███  █████  ███████ ███████     ██████  ███████  ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████ ██  ██████  ███    ██
    // ████  ████ ██   ██ ██      ██          ██   ██ ██      ██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██ ██    ██ ████   ██
    // ██ ████ ██ ███████ ███████ ███████     ██████  █████   ██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██ ██    ██ ██ ██  ██
    // ██  ██  ██ ██   ██      ██      ██     ██   ██ ██      ██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██ ██    ██ ██  ██ ██
    // ██      ██ ██   ██ ███████ ███████     ██   ██ ███████  ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██    ██  ██████  ██   ████
    //
    //  ██████  █████  ████████      █████
    // ██      ██   ██    ██        ██   ██
    // ██      ███████    ██        ███████
    // ██      ██   ██    ██        ██   ██
    //  ██████ ██   ██    ██        ██   ██


    if(!selectionPass) continue;  // selection must be passed
    if((N_el >= 1 || N_mu >= 3) && N_muPlus >= 1 && N_muMinus >= 1)  // cat A
    {
      N_catA->Fill(1.0);
      //RECONSTRUCTION OF THE NEUTRINO
      vector <TLorentzVector> addLeptonCandidates;
      if(N_el >= 1 && mElSelection) //there is at least one electron -> reconstruct the semi-leptonic top from the leading electron
      {
        N_catAel->Fill(1.0);
        TLorentzVector addElectron;
        addElectron.SetPtEtaPhiM(pT_el.at(0),eta_el.at(0),phi_el.at(0),elecMass);
        addLeptonCandidates.push_back(addElectron);
      }
      // cout << "13" << endl;
      if(N_el == 0 && N_mu >= 3 && mMuSelection) //there is no electron but at least one additional muon -> reconstruct the semi-leptonic top from the leading additional muon
      {
        N_catAmu->Fill(1.0);
        TLorentzVector addMuon1;
        TLorentzVector addMuon2;
        bool oppositeCharge = false;
        for(int i=0; i<N_mu; i++)
        {
          for(int j=0; j<N_mu; j++)
          {
            if(i<j)
            {
              if(charge_mu.at(i) != charge_mu.at(j)) oppositeCharge = true;
            }
          }
        }
        if(oppositeCharge == true)
        {
          if(charge_mu.at(0) == charge_mu.at(1))
          {
            addMuon1.SetPtEtaPhiM(pT_mu.at(0),eta_mu.at(0),phi_mu.at(0),M_muon);
            addLeptonCandidates.push_back(addMuon1);
            addMuon2.SetPtEtaPhiM(pT_mu.at(1),eta_mu.at(1),phi_mu.at(1),M_muon);
            addLeptonCandidates.push_back(addMuon2);
          }
          else if(charge_mu.at(0) == charge_mu.at(2))
          {
            addMuon1.SetPtEtaPhiM(pT_mu.at(0),eta_mu.at(0),phi_mu.at(0),M_muon);
            addLeptonCandidates.push_back(addMuon1);
            addMuon2.SetPtEtaPhiM(pT_mu.at(2),eta_mu.at(2),phi_mu.at(2),M_muon);
            addLeptonCandidates.push_back(addMuon2);
          }
          else if(charge_mu.at(1) == charge_mu.at(2))
          {
            addMuon1.SetPtEtaPhiM(pT_mu.at(1),eta_mu.at(1),phi_mu.at(1),M_muon);
            addLeptonCandidates.push_back(addMuon1);
            addMuon2.SetPtEtaPhiM(pT_mu.at(2),eta_mu.at(2),phi_mu.at(2),M_muon);
            addLeptonCandidates.push_back(addMuon2);
          }
        }
        else
        {
          addMuon1.SetPtEtaPhiM(pT_mu.at(0),eta_mu.at(0),phi_mu.at(0),M_muon);
          addLeptonCandidates.push_back(addMuon1);
        }
      }
      // cout << "14" << endl;
      double metPx = MET * cos(METphi);
      double metPy = MET * sin(METphi);
      vector <TLorentzVector> neutrinoCandidates;
      vector <TLorentzVector> WCandidates;

      for(unsigned int i=0; i<addLeptonCandidates.size(); i++)
      {
        double mu = massW * massW / 2 + addLeptonCandidates.at(i).Px() * metPx + addLeptonCandidates.at(i).Py() * metPy; //scalar product between lepton and neutrino
        double D  = mu * mu * (addLeptonCandidates.at(i).Pz() * addLeptonCandidates.at(i).Pz() + addLeptonCandidates.at(i).Pt() * addLeptonCandidates.at(i).Pt()) - addLeptonCandidates.at(i).E() * addLeptonCandidates.at(i).E() * MET * MET * addLeptonCandidates.at(i).Pt() * addLeptonCandidates.at(i).Pt();

        if(D <= 0)
        {
          double neutrinoPz = mu * addLeptonCandidates.at(i).Pz() / (addLeptonCandidates.at(i).Pt() * addLeptonCandidates.at(i).Pt());
          double E = TMath::Sqrt(metPx * metPx + metPy * metPy + neutrinoPz * neutrinoPz);
          TLorentzVector solution;
          solution.SetPxPyPzE(metPx,metPy,neutrinoPz,E);
          neutrinoCandidates.push_back(solution);
        }
        else
        {
          double neutrinoPz1 = (mu * addLeptonCandidates.at(i).Pz() + TMath::Sqrt(D)) / (addLeptonCandidates.at(i).Pt() * addLeptonCandidates.at(i).Pt());
          double E1 = TMath::Sqrt(metPx * metPx + metPy * metPy + neutrinoPz1 * neutrinoPz1);
          TLorentzVector solution1;
          solution1.SetPxPyPzE(metPx,metPy,neutrinoPz1,E1);
          neutrinoCandidates.push_back(solution1);
          double neutrinoPz2 = (mu * addLeptonCandidates.at(i).Pz() - TMath::Sqrt(D)) / (addLeptonCandidates.at(i).Pt() * addLeptonCandidates.at(i).Pt());
          double E2 = TMath::Sqrt(metPx * metPx + metPy * metPy + neutrinoPz2 * neutrinoPz2);
          TLorentzVector solution2;
          solution2.SetPxPyPzE(metPx,metPy,neutrinoPz2,E2);
          neutrinoCandidates.push_back(solution2);
        }

        //RECONSTRUCTION OF THE W BOSON
        for(unsigned int j=0; j<neutrinoCandidates.size(); j++)
        {
          WCandidates.push_back(addLeptonCandidates.at(i) + neutrinoCandidates.at(j));
          double WMassReco = WCandidates.at(j).M();
          M_Ws->Fill(WMassReco,hweight);
        }
      }
      // cout << "15" << endl;

      //RECONSTRUCTION OF LEPTON + JETS t tbar SYSTEM
      //store all DetJets
      vector <TLorentzVector> Jet_v4;
      for(int j=0; j<nJets; j++)
      {
        if(j == 7) break; //take the 7 leading jets
        if(pT_jet.at(j) >= 30. && fabs(eta_jet.at(j)) <= 2.4)
        {
          TLorentzVector jet_v4_temp;
          jet_v4_temp.SetPtEtaPhiM(pT_jet.at(j),eta_jet.at(j),phi_jet.at(j),M_jet.at(j));
          Jet_v4.push_back(jet_v4_temp); //all selected jets
        }
      }
      // cout << "16" << endl;
      vector <TLorentzVector> lepTopCandidates;
      vector <TLorentzVector> hadTopCandidates;
      for(unsigned int first=0; first<Jet_v4.size(); first++)
      {
        for(unsigned int i=0; i<WCandidates.size(); i++) //leptonic top
        {
          lepTopCandidates.push_back(WCandidates.at(i) + Jet_v4.at(first)); //single jets
        }
        for(unsigned int second=first+1; second<Jet_v4.size(); second++)
        {
          for(unsigned int i=0; i<WCandidates.size(); i++)
          {
            lepTopCandidates.push_back(WCandidates.at(i) + Jet_v4.at(first) + Jet_v4.at(second));  //dijets
          }
          for(unsigned int third=second+1; third<Jet_v4.size(); third++)  //hadronic top
          {
            hadTopCandidates.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third)); //three jets
            for(unsigned int fourth=third+1; fourth<Jet_v4.size(); fourth++)
            {
              hadTopCandidates.push_back(Jet_v4.at(first) + Jet_v4.at(second) + Jet_v4.at(third) + Jet_v4.at(fourth)); //four jets
              // for(unsigned int fifth=fourth+1; fifth<Jet_v4.size(); fifth++)
              // {
              //
              // }
            }
          }
        }
      }
      // cout << "17" << endl;
      vector <TLorentzVector> lepLQCandidates;
      vector <TLorentzVector> hadLQCandidates;

      if(N_el >= 1 && mElSelection)
      {
        for(int i=0; i<2; i++)  //two leading muons
        {
          if(charge_mu.at(i) != charge_el.at(0))  //OS of mu & e
          {
            for(unsigned int j=0; j<lepTopCandidates.size(); j++)
            {
              TLorentzVector muon_to_associate_v4_temp;
              muon_to_associate_v4_temp.SetPtEtaPhiM(pT_mu.at(i),eta_mu.at(i),phi_mu.at(i),M_muon);
              TLorentzVector LQRecos_v4_temp = lepTopCandidates.at(j) + muon_to_associate_v4_temp;
              lepLQCandidates.push_back(LQRecos_v4_temp);
            }
          }
          //LQ from hadronic top
          else  //SS of mu & e
          {
            for(unsigned int j=0; j<hadTopCandidates.size(); j++)
            {
              TLorentzVector muon_to_associate_v4_temp;
              muon_to_associate_v4_temp.SetPtEtaPhiM(pT_mu.at(i),eta_mu.at(i),phi_mu.at(i),M_muon);
              TLorentzVector LQRecos_v4_temp = hadTopCandidates.at(j) + muon_to_associate_v4_temp;
              hadLQCandidates.push_back(LQRecos_v4_temp);
            }
          }
        }
      }
      // cout << "18" << endl;
      if(N_el == 0 && N_mu >= 3 && mMuSelection)
      {
        for(int l1=0; l1<3; l1++)
        {
          for (int l2 = 0; l2<3; l2++)
          {
            if(l1 == l2) continue;
            if(charge_mu.at(l2) != charge_mu.at(l1)) //LQ from leptonic top
            {
              for(unsigned int j=0; j<lepTopCandidates.size(); j++)
              {
                TLorentzVector muon_to_associate_v4_temp;
                muon_to_associate_v4_temp.SetPtEtaPhiM(pT_mu.at(l2),eta_mu.at(l2),phi_mu.at(l2),M_muon);
                TLorentzVector LQRecos_v4_temp = lepTopCandidates.at(j) + muon_to_associate_v4_temp;
                lepLQCandidates.push_back(LQRecos_v4_temp);
              }
            }
            else //LQ from hadronic top
            {
              for (unsigned int j=0; j<hadTopCandidates.size(); j++)
              {
                TLorentzVector muon_to_associate_v4_temp;
                muon_to_associate_v4_temp.SetPtEtaPhiM(pT_mu.at(l2),eta_mu.at(l2),phi_mu.at(l2),M_muon);
                TLorentzVector LQRecos_v4_temp = hadTopCandidates.at(j) + muon_to_associate_v4_temp;
                hadLQCandidates.push_back(LQRecos_v4_temp);
              }
            }
          }
        }
      }
      // cout << "19" << endl;
      //ONLY IF THERE ARE CANDIDATES -> CHOOSE THE BEST HYPOTHESIS
      if(lepTopCandidates.size() > 0 && hadTopCandidates.size() > 0 && hadLQCandidates.size() > 0 && lepLQCandidates.size() > 0)
      {
        //defintion of the chiSquare
        const double mass_thad = 174.;
        const double mass_thad_sigma = 17.;
        const double mass_tlep = 174.;
        const double mass_tlep_sigma = 23.;
        const double mass_LQ_diff_rel = -0.00132;
        const double mass_LQ_diff_rel_sigma = 0.089;
        double chi2_total = 1.0E+08;

        double Top_Hadr_rec_mass = -10;
        double Top_Lept_rec_mass = -10;
        double LQHadrMass = -10;
        double LQLeptMass = -10;
        double LQHadrPt = -10;
        double LQLeptPt = -10;
        double LQHadrEta = -10;
        double LQLeptEta = -10;
        double Top_Hadr_rec_pt = -10;
        double Top_Lept_rec_pt = -10;
        double Top_Hadr_rec_eta = -10;
        double Top_Lept_rec_eta = -10;

        for(unsigned int j=0; j<lepTopCandidates.size(); j++)
        {
          double chi2_top_lept = pow((lepTopCandidates.at(j).M() - mass_tlep) / mass_tlep_sigma, 2);
          for(unsigned int i=0; i<hadTopCandidates.size(); i++)
          {
            double chi2_thad = pow((hadTopCandidates.at(i).M() - mass_thad) / mass_thad_sigma, 2);
            for(unsigned int t=0; t<hadLQCandidates.size(); t++)
            {
              for(unsigned int g=0; g<lepLQCandidates.size(); g++)
              {
                double chi2_MLQdiff_rel = pow(((hadLQCandidates.at(t).M() - lepLQCandidates.at(g).M()) / ((hadLQCandidates.at(t).M() + lepLQCandidates.at(g).M()) / 2) - mass_LQ_diff_rel) / mass_LQ_diff_rel_sigma, 2);
                double chi2_total_temp = chi2_top_lept + chi2_thad + chi2_MLQdiff_rel;
                if(chi2_total_temp < chi2_total)
                {
                  chi2_total = chi2_total_temp;
                  LQHadrMass = hadLQCandidates.at(t).M();
                  LQLeptMass = lepLQCandidates.at(g).M();
                  LQHadrPt = hadLQCandidates.at(t).Pt();
                  LQLeptPt = lepLQCandidates.at(g).Pt();
                  LQHadrEta = hadLQCandidates.at(t).Eta();
                  LQLeptEta = lepLQCandidates.at(g).Eta();
                  Top_Hadr_rec_mass = hadTopCandidates.at(i).M();
                  Top_Lept_rec_mass = lepTopCandidates.at(j).M();
                  Top_Hadr_rec_pt = hadTopCandidates.at(i).Pt();
                  Top_Lept_rec_pt = lepTopCandidates.at(j).Pt();
                  Top_Hadr_rec_eta = hadTopCandidates.at(i).Eta();
                  Top_Lept_rec_eta = lepTopCandidates.at(j).Eta();
                }
              }
            }
          }
        }
        // cout << "20" << endl;
        //plot top mass and chiSquare
        if(addLeptonCandidates.size() > 0) //gets the right number of entries if one channel is muted
        {
          //NOTE: if nessecary cut here on chi^2
          double AverageMass = (LQHadrMass + LQLeptMass) / 2.;
          if(AverageMass <= 1000.) M_LQs_binArne->Fill(AverageMass,hweight);
          else M_LQs_binArne->AddBinContent(6,hweight);

          if(LQHadrMass <= 3000.) M_LQs->Fill(LQHadrMass,hweight);
          else M_LQs->AddBinContent(150,hweight);
          if(LQLeptMass <= 3000.) M_LQs->Fill(LQLeptMass,hweight);
          else M_LQs->AddBinContent(150,hweight);

          M_LQs_had ->Fill(LQHadrMass,hweight);
          M_LQs_lep ->Fill(LQLeptMass,hweight);
          pT_LQs ->Fill(LQHadrPt,hweight);
          pT_LQs ->Fill(LQLeptPt,hweight);
          eta_LQs->Fill(LQHadrEta,hweight);
          eta_LQs->Fill(LQLeptEta,hweight);
          m_tops_had->Fill(Top_Hadr_rec_mass,hweight);
          m_tops_lep->Fill(Top_Lept_rec_mass,hweight);
          if(Top_Hadr_rec_mass <= 1000.) m_tops->Fill(Top_Hadr_rec_mass,hweight);
          else m_tops->AddBinContent(50,hweight);
          if(Top_Lept_rec_mass <= 1000.) m_tops->Fill(Top_Lept_rec_mass,hweight);
          else m_tops->AddBinContent(50,hweight);
          pT_tops ->Fill(Top_Hadr_rec_pt,hweight);
          pT_tops ->Fill(Top_Lept_rec_pt,hweight);
          eta_tops->Fill(Top_Hadr_rec_eta,hweight);
          eta_tops->Fill(Top_Lept_rec_eta,hweight);
          chiSquare->Fill(chi2_total);
        }
        // cout << "21" << endl;
        //clear all vectors
        hadLQCandidates   .clear();
        lepLQCandidates   .clear();
        hadTopCandidates  .clear();
        lepTopCandidates  .clear();
        Jet_v4            .clear();
        neutrinoCandidates.clear();
        WCandidates       .clear();
      }
    }
    else

    //  ██████  █████  ████████     ██████
    // ██      ██   ██    ██        ██   ██
    // ██      ███████    ██        ██████
    // ██      ██   ██    ██        ██   ██
    //  ██████ ██   ██    ██        ██████

    // cout << "22" << endl;
    {
      N_catB->Fill(1.0);
      //compute and plot ST
      double st = STel + STmu + STjet + MET; //all at DET level
      ST->Fill(st,hweight);
      if(st <= 3000.) ST_binArne->Fill(st,hweight);
      else ST_binArne->AddBinContent(15,hweight);
    }
    // cout << endl;
  } // end of event loop


  // LEPTON ISOLATION
  N_mus_iso->SetBinContent(1, (double) N_mu_iso / (N_mu_total * N_filesAdded));
  N_els_iso->SetBinContent(1, (double) N_el_iso / (N_el_total * N_filesAdded));


  //OUTPUT
  cout << "weight: " << hweight << endl;
  cout << "total cut efficiencies" << endl;
  cout << "       total events: " << N_noCuts->GetBinContent(1) << endl;
  cout << "after pre-selection: " << N_preSel->GetBinContent(1) << endl;
  cout << "    after b-tag cut: " << N_bTag->GetBinContent(1) << endl;
  cout << "   after M_mumu cut: " << N_invMuMass->GetBinContent(1) << endl;
  cout << "    after STlep cut: " << N_STlep->GetBinContent(1) << endl;
  cout << endl;
  cout << "full mass reconstruction" << endl;
  cout << "     events in Cat A: " << N_catA->GetBinContent(1) << endl;
  cout << "events in el channel: " << N_catAel->GetBinContent(1) << endl;
  cout << "events in mu channel: " << N_catAmu->GetBinContent(1) << endl;
  cout << "     events in Cat B: " << N_catB->GetBinContent(1) << endl;

  // // lepton isolation study
  // TGraphAsymmErrors IsoEff_mus_pT = TGraphAsymmErrors(pT_mus_iso,pT_mus_iso_total);
  // IsoEff_mus_pT.Write("IsoEff_mus_pT");
  // TGraphAsymmErrors IsoEff_els_pT = TGraphAsymmErrors(pT_els_iso,pT_els_iso_total);
  // IsoEff_els_pT.Write("IsoEff_els_pT");


}  // closing analyze() function

FastSimAnalysis_LQtoTopMu::~FastSimAnalysis_LQtoTopMu()
{
}

DEFINE_FWK_MODULE(FastSimAnalysis_LQtoTopMu);
