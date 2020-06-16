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

    cout << "reading in histograms from root file..." << endl;
    TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/";
    TFile *rootfile = TFile::Open(dir + "SMEFT_" + WilsonCoeff + ".root", "READ");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min5p0"); TH1F* h_EFTweight_min5p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min4p0"); TH1F* h_EFTweight_min4p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min3p0"); TH1F* h_EFTweight_min3p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min2p0"); TH1F* h_EFTweight_min2p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min1p0"); TH1F* h_EFTweight_min1p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_SM");                         TH1F* h_EFTweight_0p0    = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_1p0");    TH1F* h_EFTweight_1p0    = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_2p0");    TH1F* h_EFTweight_2p0    = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_3p0");    TH1F* h_EFTweight_3p0    = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_4p0");    TH1F* h_EFTweight_4p0    = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_5p0");    TH1F* h_EFTweight_5p0    = (TH1F*) gDirectory->Get("EFTweight");


    double WCs[11]       = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
    double WCsErrors[11] = {0,0,0,0,0,0,0,0,0,0,0};
    double v_means[11] = {
      h_EFTweight_min5p0->GetMean(1),
      h_EFTweight_min4p0->GetMean(1),
      h_EFTweight_min3p0->GetMean(1),
      h_EFTweight_min2p0->GetMean(1),
      h_EFTweight_min1p0->GetMean(1),
      h_EFTweight_0p0   ->GetMean(1),
      h_EFTweight_1p0   ->GetMean(1),
      h_EFTweight_2p0   ->GetMean(1),
      h_EFTweight_3p0   ->GetMean(1),
      h_EFTweight_4p0   ->GetMean(1),
      h_EFTweight_5p0   ->GetMean(1)
    };
    double v_meanStdDev[11] = {
      h_EFTweight_min5p0->GetMeanError(1),
      h_EFTweight_min4p0->GetMeanError(1),
      h_EFTweight_min3p0->GetMeanError(1),
      h_EFTweight_min2p0->GetMeanError(1),
      h_EFTweight_min1p0->GetMeanError(1),
      h_EFTweight_0p0   ->GetMeanError(1),
      h_EFTweight_1p0   ->GetMeanError(1),
      h_EFTweight_2p0   ->GetMeanError(1),
      h_EFTweight_3p0   ->GetMeanError(1),
      h_EFTweight_4p0   ->GetMeanError(1),
      h_EFTweight_5p0   ->GetMeanError(1)
    };

    cout << "plotting..." << endl;
    //plot
    TCanvas *c1 = new TCanvas("c1","c1",0,0,800,800);
    c1->SetTitle("TCanvas");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    gPad->SetTicks();
    gPad->SetTopMargin(0.05);
    gPad->SetLeftMargin(0.165);
    gPad->SetRightMargin(0.05);
    gPad->SetBottomMargin(0.14);

    TGraphAsymmErrors *graph;
    graph = new TGraphAsymmErrors(11,WCs,v_means,WCsErrors,WCsErrors,v_meanStdDev,v_meanStdDev);
    graph->SetMarkerStyle(8);
    graph->SetMarkerColor(kBlack);
    //x axis
    graph->GetXaxis()->SetTitle(WC_name);
    graph->GetXaxis()->SetTitleOffset(1.4);
    graph->GetXaxis()->SetLimits(-5.999,5.999);
    //y axis
    graph->GetYaxis()->SetTitle("mean of EFT weights");
    graph->GetYaxis()->SetTitleOffset(1.7);
    graph->GetYaxis()->SetRangeUser(-4,6);

    graph->Draw("AP");
    graph->Fit("pol1");

    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/EFTweights_mean_" + WilsonCoeff + ".pdf");
    c1->Close();
  }




}
