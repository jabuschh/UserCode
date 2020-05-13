#ifndef AnalysisTemplate_h
#define AnalysisTemplate_h

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

float DeltaR(float eta1,float phi1,float eta2,float phi2)
{
  float deltaPhi = TMath::Abs(phi1-phi2);
  float deltaEta = eta1-eta2;
  if(deltaPhi > TMath::Pi())
  deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
}

class Analysis_Template_MC : public edm::EDAnalyzer
{
public:
  explicit Analysis_Template_MC(edm::ParameterSet const& cfg);
  virtual void beginJob();
  virtual void analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup);
  virtual void endJob();
  virtual ~Analysis_Template_MC();

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

  /*
  ██████  ███████  ██████ ██       █████  ██████  ███████     ██   ██ ██ ███████ ████████ ███████
  ██   ██ ██      ██      ██      ██   ██ ██   ██ ██          ██   ██ ██ ██         ██    ██
  ██   ██ █████   ██      ██      ███████ ██████  █████       ███████ ██ ███████    ██    ███████
  ██   ██ ██      ██      ██      ██   ██ ██   ██ ██          ██   ██ ██      ██    ██         ██
  ██████  ███████  ██████ ███████ ██   ██ ██   ██ ███████     ██   ██ ██ ███████    ██    ███████
  */

  //jets
  TH1F *N_jets;
  TH1F *pt_jet;
  TH1F *pt_jet1;
  TH1F *pt_jet2;
  TH1F *pt_jet3;
  TH1F *eta_jet;
  TH1F *phi_jet;
  TH1F *E_jet;
  TH1F *m_jet;
  //top
  // TH1F *id_top;
  // TH1F *status_top;
  TH1F *pt_top;
  TH1F *eta_top;
  TH1F *phi_top;
  TH1F *E_top;
  //antitop
  // TH1F *id_antitop;
  // TH1F *status_antitop;
  TH1F *pt_antitop;
  TH1F *eta_antitop;
  TH1F *phi_antitop;
  TH1F *E_antitop;
  //ditop mass
  TH1F *mass_ditop;
  //W boson
  // TH1F *id_W;
  // TH1F *status_W;
  TH1F *pt_W;
  TH1F *eta_W;
  TH1F *phi_W;
  TH1F *E_W;
  // EFT weights
  TH1F *EFTweight_cQq81;
};

#endif
