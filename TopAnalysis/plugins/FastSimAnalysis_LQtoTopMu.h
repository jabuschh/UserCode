#ifndef FastSimAnalysis_LQtoTopMu_h
#define FastSimAnalysis_LQtoTopMu_h
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

float DeltaPhiFSA(float phi1, float phi2)
{
	float dPhi = TMath::Abs(phi1 - phi2);
	if(dPhi > TMath::Pi())
	{
		dPhi = TMath::TwoPi() - dPhi;
	}
	return dPhi;
}

float DeltaEtaFSA(float eta1, float eta2)
{
	return eta1 - eta2;
}

float DeltaRFSA(float eta1, float phi1, float eta2, float phi2)
{
	float deltaEta = DeltaEtaFSA(eta1,eta2);
	float deltaPhi = DeltaPhiFSA(phi1, phi2);
	return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
}


class FastSimAnalysis_LQtoTopMu : public edm::EDAnalyzer
{

public:
	//typedef reco::Particle::LorentzVector LorentzVector;
	explicit FastSimAnalysis_LQtoTopMu(edm::ParameterSet const& cfg);
	virtual void beginJob();
	virtual void analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup);
	virtual void endJob();
	virtual ~FastSimAnalysis_LQtoTopMu();

private:
	// PARAMETERS
	std::string mFileName,mTreeName,mDirName;
	double mMinPt, mYMax;
	int mJetID;	// looseID == 1,  tightID == 2
	bool mIsMCarlo;
	bool mElSelection;
	bool mMuSelection;
	bool mHadSelection;
	double mCrossSection;
	double mIntLumi;
	vector<std::string> mTriggers;
	edm::Service<TFileService> fs;
	TTree *mTree;
	TFile *mInf, *mPuf;
	TDirectoryFile *mDir;

	/*
	██ ███    ██ ███████ ████████  █████  ███    ██ ████████ ██  █████  ████████ ███████     ██   ██ ██ ███████ ████████  ██████   ██████  ██████   █████  ███    ███ ███████
	██ ████   ██ ██         ██    ██   ██ ████   ██    ██    ██ ██   ██    ██    ██          ██   ██ ██ ██         ██    ██    ██ ██       ██   ██ ██   ██ ████  ████ ██
	██ ██ ██  ██ ███████    ██    ███████ ██ ██  ██    ██    ██ ███████    ██    █████       ███████ ██ ███████    ██    ██    ██ ██   ███ ██████  ███████ ██ ████ ██ ███████
	██ ██  ██ ██      ██    ██    ██   ██ ██  ██ ██    ██    ██ ██   ██    ██    ██          ██   ██ ██      ██    ██    ██    ██ ██    ██ ██   ██ ██   ██ ██  ██  ██      ██
	██ ██   ████ ███████    ██    ██   ██ ██   ████    ██    ██ ██   ██    ██    ███████     ██   ██ ██ ███████    ██     ██████   ██████  ██   ██ ██   ██ ██      ██ ███████
	*/
	// in general
	TH1D *N_noCuts;
	TH1D *N_preSel;
	TH1D *N_bTag;
	TH1D *N_invMuMass;
	TH1D *N_STlep;
	TH1D *N_catA;
	TH1D *N_catAmu;
	TH1D *N_catAel;
	TH1D *N_catB;

	// RECO level
	// jets
	TH1F *N_jets;
	TH1F *pT_jets;
	TH1F *eta_jets;
	TH1F *phi_jets;
	TH1F *m_jets;
	TH1F *bTag_jets;
	TH1F *bTagAlgo_jets;
	TH1F *flavor_jets;
	// muons
	TH1F *N_mus;
	TH1F *pT_mus;
	TH1F *eta_mus;
	TH1F *phi_mus;
	TH1F *charge_mus;
	TH1F *isoVar_mus;
	TH1F *isoVarRhoCorr_mus;
	// electrons
	TH1F *N_els;
	TH1F *pT_els;
	TH1F *eta_els;
	TH1F *phi_els;
	TH1F *charge_els;
	TH1F *isoVar_els;
	TH1F *isoVarRhoCorr_els;
	// MET
	TH1F *ETmiss;
	TH1F *phi_ETmiss;
	// results: cat A
	TH1F *M_Ws;
	TH1F *M_LQs_binArne;
	TH1F *M_LQs;
	TH1F *M_LQs_lep;
	TH1F *M_LQs_had;
	TH1F *pT_LQs;
	TH1F *eta_LQs;
	TH1F *m_tops;
	TH1F *m_tops_lep;
	TH1F *m_tops_had;
	TH1F *pT_tops;
	TH1F *eta_tops;
	TH1F *chiSquare;
	// results: cat B
	TH1F *ST_binArne;
	TH1F *ST;

	// cut flow
	TH1F *cutflow_total;
	TH1F *cutflow_rel;

	// resolution
	TH1F *pTresolution_jets;
	TH1F *pTresolution_mus;
	TH1F *pTresolution_els;

	// isolation efficiencies
	TH1F *N_mus_iso;
	TH1F *N_els_iso;
	TH1F *pT_mus_iso;
	TH1F *pT_mus_iso_total;
	TH1F *pT_els_iso;
	TH1F *pT_els_iso_total;

	// btag efficiencies
	TH1F *pT_btag1;
	TH1F *pT_btag2;
	TH1F *pT_btag3;
	TH1F *pT_btag4;
	TH1F *pT_btag5;
	TH1F *pT_btag6;
	TH1F *pT_btag7;
	TH1F *pT_btag_real;

	// GEN level
	// jets
	TH1F *N_GENjets;
	TH1F *pT_GENjets;
	TH1F *eta_GENjets;
	TH1F *phi_GENjets;
	TH1F *m_GENjets;
	// muons
	TH1F *N_GENmus;
	TH1F *pT_GENmus;
	TH1F *pT_GENmus_leadingMu;
	TH1F *pT_GENmus_fromLQdecay;
	TH1F *eta_GENmus;
	TH1F *phi_GENmus;
	TH1F *m_GENmus;
	// electrons
	TH1F *N_GENels;
	TH1F *pT_GENels;
	TH1F *eta_GENels;
	TH1F *phi_GENels;
	TH1F *m_GENels;
	// tops
	TH1F *N_GENtops;
	TH1F *pT_GENtops;
	TH1F *eta_GENtops;
	TH1F *phi_GENtops;
	TH1F *m_GENtops;
	// LQs
	TH1F *N_GENLQs;
	TH1F *pT_GENLQs;
	TH1F *eta_GENLQs;
	TH1F *phi_GENLQs;
	TH1F *M_GENLQs;
	// MET
	TH1F *GENETmiss;
	TH1F *phi_GENETmiss;
};

#endif
