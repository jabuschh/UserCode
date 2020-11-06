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
    TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/SMEFT_interferenceOnly/";
    TFile *rootfile = TFile::Open(dir + "SMEFT_" + WilsonCoeff + ".root", "READ");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p25"); TH1F* h_EFTweight_min5p0 = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p2");  TH1F* h_EFTweight_min4p0 = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p15"); TH1F* h_EFTweight_min3p0 = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p1");  TH1F* h_EFTweight_min2p0 = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min0p05"); TH1F* h_EFTweight_min1p0 = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_SM");                          TH1F* h_EFTweight_0p0    = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p05");    TH1F* h_EFTweight_1p0    = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p1");     TH1F* h_EFTweight_2p0    = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p15");    TH1F* h_EFTweight_3p0    = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p2");     TH1F* h_EFTweight_4p0    = (TH1F*) gDirectory->Get("EFTweight_pure");
    rootfile->cd("rwgt_" + WilsonCoeff + "_0p25");    TH1F* h_EFTweight_5p0    = (TH1F*) gDirectory->Get("EFTweight_pure");


    double WCs[11]       = {-0.25,-0.20,-0.15,-0.10,-0.05,0.0,0.05,0.10,0.15,0.20,0.25};
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
    graph->GetXaxis()->SetLimits(-0.2999,0.2999);
    //y axis
    graph->GetYaxis()->SetTitle("mean of EFT weights");
    graph->GetYaxis()->SetTitleOffset(1.7);
    graph->GetYaxis()->SetRangeUser(-2,2);

    graph->Draw("AP");
    graph->Fit("pol1");

    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/SMEFT_interferenceOnly/EFTweights_mean_" + WilsonCoeff + ".pdf");
    c1->Close();
  }
}
