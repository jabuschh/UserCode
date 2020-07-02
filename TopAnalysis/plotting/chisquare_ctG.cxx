{
  // specify the Wilson coefficient
  vector<TString> v_WilsonCoeff = {"ctG"};
  vector<TString> v_WC_name     = {"C_{tG}"};


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


    // rescaling
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

    // //rebinning
    // h_ditopmass_min0p25->Rebin(5);
    // h_ditopmass_min0p2 ->Rebin(5);
    // h_ditopmass_min0p15->Rebin(5);
    // h_ditopmass_min0p1 ->Rebin(5);
    // h_ditopmass_min0p05->Rebin(5);
    // h_ditopmass_SM     ->Rebin(5);
    // h_ditopmass_0p05   ->Rebin(5);
    // h_ditopmass_0p1    ->Rebin(5);
    // h_ditopmass_0p15   ->Rebin(5);
    // h_ditopmass_0p2    ->Rebin(5);
    // h_ditopmass_0p25   ->Rebin(5);

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

    //chi square
    h_ditopmass_min0p25->Add(h_ditopmass_SM,-1); h_ditopmass_min0p25->Multiply(h_ditopmass_min0p25); h_ditopmass_min0p25->Divide(h_ditopmass_SM);
    h_ditopmass_min0p2 ->Add(h_ditopmass_SM,-1); h_ditopmass_min0p2 ->Multiply(h_ditopmass_min0p2 ); h_ditopmass_min0p2 ->Divide(h_ditopmass_SM);
    h_ditopmass_min0p15->Add(h_ditopmass_SM,-1); h_ditopmass_min0p15->Multiply(h_ditopmass_min0p15); h_ditopmass_min0p15->Divide(h_ditopmass_SM);
    h_ditopmass_min0p1 ->Add(h_ditopmass_SM,-1); h_ditopmass_min0p1 ->Multiply(h_ditopmass_min0p1 ); h_ditopmass_min0p1 ->Divide(h_ditopmass_SM);
    h_ditopmass_min0p05->Add(h_ditopmass_SM,-1); h_ditopmass_min0p05->Multiply(h_ditopmass_min0p05); h_ditopmass_min0p05->Divide(h_ditopmass_SM);
    h_ditopmass_0p05   ->Add(h_ditopmass_SM,-1); h_ditopmass_0p05   ->Multiply(h_ditopmass_0p05   ); h_ditopmass_0p05   ->Divide(h_ditopmass_SM);
    h_ditopmass_0p1    ->Add(h_ditopmass_SM,-1); h_ditopmass_0p1    ->Multiply(h_ditopmass_0p1    ); h_ditopmass_0p1    ->Divide(h_ditopmass_SM);
    h_ditopmass_0p15   ->Add(h_ditopmass_SM,-1); h_ditopmass_0p15   ->Multiply(h_ditopmass_0p15   ); h_ditopmass_0p15   ->Divide(h_ditopmass_SM);
    h_ditopmass_0p2    ->Add(h_ditopmass_SM,-1); h_ditopmass_0p2    ->Multiply(h_ditopmass_0p2    ); h_ditopmass_0p2    ->Divide(h_ditopmass_SM);
    h_ditopmass_0p25   ->Add(h_ditopmass_SM,-1); h_ditopmass_0p25   ->Multiply(h_ditopmass_0p25   ); h_ditopmass_0p25   ->Divide(h_ditopmass_SM);
    h_ditopmass_SM     ->Add(h_ditopmass_SM,-1); h_ditopmass_SM     ->Multiply(h_ditopmass_SM     ); h_ditopmass_SM     ->Divide(h_ditopmass_SM);


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
    graph->GetYaxis()->SetRangeUser(0.0,0.44);
    // gPad->SetLogy();


    // draw
    graph->Draw("AP");

    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/chisquare_" + WilsonCoeff + ".pdf");
    c1->Close();
  }
}
