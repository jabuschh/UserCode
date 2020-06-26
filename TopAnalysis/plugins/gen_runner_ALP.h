#ifndef gen_runner_ALP_h
#define gen_runner_ALP_h

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionData.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionEvaluator.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionParser.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Candidate/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/JetReco/interface/JetCollection.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"
#include "JetMETCorrections/Objects/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/contrib/SoftDrop.hh"

using namespace reco;

class gen_runner_ALP : public edm::EDAnalyzer
{
public:
  typedef reco::Particle::LorentzVector LorentzVector;
  explicit gen_runner_ALP(edm::ParameterSet const& cfg);
  virtual void beginJob();
  virtual void beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup);
  virtual void endRun(edm::Run const& iRun, edm::EventSetup const& iSetup);
  virtual void analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup);
  virtual void endJob();
  virtual ~gen_runner_ALP();

private:
  void initialize();
  //---- configurable parameters --------
  edm::EDGetTokenT<GenJetCollection> genjetsToken;
  edm::EDGetTokenT<GenEventInfoProduct> genEvtInfoToken;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesToken;
  edm::EDGetTokenT<LHEEventProduct> lheEvtInfoToken;

  double etaMax_,ptMin_,ptMinLeading_,massMin_,btagMin_,minMuPt_,minElPt_,GenetaMax_,GenptMin_;
  bool   isMC_,isPrint_,saveWeights_,debug_,isHigherOrder_;
  //---------------------------------------------------
  edm::Service<TFileService> fs_;
  TTree *outTree_;
  int   run_,evt_,nVtx_,lumi_,nJets_,nBJets_,nLeptons_,nGenJets_,decay_;
  double weight_;

  bool printWeights;

  std::vector<string> weight_vector_;

  float genEvtWeight_,lheOriginalXWGTUP_;
  std::vector<float> *scaleWeights_,*pdfWeights_;

  TH1F *EventsHisto_;

  std::vector<int>   *WBosonId_,*WBosonSt_;
  std::vector<float> *WBosonPt_,*WBosonEta_,*WBosonPhi_,*WBosonE_;

  std::vector<float> *TopPt_,*TopEta_,*TopPhi_,*TopE_,*DiTopMass_;
  std::vector<float> *AntiTopPt_,*AntiTopEta_,*AntiTopPhi_,*AntiTopE_;

  //gen jets
  std::vector<float> *GenSoftDropMass_,*GenSoftDropTau32_,*GenSoftDropTau31_,*GenSoftDropTau3_,*GenSoftDropTau1_,*GenSoftDropTau2_;
  std::vector<float> *GenJetpt_;
  std::vector<float> *GenJetphi_;
  std::vector<float> *GenJeteta_;
  std::vector<float> *GenJetenergy_;
  std::vector<float> *GenJetmass_;

  edm::Handle<GenJetCollection> genjets;
  edm::Handle<edm::View<reco::GenParticle> > genParticles;
  edm::Handle<GenEventInfoProduct> genEvtInfo;
  edm::Handle<LHEEventProduct> lheEvtInfo;

  //fastjet
  fastjet::Filter* fTrimmer1;
  fastjet::JetDefinition*       fAKJetDef;
  fastjet::ActiveAreaSpec*      fActiveArea;
  fastjet::AreaDefinition*      fAreaDefinition;
  fastjet::ClusterSequenceArea* fClustering;
  fastjet::contrib::SoftDrop* sd;
};





#endif
