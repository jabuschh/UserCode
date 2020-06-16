{
  // specify the Wilson coefficient
  vector<TString> v_WilsonCoeff = {"cQq81"       ,"cQq83"       ,"ctu8"      ,"ctd8"      ,"cQu8"      ,"cQd8"      ,"ctq8"      ,"ctG"};
  vector<TString> v_WC_name     = {"C_{Qq}^{1,8}","C_{Qq}^{3,8}","C_{tu}^{8}","C_{td}^{8}","C_{Qu}^{8}","C_{Qd}^{8}","C_{tq}^{8}","C_{tG}"};

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

  for(int n=0; n<v_WilsonCoeff.size()-1; n++){

    TString WilsonCoeff = v_WilsonCoeff.at(n);
    TString WC_name     = v_WC_name.at(n);
    cout << endl;
    cout << "Wilson coefficient: " << WilsonCoeff << endl;

    /*
    // ██████  ███████  █████  ██████      ██ ███    ██
    // ██   ██ ██      ██   ██ ██   ██     ██ ████   ██
    // ██████  █████   ███████ ██   ██     ██ ██ ██  ██
    // ██   ██ ██      ██   ██ ██   ██     ██ ██  ██ ██
    // ██   ██ ███████ ██   ██ ██████      ██ ██   ████
    */
    cout << "reading in EFT signals from root file..." << endl;
    // EFT signals
    dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/";
    TFile *rootfile = TFile::Open(dir + "SMEFT_" + WilsonCoeff + ".root", "READ");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min5p0"); TH1F* h_ditopmass_min5p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min4p0"); TH1F* h_ditopmass_min4p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min3p0"); TH1F* h_ditopmass_min3p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min2p0"); TH1F* h_ditopmass_min2p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min1p0"); TH1F* h_ditopmass_min1p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_SM");                         TH1F* h_ditopmass_0p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_1p0");    TH1F* h_ditopmass_1p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_2p0");    TH1F* h_ditopmass_2p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_3p0");    TH1F* h_ditopmass_3p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_4p0");    TH1F* h_ditopmass_4p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_5p0");    TH1F* h_ditopmass_5p0    = (TH1F*) gDirectory->Get("mass_ditop");



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



    // normalizing
    h_ditopmass_min5p0->Scale(1./(h_ditopmass_min5p0->Integral()));
    h_ditopmass_min4p0->Scale(1./(h_ditopmass_min4p0->Integral()));
    h_ditopmass_min3p0->Scale(1./(h_ditopmass_min3p0->Integral()));
    h_ditopmass_min2p0->Scale(1./(h_ditopmass_min2p0->Integral()));
    h_ditopmass_min1p0->Scale(1./(h_ditopmass_min1p0->Integral()));
    h_ditopmass_0p0   ->Scale(1./(h_ditopmass_0p0->Integral()));
    h_ditopmass_1p0   ->Scale(1./(h_ditopmass_1p0->Integral()));
    h_ditopmass_2p0   ->Scale(1./(h_ditopmass_2p0->Integral()));
    h_ditopmass_3p0   ->Scale(1./(h_ditopmass_3p0->Integral()));
    h_ditopmass_4p0   ->Scale(1./(h_ditopmass_4p0->Integral()));
    h_ditopmass_5p0   ->Scale(1./(h_ditopmass_5p0->Integral()));
    //rebinning
    h_ditopmass_min5p0->Rebin(5);
    h_ditopmass_min4p0->Rebin(5);
    h_ditopmass_min3p0->Rebin(5);
    h_ditopmass_min2p0->Rebin(5);
    h_ditopmass_min1p0->Rebin(5);
    h_ditopmass_0p0   ->Rebin(5);
    h_ditopmass_1p0   ->Rebin(5);
    h_ditopmass_2p0   ->Rebin(5);
    h_ditopmass_3p0   ->Rebin(5);
    h_ditopmass_4p0   ->Rebin(5);
    h_ditopmass_5p0   ->Rebin(5);

    // sensitivity
    h_ditopmass_min5p0->Add(h_ditopmass_0p0,-1); h_ditopmass_min5p0->Divide(h_ditopmass_0p0);
    h_ditopmass_min4p0->Add(h_ditopmass_0p0,-1); h_ditopmass_min4p0->Divide(h_ditopmass_0p0);
    h_ditopmass_min3p0->Add(h_ditopmass_0p0,-1); h_ditopmass_min3p0->Divide(h_ditopmass_0p0);
    h_ditopmass_min2p0->Add(h_ditopmass_0p0,-1); h_ditopmass_min2p0->Divide(h_ditopmass_0p0);
    h_ditopmass_min1p0->Add(h_ditopmass_0p0,-1); h_ditopmass_min1p0->Divide(h_ditopmass_0p0);
    h_ditopmass_1p0   ->Add(h_ditopmass_0p0,-1); h_ditopmass_1p0   ->Divide(h_ditopmass_0p0);
    h_ditopmass_2p0   ->Add(h_ditopmass_0p0,-1); h_ditopmass_2p0   ->Divide(h_ditopmass_0p0);
    h_ditopmass_3p0   ->Add(h_ditopmass_0p0,-1); h_ditopmass_3p0   ->Divide(h_ditopmass_0p0);
    h_ditopmass_4p0   ->Add(h_ditopmass_0p0,-1); h_ditopmass_4p0   ->Divide(h_ditopmass_0p0);
    h_ditopmass_5p0   ->Add(h_ditopmass_0p0,-1); h_ditopmass_5p0   ->Divide(h_ditopmass_0p0);

    int N_bins = (int) h_ditopmass_0p0->GetSize();

    // cout << "EFT signal total bins: " << N_bins << endl;
    // cout << endl;

    double mtt[N_bins], mtt_err[N_bins];
    double sens_min5p0[N_bins], sens_err_min5p0[N_bins];
    double sens_min4p0[N_bins], sens_err_min4p0[N_bins];
    double sens_min3p0[N_bins], sens_err_min3p0[N_bins];
    double sens_min2p0[N_bins], sens_err_min2p0[N_bins];
    double sens_min1p0[N_bins], sens_err_min1p0[N_bins];
    double sens_1p0[N_bins], sens_err_1p0[N_bins];
    double sens_2p0[N_bins], sens_err_2p0[N_bins];
    double sens_3p0[N_bins], sens_err_3p0[N_bins];
    double sens_4p0[N_bins], sens_err_4p0[N_bins];
    double sens_5p0[N_bins], sens_err_5p0[N_bins];

    for(int i=0; i<N_bins; i++){
      mtt[i]  = h_ditopmass_0p0->GetBinCenter(i);
      mtt_err[i] = h_ditopmass_0p0->GetBinWidth(i) / 2;

      if(h_ditopmass_0p0->GetBinContent(i) > 0.){
        sens_min5p0[i] = h_ditopmass_min5p0->GetBinContent(i);
        sens_min4p0[i] = h_ditopmass_min4p0->GetBinContent(i);
        sens_min3p0[i] = h_ditopmass_min3p0->GetBinContent(i);
        sens_min2p0[i] = h_ditopmass_min2p0->GetBinContent(i);
        sens_min1p0[i] = h_ditopmass_min1p0->GetBinContent(i);
        sens_1p0[i]    = h_ditopmass_1p0   ->GetBinContent(i);
        sens_2p0[i]    = h_ditopmass_2p0   ->GetBinContent(i);
        sens_3p0[i]    = h_ditopmass_3p0   ->GetBinContent(i);
        sens_4p0[i]    = h_ditopmass_4p0   ->GetBinContent(i);
        sens_5p0[i]    = h_ditopmass_5p0   ->GetBinContent(i);
        sens_err_min5p0[i] = h_ditopmass_min5p0->GetBinError(i);
        sens_err_min4p0[i] = h_ditopmass_min4p0->GetBinError(i);
        sens_err_min3p0[i] = h_ditopmass_min3p0->GetBinError(i);
        sens_err_min2p0[i] = h_ditopmass_min2p0->GetBinError(i);
        sens_err_min1p0[i] = h_ditopmass_min1p0->GetBinError(i);
        sens_err_1p0[i]    = h_ditopmass_1p0   ->GetBinError(i);
        sens_err_2p0[i]    = h_ditopmass_2p0   ->GetBinError(i);
        sens_err_3p0[i]    = h_ditopmass_3p0   ->GetBinError(i);
        sens_err_4p0[i]    = h_ditopmass_4p0   ->GetBinError(i);
        sens_err_5p0[i]    = h_ditopmass_5p0   ->GetBinError(i);
      }
      else{
        sens_min5p0[i] = 0.;
        sens_min4p0[i] = 0.;
        sens_min3p0[i] = 0.;
        sens_min2p0[i] = 0.;
        sens_min1p0[i] = 0.;
        sens_1p0[i]    = 0.;
        sens_2p0[i]    = 0.;
        sens_3p0[i]    = 0.;
        sens_4p0[i]    = 0.;
        sens_5p0[i]    = 0.;
        sens_err_min5p0[i] = 0.;
        sens_err_min4p0[i] = 0.;
        sens_err_min3p0[i] = 0.;
        sens_err_min2p0[i] = 0.;
        sens_err_min1p0[i] = 0.;
        sens_err_1p0[i]    = 0.;
        sens_err_2p0[i]    = 0.;
        sens_err_3p0[i]    = 0.;
        sens_err_4p0[i]    = 0.;
        sens_err_5p0[i]    = 0.;
      }
    }


    TGraphErrors* gr_min5p0 = new TGraphErrors(N_bins,mtt,sens_min5p0,mtt_err,sens_err_min5p0);
    TGraphErrors* gr_min4p0 = new TGraphErrors(N_bins,mtt,sens_min4p0,mtt_err,sens_err_min4p0);
    TGraphErrors* gr_min3p0 = new TGraphErrors(N_bins,mtt,sens_min3p0,mtt_err,sens_err_min3p0);
    TGraphErrors* gr_min2p0 = new TGraphErrors(N_bins,mtt,sens_min2p0,mtt_err,sens_err_min2p0);
    TGraphErrors* gr_min1p0 = new TGraphErrors(N_bins,mtt,sens_min1p0,mtt_err,sens_err_min1p0);
    TGraphErrors* gr_1p0    = new TGraphErrors(N_bins,mtt,sens_1p0   ,mtt_err,sens_err_1p0);
    TGraphErrors* gr_2p0    = new TGraphErrors(N_bins,mtt,sens_2p0   ,mtt_err,sens_err_2p0);
    TGraphErrors* gr_3p0    = new TGraphErrors(N_bins,mtt,sens_3p0   ,mtt_err,sens_err_3p0);
    TGraphErrors* gr_4p0    = new TGraphErrors(N_bins,mtt,sens_4p0   ,mtt_err,sens_err_4p0);
    TGraphErrors* gr_5p0    = new TGraphErrors(N_bins,mtt,sens_5p0   ,mtt_err,sens_err_5p0);


    // color scheme
    gr_min5p0->SetMarkerColorAlpha(kBlue,1.0);
    gr_min4p0->SetMarkerColorAlpha(kBlue,0.8);
    gr_min3p0->SetMarkerColorAlpha(kBlue,0.6);
    gr_min2p0->SetMarkerColorAlpha(kBlue,0.4);
    gr_min1p0->SetMarkerColorAlpha(kBlue,0.2);
    gr_1p0   ->SetMarkerColorAlpha(kRed,0.2);
    gr_2p0   ->SetMarkerColorAlpha(kRed,0.4);
    gr_3p0   ->SetMarkerColorAlpha(kRed,0.6);
    gr_4p0   ->SetMarkerColorAlpha(kRed,0.8);
    gr_5p0   ->SetMarkerColorAlpha(kRed,1.0);
    // marker style
    gr_min5p0->SetMarkerStyle(8);
    gr_min4p0->SetMarkerStyle(8);
    gr_min3p0->SetMarkerStyle(8);
    gr_min2p0->SetMarkerStyle(8);
    gr_min1p0->SetMarkerStyle(8);
    gr_1p0   ->SetMarkerStyle(8);
    gr_2p0   ->SetMarkerStyle(8);
    gr_3p0   ->SetMarkerStyle(8);
    gr_4p0   ->SetMarkerStyle(8);
    gr_5p0   ->SetMarkerStyle(8);
    // line color
    gr_min5p0->SetLineColorAlpha(kBlue,1.0);
    gr_min4p0->SetLineColorAlpha(kBlue,0.8);
    gr_min3p0->SetLineColorAlpha(kBlue,0.6);
    gr_min2p0->SetLineColorAlpha(kBlue,0.4);
    gr_min1p0->SetLineColorAlpha(kBlue,0.2);
    gr_1p0   ->SetLineColorAlpha(kRed,0.2);
    gr_2p0   ->SetLineColorAlpha(kRed,0.4);
    gr_3p0   ->SetLineColorAlpha(kRed,0.6);
    gr_4p0   ->SetLineColorAlpha(kRed,0.8);
    gr_5p0   ->SetLineColorAlpha(kRed,1.0);

    // gr_min5p0->SetDrawOption("AP");
    // gr_min4p0->SetDrawOption("AP");
    // gr_min3p0->SetDrawOption("AP");
    // gr_min2p0->SetDrawOption("AP");
    // gr_min1p0->SetDrawOption("AP");
    // gr_1p0   ->SetDrawOption("AP");
    // gr_2p0   ->SetDrawOption("AP");
    // gr_3p0   ->SetDrawOption("AP");
    // gr_4p0   ->SetDrawOption("AP");
    // gr_5p0   ->SetDrawOption("AP");


    cout << "plotting..." << endl;
    TCanvas *c1 = new TCanvas("c1","c1",0,0,800,800);
    c1->SetTitle("TCanvas");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetTicks();
    gPad->SetTopMargin(0.05);
    gPad->SetLeftMargin(0.165);
    gPad->SetRightMargin(0.05);
    gPad->SetBottomMargin(0.14);

    // x axis
    gr_min5p0->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
    gr_min5p0->GetXaxis()->SetTitleOffset(1.5);
    gr_min5p0->GetXaxis()->SetLimits(0,4000);
    // y axis
    gr_min5p0->GetYaxis()->SetTitle("#frac{N_{events}^{WC} - N_{events}^{SM}}{N_{events}^{SM}}");
    gr_min5p0->GetYaxis()->SetTitleOffset(2.0);
    gr_min5p0->GetYaxis()->SetRangeUser(-2.1,2.1);




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
    legend->AddEntry(gr_min1p0, WC_name + " = -1.0","l");
    legend->AddEntry(gr_min2p0, WC_name + " = -2.0","l");
    legend->AddEntry(gr_min3p0, WC_name + " = -3.0","l");
    legend->AddEntry(gr_min4p0, WC_name + " = -4.0","l");
    legend->AddEntry(gr_min5p0, WC_name + " = -5.0","l");
    legend->AddEntry(gr_1p0   , WC_name + " = +1.0","l");
    legend->AddEntry(gr_2p0   , WC_name + " = +2.0","l");
    legend->AddEntry(gr_3p0   , WC_name + " = +3.0","l");
    legend->AddEntry(gr_4p0   , WC_name + " = +4.0","l");
    legend->AddEntry(gr_5p0   , WC_name + " = +5.0","l");
    legend->AddEntry(h_ljets, "l+jets");
    legend->AddEntry(h_dilep, "dilepton");
    legend->AddEntry(h_hadr , "hadronic");




    // draw
    gr_min5p0  ->Draw("AP");
    h_ljets    ->Draw("hist same");
    h_ljets_neg->Draw("hist same");
    h_dilep    ->Draw("hist same");
    h_dilep_neg->Draw("hist same");
    h_hadr     ->Draw("hist same");
    h_hadr_neg ->Draw("hist same");
    gr_min5p0  ->Draw("P same");
    gr_min4p0  ->Draw("P same");
    gr_min3p0  ->Draw("P same");
    gr_min2p0  ->Draw("P same");
    gr_min1p0  ->Draw("P same");
    gr_1p0     ->Draw("P same");
    gr_2p0     ->Draw("P same");
    gr_3p0     ->Draw("P same");
    gr_4p0     ->Draw("P same");
    gr_5p0     ->Draw("P same");
    legend     ->Draw("same");


    // break;
    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/sensitivity_normalizedmtt_" + WilsonCoeff + ".pdf");
    // break;
    c1->Close();
  }
}
