#include <string>
#include <cmath>
#include <functional>
#include <vector>
#include <cassert>
#include "Math/SpecFuncMathMore.h"
#include "TMath.h"
#include "TVectorD.h"
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "fastjet/contrib/Njettiness.hh"
#include "fastjet/tools/MassDropTagger.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "UserCode/TopAnalysis/plugins/BoostedTTbarFlatTreeProducerGenLevel.h"

#include "Math/Vector3D.h"
#include "Math/Vector4D.h"

//#include <UHH2/TopSubstructure/include/TopSubstructureUtils.h>

using namespace std;
using namespace reco;
using namespace fastjet;

BoostedTTbarFlatTreeProducerGenLevel::BoostedTTbarFlatTreeProducerGenLevel(edm::ParameterSet const& cfg)
{
  genjetsToken          = consumes<GenJetCollection>(cfg.getUntrackedParameter<edm::InputTag>("genjets",edm::InputTag("")));

  genParticlesToken     = consumes<edm::View<reco::GenParticle> >(edm::InputTag("genParticles"));
  GenptMin_             = cfg.getUntrackedParameter<double>("GenptMin");
  GenetaMax_            = cfg.getUntrackedParameter<double>("GenetaMax");
  genEvtInfoToken = consumes<GenEventInfoProduct>(edm::InputTag("generator"));
  jetFlavourInfosToken_ = consumes<reco::JetFlavourInfoMatchingCollection>( cfg.getParameter<edm::InputTag>("jetFlavourInfos"));
  isHigherOrder_ = cfg.getUntrackedParameter<bool>("isHigherOrder",false);
  pupInfoToken          = consumes<edm::View<PileupSummaryInfo> >(edm::InputTag("slimmedAddPileupInfo"));
  lheEvtInfoToken = consumes<LHEEventProduct>(edm::InputTag("externalLHEProducer"));

  //Gen Jet information
  /*fAKJetDef = new fastjet::JetDefinition(fastjet::antikt_algorithm, 0.8);
  int activeAreaRepeats = 1;
  double ghostArea      = 0.01;
  double ghostEtaMax    = 7.0;
  fActiveArea           = new fastjet::ActiveAreaSpec (ghostEtaMax,activeAreaRepeats,ghostArea);
  fAreaDefinition       = new fastjet::AreaDefinition (fastjet::active_area_explicit_ghosts, *fActiveArea );
  sd = new fastjet::contrib::SoftDrop(0.0,0.1,0.8);//beta_, zCut_, R0 );*/
}
//////////////////////////////////////////////////////////////////////////////////////////
void BoostedTTbarFlatTreeProducerGenLevel::beginJob()
{

  //--- book the tree -----------------------
  outTree_ = fs_->make<TTree>("events","events");
  EventsHisto_ = fs_->make<TH1F>("EventHisto","EventHisto",1,0.5,1.5);

  outTree_->Branch("nGenJets",&nGenJets_,"nGenJets_/I");
  outTree_->Branch("nS3LQs"  ,&nS3LQs_  ,"nS3LQs_/I");    	//for LQ
  outTree_->Branch("nMus"    ,&nMus_  	,"nMus_/I");     		//for muons
	outTree_->Branch("nEls"    ,&nEls_  	,"nEls_/I");     		//for electrons
	outTree_->Branch("nNus"    ,&nNus_  	,"nNus_/I");     		//for neutrinos

  //------------------- MC ---------------------------------
  outTree_->Branch("decay" ,&decay_ ,"decay_/I");
  outTree_->Branch("weight",&weight_,"weight_/D");
  ///////

  //for LQs
  S3LQId_  = new std::vector<int>;
  S3LQSt_  = new std::vector<int>;
  S3LQPt_  = new std::vector<float>;
  S3LQEta_ = new std::vector<float>;
  S3LQPhi_ = new std::vector<float>;
  S3LQE_   = new std::vector<float>;
  S3LQM_   = new std::vector<float>;
  outTree_->Branch("S3LQId"   ,"vector<int>"   ,&S3LQId_);
  outTree_->Branch("S3LQSt"   ,"vector<int>"   ,&S3LQSt_);
  outTree_->Branch("S3LQPt"   ,"vector<float>" ,&S3LQPt_);
  outTree_->Branch("S3LQEta"  ,"vector<float>" ,&S3LQEta_);
  outTree_->Branch("S3LQPhi"  ,"vector<float>" ,&S3LQPhi_);
  outTree_->Branch("S3LQE"    ,"vector<float>" ,&S3LQE_);
  outTree_->Branch("S3LQM"    ,"vector<float>" ,&S3LQM_);

  //for muons
	MuId_  = new std::vector<int>;
  MuSt_  = new std::vector<int>;
  MuPt_  = new std::vector<float>;
  MuEta_ = new std::vector<float>;
  MuPhi_ = new std::vector<float>;
  MuE_   = new std::vector<float>;
  MuM_   = new std::vector<float>;
  outTree_->Branch("MuId"   ,"vector<int>"   ,&MuId_);
  outTree_->Branch("MuSt"   ,"vector<int>"   ,&MuSt_);
  outTree_->Branch("MuPt"   ,"vector<float>" ,&MuPt_);
  outTree_->Branch("MuEta"  ,"vector<float>" ,&MuEta_);
  outTree_->Branch("MuPhi"  ,"vector<float>" ,&MuPhi_);
  outTree_->Branch("MuE"    ,"vector<float>" ,&MuE_);
  outTree_->Branch("MuM"    ,"vector<float>" ,&MuM_);

	//for electrons
	ElId_  = new std::vector<int>;
	ElSt_  = new std::vector<int>;
	ElPt_  = new std::vector<float>;
	ElEta_ = new std::vector<float>;
	ElPhi_ = new std::vector<float>;
	ElE_   = new std::vector<float>;
	ElM_   = new std::vector<float>;
	outTree_->Branch("ElId"   ,"vector<int>"   ,&ElId_);
	outTree_->Branch("ElSt"   ,"vector<int>"   ,&ElSt_);
	outTree_->Branch("ElPt"   ,"vector<float>" ,&ElPt_);
	outTree_->Branch("ElEta"  ,"vector<float>" ,&ElEta_);
	outTree_->Branch("ElPhi"  ,"vector<float>" ,&ElPhi_);
	outTree_->Branch("ElE"    ,"vector<float>" ,&ElE_);
	outTree_->Branch("ElM"    ,"vector<float>" ,&ElM_);

  //for neutrinos
  NuPt_  = new std::vector<float>;
  outTree_->Branch("NuPt"   ,"vector<float>" ,&NuPt_);

  //gen jets
  GenSoftDropMass_  = new std::vector<float>;
  GenSoftDropTau32_ = new std::vector<float>;
  GenSoftDropTau31_ = new std::vector<float>;
  GenSoftDropTau3_  = new std::vector<float>;
  GenSoftDropTau2_  = new std::vector<float>;
  GenSoftDropTau1_  = new std::vector<float>;
  GenJetpt_         = new std::vector<float>;
  GenJetphi_        = new std::vector<float>;
  GenJeteta_        = new std::vector<float>;
  GenJetenergy_     = new std::vector<float>;
  GenJetmass_       = new std::vector<float>;
  isBJetGen_        = new std::vector<bool>;
  isWJetGen_        = new std::vector<bool>;
  outTree_->Branch("GenSoftDropMass"       ,"vector<float>"   ,&GenSoftDropMass_);
  outTree_->Branch("GenSoftDropTau32"       ,"vector<float>"   ,&GenSoftDropTau32_);
  outTree_->Branch("GenSoftDropTau31"       ,"vector<float>"   ,&GenSoftDropTau31_);
  outTree_->Branch("GenSoftDropTau3"       ,"vector<float>"   ,&GenSoftDropTau3_);
  outTree_->Branch("GenSoftDropTau2"       ,"vector<float>"   ,&GenSoftDropTau2_);
  outTree_->Branch("GenSoftDropTau1"       ,"vector<float>"   ,&GenSoftDropTau1_);
  outTree_->Branch("GenJetpt"       ,"vector<float>"   ,&GenJetpt_);
  outTree_->Branch("GenJeteta"       ,"vector<float>"   ,&GenJeteta_);
  outTree_->Branch("GenJetphi"       ,"vector<float>"   ,&GenJetphi_);
  outTree_->Branch("GenJetenergy"       ,"vector<float>"   ,&GenJetenergy_);
  outTree_->Branch("GenJetmass"       ,"vector<float>"   ,&GenJetmass_);
  outTree_->Branch("isBJetGen"       ,"vector<bool>"   ,&isBJetGen_);
  outTree_->Branch("isWJetGen"       ,"vector<bool>"   ,&isWJetGen_);


  GenSubJet1Pt_   = new std::vector<float>;
  GenSubJet2Pt_   = new std::vector<float>;
  GenSubJet1Eta_  = new std::vector<float>;
  GenSubJet2Eta_  = new std::vector<float>;
  GenSubJet1Phi_  = new std::vector<float>;
  GenSubJet2Phi_  = new std::vector<float>;
  GenSubJet1Mass_ = new std::vector<float>;
  GenSubJet2Mass_ = new std::vector<float>;

  outTree_->Branch("GenSubJet1Pt"       ,"vector<float>"   ,&GenSubJet1Pt_);
  outTree_->Branch("GenSubJet2Pt"       ,"vector<float>"   ,&GenSubJet2Pt_);
  outTree_->Branch("GenSubJet1Eta"      ,"vector<float>"   ,&GenSubJet1Eta_);
  outTree_->Branch("GenSubJet2Eta"      ,"vector<float>"   ,&GenSubJet2Eta_);
  outTree_->Branch("GenSubJet1Phi"      ,"vector<float>"   ,&GenSubJet1Phi_);
  outTree_->Branch("GenSubJet2Phi"      ,"vector<float>"   ,&GenSubJet2Phi_);
  outTree_->Branch("GenSubJet1Mass"     ,"vector<float>"   ,&GenSubJet1Mass_);
  outTree_->Branch("GenSubJet2Mass"     ,"vector<float>"   ,&GenSubJet2Mass_);

  outTree_->Branch("npu"                  ,&npu_               ,"npu_/I");
  outTree_->Branch("genEvtWeight"         ,&genEvtWeight_      ,"genEvtWeight_/F");
  outTree_->Branch("lheOriginalXWGTUP"    ,&lheOriginalXWGTUP_ ,"lheOriginalXWGTUP_/F");
  if (isHigherOrder_)
  {
    scaleWeights_  = new std::vector<float>;
    pdfWeights_  = new std::vector<float>;
    outTree_->Branch("scaleWeights"         ,"vector<float>"     ,&scaleWeights_);
    outTree_->Branch("pdfWeights"           ,"vector<float>"     ,&pdfWeights_);
  }

  cout << "Begin job finished" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////
void BoostedTTbarFlatTreeProducerGenLevel::endJob()
{
  delete S3LQSt_;
  delete S3LQId_;
  delete S3LQPt_;
  delete S3LQEta_;
  delete S3LQPhi_;
  delete S3LQE_;
  delete S3LQM_;

  delete MuSt_;
  delete MuId_;
  delete MuPt_;
  delete MuEta_;
  delete MuPhi_;
  delete MuE_;
  delete MuM_;

  delete ElSt_;
  delete ElId_;
  delete ElPt_;
  delete ElEta_;
  delete ElPhi_;
  delete ElE_;
  delete ElM_;

  delete NuPt_;

  delete GenSoftDropMass_;
  delete GenSoftDropTau32_;
  delete GenSoftDropTau3_;
  delete GenSoftDropTau2_;
  delete GenSoftDropTau1_;
  delete GenSoftDropTau31_;
  delete GenJetpt_;
  delete GenJetphi_;
  delete GenJeteta_;
  delete GenJetenergy_;
  delete GenJetmass_;
  delete isBJetGen_;
  delete isWJetGen_;

  delete GenSubJet1Pt_;
  delete GenSubJet2Pt_;
  delete GenSubJet1Eta_;
  delete GenSubJet2Eta_;
  delete GenSubJet1Phi_;
  delete GenSubJet2Phi_;
  delete GenSubJet1Mass_;
  delete GenSubJet2Mass_;

  if (isHigherOrder_)
  {
    delete scaleWeights_;
    delete pdfWeights_;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void BoostedTTbarFlatTreeProducerGenLevel::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
  cout << "Begin run finished" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////
void BoostedTTbarFlatTreeProducerGenLevel::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
}
//////////////////////////////////////////////////////////////////////////////////////////
void BoostedTTbarFlatTreeProducerGenLevel::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup)
{
  initialize();

  //---------- mc -----------------------
  bool cut_GEN(true);

  if (!iEvent.isRealData())
  {
    iEvent.getByToken(genEvtInfoToken,genEvtInfo);
    iEvent.getByToken(genParticlesToken,genParticles);
    iEvent.getByToken(genjetsToken,genjets);

    weight_ = genEvtInfo->weight();

    LorentzVector p4T(0,0,0,0), p4Tbar(0,0,0,0);


    for(unsigned ip = 0; ip < genParticles->size(); ++ip)
    {
      const GenParticle &p = (*genParticles)[ip];


			//ELECTRONS
			if(abs(p.pdgId()) == 11)    		//(anti-)electron
			{
				nEls_++;
				ElId_ ->push_back(p.pdgId());
				ElSt_ ->push_back(p.status());
				ElPt_ ->push_back(p.pt());
				ElEta_->push_back(p.eta());
				ElPhi_->push_back(p.phi());
				ElE_  ->push_back(p.energy());
				ElM_  ->push_back(p.mass());
			}

			//MUONS
      if(abs(p.pdgId()) == 13)    		//(anti-)muon
      {
        nMus_++;
        MuId_ ->push_back(p.pdgId());
        //cout << "id of muon:     " << p.pdgId() << '\n';
        MuSt_ ->push_back(p.status());
        //cout << "status of muon: " << p.status() << '\n';
        MuPt_ ->push_back(p.pt());
        MuEta_->push_back(p.eta());
        MuPhi_->push_back(p.phi());
        MuE_  ->push_back(p.energy());
        MuM_  ->push_back(p.mass());
			}


			//LEPTOQUARKS
      if(abs(p.pdgId()) == 9000005 && p.status() == 22)   //(anti-)leptoquark from hard scattering
      {
        nS3LQs_++;
        S3LQId_ ->push_back(p.pdgId());
        //cout << "id of LQ:  " << p.pdgId() << '\n';
        S3LQSt_ ->push_back(p.status());
        //cout << "status of LQ:  " << p.status() << '\n';
        S3LQPt_ ->push_back(p.pt());
        //cout << "pt of LQ:  " << p.pt() << '\n';
        S3LQEta_->push_back(p.eta());
        S3LQPhi_->push_back(p.phi());
        S3LQE_  ->push_back(p.energy());
        S3LQM_  ->push_back(p.mass());

      }

			//NEUTRINOS
			if(abs(p.pdgId()) == 12 || abs(p.pdgId()) == 14 || abs(p.pdgId()) == 16)	//(anti-)neutrinos
			{
				nNus_++;
        NuPt_ ->push_back(p.pt());
			}

      /*
			//b QUARKS
			if(abs(p.pdgId()) == 5)
			{
				nBs_++;
				cout << "numberOfBquarks: " << nBs_ << '\n';
			}
      */
    } //end of particle loop

    //cout << "new event" << '\n';

    /*
    //cout << "E of LQ:  " << S3LQE_->front() << '\n';
    for(int i=0; i<nS3LQs_; i++)
    {
      cout << "E of LQ:  " << S3LQE_->at(i) << " (" << S3LQId_->at(i) << ")" << '\n';
    }
    */



    iEvent.getByToken(genjetsToken,genjets);

    if(isHigherOrder_)
    {
      iEvent.getByToken(lheEvtInfoToken,lheEvtInfo);
      iEvent.getByToken(pupInfoToken,pupInfo);

      edm::View<PileupSummaryInfo>::const_iterator PUI;
      for(PUI = pupInfo->begin(); PUI != pupInfo->end(); ++PUI)
      {
	       if (PUI->getBunchCrossing() == 0)
         {
	          npu_ = PUI->getTrueNumInteractions();
	       }
      }

      genEvtWeight_ = genEvtInfo->weight();
      lheOriginalXWGTUP_ = lheEvtInfo->originalXWGTUP();

      for(unsigned i=0; i<lheEvtInfo->weights().size(); i++)
      {
        string wtid(lheEvtInfo->weights()[i].id);
        float wgt(lheEvtInfo->weights()[i].wgt);
        if (wtid == "1002" || wtid == "2") scaleWeights_->push_back(wgt/lheOriginalXWGTUP_);
        if (wtid == "1003" || wtid == "3") scaleWeights_->push_back(wgt/lheOriginalXWGTUP_);
        if (wtid == "1004" || wtid == "4") scaleWeights_->push_back(wgt/lheOriginalXWGTUP_);
        if (wtid == "1005" || wtid == "5") scaleWeights_->push_back(wgt/lheOriginalXWGTUP_);
        if (wtid == "1007" || wtid == "7") scaleWeights_->push_back(wgt/lheOriginalXWGTUP_);
        if (wtid == "1009" || wtid == "9") scaleWeights_->push_back(wgt/lheOriginalXWGTUP_);

        if ((stoi(wtid) > 2000 && stoi(wtid) <= 2102) || (stoi(wtid) > 10 && stoi(wtid) <= 110))
        {
          pdfWeights_->push_back(wgt/lheOriginalXWGTUP_);
        }
      }
    }

    vector<LorentzVector> vP4Gen;

		for(GenJetCollection::const_iterator i_gen = genjets->begin(); i_gen != genjets->end(); i_gen++)
    {
      if(i_gen->pt() > GenptMin_ && fabs(i_gen->y()) < GenetaMax_)
      {
	       nGenJets_++;
         GenJetpt_->push_back(i_gen->pt());
         GenJetphi_->push_back(i_gen->phi());
         GenJeteta_->push_back(i_gen->y());
         GenJetenergy_->push_back(i_gen->energy());
         GenJetmass_->push_back(i_gen->mass());

         /*
	       //LQ jet flag
         for(unsigned ip = 0; ip < genParticles->size(); ++ip)
         {
           const GenParticle &p = (*genParticles)[ip];
           if (fabs(p.pdgId()) == 9000005)
           {
             double deltaEta = i_gen->eta() - p.momentum().eta();
             double deltaPhiJP = deltaPhi(i_gen->phi(), p.momentum().phi());
             double deltaRJPMin = sqrt(pow(deltaEta,2) + pow(deltaPhiJP,2));

             if(deltaRJPMin < 0.6)
             {
               isWJetGen_->push_back(true);
             }
	           else
             {
               isWJetGen_->push_back(false);
             }
           }
	       }
         */

         /*
         std::vector<fastjet::PseudoJet>  lClusterParticles;
         for(unsigned int ic=0; ic<i_gen->numberOfDaughters(); ic++)
         {
           const reco::Candidate* gencand = i_gen->daughter(ic);
           fastjet::PseudoJet   pPart(gencand->px(),gencand->py(),gencand->pz(),gencand->energy());
           lClusterParticles.push_back(pPart);
         }

        fClustering = new fastjet::ClusterSequenceArea(lClusterParticles, *fAKJetDef, *fAreaDefinition);
        std::vector<fastjet::PseudoJet>  lOutJets = fClustering->inclusive_jets(20.0);

        if(lOutJets.size() == 0)
        {
          delete fClustering;
          return;
        }

	      fastjet::PseudoJet pT1JetSD = (*sd)( lOutJets[0]);
        float iMSoftDrop = pT1JetSD.m();

        fastjet::contrib::NormalizedMeasure          normalizedMeasure        (1.0,0.8);
        fastjet::contrib::Njettiness routine(fastjet::contrib::Njettiness::onepass_kt_axes,normalizedMeasure);
        float iTau1 = routine.getTau(1.,lClusterParticles);
        float iTau2 = routine.getTau(2.,lClusterParticles);
        float iTau3 = routine.getTau(3.,lClusterParticles);

	      float Tau32=-1;
	      float Tau31=-1;

	      GenSoftDropTau3_->push_back(iTau3);
	      GenSoftDropTau2_->push_back(iTau2);
        GenSoftDropTau1_->push_back(iTau1);

        if(iTau2!=0) Tau32=iTau3/iTau2;
        if(iTau1!=0) Tau31=iTau3/iTau1;
        GenSoftDropTau32_->push_back(Tau32);
        GenSoftDropTau31_->push_back(Tau31);
        GenSoftDropMass_->push_back(iMSoftDrop);

	      lOutJets.clear();
        delete fClustering;
        lClusterParticles.clear();
        */
      }
    }

    edm::Handle<reco::JetFlavourInfoMatchingCollection> theJetFlavourInfos;
    iEvent.getByToken(jetFlavourInfosToken_, theJetFlavourInfos );

    /*
    for(reco::JetFlavourInfoMatchingCollection::const_iterator j  = theJetFlavourInfos->begin();j != theJetFlavourInfos->end(); ++j )
    {
      const reco::Jet *aJet = (*j).first.get();
      reco::JetFlavourInfo aInfo = (*j).second;

      if (aJet->pt() > GenptMin_ && fabs(aJet->y()) < GenetaMax_ )
      {
	       int FlavourGenHadron = aInfo.getHadronFlavour();
	       if(abs(FlavourGenHadron)==5)
         {
           isBJetGen_->push_back(true);
         }
         else isBJetGen_->push_back(false);
      }
    }
    */

    cut_GEN = (nGenJets_>=0);

  }//--- end of MC -------

  EventsHisto_->Fill(1.,1.);

  if (cut_GEN)
  {
    outTree_->Fill();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void BoostedTTbarFlatTreeProducerGenLevel::initialize()
{

  //cout<<"Ini starts"<<endl;
  nGenJets_ = 0;
  nS3LQs_   = 0;
  nMus_    	= 0;
	nEls_ 		= 0;
	nNus_			= 0;

  //----- MC -------
  decay_ = 10;
  weight_=1;

  //for LQ
  S3LQSt_ ->clear();
  S3LQId_ ->clear();
  S3LQPt_ ->clear();
  S3LQEta_->clear();
  S3LQPhi_->clear();
  S3LQE_  ->clear();
  S3LQM_  ->clear();

  //for muons
  MuSt_ ->clear();
  MuId_ ->clear();
  MuPt_ ->clear();
  MuEta_->clear();
  MuPhi_->clear();
  MuE_  ->clear();
  MuM_  ->clear();

  //for electrons
  ElSt_ ->clear();
  ElId_ ->clear();
  ElPt_ ->clear();
  ElEta_->clear();
  ElPhi_->clear();
  ElE_  ->clear();
  ElM_  ->clear();

  //for neutrinos
  NuPt_ ->clear();

  isBJetGen_->clear();
  isWJetGen_->clear();
  GenSoftDropMass_->clear();
  GenSoftDropTau32_->clear();
  GenSoftDropTau31_->clear();
  GenSoftDropTau3_->clear();
  GenSoftDropTau2_->clear();
  GenSoftDropTau1_->clear();
  GenJetpt_->clear();
  GenJetphi_->clear();
  GenJeteta_->clear();
  GenJetenergy_->clear();
  GenJetmass_->clear();

  GenSubJet1Pt_->clear();
  GenSubJet2Pt_->clear();
  GenSubJet1Eta_->clear();
  GenSubJet2Eta_->clear();
  GenSubJet1Phi_->clear();
  GenSubJet2Phi_->clear();
  GenSubJet1Mass_->clear();
  GenSubJet2Mass_->clear();

  if (isHigherOrder_)
  {
    scaleWeights_->clear();
    pdfWeights_->clear();
  }

  npu_               = -1;
  genEvtWeight_      = -999;
  lheOriginalXWGTUP_ = -999;

}
//////////////////////////////////////////////////////////////////////////////////////////
BoostedTTbarFlatTreeProducerGenLevel::~BoostedTTbarFlatTreeProducerGenLevel()
{
}

DEFINE_FWK_MODULE(BoostedTTbarFlatTreeProducerGenLevel);
