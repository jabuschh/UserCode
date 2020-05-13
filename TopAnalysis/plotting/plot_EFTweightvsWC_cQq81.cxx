{
  /*
  // ██████  ███████  █████  ██████      ██ ███    ██
  // ██   ██ ██      ██   ██ ██   ██     ██ ████   ██
  // ██████  █████   ███████ ██   ██     ██ ██ ██  ██
  // ██   ██ ██      ██   ██ ██   ██     ██ ██  ██ ██
  // ██   ██ ███████ ██   ██ ██████      ██ ██   ████
  */
  TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/";

  TFile *rootfile = TFile::Open(dir + "rwgt_cQq81.root", "READ");
  rootfile->cd("analysis");
  TH1F* h_EFTweight_cQq81_min5p0 = (TH1F*) gDirectory->Get("EFTweight_cQq81_min5p0");
  TH1F* h_EFTweight_cQq81_min4p0 = (TH1F*) gDirectory->Get("EFTweight_cQq81_min4p0");
  TH1F* h_EFTweight_cQq81_min3p0 = (TH1F*) gDirectory->Get("EFTweight_cQq81_min3p0");
  TH1F* h_EFTweight_cQq81_min2p0 = (TH1F*) gDirectory->Get("EFTweight_cQq81_min2p0");
  TH1F* h_EFTweight_cQq81_min1p0 = (TH1F*) gDirectory->Get("EFTweight_cQq81_min1p0");
  TH1F* h_EFTweight_cQq81_0p0    = (TH1F*) gDirectory->Get("EFTweight_cQq81_0p0");
  TH1F* h_EFTweight_cQq81_1p0    = (TH1F*) gDirectory->Get("EFTweight_cQq81_1p0");
  TH1F* h_EFTweight_cQq81_2p0    = (TH1F*) gDirectory->Get("EFTweight_cQq81_2p0");
  TH1F* h_EFTweight_cQq81_3p0    = (TH1F*) gDirectory->Get("EFTweight_cQq81_3p0");
  TH1F* h_EFTweight_cQq81_4p0    = (TH1F*) gDirectory->Get("EFTweight_cQq81_4p0");
  TH1F* h_EFTweight_cQq81_5p0    = (TH1F*) gDirectory->Get("EFTweight_cQq81_5p0");


  double WCs[11]       = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
  double WCsErrors[11] = {0,0,0,0,0,0,0,0,0,0,0};
  double v_means[11] = {
    h_EFTweight_cQq81_min5p0->GetMean(1),
    h_EFTweight_cQq81_min4p0->GetMean(1),
    h_EFTweight_cQq81_min3p0->GetMean(1),
    h_EFTweight_cQq81_min2p0->GetMean(1),
    h_EFTweight_cQq81_min1p0->GetMean(1),
    h_EFTweight_cQq81_0p0->GetMean(1),
    h_EFTweight_cQq81_1p0->GetMean(1),
    h_EFTweight_cQq81_2p0->GetMean(1),
    h_EFTweight_cQq81_3p0->GetMean(1),
    h_EFTweight_cQq81_4p0->GetMean(1),
    h_EFTweight_cQq81_5p0->GetMean(1)
  };
  double v_meanErrors[11] = {
    h_EFTweight_cQq81_min5p0->GetMeanError(1),
    h_EFTweight_cQq81_min4p0->GetMeanError(1),
    h_EFTweight_cQq81_min3p0->GetMeanError(1),
    h_EFTweight_cQq81_min2p0->GetMeanError(1),
    h_EFTweight_cQq81_min1p0->GetMeanError(1),
    h_EFTweight_cQq81_0p0->GetMeanError(1),
    h_EFTweight_cQq81_1p0->GetMeanError(1),
    h_EFTweight_cQq81_2p0->GetMeanError(1),
    h_EFTweight_cQq81_3p0->GetMeanError(1),
    h_EFTweight_cQq81_4p0->GetMeanError(1),
    h_EFTweight_cQq81_5p0->GetMeanError(1)
  };


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
  graph = new TGraphAsymmErrors(11,WCs,v_means,WCsErrors,WCsErrors,v_meanErrors,v_meanErrors);
  graph->SetMarkerStyle(8);
  graph->SetMarkerColor(kBlack);
  //x axis
  graph->GetXaxis()->SetTitle("C_{Qq}^{1,8}");
  graph->GetXaxis()->SetTitleOffset(1.4);
  graph->GetXaxis()->SetLimits(-5.999,5.999);
  //y axis
  graph->GetYaxis()->SetTitle("EFT weight");
  graph->GetYaxis()->SetTitleOffset(1.4);
  graph->GetYaxis()->SetRangeUser(-0.3,0.3);

  graph->Draw("AP");
  graph->Fit("pol1");

  c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/EFTweight_vs_cQq81.pdf");





  //linear fit
  // TF1 *fit = graph->GetFunction("pol1");
  // gStyle->SetOptFit();
  // fit->SetLineColor(kRed);
  // fit->SetLineWidth(1);

  // legend
  // TLegend* legend;
  // legend = new TLegend(0.67,0.62,0.92,0.92); // mid right
  // legend->SetBorderSize(1);
  // // legend->SetTextSize(0.032);
  // legend->SetLineColor(1); // 0: white, 1: black
  // legend->SetFillColor(0);
  // legend->SetFillStyle(1001);
  // legend->AddEntry(graph,"EFT weights");
  // legend->AddEntry(fit)





}
