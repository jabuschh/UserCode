{
  // settings
  TString histname = "mass_ditop";
  TString filename = "ditopmass";
  TString x_label = "M_{t#bar{t}} [GeV]";
  double  x_labeloffset = 1.5;
  double  x_min = 0.;
  double  x_max = 2000;
  TString y_label = "#sigma [pb]";
  double  y_labeloffset = 1.5;
  double  y_min = 0.;
  double  y_max = 40.;
  // legend
  double xpos   = 0.70;
  double xwidth = 0.20;
  double ypos   = 0.80;
  double ywidth = 0.10;



  cout << "reading in histograms from root file..." << endl;
  TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/ALP/";

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
  TFile *file_CaPhi1_CaG1 = TFile::Open(dir + "ALP_CaPhi1_CaG1.root","READ");
  file_CaPhi1_CaG1->cd("analysis");
  TH1F *h_CaPhi1_CaG1 = (TH1F*) gDirectory->Get(histname);
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
  // h_CaPhimin5_CaG1->Rebin(5);
  // h_CaPhimin4_CaG1->Rebin(5);
  // h_CaPhimin3_CaG1->Rebin(5);
  // h_CaPhimin2_CaG1->Rebin(5);
  // h_CaPhimin1_CaG1->Rebin(5);
  // h_CaPhi1_CaG1   ->Rebin(5);
  // h_CaPhi2_CaG1   ->Rebin(5);
  // h_CaPhi3_CaG1   ->Rebin(5);
  // h_CaPhi4_CaG1   ->Rebin(5);
  // h_CaPhi5_CaG1   ->Rebin(5);
  // h_SM            ->Rebin(5);
  // color scheme
  // h_CaPhimin5_CaG1->SetLineColorAlpha(kBlue,1.0);
  // h_CaPhimin4_CaG1->SetLineColorAlpha(kBlue,0.8);
  // h_CaPhimin3_CaG1->SetLineColorAlpha(kBlue,0.6);
  // h_CaPhimin2_CaG1->SetLineColorAlpha(kBlue,0.4);
  h_CaPhimin1_CaG1->SetLineColorAlpha(kBlue,1.0);
  h_CaPhi1_CaG1   ->SetLineColorAlpha(kRed ,1.0);
  // h_CaPhi2_CaG1   ->SetLineColorAlpha(kRed ,0.4);
  // h_CaPhi3_CaG1   ->SetLineColorAlpha(kRed ,0.6);
  // h_CaPhi4_CaG1   ->SetLineColorAlpha(kRed ,0.8);
  // h_CaPhi5_CaG1   ->SetLineColorAlpha(kRed ,1.0);
  h_SM            ->SetLineColorAlpha(kBlack,1.0);
  //line width
  // h_CaPhimin5_CaG1->SetLineWidth(2);
  // h_CaPhimin4_CaG1->SetLineWidth(2);
  // h_CaPhimin3_CaG1->SetLineWidth(2);
  // h_CaPhimin2_CaG1->SetLineWidth(2);
  h_CaPhimin1_CaG1->SetLineWidth(2);
  h_CaPhi1_CaG1   ->SetLineWidth(2);
  // h_CaPhi2_CaG1   ->SetLineWidth(2);
  // h_CaPhi3_CaG1   ->SetLineWidth(2);
  // h_CaPhi4_CaG1   ->SetLineWidth(2);
  // h_CaPhi5_CaG1   ->SetLineWidth(2);
  h_SM            ->SetLineWidth(2);


  cout << "plotting..." << endl;
  TCanvas *c1 = new TCanvas("c1","c1",0,0,800,800);
  c1->SetTitle("TCanvas");
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(kFALSE);
  gPad->SetTicks();
  gPad->SetTopMargin(0.05);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.05);
  gPad->SetBottomMargin(0.14);

  TH1F *hist;
  hist = h_CaPhimin1_CaG1;
  // x axis
  hist->GetXaxis()->SetTitle(x_label);
  hist->GetXaxis()->SetTitleOffset(x_labeloffset);
  hist->SetAxisRange(x_min,x_max,"X");
  // y axis
  hist->GetYaxis()->SetTitle(y_label);
  hist->GetYaxis()->SetTitleOffset(y_labeloffset);
  hist->SetAxisRange(y_min,y_max,"Y");

  //legend
  TLegend* legend;
  legend = new TLegend(xpos,ypos,xpos+xwidth,ypos+ywidth);
  legend->SetBorderSize(1);
  legend->SetTextSize(0.020);
  legend->SetLineColor(0); // 0: white, 1: black
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->AddEntry(h_SM,            "SM (C_{a#Phi}=C_{aG}=0)","l");
  legend->AddEntry(h_CaPhimin1_CaG1,"C_{a#Phi}=-1, C_{aG}=+1","l");
  legend->AddEntry(h_CaPhi1_CaG1,   "C_{a#Phi}=+1, C_{aG}=+1","l");
  // legend->AddEntry(h_CaPhimin5_CaG1,"C_{a#Phi}=-5, C_{aG}=+1","l");
  // legend->AddEntry(h_CaPhimin4_CaG1,"C_{a#Phi}=-4, C_{aG}=+1","l");
  // legend->AddEntry(h_CaPhimin3_CaG1,"C_{a#Phi}=-3, C_{aG}=+1","l");
  // legend->AddEntry(h_CaPhimin2_CaG1,"C_{a#Phi}=-2, C_{aG}=+1","l");
  // legend->AddEntry(h_CaPhi2_CaG1,   "C_{a#Phi}=+2, C_{aG}=+1","l");
  // legend->AddEntry(h_CaPhi3_CaG1,   "C_{a#Phi}=+3, C_{aG}=+1","l");
  // legend->AddEntry(h_CaPhi4_CaG1,   "C_{a#Phi}=+4, C_{aG}=+1","l");
  // legend->AddEntry(h_CaPhi5_CaG1,   "C_{a#Phi}=+5, C_{aG}=+1","l");
  // draw
  h_CaPhimin1_CaG1->Draw("hist");
  h_CaPhi1_CaG1   ->Draw("hist same");
  // h_CaPhimin5_CaG1->Draw("hist same");
  // h_CaPhimin4_CaG1->Draw("hist same");
  // h_CaPhimin3_CaG1->Draw("hist same");
  // h_CaPhimin2_CaG1->Draw("hist same");
  // h_CaPhi2_CaG1   ->Draw("hist same");
  // h_CaPhi3_CaG1   ->Draw("hist same");
  // h_CaPhi4_CaG1   ->Draw("hist same");
  // h_CaPhi5_CaG1   ->Draw("hist same");
  h_SM            ->Draw("hist same");
  legend->Draw("same");
  // save
  c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/ALP/" + filename + "_CaPhi.pdf");
  c1->Close();
}
