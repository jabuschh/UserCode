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

Analysis_Template_MC::Analysis_Template_MC(edm::ParameterSet const& cfg)
{
  mFileName     = cfg.getParameter<std::string>("filename");
  mTreeName     = cfg.getParameter<std::string>("treename");
  mDirName      = cfg.getParameter<std::string>("dirname");
  mIsMCarlo     = cfg.getUntrackedParameter<bool>("isMCarlo");
  mCrossSection = cfg.getUntrackedParameter<double>("CrossSection");
  mIntLumi      = cfg.getUntrackedParameter<double>("IntLumi");
  mTriggers     = cfg.getUntrackedParameter<std::vector<std::string>>("Triggers");
}

void Analysis_Template_MC::beginJob()
{
  model = "SMEFT_";
  // WilsonCoeff = "cQd8";
  // WilsonCoeff = "cQq81";
  // WilsonCoeff = "cQq83";
  // WilsonCoeff = "cQu8";
  // WilsonCoeff = "ctG";
  // WilsonCoeff = "ctd8";
  // WilsonCoeff = "ctq8";
  WilsonCoeff = "ctu8";
  cout << "Wilson coefficient: " << model + WilsonCoeff << endl;
  cout << endl;
  cout << "beginning job..." << endl;
  mInf = TFile::Open(mFileName.c_str());
  mDir = (TDirectoryFile*)mInf->Get(mDirName.c_str());
  mTree = (TTree*)mDir->Get(mTreeName.c_str());

  /*
  // ██████   ██████   ██████  ██   ██     ██   ██ ██ ███████ ████████ ███████
  // ██   ██ ██    ██ ██    ██ ██  ██      ██   ██ ██ ██         ██    ██
  // ██████  ██    ██ ██    ██ █████       ███████ ██ ███████    ██    ███████
  // ██   ██ ██    ██ ██    ██ ██  ██      ██   ██ ██      ██    ██         ██
  // ██████   ██████   ██████  ██   ██     ██   ██ ██ ███████    ██    ███████
  */
  cout << "booking hists..." << endl;
  //jets
  N_jets   = fs->make<TH1F>("N_jets","N_jets",20,0,20);        N_jets->Sumw2();
  pt_jet   = fs->make<TH1F>("pt_jet","pt_jet",45,0,900);       pt_jet->Sumw2();
  pt_jet1  = fs->make<TH1F>("pt_jet1","pt_jet1",45,0,900);     pt_jet1->Sumw2();
  pt_jet2  = fs->make<TH1F>("pt_jet2","pt_jet2",45,0,900);     pt_jet2->Sumw2();
  pt_jet3  = fs->make<TH1F>("pt_jet3","pt_jet3",45,0,900);     pt_jet3->Sumw2();
  eta_jet  = fs->make<TH1F>("eta_jet","eta_jet",50,-2.5,2.5);  eta_jet->Sumw2();
  phi_jet  = fs->make<TH1F>("phi_jet","phi_jet",35,-3.5,3.5);  phi_jet->Sumw2();
  E_jet    = fs->make<TH1F>("E_jet","E_jet",100,0,2000);       E_jet->Sumw2();
  m_jet    = fs->make<TH1F>("m_jet","m_jet",50,0,500);         m_jet->Sumw2();
  //top
  // id_top     = fs->make<TH1F>("id_top","id_top",50,-25.,25.);          id_top->Sumw2();
  // status_top = fs->make<TH1F>("status_top","status_top",60,0.,60.);    status_top->Sumw2();
  pt_top     = fs->make<TH1F>("pt_top","pt_top",75,0,1500);               pt_top->Sumw2();
  eta_top    = fs->make<TH1F>("eta_top","eta_top",50,-2.5,2.5);           eta_top->Sumw2();
  phi_top    = fs->make<TH1F>("phi_top","phi_top",35,-3.5,3.5);           phi_top->Sumw2();
  E_top      = fs->make<TH1F>("E_top","E_top",200,0,4000);                E_top->Sumw2();
  //antitop
  // id_antitop     = fs->make<TH1F>("id_antitop","id_antitop",50,-25.,25.);          id_antitop->Sumw2();
  // status_antitop = fs->make<TH1F>("status_antitop","status_antitop",60,0.,60.);    status_antitop->Sumw2();
  pt_antitop     = fs->make<TH1F>("pt_antitop","pt_antitop",75,0,1500);               pt_antitop->Sumw2();
  eta_antitop    = fs->make<TH1F>("eta_antitop","eta_antitop",50,-2.5,2.5);           eta_antitop->Sumw2();
  phi_antitop    = fs->make<TH1F>("phi_antitop","phi_antitop",35,-3.5,3.5);           phi_antitop->Sumw2();
  E_antitop      = fs->make<TH1F>("E_antitop","E_antitop",200,0,4000);                E_antitop->Sumw2();
  // ditop mass
  mass_ditop = fs->make<TH1F>("mass_ditop","mass_ditop",200,0,4000);   mass_ditop->Sumw2();
  //W boson
  // id_W     = fs->make<TH1F>("id_W","id_W",50,-25.,25.);          id_W->Sumw2();
  // status_W = fs->make<TH1F>("status_W","status_W",60,0.,60.);    status_W->Sumw2();
  pt_W     = fs->make<TH1F>("pt_W","pt_W",75,0,1500);               pt_W->Sumw2();
  eta_W    = fs->make<TH1F>("eta_W","eta_W",50,-2.5,2.5);           eta_W->Sumw2();
  phi_W    = fs->make<TH1F>("phi_W","phi_W",35,-3.5,3.5);           phi_W->Sumw2();
  E_W      = fs->make<TH1F>("E_W","E_W",200,0,4000);                E_W->Sumw2();
  // EFT weights
  EFTweight = fs->make<TH1F>("EFTweight","EFTweight",200,-100,100); EFTweight->Sumw2();
}


void Analysis_Template_MC::endJob()
{
  cout << "finishing job..." << endl;
  mInf->Close();
}

/*
//  █████  ███    ██  █████  ██      ███████ ██    ██ ███████ ██████
// ██   ██ ████   ██ ██   ██ ██         ███   ██  ██  ██      ██   ██
// ███████ ██ ██  ██ ███████ ██        ███     ████   █████   ██████
// ██   ██ ██  ██ ██ ██   ██ ██       ███       ██    ██      ██   ██
// ██   ██ ██   ████ ██   ██ ███████ ███████    ██    ███████ ██   ██
*/


void Analysis_Template_MC::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup)
{
  //reading in tree
  unsigned NEntries = mTree->GetEntries();
  cout << "reading in the tree..." << endl;
  cout << "total number of events: " << NEntries << endl;

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
  float hweight = 1.;  //Initial value set to one
  // int decay_ = 0;
  // double weight_ = 0;
  // float genEvtWeight_ = 0;
  // float lheOriginalXWGTUP_ = 0;
  //jets
  int nGenJets_ = 0;
  std::vector<float>* GenJetpt_         = 0;
  std::vector<float>* GenJeteta_        = 0;
  std::vector<float>* GenJetphi_        = 0;
  std::vector<float>* GenJetenergy_     = 0;
  std::vector<float>* GenJetmass_       = 0;
  std::vector<float>* GenSoftDropMass_  = 0;
  std::vector<float>* GenSoftDropTau32_ = 0;
  std::vector<float>* GenSoftDropTau31_ = 0;
  std::vector<float>* GenSoftDropTau3_  = 0;
  std::vector<float>* GenSoftDropTau2_  = 0;
  std::vector<float>* GenSoftDropTau1_  = 0;
  //tops
  std::vector<float>* TopPt_  = 0;
  std::vector<float>* TopEta_ = 0;
  std::vector<float>* TopPhi_ = 0;
  std::vector<float>* TopE_   = 0;
  //antitops
  std::vector<float>* AntiTopPt_  = 0;
  std::vector<float>* AntiTopEta_ = 0;
  std::vector<float>* AntiTopPhi_ = 0;
  std::vector<float>* AntiTopE_   = 0;
  //ditopmass
  std::vector<float>* DiTopMass_ = 0;
  //W boson
  // std::vector<int>*   WBosonId_  = 0;
  // std::vector<int>*   WBosonSt_  = 0;
  std::vector<float>* WBosonPt_  = 0;
  std::vector<float>* WBosonEta_ = 0;
  std::vector<float>* WBosonPhi_ = 0;
  std::vector<float>* WBosonE_   = 0;
  // EFT weights
  std::vector<float>*  EFTWeights_      = 0;
  std::vector<string>* EFTWeightsNames_ = 0;



  /*
  // ███████ ███████ ████████ ████████ ██ ███    ██  ██████      ██████  ██████   █████  ███    ██  ██████ ██   ██      █████  ██████  ██████  ██████  ███████ ███████ ███████ ███████ ███████
  // ██      ██         ██       ██    ██ ████   ██ ██           ██   ██ ██   ██ ██   ██ ████   ██ ██      ██   ██     ██   ██ ██   ██ ██   ██ ██   ██ ██      ██      ██      ██      ██
  // ███████ █████      ██       ██    ██ ██ ██  ██ ██   ███     ██████  ██████  ███████ ██ ██  ██ ██      ███████     ███████ ██   ██ ██   ██ ██████  █████   ███████ ███████ █████   ███████
  //      ██ ██         ██       ██    ██ ██  ██ ██ ██    ██     ██   ██ ██   ██ ██   ██ ██  ██ ██ ██      ██   ██     ██   ██ ██   ██ ██   ██ ██   ██ ██           ██      ██ ██           ██
  // ███████ ███████    ██       ██    ██ ██   ████  ██████      ██████  ██   ██ ██   ██ ██   ████  ██████ ██   ██     ██   ██ ██████  ██████  ██   ██ ███████ ███████ ███████ ███████ ███████
  */
  cout << "setting branch addresses..." << endl;
  //monte carlo...

  //jets
  mTree->SetBranchAddress("nGenJets",&nGenJets_);
  mTree->SetBranchAddress("GenJetpt",&GenJetpt_);
  mTree->SetBranchAddress("GenJeteta",&GenJeteta_);
  mTree->SetBranchAddress("GenJetphi",&GenJetphi_);
  mTree->SetBranchAddress("GenJetenergy",&GenJetenergy_);
  mTree->SetBranchAddress("GenJetmass",&GenJetmass_);
  mTree->SetBranchAddress("GenSoftDropMass",&GenSoftDropMass_);
  mTree->SetBranchAddress("GenSoftDropTau32",&GenSoftDropTau32_);
  mTree->SetBranchAddress("GenSoftDropTau31",&GenSoftDropTau31_);
  mTree->SetBranchAddress("GenSoftDropTau3",&GenSoftDropTau3_);
  mTree->SetBranchAddress("GenSoftDropTau2",&GenSoftDropTau2_);
  mTree->SetBranchAddress("GenSoftDropTau1",&GenSoftDropTau1_);
  //tops
  mTree->SetBranchAddress("TopPt",&TopPt_);
  mTree->SetBranchAddress("TopEta",&TopEta_);
  mTree->SetBranchAddress("TopPhi",&TopPhi_);
  mTree->SetBranchAddress("TopE",&TopE_);
  //antitops
  mTree->SetBranchAddress("AntiTopPt",&AntiTopPt_);
  mTree->SetBranchAddress("AntiTopEta",&AntiTopEta_);
  mTree->SetBranchAddress("AntiTopPhi",&AntiTopPhi_);
  mTree->SetBranchAddress("AntiTopE",&AntiTopE_);
  //ditopmass
  mTree->SetBranchAddress("DiTopMass",&DiTopMass_);
  //W boson
  // mTree->SetBranchAddress("WBosonId",&WBosonId_);
  // mTree->SetBranchAddress("WBosonSt",&WBosonSt_);
  mTree->SetBranchAddress("WBosonPt",&WBosonPt_);
  mTree->SetBranchAddress("WBosonEta",&WBosonEta_);
  mTree->SetBranchAddress("WBosonPhi",&WBosonPhi_);
  mTree->SetBranchAddress("WBosonE",&WBosonE_);
  // EFT weights
  mTree->SetBranchAddress("EFTWeights",&EFTWeights_);
  mTree->SetBranchAddress("EFTWeightsNames",&EFTWeightsNames_);




  TString output_filename = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/" + model + WilsonCoeff + ".root";
  TFile* output_file = new TFile(output_filename, "RECREATE");
  cout << "setting output file: " + output_filename << endl;
  cout << endl;

  vector<TString> v_EFTweightnames;
  if(WilsonCoeff.EqualTo("ctG")){
    v_EFTweightnames = {
      "rwgt_" + WilsonCoeff + "_min0p25",
      "rwgt_" + WilsonCoeff + "_min0p2",
      "rwgt_" + WilsonCoeff + "_min0p15",
      "rwgt_" + WilsonCoeff + "_min0p1",
      "rwgt_" + WilsonCoeff + "_min0p05",
      "rwgt_SM",
      "rwgt_" + WilsonCoeff + "_0p05",
      "rwgt_" + WilsonCoeff + "_0p1",
      "rwgt_" + WilsonCoeff + "_0p15",
      "rwgt_" + WilsonCoeff + "_0p2",
      "rwgt_" + WilsonCoeff + "_0p25"
    };
  }
  else{
    v_EFTweightnames = {
      "rwgt_" + WilsonCoeff + "_min5p0",
      "rwgt_" + WilsonCoeff + "_min4p0",
      "rwgt_" + WilsonCoeff + "_min3p0",
      "rwgt_" + WilsonCoeff + "_min2p0",
      "rwgt_" + WilsonCoeff + "_min1p0",
      "rwgt_SM",
      "rwgt_" + WilsonCoeff + "_1p0",
      "rwgt_" + WilsonCoeff + "_2p0",
      "rwgt_" + WilsonCoeff + "_3p0",
      "rwgt_" + WilsonCoeff + "_4p0",
      "rwgt_" + WilsonCoeff + "_5p0"
    };
  }



  for(unsigned int l=0; l<v_EFTweightnames.size(); l++){   //loop over EFT weights
    TString weightName_local = v_EFTweightnames.at(l);
    cout << "EFT weight name: " << weightName_local << endl;
    cout << "creating root directory: " << weightName_local << endl;
    output_file->mkdir(weightName_local);
    output_file->cd(weightName_local);

    vector<TH1F*> v_hists;  //vector for saving the hists

    /*
    // ███████ ██    ██ ███████ ███    ██ ████████     ██       ██████   ██████  ██████
    // ██      ██    ██ ██      ████   ██    ██        ██      ██    ██ ██    ██ ██   ██
    // █████   ██    ██ █████   ██ ██  ██    ██        ██      ██    ██ ██    ██ ██████
    // ██       ██  ██  ██      ██  ██ ██    ██        ██      ██    ██ ██    ██ ██
    // ███████   ████   ███████ ██   ████    ██        ███████  ██████   ██████  ██
    */
    cout << "starting event loop..." << endl;
    for(unsigned  i=0; i<NEntries; i++){
      //progress report
      double progress = 10.0*i / (1.0*NEntries);
      int k = TMath::FloorNint(progress);
      if(k > decade)
      cout << "-----  "<< 10*k << "%" << " -----" << endl;
      decade = k;
      //reading the event
      mTree->GetEntry(i);


      // if(mIsMCarlo){
      //    hweight = mCrossSection / NEntries;
      // }
      // cout << "hweight: " << hweight << endl;


      // EFT weights
      float weight_local = -99; //default value fot cross check
      for(unsigned int b=0; b<EFTWeightsNames_->size(); b++){
        if(weightName_local.EqualTo(EFTWeightsNames_->at(b))){
          weight_local = EFTWeights_->at(b);
          hweight = (1. + weight_local);   // for EFT
          // hweight = weight_local;              // for ALP
          EFTweight->Fill(hweight);
          // cout << "       weightName_local: " << weightName_local << endl;
          // cout << "EFTWeightsNames_->at(b): " << EFTWeightsNames_->at(b) << endl;
          // cout << "           weight_local: " << weight_local << endl;
        }
      }


      //jets
      N_jets->Fill(nGenJets_,hweight);
      if(nGenJets_ > 0) pt_jet1->Fill(GenJetpt_->at(0),hweight);
      if(nGenJets_ > 1) pt_jet2->Fill(GenJetpt_->at(1),hweight);
      if(nGenJets_ > 2) pt_jet3->Fill(GenJetpt_->at(2),hweight);
      for(int j=0; j<nGenJets_; j++){
        pt_jet ->Fill(GenJetpt_->at(j),hweight);
        eta_jet->Fill(GenJeteta_->at(j),hweight);
        phi_jet->Fill(GenJetphi_->at(j),hweight);
        E_jet  ->Fill(GenJetenergy_->at(j),hweight);
        m_jet  ->Fill(GenJetmass_->at(j),hweight);
      }
      //top
      for(unsigned int j=0; j<TopPt_->size(); j++){
        // id_top    ->Fill(,hweight);
        // status_top->Fill(,hweight);
        pt_top    ->Fill(TopPt_->at(j),hweight);
        eta_top   ->Fill(TopEta_->at(j),hweight);
        phi_top   ->Fill(TopPhi_->at(j),hweight);
        E_top     ->Fill(TopE_->at(j),hweight);
      }
      //antitop
      for(unsigned int j=0; j<AntiTopPt_->size(); j++){
        // id_tantiop    ->Fill(,hweight);
        // status_antitop->Fill(,hweight);
        pt_antitop    ->Fill(AntiTopPt_->at(j),hweight);
        eta_antitop   ->Fill(AntiTopEta_->at(j),hweight);
        phi_antitop   ->Fill(AntiTopPhi_->at(j),hweight);
        E_antitop     ->Fill(AntiTopE_->at(j),hweight);
      }
      //ditop mass
      mass_ditop->Fill(DiTopMass_->at(0),hweight);
      //W boson
      for(unsigned int j=0; j<WBosonPt_->size(); j++){
        // id_W    ->Fill();
        // status_W->Fill();
        pt_W    ->Fill(WBosonPt_->at(j),hweight);
        eta_W   ->Fill(WBosonEta_->at(j),hweight);
        phi_W   ->Fill(WBosonPhi_->at(j),hweight);
        E_W     ->Fill(WBosonE_->at(j),hweight);
      }
    }

    cout << "----- 100% -----" << endl;

    // write hists to the root file
    cout << "writing hists to root file..." << endl;
    // if(weightName_local.EndsWith("_min5p0"))
    v_hists.push_back(EFTweight);
    v_hists.push_back(N_jets);
    v_hists.push_back(pt_jet1);
    v_hists.push_back(pt_jet2);
    v_hists.push_back(pt_jet3);
    v_hists.push_back(pt_jet);
    v_hists.push_back(eta_jet);
    v_hists.push_back(phi_jet);
    v_hists.push_back(E_jet);
    v_hists.push_back(m_jet);
    v_hists.push_back(pt_top);
    v_hists.push_back(eta_top);
    v_hists.push_back(phi_top);
    v_hists.push_back(E_top);
    v_hists.push_back(pt_antitop);
    v_hists.push_back(eta_antitop);
    v_hists.push_back(phi_antitop);
    v_hists.push_back(E_antitop);
    v_hists.push_back(mass_ditop);
    v_hists.push_back(pt_W);
    v_hists.push_back(eta_W);
    v_hists.push_back(phi_W);
    v_hists.push_back(E_W);

    for(unsigned int a=0; a<v_hists.size(); a++){
      v_hists.at(a)->Write();
      v_hists.at(a)->Reset("M");
    };

    cout << endl;
  }
  output_file->Close();



}

Analysis_Template_MC::~Analysis_Template_MC()
{
}

DEFINE_FWK_MODULE(Analysis_Template_MC);
