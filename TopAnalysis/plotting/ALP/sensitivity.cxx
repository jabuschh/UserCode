{
  // settings
  TString histname = "mass_ditop";
  TString filename = "sensitivity";
  TString x_label = "M_{t#bar{t}} [GeV]";
  double  x_labeloffset = 1.5;
  double  x_min = 0.;
  double  x_max = 4000;
  TString y_label = "#frac{N_{events}^{WC} - N_{events}^{SM}}{N_{events}^{SM}}";
  double  y_labeloffset = 1.5;
  double  y_min = -4.1;
  double  y_max = 4.1;

  // data from b2g-17-017: lepton + jets (rebinned)
  cout << "reading in SM data from root files: lepton + jets..." << endl;
  TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/b2g-17-017/input/postfit/";
  vector<TH1F*> v_hists_ljets;
  // 1 lep + jets
  TFile *datafile_1e = TFile::Open(dir + "mtt2017_ljets_1e_outhists.root");
  TH1F *h_mttbar_ljets_1e = (TH1F*) gDirectory->Get("ele_0top_antiWJetsMVA2_chi2_mttbar");
  v_hists_ljets.push_back(h_mttbar_ljets_1e);
  TFile *datafile_1m = TFile::Open(dir + "mtt2017_ljets_1m_outhists.root");
  TH1F *h_mttbar_ljets_1m = (TH1F*) gDirectory->Get("mu_0top_antiWJetsMVA2_chi2_mttbar");
  v_hists_ljets.push_back(h_mttbar_ljets_1m);
  // 2 lep + jets
  TFile *datafile_2e = TFile::Open(dir + "mtt2017_ljets_2e_outhists.root");
  TH1F *h_mttbar_ljets_2e = (TH1F*) gDirectory->Get("ele_0top_antiWJetsMVA3_chi2_mttbar");
  v_hists_ljets.push_back(h_mttbar_ljets_2e);
  TFile *datafile_2m = TFile::Open(dir + "mtt2017_ljets_2m_outhists.root");
  TH1F *h_mttbar_ljets_2m = (TH1F*) gDirectory->Get("mu_0top_antiWJetsMVA3_chi2_mttbar");
  v_hists_ljets.push_back(h_mttbar_ljets_2m);
  // 3 lep + jets
  TFile *datafile_3e = TFile::Open(dir + "mtt2017_ljets_3e_outhists.root");
  TH1F *h_mttbar_ljets_3e = (TH1F*) gDirectory->Get("ele_0top_WJetsMVA_chi2_mttbar");
  v_hists_ljets.push_back(h_mttbar_ljets_3e);
  TFile *datafile_3m = TFile::Open(dir + "mtt2017_ljets_3m_outhists.root");
  TH1F *h_mttbar_ljets_3m = (TH1F*) gDirectory->Get("mu_0top_WJetsMVA_chi2_mttbar");
  v_hists_ljets.push_back(h_mttbar_ljets_3m);
  // 4 lep + jets
  TFile *datafile_4e = TFile::Open(dir + "mtt2017_ljets_4e_outhists.root");
  TH1F *h_mttbar_ljets_4e = (TH1F*) gDirectory->Get("ele_1top_WJetsMVA_chi2_mttbar");
  v_hists_ljets.push_back(h_mttbar_ljets_4e);
  TFile *datafile_4m = TFile::Open(dir + "mtt2017_ljets_4m_outhists.root");
  TH1F *h_mttbar_ljets_4m = (TH1F*) gDirectory->Get("mu_1top_WJetsMVA_chi2_mttbar");
  v_hists_ljets.push_back(h_mttbar_ljets_4m);

  // data from b2g-17-017: dilepton (rebinned)
  cout << "reading in SM data from root files: dilepton..." << endl;
  dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/b2g-17-017/input/postfit/";
  vector<TH1F*> v_hists_dilep;
  // 1ll
  TFile *datafile_1ee = TFile::Open(dir + "mtt2017_dilep_1ee_outhists.root");
  TH1F *h_mttbar_dilep_1ee = (TH1F*) gDirectory->Get("eerev");
  v_hists_dilep.push_back(h_mttbar_dilep_1ee);
  TFile *datafile_1em = TFile::Open(dir + "mtt2017_dilep_1em_outhists.root");
  TH1F *h_mttbar_dilep_1em = (TH1F*) gDirectory->Get("emrev");
  v_hists_dilep.push_back(h_mttbar_dilep_1em);
  TFile *datafile_1mm = TFile::Open(dir + "mtt2017_dilep_1mm_outhists.root");
  TH1F *h_mttbar_dilep_1mm = (TH1F*) gDirectory->Get("mmrev");
  v_hists_dilep.push_back(h_mttbar_dilep_1mm);
  // 2ll
  TFile *datafile_2ee = TFile::Open(dir + "mtt2017_dilep_2ee_outhists.root");
  TH1F *h_mttbar_dilep_2ee = (TH1F*) gDirectory->Get("eenb");
  v_hists_dilep.push_back(h_mttbar_dilep_2ee);
  TFile *datafile_2em = TFile::Open(dir + "mtt2017_dilep_2em_outhists.root");
  TH1F *h_mttbar_dilep_2em = (TH1F*) gDirectory->Get("emnb");
  v_hists_dilep.push_back(h_mttbar_dilep_2em);
  TFile *datafile_2mm = TFile::Open(dir + "mtt2017_dilep_2mm_outhists.root");
  TH1F *h_mttbar_dilep_2mm = (TH1F*) gDirectory->Get("mmnb");
  v_hists_dilep.push_back(h_mttbar_dilep_2mm);
  // 2ll
  TFile *datafile_3ee = TFile::Open(dir + "mtt2017_dilep_3ee_outhists.root");
  TH1F *h_mttbar_dilep_3ee = (TH1F*) gDirectory->Get("eebt");
  v_hists_dilep.push_back(h_mttbar_dilep_3ee);
  TFile *datafile_3em = TFile::Open(dir + "mtt2017_dilep_3em_outhists.root");
  TH1F *h_mttbar_dilep_3em = (TH1F*) gDirectory->Get("embt");
  v_hists_dilep.push_back(h_mttbar_dilep_3em);
  TFile *datafile_3mm = TFile::Open(dir + "mtt2017_dilep_3mm_outhists.root");
  TH1F *h_mttbar_dilep_3mm = (TH1F*) gDirectory->Get("mmbt");
  v_hists_dilep.push_back(h_mttbar_dilep_3mm);

  // data from b2g-17-017: hadronic
  cout << "reading in SM data from root files: hadronic..." << endl;
  dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/b2g-17-017/input/postfit/";
  vector<TH1F*> v_hists_hadr;
  // btag0
  TFile *datafile_btag0 = TFile::Open(dir + "mtt2017_had_btag0_outhists.root");
  TH1F *h_mttbar_hadr_0 = (TH1F*) gDirectory->Get("btag0");
  v_hists_hadr.push_back(h_mttbar_hadr_0);
  // btag1
  TFile *datafile_btag1 = TFile::Open(dir + "mtt2017_had_btag1_outhists.root");
  TH1F *h_mttbar_hadr_1 = (TH1F*) gDirectory->Get("btag1");
  v_hists_hadr.push_back(h_mttbar_hadr_1);
  // btag2
  TFile *datafile_btag2 = TFile::Open(dir + "mtt2017_had_btag2_outhists.root");
  TH1F *h_mttbar_hadr_2 = (TH1F*) gDirectory->Get("btag2");
  v_hists_hadr.push_back(h_mttbar_hadr_2);
  // btag3
  TFile *datafile_btag3 = TFile::Open(dir + "mtt2017_had_btag3_outhists.root");
  TH1F *h_mttbar_hadr_3 = (TH1F*) gDirectory->Get("btag3");
  v_hists_hadr.push_back(h_mttbar_hadr_3);
  // btag4
  TFile *datafile_btag4 = TFile::Open(dir + "mtt2017_had_btag4_outhists.root");
  TH1F *h_mttbar_hadr_4 = (TH1F*) gDirectory->Get("btag4");
  v_hists_hadr.push_back(h_mttbar_hadr_4);
  // btag5
  TFile *datafile_btag5 = TFile::Open(dir + "mtt2017_had_btag5_outhists.root");
  TH1F *h_mttbar_hadr_5 = (TH1F*) gDirectory->Get("btag5");
  v_hists_hadr.push_back(h_mttbar_hadr_5);

  // SM data uncertainty: l + jets
  TH1F* h_ljets = v_hists_ljets.at(0);
  for(int i=1; i<v_hists_ljets.size(); i++){
    h_ljets->Add(v_hists_ljets.at(i));
  }
  for(int i=0; i<h_ljets->GetSize(); i++){
    if(h_ljets->GetBinContent(i) > 0){
      double rel_uncert = (h_ljets->GetBinError(i) / h_ljets->GetBinContent(i));
      h_ljets->SetBinContent(i,rel_uncert);
    }
  }
  h_ljets->SetFillStyle(3335);
  h_ljets->SetFillColor(kGray);
  h_ljets->SetLineColor(kGray);
  // negative
  TH1F* h_ljets_neg = (TH1F*) h_ljets->Clone();
  for(int i=0; i<h_ljets_neg->GetSize(); i++){
    double temp = h_ljets_neg->GetBinContent(i);
    h_ljets_neg->SetBinContent(i,temp * -1);
  }

  // SM data uncertainty: dilepton
  TH1F* h_dilep = v_hists_dilep.at(0);
  for(int i=1; i<v_hists_dilep.size(); i++){
    h_dilep->Add(v_hists_dilep.at(i));
  }
  for(int i=0; i<h_dilep->GetSize(); i++){
    if(h_dilep->GetBinContent(i) > 0){
      double rel_uncert = (h_dilep->GetBinError(i) / h_dilep->GetBinContent(i));
      h_dilep->SetBinContent(i,rel_uncert);
    }
  }
  h_dilep->SetFillStyle(3353);
  h_dilep->SetFillColor(kGray+2);
  h_dilep->SetLineColor(kGray+2);
  // negative
  TH1F* h_dilep_neg = (TH1F*) h_dilep->Clone();
  for(int i=0; i<h_dilep_neg->GetSize(); i++){
    double temp = h_dilep_neg->GetBinContent(i);
    h_dilep_neg->SetBinContent(i,temp * -1);
  }

  // SM data uncertainty: hadronic
  TH1F *h_hadr = v_hists_hadr.at(0);
  for(int i=0; i<v_hists_hadr.size(); i++){
    h_hadr->Add(v_hists_hadr.at(i));
  }
  for(int i=0; i<h_hadr->GetSize(); i++){
    if(h_hadr->GetBinContent(i) > 0){
      double rel_uncert = (h_hadr->GetBinError(i) / h_hadr->GetBinContent(i));
      h_hadr->SetBinContent(i,rel_uncert);
    }
  }
  h_hadr->SetFillStyle(3359);
  h_hadr->SetFillColor(kGray+3);
  h_hadr->SetLineColor(kGray+3);
  // negative
  TH1F* h_hadr_neg = (TH1F*) h_hadr->Clone();
  for(int i=0; i<h_hadr_neg->GetSize(); i++){
    double temp = h_hadr_neg->GetBinContent(i);
    h_hadr_neg->SetBinContent(i,temp * -1);
  }




  cout << "reading in histograms from root file..." << endl;
  dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/ALP/";

  TFile *file_CaPhi1_CaGmin5 = TFile::Open(dir + "ALP_CaPhi1_CaGmin5.root", "READ");
  file_CaPhi1_CaGmin5->cd("analysis");
  TH1F *h_CaPhi1_CaGmin5 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaGmin4 = TFile::Open(dir + "ALP_CaPhi1_CaGmin4.root", "READ");
  file_CaPhi1_CaGmin4->cd("analysis");
  TH1F *h_CaPhi1_CaGmin4 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaGmin3 = TFile::Open(dir + "ALP_CaPhi1_CaGmin3.root", "READ");
  file_CaPhi1_CaGmin3->cd("analysis");
  TH1F *h_CaPhi1_CaGmin3 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaGmin2 = TFile::Open(dir + "ALP_CaPhi1_CaGmin2.root", "READ");
  file_CaPhi1_CaGmin2->cd("analysis");
  TH1F *h_CaPhi1_CaGmin2 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaGmin1 = TFile::Open(dir + "ALP_CaPhi1_CaGmin1.root", "READ");
  file_CaPhi1_CaGmin1->cd("analysis");
  TH1F *h_CaPhi1_CaGmin1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG1 = TFile::Open(dir + "ALP_CaPhi1_CaG1.root", "READ");
  file_CaPhi1_CaG1->cd("analysis");
  TH1F *h_CaPhi1_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG2 = TFile::Open(dir + "ALP_CaPhi1_CaG2.root", "READ");
  file_CaPhi1_CaG2->cd("analysis");
  TH1F *h_CaPhi1_CaG2 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG3 = TFile::Open(dir + "ALP_CaPhi1_CaG3.root", "READ");
  file_CaPhi1_CaG3->cd("analysis");
  TH1F *h_CaPhi1_CaG3 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG4 = TFile::Open(dir + "ALP_CaPhi1_CaG4.root", "READ");
  file_CaPhi1_CaG4->cd("analysis");
  TH1F *h_CaPhi1_CaG4 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG5 = TFile::Open(dir + "ALP_CaPhi1_CaG5.root", "READ");
  file_CaPhi1_CaG5->cd("analysis");
  TH1F *h_CaPhi1_CaG5 = (TH1F*) gDirectory->Get(histname);

  TFile *file_CaPhimin5_CaG1 = TFile::Open(dir + "ALP_CaPhimin5_CaG1.root","READ");
  file_CaPhimin5_CaG1->cd("analysis");
  TH1F *h_CaPhimin5_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhimin4_CaG1 = TFile::Open(dir + "ALP_CaPhimin4_CaG1.root","READ");
  file_CaPhimin4_CaG1->cd("analysis");
  TH1F *h_CaPhimin4_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhimin3_CaG1 = TFile::Open(dir + "ALP_CaPhimin3_CaG1.root","READ");
  file_CaPhimin3_CaG1->cd("analysis");
  TH1F *h_CaPhimin3_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhimin2_CaG1 = TFile::Open(dir + "ALP_CaPhimin2_CaG1.root","READ");
  file_CaPhimin2_CaG1->cd("analysis");
  TH1F *h_CaPhimin2_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhimin1_CaG1 = TFile::Open(dir + "ALP_CaPhimin1_CaG1.root","READ");
  file_CaPhimin1_CaG1->cd("analysis");
  TH1F *h_CaPhimin1_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi2_CaG1 = TFile::Open(dir + "ALP_CaPhi2_CaG1.root","READ");
  file_CaPhi2_CaG1->cd("analysis");
  TH1F *h_CaPhi2_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi3_CaG1 = TFile::Open(dir + "ALP_CaPhi3_CaG1.root","READ");
  file_CaPhi3_CaG1->cd("analysis");
  TH1F *h_CaPhi3_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi4_CaG1 = TFile::Open(dir + "ALP_CaPhi4_CaG1.root","READ");
  file_CaPhi4_CaG1->cd("analysis");
  TH1F *h_CaPhi4_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi5_CaG1 = TFile::Open(dir + "ALP_CaPhi5_CaG1.root","READ");
  file_CaPhi5_CaG1->cd("analysis");
  TH1F *h_CaPhi5_CaG1 = (TH1F*) gDirectory->Get(histname);

  TFile *file_SM = TFile::Open(dir + "ALP_SM.root","READ");
  file_SM->cd("analysis");
  TH1F *h_SM = (TH1F*) gDirectory->Get(histname);


  // rebin
  h_CaPhi1_CaGmin5->Rebin(5);
  h_CaPhi1_CaGmin4->Rebin(5);
  h_CaPhi1_CaGmin3->Rebin(5);
  h_CaPhi1_CaGmin2->Rebin(5);
  h_CaPhi1_CaGmin1->Rebin(5);
  h_CaPhi1_CaG1   ->Rebin(5);
  h_CaPhi1_CaG2   ->Rebin(5);
  h_CaPhi1_CaG3   ->Rebin(5);
  h_CaPhi1_CaG4   ->Rebin(5);
  h_CaPhi1_CaG5   ->Rebin(5);
  h_CaPhimin5_CaG1->Rebin(5);
  h_CaPhimin4_CaG1->Rebin(5);
  h_CaPhimin3_CaG1->Rebin(5);
  h_CaPhimin2_CaG1->Rebin(5);
  h_CaPhimin1_CaG1->Rebin(5);
  h_CaPhi2_CaG1   ->Rebin(5);
  h_CaPhi3_CaG1   ->Rebin(5);
  h_CaPhi4_CaG1   ->Rebin(5);
  h_CaPhi5_CaG1   ->Rebin(5);
  h_SM            ->Rebin(5);
  // sensitivity
  h_CaPhi1_CaGmin5->Add(h_SM,-1); h_CaPhi1_CaGmin5->Divide(h_SM);
  h_CaPhi1_CaGmin4->Add(h_SM,-1); h_CaPhi1_CaGmin4->Divide(h_SM);
  h_CaPhi1_CaGmin3->Add(h_SM,-1); h_CaPhi1_CaGmin3->Divide(h_SM);
  h_CaPhi1_CaGmin2->Add(h_SM,-1); h_CaPhi1_CaGmin2->Divide(h_SM);
  h_CaPhi1_CaGmin1->Add(h_SM,-1); h_CaPhi1_CaGmin1->Divide(h_SM);
  h_CaPhi1_CaG1   ->Add(h_SM,-1); h_CaPhi1_CaG1   ->Divide(h_SM);
  h_CaPhi1_CaG2   ->Add(h_SM,-1); h_CaPhi1_CaG2   ->Divide(h_SM);
  h_CaPhi1_CaG3   ->Add(h_SM,-1); h_CaPhi1_CaG3   ->Divide(h_SM);
  h_CaPhi1_CaG4   ->Add(h_SM,-1); h_CaPhi1_CaG4   ->Divide(h_SM);
  h_CaPhi1_CaG5   ->Add(h_SM,-1); h_CaPhi1_CaG5   ->Divide(h_SM);
  h_CaPhimin5_CaG1->Add(h_SM,-1); h_CaPhimin5_CaG1->Divide(h_SM);
  h_CaPhimin4_CaG1->Add(h_SM,-1); h_CaPhimin4_CaG1->Divide(h_SM);
  h_CaPhimin3_CaG1->Add(h_SM,-1); h_CaPhimin3_CaG1->Divide(h_SM);
  h_CaPhimin2_CaG1->Add(h_SM,-1); h_CaPhimin2_CaG1->Divide(h_SM);
  h_CaPhimin1_CaG1->Add(h_SM,-1); h_CaPhimin1_CaG1->Divide(h_SM);
  h_CaPhi2_CaG1   ->Add(h_SM,-1); h_CaPhi2_CaG1   ->Divide(h_SM);
  h_CaPhi3_CaG1   ->Add(h_SM,-1); h_CaPhi3_CaG1   ->Divide(h_SM);
  h_CaPhi4_CaG1   ->Add(h_SM,-1); h_CaPhi4_CaG1   ->Divide(h_SM);
  h_CaPhi5_CaG1   ->Add(h_SM,-1); h_CaPhi5_CaG1   ->Divide(h_SM);



  double mtt[42], mtt_err[42];
  double sens_CaPhi1_CaGmin5[42], sens_err_CaPhi1_CaGmin5[42];
  double sens_CaPhi1_CaGmin4[42], sens_err_CaPhi1_CaGmin4[42];
  double sens_CaPhi1_CaGmin3[42], sens_err_CaPhi1_CaGmin3[42];
  double sens_CaPhi1_CaGmin2[42], sens_err_CaPhi1_CaGmin2[42];
  double sens_CaPhi1_CaGmin1[42], sens_err_CaPhi1_CaGmin1[42];
  double sens_CaPhi1_CaG1[42]   , sens_err_CaPhi1_CaG1[42];
  double sens_CaPhi1_CaG2[42]   , sens_err_CaPhi1_CaG2[42];
  double sens_CaPhi1_CaG3[42]   , sens_err_CaPhi1_CaG3[42];
  double sens_CaPhi1_CaG4[42]   , sens_err_CaPhi1_CaG4[42];
  double sens_CaPhi1_CaG5[42]   , sens_err_CaPhi1_CaG5[42];
  double sens_CaPhimin5_CaG1[42], sens_err_CaPhimin5_CaG1[42];
  double sens_CaPhimin4_CaG1[42], sens_err_CaPhimin4_CaG1[42];
  double sens_CaPhimin3_CaG1[42], sens_err_CaPhimin3_CaG1[42];
  double sens_CaPhimin2_CaG1[42], sens_err_CaPhimin2_CaG1[42];
  double sens_CaPhimin1_CaG1[42], sens_err_CaPhimin1_CaG1[42];
  double sens_CaPhi2_CaG1[42]   , sens_err_CaPhi2_CaG1[42];
  double sens_CaPhi3_CaG1[42]   , sens_err_CaPhi3_CaG1[42];
  double sens_CaPhi4_CaG1[42]   , sens_err_CaPhi4_CaG1[42];
  double sens_CaPhi5_CaG1[42]   , sens_err_CaPhi5_CaG1[42];

  for(int i=0; i<42; i++){
    mtt[i]     = h_SM->GetBinCenter(i);
    mtt_err[i] = h_SM->GetBinWidth(i)/2.;

    sens_CaPhi1_CaGmin5[i] = h_CaPhi1_CaGmin5->GetBinContent(i);
    sens_CaPhi1_CaGmin4[i] = h_CaPhi1_CaGmin4->GetBinContent(i);
    sens_CaPhi1_CaGmin3[i] = h_CaPhi1_CaGmin3->GetBinContent(i);
    sens_CaPhi1_CaGmin2[i] = h_CaPhi1_CaGmin2->GetBinContent(i);
    sens_CaPhi1_CaGmin1[i] = h_CaPhi1_CaGmin1->GetBinContent(i);
    sens_CaPhi1_CaG1[i]    = h_CaPhi1_CaG1   ->GetBinContent(i);
    sens_CaPhi1_CaG2[i]    = h_CaPhi1_CaG2   ->GetBinContent(i);
    sens_CaPhi1_CaG3[i]    = h_CaPhi1_CaG3   ->GetBinContent(i);
    sens_CaPhi1_CaG4[i]    = h_CaPhi1_CaG4   ->GetBinContent(i);
    sens_CaPhi1_CaG5[i]    = h_CaPhi1_CaG5   ->GetBinContent(i);
    sens_CaPhimin5_CaG1[i] = h_CaPhimin5_CaG1->GetBinContent(i);
    sens_CaPhimin4_CaG1[i] = h_CaPhimin4_CaG1->GetBinContent(i);
    sens_CaPhimin3_CaG1[i] = h_CaPhimin3_CaG1->GetBinContent(i);
    sens_CaPhimin2_CaG1[i] = h_CaPhimin2_CaG1->GetBinContent(i);
    sens_CaPhimin1_CaG1[i] = h_CaPhimin1_CaG1->GetBinContent(i);
    sens_CaPhi2_CaG1[i]    = h_CaPhi2_CaG1   ->GetBinContent(i);
    sens_CaPhi3_CaG1[i]    = h_CaPhi3_CaG1   ->GetBinContent(i);
    sens_CaPhi4_CaG1[i]    = h_CaPhi4_CaG1   ->GetBinContent(i);
    sens_CaPhi5_CaG1[i]    = h_CaPhi5_CaG1   ->GetBinContent(i);

    sens_err_CaPhi1_CaGmin5[i] = h_CaPhi1_CaGmin5->GetBinError(i);
    sens_err_CaPhi1_CaGmin4[i] = h_CaPhi1_CaGmin4->GetBinError(i);
    sens_err_CaPhi1_CaGmin3[i] = h_CaPhi1_CaGmin3->GetBinError(i);
    sens_err_CaPhi1_CaGmin2[i] = h_CaPhi1_CaGmin2->GetBinError(i);
    sens_err_CaPhi1_CaGmin1[i] = h_CaPhi1_CaGmin1->GetBinError(i);
    sens_err_CaPhi1_CaG1[i]    = h_CaPhi1_CaG1   ->GetBinError(i);
    sens_err_CaPhi1_CaG2[i]    = h_CaPhi1_CaG2   ->GetBinError(i);
    sens_err_CaPhi1_CaG3[i]    = h_CaPhi1_CaG3   ->GetBinError(i);
    sens_err_CaPhi1_CaG4[i]    = h_CaPhi1_CaG4   ->GetBinError(i);
    sens_err_CaPhi1_CaG5[i]    = h_CaPhi1_CaG5   ->GetBinError(i);
    sens_err_CaPhimin5_CaG1[i] = h_CaPhimin5_CaG1->GetBinError(i);
    sens_err_CaPhimin4_CaG1[i] = h_CaPhimin4_CaG1->GetBinError(i);
    sens_err_CaPhimin3_CaG1[i] = h_CaPhimin3_CaG1->GetBinError(i);
    sens_err_CaPhimin2_CaG1[i] = h_CaPhimin2_CaG1->GetBinError(i);
    sens_err_CaPhimin1_CaG1[i] = h_CaPhimin1_CaG1->GetBinError(i);
    sens_err_CaPhi2_CaG1[i]    = h_CaPhi2_CaG1   ->GetBinError(i);
    sens_err_CaPhi3_CaG1[i]    = h_CaPhi3_CaG1   ->GetBinError(i);
    sens_err_CaPhi4_CaG1[i]    = h_CaPhi4_CaG1   ->GetBinError(i);
    sens_err_CaPhi5_CaG1[i]    = h_CaPhi5_CaG1   ->GetBinError(i);
  }

  TGraphErrors *gr_CaPhi1_CaGmin5 = new TGraphErrors(42,mtt,sens_CaPhi1_CaGmin5,mtt_err,sens_err_CaPhi1_CaGmin5);
  TGraphErrors *gr_CaPhi1_CaGmin4 = new TGraphErrors(42,mtt,sens_CaPhi1_CaGmin4,mtt_err,sens_err_CaPhi1_CaGmin4);
  TGraphErrors *gr_CaPhi1_CaGmin3 = new TGraphErrors(42,mtt,sens_CaPhi1_CaGmin3,mtt_err,sens_err_CaPhi1_CaGmin3);
  TGraphErrors *gr_CaPhi1_CaGmin2 = new TGraphErrors(42,mtt,sens_CaPhi1_CaGmin2,mtt_err,sens_err_CaPhi1_CaGmin2);
  TGraphErrors *gr_CaPhi1_CaGmin1 = new TGraphErrors(42,mtt,sens_CaPhi1_CaGmin1,mtt_err,sens_err_CaPhi1_CaGmin1);
  TGraphErrors *gr_CaPhi1_CaG1    = new TGraphErrors(42,mtt,sens_CaPhi1_CaG1,mtt_err,sens_err_CaPhi1_CaG1);
  TGraphErrors *gr_CaPhi1_CaG2    = new TGraphErrors(42,mtt,sens_CaPhi1_CaG2,mtt_err,sens_err_CaPhi1_CaG2);
  TGraphErrors *gr_CaPhi1_CaG3    = new TGraphErrors(42,mtt,sens_CaPhi1_CaG3,mtt_err,sens_err_CaPhi1_CaG3);
  TGraphErrors *gr_CaPhi1_CaG4    = new TGraphErrors(42,mtt,sens_CaPhi1_CaG4,mtt_err,sens_err_CaPhi1_CaG4);
  TGraphErrors *gr_CaPhi1_CaG5    = new TGraphErrors(42,mtt,sens_CaPhi1_CaG5,mtt_err,sens_err_CaPhi1_CaG5);
  TGraphErrors *gr_CaPhimin5_CaG1 = new TGraphErrors(42,mtt,sens_CaPhimin5_CaG1,mtt_err,sens_err_CaPhimin5_CaG1);
  TGraphErrors *gr_CaPhimin4_CaG1 = new TGraphErrors(42,mtt,sens_CaPhimin4_CaG1,mtt_err,sens_err_CaPhimin4_CaG1);
  TGraphErrors *gr_CaPhimin3_CaG1 = new TGraphErrors(42,mtt,sens_CaPhimin3_CaG1,mtt_err,sens_err_CaPhimin3_CaG1);
  TGraphErrors *gr_CaPhimin2_CaG1 = new TGraphErrors(42,mtt,sens_CaPhimin2_CaG1,mtt_err,sens_err_CaPhimin2_CaG1);
  TGraphErrors *gr_CaPhimin1_CaG1 = new TGraphErrors(42,mtt,sens_CaPhimin1_CaG1,mtt_err,sens_err_CaPhimin1_CaG1);
  TGraphErrors *gr_CaPhi2_CaG1    = new TGraphErrors(42,mtt,sens_CaPhi2_CaG1,mtt_err,sens_err_CaPhi2_CaG1);
  TGraphErrors *gr_CaPhi3_CaG1    = new TGraphErrors(42,mtt,sens_CaPhi3_CaG1,mtt_err,sens_err_CaPhi3_CaG1);
  TGraphErrors *gr_CaPhi4_CaG1    = new TGraphErrors(42,mtt,sens_CaPhi4_CaG1,mtt_err,sens_err_CaPhi4_CaG1);
  TGraphErrors *gr_CaPhi5_CaG1    = new TGraphErrors(42,mtt,sens_CaPhi5_CaG1,mtt_err,sens_err_CaPhi5_CaG1);

  // marker style
  gr_CaPhi1_CaGmin5->SetMarkerStyle(8);
  gr_CaPhi1_CaGmin4->SetMarkerStyle(8);
  gr_CaPhi1_CaGmin3->SetMarkerStyle(8);
  gr_CaPhi1_CaGmin2->SetMarkerStyle(8);
  gr_CaPhi1_CaGmin1->SetMarkerStyle(8);
  gr_CaPhi1_CaG1   ->SetMarkerStyle(8);
  gr_CaPhi1_CaG2   ->SetMarkerStyle(8);
  gr_CaPhi1_CaG3   ->SetMarkerStyle(8);
  gr_CaPhi1_CaG4   ->SetMarkerStyle(8);
  gr_CaPhi1_CaG5   ->SetMarkerStyle(8);
  gr_CaPhimin5_CaG1->SetMarkerStyle(8);
  gr_CaPhimin4_CaG1->SetMarkerStyle(8);
  gr_CaPhimin3_CaG1->SetMarkerStyle(8);
  gr_CaPhimin2_CaG1->SetMarkerStyle(8);
  gr_CaPhimin1_CaG1->SetMarkerStyle(8);
  gr_CaPhi2_CaG1   ->SetMarkerStyle(8);
  gr_CaPhi3_CaG1   ->SetMarkerStyle(8);
  gr_CaPhi4_CaG1   ->SetMarkerStyle(8);
  gr_CaPhi5_CaG1   ->SetMarkerStyle(8);
  // color scheme
  gr_CaPhi1_CaGmin5->SetMarkerColorAlpha(kBlue,1.0);
  gr_CaPhi1_CaGmin4->SetMarkerColorAlpha(kBlue,0.8);
  gr_CaPhi1_CaGmin3->SetMarkerColorAlpha(kBlue,0.6);
  gr_CaPhi1_CaGmin2->SetMarkerColorAlpha(kBlue,0.4);
  gr_CaPhi1_CaGmin1->SetMarkerColorAlpha(kBlue,0.2);
  gr_CaPhi1_CaG1   ->SetMarkerColorAlpha(kRed ,0.2);
  gr_CaPhi1_CaG2   ->SetMarkerColorAlpha(kRed ,0.4);
  gr_CaPhi1_CaG3   ->SetMarkerColorAlpha(kRed ,0.6);
  gr_CaPhi1_CaG4   ->SetMarkerColorAlpha(kRed ,0.8);
  gr_CaPhi1_CaG5   ->SetMarkerColorAlpha(kRed ,1.0);
  gr_CaPhimin5_CaG1->SetMarkerColorAlpha(kBlue,1.0);
  gr_CaPhimin4_CaG1->SetMarkerColorAlpha(kBlue,0.8);
  gr_CaPhimin3_CaG1->SetMarkerColorAlpha(kBlue,0.6);
  gr_CaPhimin2_CaG1->SetMarkerColorAlpha(kBlue,0.4);
  gr_CaPhimin1_CaG1->SetMarkerColorAlpha(kBlue,0.2);
  gr_CaPhi2_CaG1   ->SetMarkerColorAlpha(kRed ,0.4);
  gr_CaPhi3_CaG1   ->SetMarkerColorAlpha(kRed ,0.6);
  gr_CaPhi4_CaG1   ->SetMarkerColorAlpha(kRed ,0.8);
  gr_CaPhi5_CaG1   ->SetMarkerColorAlpha(kRed ,1.0);
  // line color
  gr_CaPhi1_CaGmin5->SetLineColorAlpha(kBlue,1.0);
  gr_CaPhi1_CaGmin4->SetLineColorAlpha(kBlue,0.8);
  gr_CaPhi1_CaGmin3->SetLineColorAlpha(kBlue,0.6);
  gr_CaPhi1_CaGmin2->SetLineColorAlpha(kBlue,0.4);
  gr_CaPhi1_CaGmin1->SetLineColorAlpha(kBlue,0.2);
  gr_CaPhi1_CaG1   ->SetLineColorAlpha(kRed ,0.2);
  gr_CaPhi1_CaG2   ->SetLineColorAlpha(kRed ,0.4);
  gr_CaPhi1_CaG3   ->SetLineColorAlpha(kRed ,0.6);
  gr_CaPhi1_CaG4   ->SetLineColorAlpha(kRed ,0.8);
  gr_CaPhi1_CaG5   ->SetLineColorAlpha(kRed ,1.0);
  gr_CaPhimin5_CaG1->SetLineColorAlpha(kBlue,1.0);
  gr_CaPhimin4_CaG1->SetLineColorAlpha(kBlue,0.8);
  gr_CaPhimin3_CaG1->SetLineColorAlpha(kBlue,0.6);
  gr_CaPhimin2_CaG1->SetLineColorAlpha(kBlue,0.4);
  gr_CaPhimin1_CaG1->SetLineColorAlpha(kBlue,0.2);
  gr_CaPhi2_CaG1   ->SetLineColorAlpha(kRed ,0.4);
  gr_CaPhi3_CaG1   ->SetLineColorAlpha(kRed ,0.6);
  gr_CaPhi4_CaG1   ->SetLineColorAlpha(kRed ,0.8);
  gr_CaPhi5_CaG1   ->SetLineColorAlpha(kRed ,1.0);

  cout << "plotting..." << endl;

  for(int i=0; i<2; i++){
    TCanvas *c1 = new TCanvas("c1","c1",0,0,800,800);
    c1->SetTitle("TCanvas");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetTicks();
    gPad->SetTopMargin(0.05);
    gPad->SetLeftMargin(0.165);
    gPad->SetRightMargin(0.05);
    gPad->SetBottomMargin(0.14);

    TGraphErrors *gr;
    if(i==0){gr = gr_CaPhi1_CaGmin5;}
    else    {gr = gr_CaPhimin5_CaG1;}
    // x axis
    gr->GetXaxis()->SetTitle(x_label);
    gr->GetXaxis()->SetTitleOffset(x_labeloffset);
    gr->GetXaxis()->SetLimits(x_min,x_max);
    // y axis
    gr->GetYaxis()->SetTitle(y_label);
    gr->GetYaxis()->SetTitleOffset(y_labeloffset);
    gr->GetYaxis()->SetRangeUser(y_min,y_max);

    //legend
    TLegend* legend;
    double xpos   = 0.20;
    double xwidth = 0.70;
    double ypos   = 0.82;
    double ywidth = 0.10;
    legend = new TLegend(xpos,ypos,xpos+xwidth,ypos+ywidth);
    legend->SetBorderSize(1);
    legend->SetTextSize(0.020);
    legend->SetLineColor(0); // 0: white, 1: black
    legend->SetFillColor(0);
    legend->SetFillStyle(1001);
    legend->SetNColumns(5);
    if(i==0){
      legend->AddEntry(gr_CaPhi1_CaGmin5,"C_{a#Phi}=+1, C_{aG}=-5","l");
      // legend->AddEntry(gr_CaPhi1_CaGmin4,"C_{a#Phi}=+1, C_{aG}=-4","l");
      // legend->AddEntry(gr_CaPhi1_CaGmin3,"C_{a#Phi}=+1, C_{aG}=-3","l");
      // legend->AddEntry(gr_CaPhi1_CaGmin2,"C_{a#Phi}=+1, C_{aG}=-2","l");
      // legend->AddEntry(gr_CaPhi1_CaGmin1,"C_{a#Phi}=+1, C_{aG}=-1","l");
      // legend->AddEntry(gr_CaPhi1_CaG1,   "C_{a#Phi}=+1, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhi1_CaG2,   "C_{a#Phi}=+1, C_{aG}=+2","l");
      // legend->AddEntry(gr_CaPhi1_CaG3,   "C_{a#Phi}=+1, C_{aG}=+3","l");
      // legend->AddEntry(gr_CaPhi1_CaG4,   "C_{a#Phi}=+1, C_{aG}=+4","l");
      legend->AddEntry(gr_CaPhi1_CaG5,   "C_{a#Phi}=+1, C_{aG}=+5","l");
      legend->AddEntry(h_ljets, "l+jets");
      legend->AddEntry(h_dilep, "dilepton");
      legend->AddEntry(h_hadr , "hadronic");
      // draw
      gr_CaPhi1_CaGmin5->Draw("AP");
      h_ljets          ->Draw("hist same");
      h_ljets_neg      ->Draw("hist same");
      h_dilep          ->Draw("hist same");
      h_dilep_neg      ->Draw("hist same");
      h_hadr           ->Draw("hist same");
      h_hadr_neg       ->Draw("hist same");
      gr_CaPhi1_CaGmin5->Draw("P same");
      // gr_CaPhi1_CaGmin4->Draw("P same");
      // gr_CaPhi1_CaGmin3->Draw("P same");
      // gr_CaPhi1_CaGmin2->Draw("P same");
      // gr_CaPhi1_CaGmin1->Draw("P same");
      // gr_CaPhi1_CaG1   ->Draw("P same");
      // gr_CaPhi1_CaG2   ->Draw("P same");
      // gr_CaPhi1_CaG3   ->Draw("P same");
      // gr_CaPhi1_CaG4   ->Draw("P same");
      gr_CaPhi1_CaG5   ->Draw("P same");
      legend           ->Draw("same");

      c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/ALP/" + filename + "_CaG.pdf");
      c1->Close();
    }
    else{
      legend->AddEntry(gr_CaPhimin5_CaG1,"C_{a#Phi}=-5, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhimin4_CaG1,"C_{a#Phi}=-4, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhimin3_CaG1,"C_{a#Phi}=-3, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhimin2_CaG1,"C_{a#Phi}=-2, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhimin1_CaG1,"C_{a#Phi}=-1, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhi1_CaG1,   "C_{a#Phi}=+1, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhi2_CaG1,   "C_{a#Phi}=+2, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhi3_CaG1,   "C_{a#Phi}=+3, C_{aG}=+1","l");
      // legend->AddEntry(gr_CaPhi4_CaG1,   "C_{a#Phi}=+4, C_{aG}=+1","l");
      legend->AddEntry(gr_CaPhi5_CaG1,   "C_{a#Phi}=+5, C_{aG}=+1","l");
      legend->AddEntry(h_ljets, "l+jets");
      legend->AddEntry(h_dilep, "dilepton");
      legend->AddEntry(h_hadr , "hadronic");
      // draw
      gr_CaPhimin5_CaG1->Draw("AP");
      h_ljets          ->Draw("hist same");
      h_ljets_neg      ->Draw("hist same");
      h_dilep          ->Draw("hist same");
      h_dilep_neg      ->Draw("hist same");
      h_hadr           ->Draw("hist same");
      h_hadr_neg       ->Draw("hist same");
      gr_CaPhimin5_CaG1->Draw("P same");
      // gr_CaPhimin4_CaG1->Draw("P same");
      // gr_CaPhimin3_CaG1->Draw("P same");
      // gr_CaPhimin2_CaG1->Draw("P same");
      // gr_CaPhimin1_CaG1->Draw("P same");
      // gr_CaPhi1_CaG1   ->Draw("P same");
      // gr_CaPhi2_CaG1   ->Draw("P same");
      // gr_CaPhi3_CaG1   ->Draw("P same");
      // gr_CaPhi4_CaG1   ->Draw("P same");
      gr_CaPhi5_CaG1   ->Draw("P same");
      legend           ->Draw("same");

      c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/ALP/" + filename + "_CaPhi.pdf");
      c1->Close();
    }
  }
}
