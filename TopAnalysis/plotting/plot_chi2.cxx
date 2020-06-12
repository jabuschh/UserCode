{
  // specify the Wilson coefficient
  vector<TString> v_WilsonCoeff = {"cQq81"       ,"cQq83"       ,"ctu8"      ,"ctd8"      ,"cQu8"      ,"cQd8"      ,"ctq8"      ,"ctG"};
  vector<TString> v_WC_name     = {"C_{Qq}^{1,8}","C_{Qq}^{3,8}","C_{tu}^{8}","C_{td}^{8}","C_{Qu}^{8}","C_{Qd}^{8}","C_{tq}^{8}","C_{tG}"};


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
    TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/";
    TFile *rootfile = TFile::Open(dir + "rwgt_" + WilsonCoeff + ".root", "READ");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min5p0"); TH1F* h_ditopmass_min5p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min4p0"); TH1F* h_ditopmass_min4p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min3p0"); TH1F* h_ditopmass_min3p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min2p0"); TH1F* h_ditopmass_min2p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min1p0"); TH1F* h_ditopmass_min1p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p0");    TH1F* h_ditopmass_0p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_1p0");    TH1F* h_ditopmass_1p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_2p0");    TH1F* h_ditopmass_2p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_3p0");    TH1F* h_ditopmass_3p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_4p0");    TH1F* h_ditopmass_4p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_5p0");    TH1F* h_ditopmass_5p0    = (TH1F*) gDirectory->Get("mass_ditop");

    // rescaling
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



    int N = 11;
    double WCs[11] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
    double chiSquare[11];
    vector<TH1F*> v_hists = {
      h_ditopmass_min5p0,
      h_ditopmass_min4p0,
      h_ditopmass_min3p0,
      h_ditopmass_min2p0,
      h_ditopmass_min1p0,
      h_ditopmass_0p0,
      h_ditopmass_1p0,
      h_ditopmass_2p0,
      h_ditopmass_3p0,
      h_ditopmass_4p0,
      h_ditopmass_5p0
    };


    for(int j=0; j<v_hists.size(); j++){
      TH1F* h = v_hists.at(j);
      double chi2 = 0.0;

      for(int i=1; i<h->GetSize()-1; i++){ //neglect under- and overflow bin
        double ditopmass_rwgt   = h->GetBinContent(i);
        double ditopmass_SM     = h_ditopmass_0p0->GetBinContent(i);
        double ditopmass_SM_err = h_ditopmass_0p0->GetBinError(i);

        if(ditopmass_rwgt != ditopmass_SM) chi2 += (ditopmass_rwgt - ditopmass_SM) * (ditopmass_rwgt - ditopmass_SM) / (ditopmass_SM_err * ditopmass_SM_err);  // 

      }
      chiSquare[j] = chi2;

      // cout << "chi2: " << chi2 << endl;
      // cout << "   n: " << h->GetSize() << endl;
      // cout << endl;

    }



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



    TGraph *graph;
    graph = new TGraph(N,WCs,chiSquare);
    graph->SetMarkerStyle(8);
    graph->SetMarkerColor(kBlack);
    //x axis
    graph->GetXaxis()->SetTitle(WC_name);
    graph->GetXaxis()->SetTitleOffset(1.5);
    graph->GetXaxis()->SetLimits(-5.999,5.999);
    //y axis
    graph->GetYaxis()->SetTitle("#chi^{2}");
    graph->GetYaxis()->SetTitleOffset(2.0);
    // graph->GetYaxis()->SetRangeUser(0,0.01);

    graph->Draw("AP");
    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/chi2_" + WilsonCoeff + ".pdf");
    c1->Close();
  }
}
