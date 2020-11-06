{
  // settings
  TString histname = "mass_ditop";
  TString filename = "ditopmass_normalized_logscale";
  TString x_label = "M_{t#bar{t}} [GeV]";
  double  x_labeloffset = 1.5;
  double  x_min = 0.;
  double  x_max = 2000.;
  TString y_label = "fraction of #sigma [pb]";
  double  y_labeloffset = 1.5;
  double  y_min = 0.0001;
  double  y_max = 0.7;
  //legend
  double xpos   = 0.55;
  double xwidth = 0.2;
  double ypos   = 0.8;
  double ywidth = 0.1;



  cout << "reading in histograms from root file..." << endl;
  TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/ALP_M1000_signalOnly/";

  TFile *file_CaPhimin5_CaG1 = TFile::Open(dir + "ALP_NPeq2_CaPhimin5_CaG1_M1000.root","READ");
  file_CaPhimin5_CaG1->cd("analysis");
  TH1F *h_CaPhimin5_CaG1 = (TH1F*) gDirectory->Get(histname);

  TFile *file_CaPhi5_CaG1 = TFile::Open(dir + "ALP_NPeq2_CaPhi5_CaG1_M1000.root","READ");
  file_CaPhi5_CaG1->cd("analysis");
  TH1F *h_CaPhi5_CaG1 = (TH1F*) gDirectory->Get(histname);

  // rebin
  // h_CaPhimin5_CaG1->Rebin(5);
  // h_CaPhi5_CaG1   ->Rebin(5);
  //normalizing
  h_CaPhimin5_CaG1->Scale(1./(h_CaPhimin5_CaG1->Integral()));
  h_CaPhi5_CaG1   ->Scale(1./(h_CaPhi5_CaG1   ->Integral()));
  // color scheme
  h_CaPhimin5_CaG1->SetLineColorAlpha(kBlue,1.0);
  h_CaPhi5_CaG1   ->SetLineColorAlpha(kRed ,1.0);
  //line width
  h_CaPhimin5_CaG1->SetLineWidth(2);
  h_CaPhi5_CaG1   ->SetLineWidth(2);


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
  gPad->SetLogy();

  TH1F *hist;
  hist = h_CaPhimin5_CaG1;
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
  legend->SetHeader("m_{a} = 1 TeV, #Gamma_{a} = 100 GeV, f_{a} = 1 TeV");
  legend->AddEntry(h_CaPhimin5_CaG1,"C_{a#Phi}=-5, C_{aG}=+1","l");
  legend->AddEntry(h_CaPhi5_CaG1,   "C_{a#Phi}=+5, C_{aG}=+1","l");
  // draw
  h_CaPhimin5_CaG1->Draw("hist");
  h_CaPhi5_CaG1   ->Draw("hist same");
  legend->Draw("same");
  // save
  c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/ALP_M1000_signalOnly/" + filename + "_NPeq2_CaG1_M1000.pdf");
  c1->Close();
}
