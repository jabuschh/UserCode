{
  // specify the Wilson coefficient
  vector<TString> v_WilsonCoeff = {"ctG"};
  vector<TString> v_WC_name     = {"C_{tG}"};

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



  for(int n=0; n<v_WilsonCoeff.size(); n++){

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

    cout << "reading in histograms from root file..." << endl;
    TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/SMEFT/";
    TFile *rootfile = TFile::Open(dir + "SMEFT_" + WilsonCoeff + ".root", "READ");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p25"); TH1F* h_ditopmass_min0p25 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p2");  TH1F* h_ditopmass_min0p2  = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p15"); TH1F* h_ditopmass_min0p15 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p1");  TH1F* h_ditopmass_min0p1  = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p05"); TH1F* h_ditopmass_min0p05 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_SM");                          TH1F* h_ditopmass_SM      = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p05");    TH1F* h_ditopmass_0p05    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p1");     TH1F* h_ditopmass_0p1     = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p15");    TH1F* h_ditopmass_0p15    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p2");     TH1F* h_ditopmass_0p2     = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p25");    TH1F* h_ditopmass_0p25    = (TH1F*) gDirectory->Get("mass_ditop");


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

    // normalizing
    h_ditopmass_min0p25->Scale(1./(h_ditopmass_min0p25->Integral()));
    h_ditopmass_min0p2 ->Scale(1./(h_ditopmass_min0p2 ->Integral()));
    h_ditopmass_min0p15->Scale(1./(h_ditopmass_min0p15->Integral()));
    h_ditopmass_min0p1 ->Scale(1./(h_ditopmass_min0p1 ->Integral()));
    h_ditopmass_min0p05->Scale(1./(h_ditopmass_min0p05->Integral()));
    h_ditopmass_SM     ->Scale(1./(h_ditopmass_SM  ->Integral()));
    h_ditopmass_0p05   ->Scale(1./(h_ditopmass_0p05->Integral()));
    h_ditopmass_0p1    ->Scale(1./(h_ditopmass_0p1 ->Integral()));
    h_ditopmass_0p15   ->Scale(1./(h_ditopmass_0p15->Integral()));
    h_ditopmass_0p2    ->Scale(1./(h_ditopmass_0p2 ->Integral()));
    h_ditopmass_0p25   ->Scale(1./(h_ditopmass_0p25->Integral()));

    //rebinning to match binning from SM data
    h_ditopmass_min0p25->Rebin(5);
    h_ditopmass_min0p2 ->Rebin(5);
    h_ditopmass_min0p15->Rebin(5);
    h_ditopmass_min0p1 ->Rebin(5);
    h_ditopmass_min0p05->Rebin(5);
    h_ditopmass_SM     ->Rebin(5);
    h_ditopmass_0p05   ->Rebin(5);
    h_ditopmass_0p1    ->Rebin(5);
    h_ditopmass_0p15   ->Rebin(5);
    h_ditopmass_0p2    ->Rebin(5);
    h_ditopmass_0p25   ->Rebin(5);

    // color scheme
    h_ditopmass_min0p25->SetLineColorAlpha(kBlue,1.0);
    h_ditopmass_min0p2 ->SetLineColorAlpha(kBlue,0.8);
    h_ditopmass_min0p15->SetLineColorAlpha(kBlue,0.6);
    h_ditopmass_min0p1 ->SetLineColorAlpha(kBlue,0.4);
    h_ditopmass_min0p05->SetLineColorAlpha(kBlue,0.2);
    h_ditopmass_SM     ->SetLineColor(kBlack);
    h_ditopmass_0p05   ->SetLineColorAlpha(kRed,0.2);
    h_ditopmass_0p1    ->SetLineColorAlpha(kRed,0.4);
    h_ditopmass_0p15   ->SetLineColorAlpha(kRed,0.6);
    h_ditopmass_0p2    ->SetLineColorAlpha(kRed,0.8);
    h_ditopmass_0p25   ->SetLineColorAlpha(kRed,1.0);
    //line width
    h_ditopmass_min0p25->SetLineWidth(2);
    h_ditopmass_min0p2 ->SetLineWidth(2);
    h_ditopmass_min0p15->SetLineWidth(2);
    h_ditopmass_min0p1 ->SetLineWidth(2);
    h_ditopmass_min0p05->SetLineWidth(2);
    h_ditopmass_SM     ->SetLineWidth(2);
    h_ditopmass_0p05   ->SetLineWidth(2);
    h_ditopmass_0p1    ->SetLineWidth(2);
    h_ditopmass_0p15   ->SetLineWidth(2);
    h_ditopmass_0p2    ->SetLineWidth(2);
    h_ditopmass_0p25   ->SetLineWidth(2);

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

    //rebinning again to have non-empty SM data uncertainty bins
    h_ditopmass_min0p25->Rebin(4);
    h_ditopmass_min0p2 ->Rebin(4);
    h_ditopmass_min0p15->Rebin(4);
    h_ditopmass_min0p1 ->Rebin(4);
    h_ditopmass_min0p05->Rebin(4);
    h_ditopmass_SM     ->Rebin(4);
    h_ditopmass_0p05   ->Rebin(4);
    h_ditopmass_0p1    ->Rebin(4);
    h_ditopmass_0p15   ->Rebin(4);
    h_ditopmass_0p2    ->Rebin(4);
    h_ditopmass_0p25   ->Rebin(4);
    h_dilep            ->Rebin(4);


    h_dilep->Multiply(h_dilep); // sigma^2
    //only for other plotting
    h_dilep->SetFillStyle(3353);
    h_dilep->SetFillColor(kGray+2);
    h_dilep->SetLineColor(kGray+2);


    //chi square
    h_ditopmass_min0p25->Add(h_ditopmass_SM,-1); h_ditopmass_min0p25->Multiply(h_ditopmass_min0p25); //h_ditopmass_min0p25->Divide(h_dilep);
    h_ditopmass_min0p2 ->Add(h_ditopmass_SM,-1); h_ditopmass_min0p2 ->Multiply(h_ditopmass_min0p2 ); //h_ditopmass_min0p2 ->Divide(h_dilep);
    h_ditopmass_min0p15->Add(h_ditopmass_SM,-1); h_ditopmass_min0p15->Multiply(h_ditopmass_min0p15); //h_ditopmass_min0p15->Divide(h_dilep);
    h_ditopmass_min0p1 ->Add(h_ditopmass_SM,-1); h_ditopmass_min0p1 ->Multiply(h_ditopmass_min0p1 ); //h_ditopmass_min0p1 ->Divide(h_dilep);
    h_ditopmass_min0p05->Add(h_ditopmass_SM,-1); h_ditopmass_min0p05->Multiply(h_ditopmass_min0p05); //h_ditopmass_min0p05->Divide(h_dilep);
    h_ditopmass_0p05   ->Add(h_ditopmass_SM,-1); h_ditopmass_0p05   ->Multiply(h_ditopmass_0p05   ); //h_ditopmass_0p05   ->Divide(h_dilep);
    h_ditopmass_0p1    ->Add(h_ditopmass_SM,-1); h_ditopmass_0p1    ->Multiply(h_ditopmass_0p1    ); //h_ditopmass_0p1    ->Divide(h_dilep);
    h_ditopmass_0p15   ->Add(h_ditopmass_SM,-1); h_ditopmass_0p15   ->Multiply(h_ditopmass_0p15   ); //h_ditopmass_0p15   ->Divide(h_dilep);
    h_ditopmass_0p2    ->Add(h_ditopmass_SM,-1); h_ditopmass_0p2    ->Multiply(h_ditopmass_0p2    ); //h_ditopmass_0p2    ->Divide(h_dilep);
    h_ditopmass_0p25   ->Add(h_ditopmass_SM,-1); h_ditopmass_0p25   ->Multiply(h_ditopmass_0p25   ); //h_ditopmass_0p25   ->Divide(h_dilep);
    h_ditopmass_SM     ->Add(h_ditopmass_SM,-1); h_ditopmass_SM     ->Multiply(h_ditopmass_SM     ); //h_ditopmass_SM     ->Divide(h_dilep);


    for(int i=0; i<h_ditopmass_SM->GetSize(); i++){
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_min0p25->SetBinContent(i, (h_ditopmass_min0p25->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_min0p2 ->SetBinContent(i, (h_ditopmass_min0p2 ->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_min0p15->SetBinContent(i, (h_ditopmass_min0p15->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_min0p1 ->SetBinContent(i, (h_ditopmass_min0p1 ->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_min0p05->SetBinContent(i, (h_ditopmass_min0p05->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_0p05   ->SetBinContent(i, (h_ditopmass_0p05   ->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_0p1    ->SetBinContent(i, (h_ditopmass_0p1    ->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_0p15   ->SetBinContent(i, (h_ditopmass_0p15   ->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_0p2    ->SetBinContent(i, (h_ditopmass_0p2    ->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_0p25   ->SetBinContent(i, (h_ditopmass_0p25   ->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) > 0) h_ditopmass_SM     ->SetBinContent(i, (h_ditopmass_SM     ->GetBinContent(i) / h_dilep->GetBinContent(i)));
      if(h_dilep->GetBinContent(i) <= 0) cout << "bin, content: " << i << ", " << h_dilep->GetBinContent(i) << endl;
    }
    cout << "total bins (without over-/underflow bins): " << h_ditopmass_SM->GetSize()-2 << endl;

    // h_ditopmass_min0p25->Draw("hist");
    // h_ditopmass_min0p2 ->Draw("hist same");
    // h_ditopmass_min0p15->Draw("hist same");
    // h_ditopmass_min0p1 ->Draw("hist same");
    // h_ditopmass_min0p05->Draw("hist same");
    // h_ditopmass_SM     ->Draw("hist same");
    // h_ditopmass_0p05   ->Draw("hist same");
    // h_ditopmass_0p1    ->Draw("hist same");
    // h_ditopmass_0p15   ->Draw("hist same");
    // h_ditopmass_0p2    ->Draw("hist same");
    // h_ditopmass_0p25   ->Draw("hist same");
    // h_dilep            ->Draw("hist same");
    // break;

    double chisquare[11] = {
      h_ditopmass_min0p25->Integral(),
      h_ditopmass_min0p2 ->Integral(),
      h_ditopmass_min0p15->Integral(),
      h_ditopmass_min0p1 ->Integral(),
      h_ditopmass_min0p05->Integral(),
      h_ditopmass_SM     ->Integral(),
      h_ditopmass_0p05   ->Integral(),
      h_ditopmass_0p1    ->Integral(),
      h_ditopmass_0p15   ->Integral(),
      h_ditopmass_0p2    ->Integral(),
      h_ditopmass_0p25   ->Integral()
    };
    double ctG[11] = {-0.25,-0.2,-0.15,-0.1,-0.05,0.0,0.05,0.1,0.15,0.2,0.25};

    TGraph *graph = new TGraph(11,ctG,chisquare);
    graph->SetMarkerColor(kBlack);
    graph->SetMarkerStyle(8);

    // x axis
    graph->GetXaxis()->SetTitle("C_{tG}");
    graph->GetXaxis()->SetTitleOffset(1.4);
    graph->GetXaxis()->SetRangeUser(-0.29,0.29);
    // y axis
    graph->GetYaxis()->SetTitle("#chi^{2}");
    graph->GetYaxis()->SetTitleOffset(2.0);
    graph->GetYaxis()->SetRangeUser(0,0.1);
    // gPad->SetLogy();


    // draw
    graph->Draw("AP");

    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/SMEFT/chisquare_" + WilsonCoeff + ".pdf");
    c1->Close();
  }
}
