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

float DeltaPhi(float phi1, float phi2)
{
	float dPhi = TMath::Abs(phi1 - phi2);
	if(dPhi > TMath::Pi())
	{
		dPhi = TMath::TwoPi() - dPhi;
	}
	return dPhi;
}

float DeltaR(float eta1, float phi1, float eta2, float phi2)
{
	float deltaEta = eta1 - eta2;
	float deltaPhi = DeltaPhi(phi1, phi2);
	return TMath::Sqrt(deltaEta * deltaEta + deltaPhi * deltaPhi);
}

class Analysis_Template_MC : public edm::EDAnalyzer
 {



  public:
		//typedef reco::Particle::LorentzVector LorentzVector;
    explicit Analysis_Template_MC(edm::ParameterSet const& cfg);
    virtual void beginJob();
    virtual void analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup);
    virtual void endJob();
    virtual ~Analysis_Template_MC();

  private:
    //---- configurable parameters --------
    std::string mFileName,mTreeName,mDirName;

    double mMinPt, mYMax;
    int    mJetID;        // looseID==1 tightID==2
    int    mprintOk;       // noPrint=0  Print=1
    bool mIsMCarlo;
    double mCrossSection;
    double mIntLumi;
    vector<std::string> mTriggers;
    edm::Service<TFileService> fs;
    TTree *mTree;
    TFile *mInf, *mPuf;
    TDirectoryFile *mDir;

    //--------- Histogram Declaration --------------------//
    // Vertices
    TH1F *num_of_GenJets;

    ///Measurement Det jets
    TH1F *ptGENJet;
    TH1F *yGENJet;
    TH1F *phiGENJet;

		//Measurement LQ
		TH1F *num_of_S3LQ;
		TH1F *ptS3LQ;
		TH1F *phiS3LQ;
		TH1F *etaS3LQ;
		TH1F *massS3LQ;
		TH1F *energyS3LQ;

		//Measurement	muons
		TH1F *num_of_Mu;
		TH1F *ptMu;
		TH1F *phiMu;
		TH1F *etaMu;
		TH1F *massMu;
		TH1F *energyMu;

		//Measurements of deltaR
		TH1F *deltaRMuJet;

		//Measurements of MLQreco and S_T
		TH1F *CatA_MLQreco;
		TH1F *CatA_MLQreco_Arne;
		TH1F *CatB_MLQreco;
		TH1F *CatA_ST;
		TH1F *CatA_ST_Arne;
		TH1F *CatB_ST;

 };

#endif
