#ifndef analysis_module_h
#define analysis_module_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TProfile.h"
#include <TMath.h>
using namespace edm;
using namespace std;

float deltaR(float eta1,float phi1,float eta2,float phi2)
{
  float deltaEta = TMath::Abs(eta1-eta2);
  float deltaPhi = TMath::Abs(phi1-phi2);
  // if(deltaPhi > TMath::Pi()) deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
}

class analysis_module : public edm::EDAnalyzer
{
public:
  explicit analysis_module(edm::ParameterSet const& cfg);
  virtual void beginJob();
  virtual void analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup);
  virtual void endJob();
  virtual ~analysis_module();

private:
  std::string mFileName,mTreeName,mDirName;

  double mMinPt, mYMax;
  int mJetID;         // looseID==1 tightID==2
  int mprintOk;       // noPrint=0  Print=1
  bool mIsMCarlo;
  double mCrossSection;
  double mIntLumi;
  vector<std::string> mTriggers;

  edm::Service<TFileService> fs;
  TTree *mTree;
  TFile *mInf, *mPuf;
  TDirectoryFile *mDir;

  const double electron_mass = 0.0005109989461;
  const double muon_mass     = 105.6583745;
  const double Wboson_mass   = 80.379;


  /*
  ██████  ███████  ██████ ██       █████  ██████  ███████     ██   ██ ██ ███████ ████████ ███████
  ██   ██ ██      ██      ██      ██   ██ ██   ██ ██          ██   ██ ██ ██         ██    ██
  ██   ██ █████   ██      ██      ███████ ██████  █████       ███████ ██ ███████    ██    ███████
  ██   ██ ██      ██      ██      ██   ██ ██   ██ ██          ██   ██ ██      ██    ██         ██
  ██████  ███████  ██████ ███████ ██   ██ ██   ██ ███████     ██   ██ ██ ███████    ██    ███████
  */

  // parton level
  // jets
  TH1F* N_genjet;
  TH1F* pt_genjet;
  TH1F* pt_genjet1;
  TH1F* pt_genjet2;
  TH1F* eta_genjet;
  TH1F* phi_genjet;
  TH1F* mass_genjet;
  TH1F* ST_genjet;

  // tops
  TH1F* N_gentop;
  TH1F* id_gentop;
  TH1F* status_gentop;
  TH1F* daughter1_gentop;
  TH1F* daughter2_gentop;
  TH1F* pt_gentop;
  TH1F* eta_gentop;
  TH1F* phi_gentop;
  TH1F* mass_gentop;
  TH1F* deltaEta_gentops;
  TH1F* deltaPhi_gentops;
  TH1F* deltaR_gentops;


  // detector level
  // vertices
  TH1F *x_vertex;
  TH1F *y_vertex;
  TH1F *z_vertex;

  // jets
  TH1F *N_jets;
  TH1F *pt_jet;
  TH1F *pt_jet1;
  TH1F *pt_jet2;
  TH1F *pt_jet3;
  TH1F *eta_jet;
  TH1F *phi_jet;
  TH1F *m_jet;
  TH1F *btag_jet;
  TH1F *btagalgo_jet;
  TH1F *flavor_jet;

  // fat jets
  TH1F *N_fatjets;
  TH1F *pt_fatjet;
  TH1F *pt_fatjet1;
  TH1F *pt_fatjet2;
  TH1F *eta_fatjet;
  TH1F *phi_fatjet;
  TH1F *mass_fatjet;
  TH1F *ncharged_fatjet;
  TH1F *nneutral_fatjet;
  TH1F *tau1_fatjet;
  TH1F *tau2_fatjet;
  TH1F *tau3_fatjet;
  TH1F *tau4_fatjet;
  TH1F *tau5_fatjet;
  TH1F *tau32_fatjet;
  TH1F *softdropmass_fatjet;
  TH1F *nsubjetssoftdropped_fatjet;


  // electrons
  TH1F *N_electrons;
  TH1F *pt_electron;
  TH1F *eta_electron;
  TH1F *phi_electron;
  TH1F *isovar_electron;
  TH1F *charge_electron;

  // muon
  TH1F *N_muons;
  TH1F *pt_muon;
  TH1F *eta_muon;
  TH1F *phi_muon;
  TH1F *isovar_muon;
  TH1F *charge_muon;

  // MET
  TH1F *ptmiss;
  TH1F *phi_ptmiss;


  // reco level
  TH1F *chi_square_had;
  TH1F *chi_square_lep;
  TH1F *chi_square;
  TH1F *m_top_had;
  TH1F *m_top_lep;
  TH1F *m_ttbar;


};

#endif
