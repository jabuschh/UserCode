{
  // specify the Wilson coefficient
  vector<TString> v_WilsonCoeff = {"cQq81"       ,"cQq83"       ,"ctu8"      ,"ctd8"      ,"cQu8"      ,"cQd8"      ,"ctq8"      ,"ctG"};
  vector<TString> v_WC_name     = {"C_{Qq}^{1,8}","C_{Qq}^{3,8}","C_{tu}^{8}","C_{td}^{8}","C_{Qu}^{8}","C_{Qd}^{8}","C_{tq}^{8}","C_{tG}"};


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
    TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/";
    TFile *rootfile = TFile::Open(dir + "SMEFT_" + WilsonCoeff + ".root", "READ");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min5p0"); TH1F* h_ditopmass_min5p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min4p0"); TH1F* h_ditopmass_min4p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min3p0"); TH1F* h_ditopmass_min3p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min2p0"); TH1F* h_ditopmass_min2p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min1p0"); TH1F* h_ditopmass_min1p0 = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_SM");                         TH1F* h_ditopmass_SM     = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_1p0");    TH1F* h_ditopmass_1p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_2p0");    TH1F* h_ditopmass_2p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_3p0");    TH1F* h_ditopmass_3p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_4p0");    TH1F* h_ditopmass_4p0    = (TH1F*) gDirectory->Get("mass_ditop");
    rootfile->cd("rwgt_" + WilsonCoeff + "_5p0");    TH1F* h_ditopmass_5p0    = (TH1F*) gDirectory->Get("mass_ditop");


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
    h_ditopmass_min5p0->Scale(1./(h_ditopmass_min5p0->Integral()));
    h_ditopmass_min4p0->Scale(1./(h_ditopmass_min4p0->Integral()));
    h_ditopmass_min3p0->Scale(1./(h_ditopmass_min3p0->Integral()));
    h_ditopmass_min2p0->Scale(1./(h_ditopmass_min2p0->Integral()));
    h_ditopmass_min1p0->Scale(1./(h_ditopmass_min1p0->Integral()));
    h_ditopmass_SM    ->Scale(1./(h_ditopmass_SM    ->Integral()));
    h_ditopmass_1p0   ->Scale(1./(h_ditopmass_1p0   ->Integral()));
    h_ditopmass_2p0   ->Scale(1./(h_ditopmass_2p0   ->Integral()));
    h_ditopmass_3p0   ->Scale(1./(h_ditopmass_3p0   ->Integral()));
    h_ditopmass_4p0   ->Scale(1./(h_ditopmass_4p0   ->Integral()));
    h_ditopmass_5p0   ->Scale(1./(h_ditopmass_5p0   ->Integral()));

    // //rebinning
    // h_ditopmass_min5p0->Rebin(5);
    // h_ditopmass_min4p0 ->Rebin(5);
    // h_ditopmass_min3p0->Rebin(5);
    // h_ditopmass_min2p0 ->Rebin(5);
    // h_ditopmass_min1p0->Rebin(5);
    // h_ditopmass_SM     ->Rebin(5);
    // h_ditopmass_1p0   ->Rebin(5);
    // h_ditopmass_2p0    ->Rebin(5);
    // h_ditopmass_3p0   ->Rebin(5);
    // h_ditopmass_4p0    ->Rebin(5);
    // h_ditopmass_5p0   ->Rebin(5);

    // color scheme
    h_ditopmass_min5p0->SetLineColorAlpha(kBlue,1.0);
    h_ditopmass_min4p0->SetLineColorAlpha(kBlue,0.8);
    h_ditopmass_min3p0->SetLineColorAlpha(kBlue,0.6);
    h_ditopmass_min2p0->SetLineColorAlpha(kBlue,0.4);
    h_ditopmass_min1p0->SetLineColorAlpha(kBlue,0.2);
    h_ditopmass_SM    ->SetLineColor(kBlack);
    h_ditopmass_1p0   ->SetLineColorAlpha(kRed,0.2);
    h_ditopmass_2p0   ->SetLineColorAlpha(kRed,0.4);
    h_ditopmass_3p0   ->SetLineColorAlpha(kRed,0.6);
    h_ditopmass_4p0   ->SetLineColorAlpha(kRed,0.8);
    h_ditopmass_5p0   ->SetLineColorAlpha(kRed,1.0);
    //line width
    h_ditopmass_min5p0->SetLineWidth(2);
    h_ditopmass_min4p0->SetLineWidth(2);
    h_ditopmass_min3p0->SetLineWidth(2);
    h_ditopmass_min2p0->SetLineWidth(2);
    h_ditopmass_min1p0->SetLineWidth(2);
    h_ditopmass_SM    ->SetLineWidth(2);
    h_ditopmass_1p0   ->SetLineWidth(2);
    h_ditopmass_2p0   ->SetLineWidth(2);
    h_ditopmass_3p0   ->SetLineWidth(2);
    h_ditopmass_4p0   ->SetLineWidth(2);
    h_ditopmass_5p0   ->SetLineWidth(2);

    //chi square
    h_ditopmass_min5p0->Add(h_ditopmass_SM,-1); h_ditopmass_min5p0->Multiply(h_ditopmass_min5p0); h_ditopmass_min5p0->Divide(h_ditopmass_SM);
    h_ditopmass_min4p0->Add(h_ditopmass_SM,-1); h_ditopmass_min4p0->Multiply(h_ditopmass_min4p0); h_ditopmass_min4p0->Divide(h_ditopmass_SM);
    h_ditopmass_min3p0->Add(h_ditopmass_SM,-1); h_ditopmass_min3p0->Multiply(h_ditopmass_min3p0); h_ditopmass_min3p0->Divide(h_ditopmass_SM);
    h_ditopmass_min2p0->Add(h_ditopmass_SM,-1); h_ditopmass_min2p0->Multiply(h_ditopmass_min2p0); h_ditopmass_min2p0->Divide(h_ditopmass_SM);
    h_ditopmass_min1p0->Add(h_ditopmass_SM,-1); h_ditopmass_min1p0->Multiply(h_ditopmass_min1p0); h_ditopmass_min1p0->Divide(h_ditopmass_SM);
    h_ditopmass_1p0   ->Add(h_ditopmass_SM,-1); h_ditopmass_1p0   ->Multiply(h_ditopmass_1p0   ); h_ditopmass_1p0   ->Divide(h_ditopmass_SM);
    h_ditopmass_2p0   ->Add(h_ditopmass_SM,-1); h_ditopmass_2p0   ->Multiply(h_ditopmass_2p0   ); h_ditopmass_2p0   ->Divide(h_ditopmass_SM);
    h_ditopmass_3p0   ->Add(h_ditopmass_SM,-1); h_ditopmass_3p0   ->Multiply(h_ditopmass_3p0   ); h_ditopmass_3p0   ->Divide(h_ditopmass_SM);
    h_ditopmass_4p0   ->Add(h_ditopmass_SM,-1); h_ditopmass_4p0   ->Multiply(h_ditopmass_4p0   ); h_ditopmass_4p0   ->Divide(h_ditopmass_SM);
    h_ditopmass_5p0   ->Add(h_ditopmass_SM,-1); h_ditopmass_5p0   ->Multiply(h_ditopmass_5p0   ); h_ditopmass_5p0   ->Divide(h_ditopmass_SM);
    h_ditopmass_SM    ->Add(h_ditopmass_SM,-1); h_ditopmass_SM    ->Multiply(h_ditopmass_SM    ); h_ditopmass_SM    ->Divide(h_ditopmass_SM);


    double chisquare[11] = {
      h_ditopmass_min5p0->Integral(),
      h_ditopmass_min4p0->Integral(),
      h_ditopmass_min3p0->Integral(),
      h_ditopmass_min2p0->Integral(),
      h_ditopmass_min1p0->Integral(),
      h_ditopmass_SM    ->Integral(),
      h_ditopmass_1p0   ->Integral(),
      h_ditopmass_2p0   ->Integral(),
      h_ditopmass_3p0   ->Integral(),
      h_ditopmass_4p0   ->Integral(),
      h_ditopmass_5p0   ->Integral()
    };
    double ctG[11] = {-5.,-4.,-3.,-2.,-1.,0.,1.,2.,3.,4.,5.};

    TGraph *graph = new TGraph(11,ctG,chisquare);
    graph->SetMarkerColor(kBlack);
    graph->SetMarkerStyle(8);

    // x axis
    graph->GetXaxis()->SetTitle(WC_name);
    graph->GetXaxis()->SetTitleOffset(1.4);
    graph->GetXaxis()->SetRangeUser(-5.5,5.5);
    // y axis
    graph->GetYaxis()->SetTitle("#chi^{2}");
    graph->GetYaxis()->SetTitleOffset(2.0);
    // graph->GetYaxis()->SetRangeUser(0.0,0.44);
    // gPad->SetLogy();


    // draw
    graph->Draw("AP");

    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/chisquare_" + WilsonCoeff + ".pdf");
    c1->Close();
  }
}
