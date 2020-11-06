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


#include "analysis_module.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"


using namespace std;

analysis_module::analysis_module(edm::ParameterSet const& cfg)
{
  mFileName     = cfg.getParameter<std::string>("filename");
  mTreeName     = cfg.getParameter<std::string>("treename");
  mDirName      = cfg.getParameter<std::string>("dirname");
  mIsMCarlo     = cfg.getUntrackedParameter<bool>("isMCarlo");
  mCrossSection = cfg.getUntrackedParameter<double>("CrossSection");
  mIntLumi      = cfg.getUntrackedParameter<double>("IntLumi");
  mTriggers     = cfg.getUntrackedParameter<std::vector<std::string>>("Triggers");
}

void analysis_module::beginJob()
{
  mInf = TFile::Open(mFileName.c_str());
  mTree = (TTree*) mInf->Get(mTreeName.c_str());

  cout << "beginning job..." << endl;
  cout << "input file: " << mFileName.c_str() << endl;
  cout << " tree name: " << mTreeName.c_str() << endl;


  /*
  // ██████   ██████   ██████  ██   ██     ██   ██ ██ ███████ ████████ ███████
  // ██   ██ ██    ██ ██    ██ ██  ██      ██   ██ ██ ██         ██    ██
  // ██████  ██    ██ ██    ██ █████       ███████ ██ ███████    ██    ███████
  // ██   ██ ██    ██ ██    ██ ██  ██      ██   ██ ██      ██    ██         ██
  // ██████   ██████   ██████  ██   ██     ██   ██ ██ ███████    ██    ███████
  */
  cout << "booking hists..." << endl;

  // parton level
  // jets
  N_genjet    = fs->make<TH1F>("N_genjet"   ,"number of jets @ parton level"      ,20,0,20);
  pt_genjet   = fs->make<TH1F>("pt_genjet"  ,"jet p_{T} @ parton level"           ,100,0,1000);
  pt_genjet1  = fs->make<TH1F>("pt_genjet1" ,"leading jet p_{T} @ parton level"   ,100,0,1000);
  pt_genjet2  = fs->make<TH1F>("pt_genjet2" ,"subleading jet p_{T} @ parton level",100,0,1000);
  eta_genjet  = fs->make<TH1F>("eta_genjet" ,"jet #eta @ parton level"            ,200,-6,6);
  phi_genjet  = fs->make<TH1F>("phi_genjet" ,"jet #phi @ parton level"            ,100,-TMath::Pi(),TMath::Pi());
  mass_genjet = fs->make<TH1F>("mass_genjet","jet mass @ parton level"            ,100,0,100);
  ST_genjet   = fs->make<TH1F>("ST_genjet"  ,"jet S_{T} @ parton level"           ,400,0,4000);
  // tops
  N_gentop         = fs->make<TH1F>("N_gentop"        ,"number of tops @ parton level"  ,10,0,10);
  id_gentop        = fs->make<TH1F>("id_gentop"       ,"top ID @ parton level"          ,20,-10,10);
  status_gentop    = fs->make<TH1F>("status_gentop"   ,"top status @ parton level"      ,50,0,50);
  daughter1_gentop = fs->make<TH1F>("daughter1_gentop","top daughter1 ID @ parton level",100,-50,50);
  daughter2_gentop = fs->make<TH1F>("daughter2_gentop","top daughter2 ID @ parton level",100,-50,50);
  pt_gentop        = fs->make<TH1F>("pt_gentop"       ,"top p_{T} @ parton level"       ,100,0,1000);
  eta_gentop       = fs->make<TH1F>("eta_gentop"      ,"top #eta @ parton level"        ,200,-6,6);
  phi_gentop       = fs->make<TH1F>("phi_gentop"      ,"top #phi @ parton level"        ,100,-TMath::Pi(),TMath::Pi());
  mass_gentop      = fs->make<TH1F>("mass_gentop"     ,"top mass @ parton level"        ,200,0,200);
  deltaEta_gentops = fs->make<TH1F>("deltaEta_gentops","#Delta#eta(t,t~) @ parton level",100,0,10);
  deltaPhi_gentops = fs->make<TH1F>("deltaPhi_gentops","#Delta#phi(t,t~) @ parton level",100,0,10);
  deltaR_gentops   = fs->make<TH1F>("deltaR_gentops"  ,"#DeltaR(t,t~) @ parton level"   ,100,0,10);


  // detector level
  // vertices
  x_vertex = fs->make<TH1F>("x_vertex","x_{vertex}",100,-1,1);
  y_vertex = fs->make<TH1F>("y_vertex","y_{vertex}",100,-1,1);
  z_vertex = fs->make<TH1F>("z_vertex","z_{vertex}",250,-250,250);
  // jets
  N_jets       = fs->make<TH1F>("N_jets"      ,"number of AK4 jets"         ,20,0,20);
  pt_jet       = fs->make<TH1F>("pt_jet"      ,"AK4 jet p_{T}"              ,100,0,1000);
  pt_jet1      = fs->make<TH1F>("pt_jet1"     ,"leading AK4 jet p_{T}"      ,100,0,1000);
  pt_jet2      = fs->make<TH1F>("pt_jet2"     ,"subleading jet p_{T}"   ,100,0,1000);
  pt_jet3      = fs->make<TH1F>("pt_jet3"     ,"subsubleading AK4 jet p_{T}",100,0,1000);
  eta_jet      = fs->make<TH1F>("eta_jet"     ,"AK4 jet #eta"               ,200,-6,6);
  phi_jet      = fs->make<TH1F>("phi_jet"     ,"AK4 jet #phi"               ,100,-TMath::Pi(),TMath::Pi());
  m_jet        = fs->make<TH1F>("m_jet"       ,"AK4 jet mass"               ,100,0,100);
  btag_jet     = fs->make<TH1F>("btag_jet"    ,"AK4 jet btag"               ,10,0,10);
  btagalgo_jet = fs->make<TH1F>("btagalgo_jet","AK4 jet btagalgo"           ,10,0,10);
  flavor_jet   = fs->make<TH1F>("flavor_jet"  ,"AK4 jet flavor"             ,30,0,30);
  // fat jets
  N_fatjets                  = fs->make<TH1F>("N_fatjets"                 ,"number of AK8 jets"                   ,10,0,10);
  pt_fatjet                  = fs->make<TH1F>("pt_fatjet"                 ,"AK8 jet p_{T}"                        ,100,0,1000);
  pt_fatjet1                 = fs->make<TH1F>("pt_fatjet1"                ,"leading AK8 jet p_{T}"                ,100,0,1000);
  pt_fatjet2                 = fs->make<TH1F>("pt_fatjet2"                ,"subleading AK8 jet p_{T}"             ,100,0,1000);
  eta_fatjet                 = fs->make<TH1F>("eta_fatjet"                ,"AK8 jet #eta"                         ,200,-6,6);
  phi_fatjet                 = fs->make<TH1F>("phi_fatjet"                ,"AK8 jet #phi"                         ,100,-TMath::Pi(),TMath::Pi());
  mass_fatjet                = fs->make<TH1F>("mass_fatjet"               ,"AK8 jet mass"                         ,100,0,1000);
  ncharged_fatjet            = fs->make<TH1F>("ncharged_fatjet"           ,"number of charged AK8 jet constituens",100,0,100);
  nneutral_fatjet            = fs->make<TH1F>("nneutral_fatjet"           ,"number of neutral AK8 jet constituens",100,0,100);
  tau1_fatjet                = fs->make<TH1F>("tau1_fatjet"               ,"AK8 jet nsubjettiness #tau_{1}"       ,50,0,1);
  tau2_fatjet                = fs->make<TH1F>("tau2_fatjet"               ,"AK8 jet nsubjettiness #tau_{2}"       ,50,0,1);
  tau3_fatjet                = fs->make<TH1F>("tau3_fatjet"               ,"AK8 jet nsubjettiness #tau_{3}"       ,50,0,1);
  tau4_fatjet                = fs->make<TH1F>("tau4_fatjet"               ,"AK8 jet nsubjettiness #tau_{4}"       ,50,0,1);
  tau5_fatjet                = fs->make<TH1F>("tau5_fatjet"               ,"AK8 jet nsubjettiness #tau_{5}"       ,50,0,1);
  tau32_fatjet               = fs->make<TH1F>("tau32_fatjet"              ,"AK8 jet nsubjettiness ratio #tau_{32}",50,0,1);
  softdropmass_fatjet        = fs->make<TH1F>("softdropmass_fatjet"       ,"AK8 jet softdrop mass"                ,100,0,1000);
  nsubjetssoftdropped_fatjet = fs->make<TH1F>("nsubjetssoftdropped_fatjet","number of AK8 subjets softdropped"    ,10,0,10);
  // electrons
  N_electrons     = fs->make<TH1F>("N_electrons"    ,"number of electrons"        ,10,0,10);
  pt_electron     = fs->make<TH1F>("pt_electron"    ,"electron p_{T}"             ,100,0,1000);
  eta_electron    = fs->make<TH1F>("eta_electron"   ,"electron #eta"              ,200,-6,6);
  phi_electron    = fs->make<TH1F>("phi_electron"   ,"electron #phi"              ,100,-TMath::Pi(),TMath::Pi());
  isovar_electron = fs->make<TH1F>("isovar_electron","electron isolation variable",100,0,1);
  charge_electron = fs->make<TH1F>("charge_electron","electron charge"            ,10,-5,5);
  // muons
  N_muons     = fs->make<TH1F>("N_muons"    ,"number of muons",10,0,10);
  pt_muon     = fs->make<TH1F>("pt_muon"    ,"muon p_{T}"     ,100,0,1000);
  eta_muon    = fs->make<TH1F>("eta_muon"   ,"muon #eta"      ,200,-6,6);
  phi_muon    = fs->make<TH1F>("phi_muon"   ,"muon #phi"      ,100,-TMath::Pi(),TMath::Pi());
  isovar_muon = fs->make<TH1F>("isovar_muon","muon isolation variable",100,0,1);
  charge_muon = fs->make<TH1F>("charge_muon","muon charge"    ,10,-5,5);
  // MET
  ptmiss     = fs->make<TH1F>("ptmiss"    ,"ptmiss"    ,100,0,1000);
  phi_ptmiss = fs->make<TH1F>("phi_ptmiss","#phi_{MET}",100,-TMath::Pi(),TMath::Pi());

  // reco level
  chi_square_had = fs->make<TH1F>("chi_square_had","#chi^{2}_{had}",100,0,1000);
  chi_square_lep = fs->make<TH1F>("chi_square_lep","#chi^{2}_{lep}",100,0,1000);
  chi_square     = fs->make<TH1F>("chi_square"    ,"#chi^{2}"      ,100,0,1000);
  m_top_had      = fs->make<TH1F>("m_top_had"     ,"m_{had top}"   ,50,0,500);
  m_top_lep      = fs->make<TH1F>("m_top_lep"     ,"m_{lep top}"   ,50,0,500);
  m_ttbar        = fs->make<TH1F>("m_ttbar"       ,"m_{t#bar{t}}"  ,200,0,2000);
}


void analysis_module::endJob()
{
  cout << "finishing job..." << endl;
  mInf->Close();
}


void analysis_module::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup)
{
  //reading in tree
  unsigned N_total = mTree->GetEntries();
  cout << "reading in the tree..." << endl;
  cout << "total number of events: " << N_total << endl;
  cout << "cross section [pb]: " << mCrossSection << endl;

  /*
  // ██ ███    ██ ██ ████████ ██  █████  ██      ██ ███████ ██ ███    ██  ██████
  // ██ ████   ██ ██    ██    ██ ██   ██ ██      ██    ███  ██ ████   ██ ██
  // ██ ██ ██  ██ ██    ██    ██ ███████ ██      ██   ███   ██ ██ ██  ██ ██   ███
  // ██ ██  ██ ██ ██    ██    ██ ██   ██ ██      ██  ███    ██ ██  ██ ██ ██    ██
  // ██ ██   ████ ██    ██    ██ ██   ██ ███████ ██ ███████ ██ ██   ████  ██████
  */
  cout << "initializing..." << endl;
  //monte carlo
  int decade = 0;
  // double hweight = 1.0;

  // parton level
  // jets
  int gen_jet_N = 0;
  std::vector<float>* gen_jet_pt   = 0;
  std::vector<float>* gen_jet_eta  = 0;
  std::vector<float>* gen_jet_phi  = 0;
  std::vector<float>* gen_jet_mass = 0;
  // tops
  int gen_top_N = 0;
  std::vector<float>* gen_top_id        = 0;
  std::vector<float>* gen_top_status    = 0;
  std::vector<float>* gen_top_daughter1 = 0;
  std::vector<float>* gen_top_daughter2 = 0;
  std::vector<float>* gen_top_pt        = 0;
  std::vector<float>* gen_top_eta       = 0;
  std::vector<float>* gen_top_phi       = 0;
  std::vector<float>* gen_top_mass      = 0;

  // detector level
  // vertices
  int vertex_N = 0;
  std::vector<float>* vertex_x = 0;
  std::vector<float>* vertex_y = 0;
  std::vector<float>* vertex_z = 0;
  // jets
  int jet_N = 0;
  std::vector<float>* jet_pt       = 0;
  std::vector<float>* jet_eta      = 0;
  std::vector<float>* jet_phi      = 0;
  std::vector<float>* jet_mass     = 0;
  std::vector<float>* jet_btag     = 0;
  std::vector<float>* jet_btagalgo = 0;
  std::vector<float>* jet_flavor   = 0;
  // fat jets
  int fatjet_N = 0;
  std::vector<float>* fatjet_pt                  = 0;
  std::vector<float>* fatjet_eta                 = 0;
  std::vector<float>* fatjet_phi                 = 0;
  std::vector<float>* fatjet_mass                = 0;
  std::vector<int>*   fatjet_ncharged            = 0;
  std::vector<int>*   fatjet_nneutral            = 0;
  std::vector<float>* fatjet_tau1                = 0;
  std::vector<float>* fatjet_tau2                = 0;
  std::vector<float>* fatjet_tau3                = 0;
  std::vector<float>* fatjet_tau4                = 0;
  std::vector<float>* fatjet_tau5                = 0;
  std::vector<float>* fatjet_tau32               = 0;
  std::vector<float>* fatjet_softdropmass        = 0;
  std::vector<int>*   fatjet_nsubjetssoftdropped = 0;
  // electrons
  int electron_N = 0;
  std::vector<float>* electron_pt     = 0;
  std::vector<float>* electron_eta    = 0;
  std::vector<float>* electron_phi    = 0;
  std::vector<float>* electron_isovar = 0;
  std::vector<float>* electron_charge = 0;
  // muons
  int muon_N = 0;
  std::vector<float>* muon_pt     = 0;
  std::vector<float>* muon_eta    = 0;
  std::vector<float>* muon_phi    = 0;
  std::vector<float>* muon_isovar = 0;
  std::vector<float>* muon_charge = 0;
  // MET
  float MET = 0;
  float MET_phi = 0;



  /*
  // ███████ ███████ ████████ ████████ ██ ███    ██  ██████      ██████  ██████   █████  ███    ██  ██████ ██   ██      █████  ██████  ██████  ██████  ███████ ███████ ███████ ███████ ███████
  // ██      ██         ██       ██    ██ ████   ██ ██           ██   ██ ██   ██ ██   ██ ████   ██ ██      ██   ██     ██   ██ ██   ██ ██   ██ ██   ██ ██      ██      ██      ██      ██
  // ███████ █████      ██       ██    ██ ██ ██  ██ ██   ███     ██████  ██████  ███████ ██ ██  ██ ██      ███████     ███████ ██   ██ ██   ██ ██████  █████   ███████ ███████ █████   ███████
  //      ██ ██         ██       ██    ██ ██  ██ ██ ██    ██     ██   ██ ██   ██ ██   ██ ██  ██ ██ ██      ██   ██     ██   ██ ██   ██ ██   ██ ██   ██ ██           ██      ██ ██           ██
  // ███████ ███████    ██       ██    ██ ██   ████  ██████      ██████  ██   ██ ██   ██ ██   ████  ██████ ██   ██     ██   ██ ██████  ██████  ██   ██ ███████ ███████ ███████ ███████ ███████
  */
  cout << "setting branch addresses..." << endl;

  // parton level
  // jets
  mTree->SetBranchAddress("gen_jet_pt"  ,&gen_jet_pt);
  mTree->SetBranchAddress("gen_jet_eta" ,&gen_jet_eta);
  mTree->SetBranchAddress("gen_jet_phi" ,&gen_jet_phi);
  mTree->SetBranchAddress("gen_jet_mass",&gen_jet_mass);
  // tops
  mTree->SetBranchAddress("gen_top_id"       ,&gen_top_id);
  mTree->SetBranchAddress("gen_top_status"   ,&gen_top_status);
  mTree->SetBranchAddress("gen_top_daughter1",&gen_top_daughter1);
  mTree->SetBranchAddress("gen_top_daughter2",&gen_top_daughter2);
  mTree->SetBranchAddress("gen_top_pt"       ,&gen_top_pt);
  mTree->SetBranchAddress("gen_top_eta"      ,&gen_top_eta);
  mTree->SetBranchAddress("gen_top_phi"      ,&gen_top_phi);
  mTree->SetBranchAddress("gen_top_mass"     ,&gen_top_mass);

  // detector level
  // vertices
  mTree->SetBranchAddress("vertex_x",&vertex_x);
  mTree->SetBranchAddress("vertex_y",&vertex_y);
  mTree->SetBranchAddress("vertex_z",&vertex_z);
  // jets
  mTree->SetBranchAddress("jet_pt"      ,&jet_pt);
  mTree->SetBranchAddress("jet_eta"     ,&jet_eta);
  mTree->SetBranchAddress("jet_phi"     ,&jet_phi);
  mTree->SetBranchAddress("jet_mass"    ,&jet_mass);
  mTree->SetBranchAddress("jet_btag"    ,&jet_btag);
  mTree->SetBranchAddress("jet_btagalgo",&jet_btagalgo);
  mTree->SetBranchAddress("jet_flavor"  ,&jet_flavor);
  // fat jets
  mTree->SetBranchAddress("fatjet_pt"                 ,&fatjet_pt);
  mTree->SetBranchAddress("fatjet_eta"                ,&fatjet_eta);
  mTree->SetBranchAddress("fatjet_phi"                ,&fatjet_phi);
  mTree->SetBranchAddress("fatjet_mass"               ,&fatjet_mass);
  mTree->SetBranchAddress("fatjet_ncharged"           ,&fatjet_ncharged);
  mTree->SetBranchAddress("fatjet_nneutral"           ,&fatjet_nneutral);
  mTree->SetBranchAddress("fatjet_tau1"               ,&fatjet_tau1);
  mTree->SetBranchAddress("fatjet_tau2"               ,&fatjet_tau2);
  mTree->SetBranchAddress("fatjet_tau3"               ,&fatjet_tau3);
  mTree->SetBranchAddress("fatjet_tau4"               ,&fatjet_tau4);
  mTree->SetBranchAddress("fatjet_tau5"               ,&fatjet_tau5);
  mTree->SetBranchAddress("fatjet_tau32"              ,&fatjet_tau32);
  mTree->SetBranchAddress("fatjet_softdropmass"       ,&fatjet_softdropmass);
  mTree->SetBranchAddress("fatjet_nsubjetssoftdropped",&fatjet_nsubjetssoftdropped);
  // electrons
  mTree->SetBranchAddress("electron_pt"    ,&electron_pt);
  mTree->SetBranchAddress("electron_eta"   ,&electron_eta);
  mTree->SetBranchAddress("electron_phi"   ,&electron_phi);
  mTree->SetBranchAddress("electron_isovar",&electron_isovar);
  mTree->SetBranchAddress("electron_charge",&electron_charge);
  // muons
  mTree->SetBranchAddress("muon_pt"    ,&muon_pt);
  mTree->SetBranchAddress("muon_eta"   ,&muon_eta);
  mTree->SetBranchAddress("muon_phi"   ,&muon_phi);
  mTree->SetBranchAddress("muon_isovar",&muon_isovar);
  mTree->SetBranchAddress("muon_charge",&muon_charge);
  // MET
  mTree->SetBranchAddress("MET",&MET);
  mTree->SetBranchAddress("MET_phi",&MET_phi);

  int N_presel       = 0;
  int N_fullsel      = 0;
  int N_elchannel    = 0;
  int N_muchannel    = 0;
  int N_notoptagreco = 0;
  int N_toptagreco   = 0;
  int N_chi2         = 0;
  int N_chi2cut30    = 0;


  /*
  // ███████ ██    ██ ███████ ███    ██ ████████     ██       ██████   ██████  ██████
  // ██      ██    ██ ██      ████   ██    ██        ██      ██    ██ ██    ██ ██   ██
  // █████   ██    ██ █████   ██ ██  ██    ██        ██      ██    ██ ██    ██ ██████
  // ██       ██  ██  ██      ██  ██ ██    ██        ██      ██    ██ ██    ██ ██
  // ███████   ████   ███████ ██   ████    ██        ███████  ██████   ██████  ██
  */
  cout << "starting event loop..." << endl;
  for(unsigned  i=0; i<N_total; i++){
    //progress report
    double progress = 10.0*i / (1.0*N_total);
    int k = TMath::FloorNint(progress);
    if(k > decade)
    cout << "-----  "<< 10*k << "%" << " -----" << endl;
    decade = k;
    //reading the event
    mTree->GetEntry(i);


    // if(mIsMCarlo){
    //   hweight = mCrossSection / N_total;
    // }

    // ██████   █████  ██████  ████████  ██████  ███    ██     ██      ███████ ██    ██ ███████ ██
    // ██   ██ ██   ██ ██   ██    ██    ██    ██ ████   ██     ██      ██      ██    ██ ██      ██
    // ██████  ███████ ██████     ██    ██    ██ ██ ██  ██     ██      █████   ██    ██ █████   ██
    // ██      ██   ██ ██   ██    ██    ██    ██ ██  ██ ██     ██      ██       ██  ██  ██      ██
    // ██      ██   ██ ██   ██    ██     ██████  ██   ████     ███████ ███████   ████   ███████ ███████

    // jets
    gen_jet_N = gen_jet_pt->size();
    N_genjet->Fill(gen_jet_N);
    float gen_jet_ST = 0;
    for(int j=0; j<gen_jet_N; j++){
      pt_genjet  ->Fill(gen_jet_pt  ->at(j));
      eta_genjet ->Fill(gen_jet_eta ->at(j));
      phi_genjet ->Fill(gen_jet_phi ->at(j));
      mass_genjet->Fill(gen_jet_mass->at(j));
      gen_jet_ST += gen_jet_pt->at(j);
    }
    ST_genjet->Fill(gen_jet_ST);
    if(gen_jet_N >= 1) pt_genjet1->Fill(gen_jet_pt->at(0));
    if(gen_jet_N >= 2) pt_genjet2->Fill(gen_jet_pt->at(1));

    // tops
    bool topinevent     = false;
    bool antitopinevent = false;
    gen_top_N = gen_top_pt->size();
    N_gentop->Fill(gen_top_N);
    for(int j=0; j<gen_top_N; j++){
      id_gentop       ->Fill(gen_top_id       ->at(j));
      status_gentop   ->Fill(gen_top_status   ->at(j));
      daughter1_gentop->Fill(gen_top_daughter1->at(j));
      daughter2_gentop->Fill(gen_top_daughter2->at(j));
      pt_gentop       ->Fill(gen_top_pt       ->at(j));
      eta_gentop      ->Fill(gen_top_eta      ->at(j));
      phi_gentop      ->Fill(gen_top_phi      ->at(j));
      mass_gentop     ->Fill(gen_top_mass     ->at(j));

      if(gen_top_id->at(j) == 6)  topinevent     = true;
      if(gen_top_id->at(j) == -6) antitopinevent = true;
    }
    if(gen_top_N == 2 && topinevent && antitopinevent){
      float gen_top_deltaEta = TMath::Abs(gen_top_eta->at(0) - gen_top_eta->at(1));
      deltaEta_gentops->Fill(gen_top_deltaEta);
      float gen_top_deltaPhi = TMath::Abs(gen_top_phi->at(0) - gen_top_phi->at(1));
      deltaPhi_gentops->Fill(gen_top_deltaPhi);
      float gen_top_deltaR = deltaR(gen_top_eta->at(0),gen_top_phi->at(0),gen_top_eta->at(1),gen_top_phi->at(1));
      deltaR_gentops->Fill(gen_top_deltaR);
    }


    // ██████  ███████ ████████ ███████  ██████ ████████  ██████  ██████      ██      ███████ ██    ██ ███████ ██
    // ██   ██ ██         ██    ██      ██         ██    ██    ██ ██   ██     ██      ██      ██    ██ ██      ██
    // ██   ██ █████      ██    █████   ██         ██    ██    ██ ██████      ██      █████   ██    ██ █████   ██
    // ██   ██ ██         ██    ██      ██         ██    ██    ██ ██   ██     ██      ██       ██  ██  ██      ██
    // ██████  ███████    ██    ███████  ██████    ██     ██████  ██   ██     ███████ ███████   ████   ███████ ███████

    // ██████  ██████  ███████     ███████ ███████ ██      ███████  ██████ ████████ ██  ██████  ███    ██
    // ██   ██ ██   ██ ██          ██      ██      ██      ██      ██         ██    ██ ██    ██ ████   ██
    // ██████  ██████  █████ █████ ███████ █████   ██      █████   ██         ██    ██ ██    ██ ██ ██  ██
    // ██      ██   ██ ██               ██ ██      ██      ██      ██         ██    ██ ██    ██ ██  ██ ██
    // ██      ██   ██ ███████     ███████ ███████ ███████ ███████  ██████    ██    ██  ██████  ██   ████

    // jets
    vector<double> v_jet_pt;
    vector<double> v_jet_eta;
    vector<double> v_jet_phi;
    vector<double> v_jet_mass;
    vector<int>    v_jet_btag;
    vector<int>    v_jet_btagalgo;
    vector<int>    v_jet_flavor;

    for(unsigned int j=0; j<jet_pt->size(); j++){
      if(jet_pt->at(j) > 30. && TMath::Abs(jet_eta->at(j)) < 2.4){
        v_jet_pt      .push_back(jet_pt      ->at(j));
        v_jet_eta     .push_back(jet_eta     ->at(j));
        v_jet_phi     .push_back(jet_phi     ->at(j));
        v_jet_mass    .push_back(jet_mass    ->at(j));
        v_jet_btag    .push_back(jet_btag    ->at(j));
        v_jet_btagalgo.push_back(jet_btagalgo->at(j));
        v_jet_flavor  .push_back(jet_flavor  ->at(j));
      }
    }

    // fat jets
    vector<double> v_fatjet_pt;
    vector<double> v_fatjet_eta;
    vector<double> v_fatjet_phi;
    vector<double> v_fatjet_mass;
    vector<int>    v_fatjet_ncharged;
    vector<int>    v_fatjet_nneutral;
    vector<double> v_fatjet_tau1;
    vector<double> v_fatjet_tau2;
    vector<double> v_fatjet_tau3;
    vector<double> v_fatjet_tau4;
    vector<double> v_fatjet_tau5;
    vector<double> v_fatjet_tau32;
    vector<double> v_fatjet_softdropmass;
    vector<int>    v_fatjet_nsubjetssoftdropped;

    for(unsigned int j=0; j<fatjet_pt->size(); j++){
      if(fatjet_pt->at(j) > 400. && TMath::Abs(fatjet_eta->at(j)) < 2.4){
        v_fatjet_pt                 .push_back(fatjet_pt                 ->at(j));
        v_fatjet_eta                .push_back(fatjet_eta                ->at(j));
        v_fatjet_phi                .push_back(fatjet_phi                ->at(j));
        v_fatjet_mass               .push_back(fatjet_mass               ->at(j));
        v_fatjet_ncharged           .push_back(fatjet_ncharged           ->at(j));
        v_fatjet_nneutral           .push_back(fatjet_nneutral           ->at(j));
        v_fatjet_tau1               .push_back(fatjet_tau1               ->at(j));
        v_fatjet_tau2               .push_back(fatjet_tau2               ->at(j));
        v_fatjet_tau3               .push_back(fatjet_tau3               ->at(j));
        v_fatjet_tau4               .push_back(fatjet_tau4               ->at(j));
        v_fatjet_tau5               .push_back(fatjet_tau5               ->at(j));
        v_fatjet_tau32              .push_back(fatjet_tau32              ->at(j));
        v_fatjet_softdropmass       .push_back(fatjet_softdropmass       ->at(j));
        v_fatjet_nsubjetssoftdropped.push_back(fatjet_nsubjetssoftdropped->at(j));
      }
    }

    // electrons
    vector<double> v_electron_pt;
    vector<double> v_electron_eta;
    vector<double> v_electron_phi;
    vector<double> v_electron_isovar;
    vector<int>    v_electron_charge;

    for(unsigned int j=0; j<electron_pt->size(); j++){
      if(electron_pt->at(j) > 50. && TMath::Abs(electron_eta->at(j)) < 2.5){
        v_electron_pt    .push_back(electron_pt    ->at(j));
        v_electron_eta   .push_back(electron_eta   ->at(j));
        v_electron_phi   .push_back(electron_phi   ->at(j));
        v_electron_isovar.push_back(electron_isovar->at(j));
        v_electron_charge.push_back(electron_charge->at(j));
      }
    }

    // muons
    vector<double> v_muon_pt;
    vector<double> v_muon_eta;
    vector<double> v_muon_phi;
    vector<double> v_muon_isovar;
    vector<int>    v_muon_charge;

    for(unsigned int j=0; j<muon_pt->size(); j++){
      if(muon_pt->at(j) > 55. && TMath::Abs(muon_eta->at(j) < 2.4)){
        v_muon_pt    .push_back(muon_pt    ->at(j));
        v_muon_eta   .push_back(muon_eta   ->at(j));
        v_muon_phi   .push_back(muon_phi   ->at(j));
        v_muon_isovar.push_back(muon_isovar->at(j));
        v_muon_charge.push_back(muon_charge->at(j));
      }
    }

    // MET
    if(MET <= 50.) continue;

    N_presel++;


    // ███████ ██    ██ ██      ██          ███████ ███████ ██      ███████  ██████ ████████ ██  ██████  ███    ██
    // ██      ██    ██ ██      ██          ██      ██      ██      ██      ██         ██    ██ ██    ██ ████   ██
    // █████   ██    ██ ██      ██          ███████ █████   ██      █████   ██         ██    ██ ██    ██ ██ ██  ██
    // ██      ██    ██ ██      ██               ██ ██      ██      ██      ██         ██    ██ ██    ██ ██  ██ ██
    // ██       ██████  ███████ ███████     ███████ ███████ ███████ ███████  ██████    ██    ██  ██████  ██   ████


    bool electron_channel = false;
    if(v_electron_pt.size() == 1 && v_electron_pt.at(0) > 80. && v_jet_pt.size() > 1 && v_jet_pt.at(0) > 185. && v_jet_pt.at(1) > 50. && MET > 120.){
      electron_channel = true;
    }

    // if(v_muon_pt.size() == 1) double lepton_HT = MET + v_muon_pt.at(0);

    bool muon_channel = false;
    if(v_muon_pt.size() == 1 && v_muon_pt.at(0) > 55. && v_jet_pt.size() > 1 && v_jet_pt.at(0) > 150. && v_jet_pt.at(1) > 50. && MET > 50. && (MET + v_muon_pt.at(0)) > 150.){
      muon_channel = true;
    }


    if(!((electron_channel && !muon_channel) || (!electron_channel && muon_channel))) continue; // exaclty one electron or muon

    // ████████ ████████ ██████   █████  ██████      ███    ███  █████  ███████ ███████     ██████  ███████  ██████  ██████
    //    ██       ██    ██   ██ ██   ██ ██   ██     ████  ████ ██   ██ ██      ██          ██   ██ ██      ██      ██    ██
    //    ██       ██    ██████  ███████ ██████      ██ ████ ██ ███████ ███████ ███████     ██████  █████   ██      ██    ██
    //    ██       ██    ██   ██ ██   ██ ██   ██     ██  ██  ██ ██   ██      ██      ██     ██   ██ ██      ██      ██    ██
    //    ██       ██    ██████  ██   ██ ██   ██     ██      ██ ██   ██ ███████ ███████     ██   ██ ███████  ██████  ██████

    // find lepton
    TLorentzVector lepton_lv;
    if(electron_channel && !muon_channel){
      lepton_lv.SetPtEtaPhiM(v_electron_pt.at(0),v_electron_eta.at(0),v_electron_phi.at(0),electron_mass);
    }
    else if(!electron_channel && muon_channel){
      lepton_lv.SetPtEtaPhiM(v_muon_pt.at(0),v_muon_eta.at(0),v_muon_phi.at(0),muon_mass);
    }
    else{
      throw runtime_error("In ttbar mass reconstruction: cannot find primary lepton");
    }
    // cout << "lepton pt: " << lepton_lv.Pt() << endl;

    // top-tagging for AK8 jets
    vector<TLorentzVector> v_AK8jet_toptagged_lv;
    vector<double>         v_AK8jet_toptagged_sdmass;
    for(unsigned int j=0; j<v_fatjet_pt.size(); j++){
      if(105. < v_fatjet_softdropmass.at(j) && v_fatjet_softdropmass.at(j) < 210. && v_fatjet_tau32.at(j) < 0.65){
        TLorentzVector AK8jet_toptagged_lv;
        AK8jet_toptagged_lv.SetPtEtaPhiM(v_fatjet_pt.at(j),v_fatjet_eta.at(j),v_fatjet_phi.at(j),v_fatjet_mass.at(j));
        v_AK8jet_toptagged_lv.push_back(AK8jet_toptagged_lv);

        v_AK8jet_toptagged_sdmass.push_back(v_fatjet_softdropmass.at(j));
      }
    }

    // veto on >2 top-tagged AK8jet -> no overlap to hadronic analysis
    if(v_AK8jet_toptagged_lv.size() > 1) continue;

    // 2D cut on AK4 jets
    vector<TLorentzVector> v_AK4jet_2Dcut_lv;
    for(unsigned int j=0; j<v_jet_pt.size(); j++){
      TLorentzVector AK4jet_2Dcut_lv;
      AK4jet_2Dcut_lv.SetPtEtaPhiM(v_jet_pt.at(j),v_jet_eta.at(j),v_jet_phi.at(j),v_jet_mass.at(j));
      double deltaR_2Dcut = deltaR(v_jet_eta.at(j),v_jet_phi.at(j),lepton_lv.Eta(),lepton_lv.Phi());
      // cout << "       deltaR_2Dcut: " << deltaR_2Dcut << endl;

      double ptrel_AK4jet_lepton = TMath::Abs((AK4jet_2Dcut_lv.Px() * lepton_lv.Px() + AK4jet_2Dcut_lv.Py() * lepton_lv.Py()) / AK4jet_2Dcut_lv.Pt());
      // cout << "ptrel_AK4jet_lepton: " << ptrel_AK4jet_lepton << endl;

      if(deltaR_2Dcut > 0.4 || ptrel_AK4jet_lepton > 25.){
        v_AK4jet_2Dcut_lv.push_back(AK4jet_2Dcut_lv);
      }
    }
    // cout << "             # AK4 jets: " << v_jet_pt         .size() << endl;
    // cout << "# AK4 jets after 2D cut: " << v_AK4jet_2Dcut_lv.size() << endl;
    // cout << endl;

    // check event selection
    if(v_AK8jet_toptagged_lv.size() == 0 && v_AK4jet_2Dcut_lv.size() < 2){
      cout << "Event content did not allow ttbar reconstruction: AK4 jets" << endl;
      continue;
    }
    if(v_AK8jet_toptagged_lv.size() >= 1 && v_AK4jet_2Dcut_lv.size() < 1){
      cout << "Event content did not allow ttbar reconstruction: AK8 top tag" << endl;
      continue;
    }

    // event categories counting
    N_fullsel++;
    if(electron_channel){
      N_elchannel++;
      // cout << "electron channel" << endl;
    }
    if(muon_channel){
      N_muchannel++;
      // cout << "muon channel" << endl;
    }


    // neutrino reconstruction from MET
    double neutrino_px = MET * cos(MET_phi);
    double neutrino_py = MET * sin(MET_phi);
    double neutrino_pt = TMath::Sqrt(neutrino_px * neutrino_px + neutrino_py * neutrino_py);

    double mu           = Wboson_mass * Wboson_mass / 2 + lepton_lv.Pt() * neutrino_pt;
    double A            = - (lepton_lv.Pt() * lepton_lv.Pt());
    double B            = mu * lepton_lv.Pz();
    double C            = mu * mu - (lepton_lv.E() * lepton_lv.E()) * (neutrino_pt * neutrino_pt);
    double discriminant = B * B - A * C;

    vector<TLorentzVector> v_neutrino_candidates_lv;
    if(discriminant <= 0){
      double neutrino_pz = -B / A;
      double neutrino_E  = TMath::Sqrt(neutrino_px * neutrino_px + neutrino_py * neutrino_py + neutrino_pz * neutrino_pz);
      TLorentzVector solution;
      solution.SetPxPyPzE(neutrino_px,neutrino_py,neutrino_pz,neutrino_E);
      v_neutrino_candidates_lv.push_back(solution);
    }
    else{
      discriminant = TMath::Sqrt(discriminant);

      double neutrino_pz1 = (-B - discriminant) / A;
      double neutrino_E1 = TMath::Sqrt(neutrino_px * neutrino_px + neutrino_py * neutrino_py + neutrino_pz1 * neutrino_pz1);
      TLorentzVector solution1;
      solution1.SetPxPyPzE(neutrino_px,neutrino_py,neutrino_pz1,neutrino_E1);
      v_neutrino_candidates_lv.push_back(solution1);

      double neutrino_pz2 = (-B + discriminant) / A;
      double neutrino_E2 = TMath::Sqrt(neutrino_px * neutrino_px + neutrino_py * neutrino_py + neutrino_pz2 * neutrino_pz2);
      TLorentzVector solution2;
      solution2.SetPxPyPzE(neutrino_px,neutrino_py,neutrino_pz2,neutrino_E2);
      v_neutrino_candidates_lv.push_back(solution2);
    }

    // checks for top-tag reco
    // >= 1 non-overlapping jet (AK8, AK4) with respect to the lepton
    bool jet_lepton_overlap = true;
    vector<bool> v_AK8jettoptagged_lepton_overlap;
    for(unsigned int j=0; j<v_AK8jet_toptagged_lv.size(); j++){
      double dR_lepton_AK8 = deltaR(v_AK8jet_toptagged_lv.at(j).Eta(),v_AK8jet_toptagged_lv.at(j).Phi(),lepton_lv.Eta(),lepton_lv.Phi());
      if(dR_lepton_AK8 > 0.8) jet_lepton_overlap = false;
      v_AK8jettoptagged_lepton_overlap.push_back(jet_lepton_overlap);
    }
    for(unsigned int j=0; j<v_AK4jet_2Dcut_lv.size(); j++){
      double dR_lepton_AK4 = deltaR(v_AK4jet_2Dcut_lv.at(j).Eta(),v_AK4jet_2Dcut_lv.at(j).Phi(),lepton_lv.Eta(),lepton_lv.Phi());
      if(dR_lepton_AK4 > 0.8) jet_lepton_overlap = false;
    }

    // >= 1 separated AK4 jet: dR > 1.2 to top tagged AK8 jet(s)
    bool has_separated_jet = false;
    vector<bool> v_AK8toptagged_has_separated_jet;
    if(v_AK8jet_toptagged_lv.size() > 0){
      for(unsigned int j=0; j<v_AK8jet_toptagged_lv.size(); j++){
        for(unsigned int k=0; k<v_AK4jet_2Dcut_lv.size(); k++){
          double dR_AK8_AK4 = deltaR(v_AK8jet_toptagged_lv.at(j).Eta(),v_AK8jet_toptagged_lv.at(j).Phi(),v_AK4jet_2Dcut_lv.at(k).Eta(),v_AK4jet_2Dcut_lv.at(k).Phi());
          // cout << "dR_AK8_AK4: " << dR_AK8_AK4 << endl;
          if(dR_AK8_AK4 > 1.2) has_separated_jet = true;
        }
        v_AK8toptagged_has_separated_jet.push_back(has_separated_jet);
      }
    }
    else has_separated_jet = true;

    // top tag reco
    bool toptag_reco = false;
    if(v_AK8jet_toptagged_lv.size() >= 1){
      if(!jet_lepton_overlap && has_separated_jet) toptag_reco = true;
    }

    vector<TLorentzVector> v_tophad_candidates_lv;
    vector<double>         v_tophad_candidates_sdmass;
    vector<TLorentzVector> v_toplep_candidates_lv;


    if(!toptag_reco){ // no top-tag reco
      N_notoptagreco++;
      // cout << "no top-tag reco" << endl;

      unsigned int N_AK4jets = v_AK4jet_2Dcut_lv.size();
      if(N_AK4jets > 10) N_AK4jets = 10; // consider max. 10 jets

      unsigned int jet_index = pow(3, N_AK4jets);
      // cout << "N_AK4jets: " << N_AK4jets << endl;
      // cout << "jet_index: " << jet_index << endl;
      for(unsigned int j=0; j<v_neutrino_candidates_lv.size(); j++){
        for(unsigned int k=0; k<jet_index; k++){ // for loop over all possible jet combinations
          TLorentzVector top_had_lv;
          vector<TLorentzVector> v_top_had_lv;
          TLorentzVector top_lep_lv = lepton_lv + v_neutrino_candidates_lv.at(j);
          vector<TLorentzVector> v_top_lep_lv;

          int num = k;
          for(unsigned int l=0; l<N_AK4jets; l++){
            if(num % 3 == 0){ // assign jet to hadronic top
              top_had_lv = top_had_lv + v_AK4jet_2Dcut_lv.at(l);
              v_top_had_lv.push_back(top_had_lv);
            }
            if(num % 3 == 1){ // assign jet to leptonic top
              top_lep_lv = top_lep_lv + v_AK4jet_2Dcut_lv.at(l);
              v_top_lep_lv.push_back(top_lep_lv);
            }
            num /= 3; // assign jet to no top
          }

          if(v_top_had_lv.size() < 1 || v_top_lep_lv.size() < 1) continue; // at least one hadronic/leptonic top candidate each

          // set candidates
          // cout << "v_top_had_lv.size(): " << v_top_had_lv.size() << endl;
          // cout << "v_top_lep_lv.size(): " << v_top_lep_lv.size() << endl;

          v_tophad_candidates_lv.insert(v_tophad_candidates_lv.end(),v_top_had_lv.begin(),v_top_had_lv.end());
          v_toplep_candidates_lv.insert(v_toplep_candidates_lv.end(),v_top_lep_lv.begin(),v_top_lep_lv.end());
          v_top_had_lv.clear();
          v_top_lep_lv.clear();
        }
      }
    }
    else{ // top-tag reco
      N_toptagreco++;
      // cout << "top-tag reco" << endl;

      for(unsigned int j=0; j<v_neutrino_candidates_lv.size(); j++){
        // cout << "v_AK8jet_toptagged_lv.size(): " << v_AK8jet_toptagged_lv.size() << endl;
        for(unsigned int k=0; k<v_AK8jet_toptagged_lv.size(); k++){
          if(v_AK8toptagged_has_separated_jet.at(k) && !(v_AK8jettoptagged_lepton_overlap.at(k))) continue;

          vector<TLorentzVector> v_separated_AK4jets;
          for(unsigned int l=0; l<v_AK4jet_2Dcut_lv.size(); l++){
            double dR_AK8_AK4 = deltaR(v_AK8jet_toptagged_lv.at(k).Eta(),v_AK8jet_toptagged_lv.at(k).Phi(),v_AK4jet_2Dcut_lv.at(l).Eta(),v_AK4jet_2Dcut_lv.at(l).Phi());
            if(dR_AK8_AK4 > 0.8) v_separated_AK4jets.push_back(v_AK4jet_2Dcut_lv.at(l));
          }

          if(v_separated_AK4jets.size() < 1) throw runtime_error("In TopTagReco: This toptag does not have >= 1 well-separated AK4 jet. This should have been caught by earlier messages. There is a logic error.");


          unsigned int N_AK4jets = v_separated_AK4jets.size();
          if(v_separated_AK4jets.size() > 10) N_AK4jets = 10;

          unsigned int jet_index = pow(2, N_AK4jets);
          // cout << "N_AK4jets: " << N_AK4jets << endl;
          // cout << "jet_index: " << jet_index << endl;
          for(unsigned int l=0; l<jet_index; l++){
            TLorentzVector top_had_lv = v_AK8jet_toptagged_lv.at(k);
            vector<TLorentzVector> v_top_had_lv;
            v_top_had_lv.push_back(top_had_lv);
            double top_had_sdmass = v_AK8jet_toptagged_sdmass.at(k);
            vector<double> v_top_had_sdmass;
            v_top_had_sdmass.push_back(top_had_sdmass);

            TLorentzVector top_lep_lv = lepton_lv + v_neutrino_candidates_lv.at(j);
            vector<TLorentzVector> v_top_lep_lv;

            int num = l;

            for(unsigned int m=0; m<N_AK4jets; m++){
              if(num % 2 == 0){
                top_lep_lv = top_lep_lv + v_separated_AK4jets.at(m);
                v_top_lep_lv.push_back(top_lep_lv);
              }
              num /= 2;
            }

            if(v_top_had_lv.size() < 1 || v_top_lep_lv.size() < 1 || v_separated_AK4jets.size() < 1) continue;

            for(unsigned int m=0; m<v_top_lep_lv.size()-1; m++){ // set same tophad candidate for every possibe toplep candidate -> need pair: tophad + lephad
              v_top_had_lv.push_back(top_had_lv);
              v_top_had_sdmass.push_back(top_had_sdmass);
            }

            // set candidates
            v_tophad_candidates_lv.insert(v_tophad_candidates_lv.end(),v_top_had_lv.begin(),v_top_had_lv.end());
            v_top_had_lv.clear();
            v_tophad_candidates_sdmass.insert(v_tophad_candidates_sdmass.end(),v_top_had_sdmass.begin(),v_top_had_sdmass.end());
            v_top_had_sdmass.clear();

            v_toplep_candidates_lv.insert(v_toplep_candidates_lv.end(),v_top_lep_lv.begin(),v_top_lep_lv.end());
            v_top_lep_lv.clear();
          }
        }
      }
    }
    // cout << "v_tophad_candidates_lv.size(): " << v_tophad_candidates_lv.size() << endl;
    // cout << "v_toplep_candidates_lv.size(): " << v_toplep_candidates_lv.size() << endl;
    // cout << endl;

    // chi2 discriminator
    // pairs of hadronic/leptonic top candidates required
    if(v_tophad_candidates_lv.size() < 1 || v_toplep_candidates_lv.size() < 1 || (v_tophad_candidates_lv.size() != v_toplep_candidates_lv.size())) continue;
    N_chi2++;
    double N_hypotheses = v_tophad_candidates_lv.size();

    const double m_tophad     = 177.;
    const double m_toplep     = 175.;
    const double sigma_tophad = 16.;
    const double sigma_toplep = 19.;

    const double m_tophad_ttag     = 173.;
    const double m_toplep_ttag     = 175.;
    const double sigma_tophad_ttag = 15.;
    const double sigma_toplep_ttag = 19.;


    double chi2_best     = 99999999;
    double chi2_had_best = 99999999;
    double chi2_lep_best = 99999999;
    double mhad_best     = 99999999;
    double mlep_best     = 99999999;
    double mttbar_best   = 99999999;

    TLorentzVector tophad_lv;
    TLorentzVector toplep_lv;
    for(unsigned int j=0; j<N_hypotheses; j++){
      double chi2_had = 0.;
      double chi2_lep = 0.;
      double mhad     = 0.;
      double mlep     = 0.;

      if(toptag_reco){
        mhad     = v_tophad_candidates_sdmass.at(j); // AK8 jet: soft-drop mass
        mlep     = v_toplep_candidates_lv.at(j).M();
        chi2_had = pow(((mhad - m_tophad_ttag) / sigma_tophad_ttag),2);
        chi2_lep = pow(((mlep - m_toplep_ttag) / sigma_toplep_ttag),2);
      }
      else{
        mhad     = v_tophad_candidates_lv.at(j).M(); // AK4 jet: invariant mass
        mlep     = v_toplep_candidates_lv.at(j).M();
        chi2_had = pow(((mhad - m_tophad) / sigma_tophad),2);
        chi2_lep = pow(((mlep - m_toplep) / sigma_toplep),2);
      }

      double chi2   = chi2_had + chi2_lep;


      if(chi2 < chi2_best){
        chi2_best     = chi2;
        chi2_had_best = chi2_had;
        chi2_lep_best = chi2_lep;
        mhad_best     = mhad;
        mlep_best     = mlep;

        tophad_lv   = v_tophad_candidates_lv.at(j);
        toplep_lv   = v_toplep_candidates_lv.at(j);
        mttbar_best = (tophad_lv + tophad_lv).M();
      }
    }

    // chi square cut
    if(chi2_best < 30.){
      N_chi2cut30++;
    }

    // reco level
    chi_square_had->Fill(chi2_had_best);
    chi_square_lep->Fill(chi2_lep_best);
    chi_square    ->Fill(chi2_best);
    m_top_had     ->Fill(mhad_best);
    m_top_lep     ->Fill(mlep_best);
    m_ttbar       ->Fill(mttbar_best);

    // cout << " tophad_lv.Pt(): " << tophad_lv.Pt()  << endl;
    // cout << "tophad_lv.Eta(): " << tophad_lv.Eta() << endl;
    // cout << "tophad_lv.Phi(): " << tophad_lv.Phi() << endl;
    // cout << "  tophad_lv.M(): " << tophad_lv.M()   << endl;
    //
    // cout << " toplep_lv.Pt(): " << toplep_lv.Pt()  << endl;
    // cout << "toplep_lv.Eta(): " << toplep_lv.Eta() << endl;
    // cout << "toplep_lv.Phi(): " << toplep_lv.Phi() << endl;
    // cout << "  toplep_lv.M(): " << toplep_lv.M()   << endl;
    //
    // cout << "  chi2_had_best: " << chi2_had_best   << endl;
    // cout << "  chi2_lep_best: " << chi2_lep_best   << endl;
    // cout << "      chi2_best: " << chi2_best       << endl;
    // cout << "    mttbar_best: " << mttbar_best     << endl;
    // cout << endl;



    // }




















    // ███████ ██ ██      ██          ██   ██ ██ ███████ ████████  ██████   ██████  ██████   █████  ███    ███ ███████
    // ██      ██ ██      ██          ██   ██ ██ ██         ██    ██    ██ ██       ██   ██ ██   ██ ████  ████ ██
    // █████   ██ ██      ██          ███████ ██ ███████    ██    ██    ██ ██   ███ ██████  ███████ ██ ████ ██ ███████
    // ██      ██ ██      ██          ██   ██ ██      ██    ██    ██    ██ ██    ██ ██   ██ ██   ██ ██  ██  ██      ██
    // ██      ██ ███████ ███████     ██   ██ ██ ███████    ██     ██████   ██████  ██   ██ ██   ██ ██      ██ ███████

    // vertices
    vertex_N = vertex_x->size();
    for(int j=0; j<vertex_N; j++){
      x_vertex->Fill(vertex_x->at(j));
      y_vertex->Fill(vertex_y->at(j));
      z_vertex->Fill(vertex_z->at(j));
    }

    // jets
    jet_N = v_jet_pt.size();
    N_jets->Fill(jet_N);
    for(int j=0; j<jet_N; j++){
      pt_jet      ->Fill(v_jet_pt      .at(j));
      eta_jet     ->Fill(v_jet_eta     .at(j));
      phi_jet     ->Fill(v_jet_phi     .at(j));
      m_jet       ->Fill(v_jet_mass    .at(j));
      btag_jet    ->Fill(v_jet_btag    .at(j));
      btagalgo_jet->Fill(v_jet_btagalgo.at(j));
      flavor_jet  ->Fill(v_jet_flavor  .at(j));
    }
    if(jet_N > 0) pt_jet1->Fill(v_jet_pt.at(0));
    if(jet_N > 1) pt_jet2->Fill(v_jet_pt.at(1));
    if(jet_N > 2) pt_jet3->Fill(v_jet_pt.at(2));

    // fat jets
    fatjet_N = v_fatjet_pt.size();
    N_fatjets->Fill(fatjet_N);
    for(int j=0; j<fatjet_N; j++){
      pt_fatjet                 ->Fill(v_fatjet_pt                 .at(j));
      eta_fatjet                ->Fill(v_fatjet_eta                .at(j));
      phi_fatjet                ->Fill(v_fatjet_phi                .at(j));
      mass_fatjet               ->Fill(v_fatjet_mass               .at(j));
      ncharged_fatjet           ->Fill(v_fatjet_ncharged           .at(j));
      nneutral_fatjet           ->Fill(v_fatjet_nneutral           .at(j));
      tau1_fatjet               ->Fill(v_fatjet_tau1               .at(j));
      tau2_fatjet               ->Fill(v_fatjet_tau2               .at(j));
      tau3_fatjet               ->Fill(v_fatjet_tau3               .at(j));
      tau4_fatjet               ->Fill(v_fatjet_tau4               .at(j));
      tau5_fatjet               ->Fill(v_fatjet_tau5               .at(j));
      tau32_fatjet              ->Fill(v_fatjet_tau32              .at(j));
      softdropmass_fatjet       ->Fill(v_fatjet_softdropmass       .at(j));
      nsubjetssoftdropped_fatjet->Fill(v_fatjet_nsubjetssoftdropped.at(j));
    }
    if(fatjet_N > 0) pt_fatjet1->Fill(v_fatjet_pt.at(0));
    if(fatjet_N > 1) pt_fatjet2->Fill(v_fatjet_pt.at(1));

    // electrons
    electron_N = v_electron_pt.size();
    N_electrons->Fill(electron_N);
    for(int j=0; j<electron_N; j++){
      pt_electron    ->Fill(v_electron_pt    .at(j));
      eta_electron   ->Fill(v_electron_eta   .at(j));
      phi_electron   ->Fill(v_electron_phi   .at(j));
      charge_electron->Fill(v_electron_charge.at(j));
    }

    // muons
    muon_N = v_muon_pt.size();
    N_muons->Fill(muon_N);
    for(int j=0; j<muon_N; j++){
      pt_muon    ->Fill(v_muon_pt    .at(j));
      eta_muon   ->Fill(v_muon_eta   .at(j));
      phi_muon   ->Fill(v_muon_phi   .at(j));
      charge_muon->Fill(v_muon_charge.at(j));
    }

    // MET
    ptmiss    ->Fill(MET);
    phi_ptmiss->Fill(MET_phi);
  }

  cout << "----- 100% -----" << endl;
  cout << endl;
  cout << "       N_total: " << N_total        << endl;
  cout << "      N_presel: " << N_presel       << endl;
  cout << "     N_fullsel: " << N_fullsel      << endl;
  cout << "   N_elchannel: " << N_elchannel    << endl;
  cout << "   N_muchannel: " << N_muchannel    << endl;
  cout << "N_notoptagreco: " << N_notoptagreco << endl;
  cout << "  N_toptagreco: " << N_toptagreco   << endl;
  cout << "        N_chi2: " << N_chi2         << endl;
  cout << "   N_chi2cut30: " << N_chi2cut30    << endl;
}

analysis_module::~analysis_module()
{
}

DEFINE_FWK_MODULE(analysis_module);
