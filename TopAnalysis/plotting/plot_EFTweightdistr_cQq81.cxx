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
  h_EFTweight_cQq81_min5p0->Scale(1./(h_EFTweight_cQq81_min5p0->Integral()));
  h_EFTweight_cQq81_min4p0->Scale(1./(h_EFTweight_cQq81_min4p0->Integral()));
  h_EFTweight_cQq81_min3p0->Scale(1./(h_EFTweight_cQq81_min3p0->Integral()));
  h_EFTweight_cQq81_min2p0->Scale(1./(h_EFTweight_cQq81_min2p0->Integral()));
  h_EFTweight_cQq81_min1p0->Scale(1./(h_EFTweight_cQq81_min1p0->Integral()));
  h_EFTweight_cQq81_0p0   ->Scale(1./(h_EFTweight_cQq81_0p0->Integral()));
  h_EFTweight_cQq81_1p0   ->Scale(1./(h_EFTweight_cQq81_1p0->Integral()));
  h_EFTweight_cQq81_2p0   ->Scale(1./(h_EFTweight_cQq81_2p0->Integral()));
  h_EFTweight_cQq81_3p0   ->Scale(1./(h_EFTweight_cQq81_3p0->Integral()));
  h_EFTweight_cQq81_4p0   ->Scale(1./(h_EFTweight_cQq81_4p0->Integral()));
  h_EFTweight_cQq81_5p0   ->Scale(1./(h_EFTweight_cQq81_5p0->Integral()));

  //rebinning
  // h_EFTweight_cQq81_min5p0->Rebin(4);
  // h_EFTweight_cQq81_min4p0->Rebin(4);
  // h_EFTweight_cQq81_min3p0->Rebin(4);
  // h_EFTweight_cQq81_min2p0->Rebin(4);
  // h_EFTweight_cQq81_min1p0->Rebin(4);
  // h_EFTweight_cQq81_0p0   ->Rebin(4);
  // h_EFTweight_cQq81_1p0   ->Rebin(4);
  // h_EFTweight_cQq81_2p0   ->Rebin(4);
  // h_EFTweight_cQq81_3p0   ->Rebin(4);
  // h_EFTweight_cQq81_4p0   ->Rebin(4);
  // h_EFTweight_cQq81_5p0   ->Rebin(4);
  // line color
  h_EFTweight_cQq81_min5p0->SetLineColor(kOrange);
  h_EFTweight_cQq81_min4p0->SetLineColor(kGreen);
  h_EFTweight_cQq81_min3p0->SetLineColor(kCyan);
  h_EFTweight_cQq81_min2p0->SetLineColor(kBlue+1);
  h_EFTweight_cQq81_min1p0->SetLineColor(kBlue);
  h_EFTweight_cQq81_0p0   ->SetLineColor(kBlack);
  h_EFTweight_cQq81_1p0   ->SetLineColor(kRed);
  h_EFTweight_cQq81_2p0   ->SetLineColor(kRed+1);
  h_EFTweight_cQq81_3p0   ->SetLineColor(kPink-9);
  h_EFTweight_cQq81_4p0   ->SetLineColor(kMagenta);
  h_EFTweight_cQq81_5p0   ->SetLineColor(kMagenta+2);
  //rebinning
  h_EFTweight_cQq81_min5p0->SetLineWidth(2);
  h_EFTweight_cQq81_min4p0->SetLineWidth(2);
  h_EFTweight_cQq81_min3p0->SetLineWidth(2);
  h_EFTweight_cQq81_min2p0->SetLineWidth(2);
  h_EFTweight_cQq81_min1p0->SetLineWidth(2);
  h_EFTweight_cQq81_0p0   ->SetLineWidth(2);
  h_EFTweight_cQq81_1p0   ->SetLineWidth(2);
  h_EFTweight_cQq81_2p0   ->SetLineWidth(2);
  h_EFTweight_cQq81_3p0   ->SetLineWidth(2);
  h_EFTweight_cQq81_4p0   ->SetLineWidth(2);
  h_EFTweight_cQq81_5p0   ->SetLineWidth(2);


  // x axis
  h_EFTweight_cQq81_min5p0->GetXaxis()->SetTitle("EFT weight");
  h_EFTweight_cQq81_min5p0->SetAxisRange(-20,20,"X");
  // y axis
  h_EFTweight_cQq81_min5p0->GetYaxis()->SetTitle("fraction of events");
  h_EFTweight_cQq81_min5p0->SetAxisRange(0.0001,1,"Y");
  gPad->SetLogy();

  //legend
  TLegend* legend;
  legend = new TLegend(0.67,0.62,0.92,0.92); // mid right
  legend->SetBorderSize(1);
  // legend->SetTextSize(0.032);
  legend->SetLineColor(1); // 0: white, 1: black
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->AddEntry(h_EFTweight_cQq81_min5p0,"cQq81_min5p0","l");
  legend->AddEntry(h_EFTweight_cQq81_min4p0,"cQq81_min4p0","l");
  legend->AddEntry(h_EFTweight_cQq81_min3p0,"cQq81_min3p0","l");
  legend->AddEntry(h_EFTweight_cQq81_min2p0,"cQq81_min2p0","l");
  legend->AddEntry(h_EFTweight_cQq81_min1p0,"cQq81_min1p0","l");
  legend->AddEntry(h_EFTweight_cQq81_0p0,"cQq81_0p0","l");
  legend->AddEntry(h_EFTweight_cQq81_1p0,"cQq81_1p0","l");
  legend->AddEntry(h_EFTweight_cQq81_2p0,"cQq81_2p0","l");
  legend->AddEntry(h_EFTweight_cQq81_3p0,"cQq81_3p0","l");
  legend->AddEntry(h_EFTweight_cQq81_4p0,"cQq81_4p0","l");
  legend->AddEntry(h_EFTweight_cQq81_5p0,"cQq81_5p0","l");

  // draw
  h_EFTweight_cQq81_min5p0->Draw("hist");
  h_EFTweight_cQq81_min4p0->Draw("hist same");
  h_EFTweight_cQq81_min3p0->Draw("hist same");
  h_EFTweight_cQq81_min2p0->Draw("hist same");
  h_EFTweight_cQq81_min1p0->Draw("hist same");
  h_EFTweight_cQq81_1p0   ->Draw("hist same");
  h_EFTweight_cQq81_2p0   ->Draw("hist same");
  h_EFTweight_cQq81_3p0   ->Draw("hist same");
  h_EFTweight_cQq81_4p0   ->Draw("hist same");
  h_EFTweight_cQq81_5p0   ->Draw("hist same");
  h_EFTweight_cQq81_0p0   ->Draw("hist same");
  legend                  ->Draw("hist same");

  c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/EFTweightdistr_cQq81.pdf");








}
