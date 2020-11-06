{
  // settings
  TString histname = "mass_ditop";
  TString filename = "ditopmass_logscale_normalized";
  TString x_label = "M_{t#bar{t}} [GeV]";
  double  x_labeloffset = 1.5;
  double  x_min = 0.;
  double  x_max = 4000;
  TString y_label = "#sigma [pb]";
  double  y_labeloffset = 1.5;
  double  y_min = 0.00001;
  double  y_max = 1.;



  cout << "reading in histograms from root file..." << endl;
  TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/ALP/";

  TFile *file_CaPhi1_CaGmin5 = TFile::Open(dir + "ALP_CaPhi1_CaGmin5.root", "READ");
  file_CaPhi1_CaGmin5->cd("analysis");
  TH1F *h_CaPhi1_CaGmin5 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaGmin4 = TFile::Open(dir + "ALP_CaPhi1_CaGmin4.root", "READ");
  file_CaPhi1_CaGmin4->cd("analysis");
  TH1F *h_CaPhi1_CaGmin4 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaGmin3 = TFile::Open(dir + "ALP_CaPhi1_CaGmin3.root", "READ");
  file_CaPhi1_CaGmin3->cd("analysis");
  TH1F *h_CaPhi1_CaGmin3 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaGmin2 = TFile::Open(dir + "ALP_CaPhi1_CaGmin2.root", "READ");
  file_CaPhi1_CaGmin2->cd("analysis");
  TH1F *h_CaPhi1_CaGmin2 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaGmin1 = TFile::Open(dir + "ALP_CaPhi1_CaGmin1.root", "READ");
  file_CaPhi1_CaGmin1->cd("analysis");
  TH1F *h_CaPhi1_CaGmin1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG1 = TFile::Open(dir + "ALP_CaPhi1_CaG1.root", "READ");
  file_CaPhi1_CaG1->cd("analysis");
  TH1F *h_CaPhi1_CaG1 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG2 = TFile::Open(dir + "ALP_CaPhi1_CaG2.root", "READ");
  file_CaPhi1_CaG2->cd("analysis");
  TH1F *h_CaPhi1_CaG2 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG3 = TFile::Open(dir + "ALP_CaPhi1_CaG3.root", "READ");
  file_CaPhi1_CaG3->cd("analysis");
  TH1F *h_CaPhi1_CaG3 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG4 = TFile::Open(dir + "ALP_CaPhi1_CaG4.root", "READ");
  file_CaPhi1_CaG4->cd("analysis");
  TH1F *h_CaPhi1_CaG4 = (TH1F*) gDirectory->Get(histname);
  TFile *file_CaPhi1_CaG5 = TFile::Open(dir + "ALP_CaPhi1_CaG5.root", "READ");
  file_CaPhi1_CaG5->cd("analysis");
  TH1F *h_CaPhi1_CaG5 = (TH1F*) gDirectory->Get(histname);

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
  h_CaPhi1_CaGmin5->Rebin(5);
  h_CaPhi1_CaGmin4->Rebin(5);
  h_CaPhi1_CaGmin3->Rebin(5);
  h_CaPhi1_CaGmin2->Rebin(5);
  h_CaPhi1_CaGmin1->Rebin(5);
  h_CaPhi1_CaG1   ->Rebin(5);
  h_CaPhi1_CaG2   ->Rebin(5);
  h_CaPhi1_CaG3   ->Rebin(5);
  h_CaPhi1_CaG4   ->Rebin(5);
  h_CaPhi1_CaG5   ->Rebin(5);
  h_CaPhimin5_CaG1->Rebin(5);
  h_CaPhimin4_CaG1->Rebin(5);
  h_CaPhimin3_CaG1->Rebin(5);
  h_CaPhimin2_CaG1->Rebin(5);
  h_CaPhimin1_CaG1->Rebin(5);
  h_CaPhi2_CaG1   ->Rebin(5);
  h_CaPhi3_CaG1   ->Rebin(5);
  h_CaPhi4_CaG1   ->Rebin(5);
  h_CaPhi5_CaG1   ->Rebin(5);
  h_SM            ->Rebin(5);
  // normalizing
  h_CaPhi1_CaGmin5->Scale(1./(h_CaPhi1_CaGmin5->Integral()));
  h_CaPhi1_CaGmin4->Scale(1./(h_CaPhi1_CaGmin4->Integral()));
  h_CaPhi1_CaGmin3->Scale(1./(h_CaPhi1_CaGmin3->Integral()));
  h_CaPhi1_CaGmin2->Scale(1./(h_CaPhi1_CaGmin2->Integral()));
  h_CaPhi1_CaGmin1->Scale(1./(h_CaPhi1_CaGmin1->Integral()));
  h_CaPhi1_CaG1   ->Scale(1./(h_CaPhi1_CaG1   ->Integral()));
  h_CaPhi1_CaG2   ->Scale(1./(h_CaPhi1_CaG2   ->Integral()));
  h_CaPhi1_CaG3   ->Scale(1./(h_CaPhi1_CaG3   ->Integral()));
  h_CaPhi1_CaG4   ->Scale(1./(h_CaPhi1_CaG4   ->Integral()));
  h_CaPhi1_CaG5   ->Scale(1./(h_CaPhi1_CaG5   ->Integral()));
  h_CaPhimin5_CaG1->Scale(1./(h_CaPhimin5_CaG1->Integral()));
  h_CaPhimin4_CaG1->Scale(1./(h_CaPhimin4_CaG1->Integral()));
  h_CaPhimin3_CaG1->Scale(1./(h_CaPhimin3_CaG1->Integral()));
  h_CaPhimin2_CaG1->Scale(1./(h_CaPhimin2_CaG1->Integral()));
  h_CaPhimin1_CaG1->Scale(1./(h_CaPhimin1_CaG1->Integral()));
  h_CaPhi2_CaG1   ->Scale(1./(h_CaPhi2_CaG1   ->Integral()));
  h_CaPhi3_CaG1   ->Scale(1./(h_CaPhi3_CaG1   ->Integral()));
  h_CaPhi4_CaG1   ->Scale(1./(h_CaPhi4_CaG1   ->Integral()));
  h_CaPhi5_CaG1   ->Scale(1./(h_CaPhi5_CaG1   ->Integral()));
  h_SM            ->Scale(1./(h_SM            ->Integral()));
  // color scheme
  h_CaPhi1_CaGmin5->SetLineColorAlpha(kBlue,1.0);
  h_CaPhi1_CaGmin4->SetLineColorAlpha(kBlue,0.8);
  h_CaPhi1_CaGmin3->SetLineColorAlpha(kBlue,0.6);
  h_CaPhi1_CaGmin2->SetLineColorAlpha(kBlue,0.4);
  h_CaPhi1_CaGmin1->SetLineColorAlpha(kBlue,0.2);
  h_CaPhi1_CaG1   ->SetLineColorAlpha(kRed ,0.2);
  h_CaPhi1_CaG2   ->SetLineColorAlpha(kRed ,0.4);
  h_CaPhi1_CaG3   ->SetLineColorAlpha(kRed ,0.6);
  h_CaPhi1_CaG4   ->SetLineColorAlpha(kRed ,0.8);
  h_CaPhi1_CaG5   ->SetLineColorAlpha(kRed ,1.0);
  h_CaPhimin5_CaG1->SetLineColorAlpha(kBlue,1.0);
  h_CaPhimin4_CaG1->SetLineColorAlpha(kBlue,0.8);
  h_CaPhimin3_CaG1->SetLineColorAlpha(kBlue,0.6);
  h_CaPhimin2_CaG1->SetLineColorAlpha(kBlue,0.4);
  h_CaPhimin1_CaG1->SetLineColorAlpha(kBlue,0.2);
  h_CaPhi2_CaG1   ->SetLineColorAlpha(kRed ,0.4);
  h_CaPhi3_CaG1   ->SetLineColorAlpha(kRed ,0.6);
  h_CaPhi4_CaG1   ->SetLineColorAlpha(kRed ,0.8);
  h_CaPhi5_CaG1   ->SetLineColorAlpha(kRed ,1.0);
  h_SM            ->SetLineColorAlpha(kBlack,1.0);
  //line width
  h_CaPhi1_CaGmin5->SetLineWidth(2);
  h_CaPhi1_CaGmin4->SetLineWidth(2);
  h_CaPhi1_CaGmin3->SetLineWidth(2);
  h_CaPhi1_CaGmin2->SetLineWidth(2);
  h_CaPhi1_CaGmin1->SetLineWidth(2);
  h_CaPhi1_CaG1   ->SetLineWidth(2);
  h_CaPhi1_CaG2   ->SetLineWidth(2);
  h_CaPhi1_CaG3   ->SetLineWidth(2);
  h_CaPhi1_CaG4   ->SetLineWidth(2);
  h_CaPhi1_CaG5   ->SetLineWidth(2);
  h_CaPhimin5_CaG1->SetLineWidth(2);
  h_CaPhimin4_CaG1->SetLineWidth(2);
  h_CaPhimin3_CaG1->SetLineWidth(2);
  h_CaPhimin2_CaG1->SetLineWidth(2);
  h_CaPhimin1_CaG1->SetLineWidth(2);
  h_CaPhi2_CaG1   ->SetLineWidth(2);
  h_CaPhi3_CaG1   ->SetLineWidth(2);
  h_CaPhi4_CaG1   ->SetLineWidth(2);
  h_CaPhi5_CaG1   ->SetLineWidth(2);
  h_SM            ->SetLineWidth(2);


  cout << "plotting..." << endl;
  for(int i=0; i<2; i++){
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
    if(i==0){hist = h_CaPhi1_CaGmin5;}
    else    {hist = h_CaPhimin5_CaG1;}
    // x axis
    hist->GetXaxis()->SetTitle(x_label);
    hist->GetXaxis()->SetTitleOffset(x_labeloffset);
    hist->GetXaxis()->SetLimits(x_min,x_max);
    // y axis
    hist->GetYaxis()->SetTitle(y_label);
    hist->GetYaxis()->SetTitleOffset(y_labeloffset);
    hist->SetAxisRange(y_min,y_max,"Y");

    //legend
    TLegend* legend;
    double xpos   = 0.70;
    double xwidth = 0.20;
    double ypos   = 0.60;
    double ywidth = 0.30;
    legend = new TLegend(xpos,ypos,xpos+xwidth,ypos+ywidth);
    legend->SetBorderSize(1);
    legend->SetTextSize(0.020);
    legend->SetLineColor(0); // 0: white, 1: black
    legend->SetFillColor(0);
    legend->SetFillStyle(1001);
    if(i==0){ //CaPhi=1
      legend->AddEntry(h_SM,            "SM (C_{a#Phi}=C_{aG}=0)","l");
      legend->AddEntry(h_CaPhi1_CaGmin5,"C_{a#Phi}=+1, C_{aG}=-5","l");
      // legend->AddEntry(h_CaPhi1_CaGmin4,"C_{a#Phi}=+1, C_{aG}=-4","l");
      // legend->AddEntry(h_CaPhi1_CaGmin3,"C_{a#Phi}=+1, C_{aG}=-3","l");
      // legend->AddEntry(h_CaPhi1_CaGmin2,"C_{a#Phi}=+1, C_{aG}=-2","l");
      // legend->AddEntry(h_CaPhi1_CaGmin1,"C_{a#Phi}=+1, C_{aG}=-1","l");
      // legend->AddEntry(h_CaPhi1_CaG1,   "C_{a#Phi}=+1, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhi1_CaG2,   "C_{a#Phi}=+1, C_{aG}=+2","l");
      // legend->AddEntry(h_CaPhi1_CaG3,   "C_{a#Phi}=+1, C_{aG}=+3","l");
      // legend->AddEntry(h_CaPhi1_CaG4,   "C_{a#Phi}=+1, C_{aG}=+4","l");
      legend->AddEntry(h_CaPhi1_CaG5,   "C_{a#Phi}=+1, C_{aG}=+5","l");
      // draw
      h_CaPhi1_CaGmin5->Draw("hist");
      // h_CaPhi1_CaGmin4->Draw("hist same");
      // h_CaPhi1_CaGmin3->Draw("hist same");
      // h_CaPhi1_CaGmin2->Draw("hist same");
      // h_CaPhi1_CaGmin1->Draw("hist same");
      // h_CaPhi1_CaG1   ->Draw("hist same");
      // h_CaPhi1_CaG2   ->Draw("hist same");
      // h_CaPhi1_CaG3   ->Draw("hist same");
      // h_CaPhi1_CaG4   ->Draw("hist same");
      h_CaPhi1_CaG5   ->Draw("hist same");
      h_SM            ->Draw("hist same");
      legend->Draw("same");
      // save
      c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/ALP/" + filename + "_CaG.pdf");
      c1->Close();
    }
    else{ //CaG=1
      legend->AddEntry(h_SM,            "SM (C_{a#Phi}=C_{aG}=0)","l");
      legend->AddEntry(h_CaPhimin5_CaG1,"C_{a#Phi}=-5, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhimin4_CaG1,"C_{a#Phi}=-4, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhimin3_CaG1,"C_{a#Phi}=-3, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhimin2_CaG1,"C_{a#Phi}=-2, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhimin1_CaG1,"C_{a#Phi}=-1, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhi1_CaG1,   "C_{a#Phi}=+1, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhi2_CaG1,   "C_{a#Phi}=+2, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhi3_CaG1,   "C_{a#Phi}=+3, C_{aG}=+1","l");
      // legend->AddEntry(h_CaPhi4_CaG1,   "C_{a#Phi}=+4, C_{aG}=+1","l");
      legend->AddEntry(h_CaPhi5_CaG1,   "C_{a#Phi}=+5, C_{aG}=+1","l");
      // draw
      h_CaPhimin5_CaG1->Draw("hist");
      // h_CaPhimin4_CaG1->Draw("hist same");
      // h_CaPhimin3_CaG1->Draw("hist same");
      // h_CaPhimin2_CaG1->Draw("hist same");
      // h_CaPhimin1_CaG1->Draw("hist same");
      // h_CaPhi1_CaG1   ->Draw("hist same");
      // h_CaPhi2_CaG1   ->Draw("hist same");
      // h_CaPhi3_CaG1   ->Draw("hist same");
      // h_CaPhi4_CaG1   ->Draw("hist same");
      h_CaPhi5_CaG1   ->Draw("hist same");
      h_SM            ->Draw("hist same");
      legend->Draw("same");
      // save
      c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/ALP/" + filename + "_CaPhi.pdf");
      c1->Close();
    }
  }
}
