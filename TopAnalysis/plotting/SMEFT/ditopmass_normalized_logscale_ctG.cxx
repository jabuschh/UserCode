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
    TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/SMEFT/";
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
    gPad->SetLeftMargin(0.14);
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

    //rebinning
    h_ditopmass_min0p25->Rebin(5);
    h_ditopmass_min0p2 ->Rebin(5);
    h_ditopmass_min0p15->Rebin(5);
    h_ditopmass_min0p1 ->Rebin(5);
    h_ditopmass_min0p05->Rebin(5);
    h_ditopmass_SM     ->Rebin(5);
    h_ditopmass_0p05   ->Rebin(5);
    h_ditopmass_0p1    ->Rebin(5);
    h_ditopmass_0p15   ->Rebin(5);
    h_ditopmass_0p2    ->Rebin(5);
    h_ditopmass_0p25   ->Rebin(5);
    // line color
    // h_ditopmass_min0p25->SetLineColor(kOrange);
    // h_ditopmass_min0p2 ->SetLineColor(kGreen);
    // h_ditopmass_min0p15->SetLineColor(kCyan);
    // h_ditopmass_min0p1 ->SetLineColor(kBlue+1);
    // h_ditopmass_min0p05->SetLineColor(kBlue);
    // h_ditopmass_SM     ->SetLineColor(kBlack);
    // h_ditopmass_0p05   ->SetLineColor(kRed);
    // h_ditopmass_0p1    ->SetLineColor(kRed+1);
    // h_ditopmass_0p15   ->SetLineColor(kPink-9);
    // h_ditopmass_0p2    ->SetLineColor(kMagenta);
    // h_ditopmass_0p25   ->SetLineColor(kMagenta+2);
    // different color scheme
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
    //line style
    // h_ditopmass_min0p25->SetLineStyle(2);
    // h_ditopmass_min0p2 ->SetLineStyle(2);
    // h_ditopmass_min0p15->SetLineStyle(2);
    // h_ditopmass_min0p1 ->SetLineStyle(2);
    // h_ditopmass_min0p05->SetLineStyle(2);
    // h_ditopmass_SM     ->SetLineStyle(1);
    // h_ditopmass_0p05   ->SetLineStyle(2);
    // h_ditopmass_0p1    ->SetLineStyle(2);
    // h_ditopmass_0p15   ->SetLineStyle(2);
    // h_ditopmass_0p2    ->SetLineStyle(2);
    // h_ditopmass_0p25   ->SetLineStyle(2);


    // x axis
    h_ditopmass_min0p25->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
    h_ditopmass_min0p25->GetXaxis()->SetTitleOffset(1.4);
    // h_ditopmass_min0p25->SetAxisRange(0,4000,"X");
    // y axis
    h_ditopmass_min0p25->GetYaxis()->SetTitle("fraction of #sigma");
    h_ditopmass_min0p25->GetYaxis()->SetTitleOffset(2.0);
    h_ditopmass_min0p25->SetAxisRange(1E-06,5E-01,"Y");
    gPad->SetLogy();

    //legend
    TLegend* legend;
    double xpos   = 0.70;
    double xwidth = 0.20;
    double ypos   = 0.52;
    double ywidth = 0.40;
    legend = new TLegend(xpos,ypos,xpos+xwidth,ypos+ywidth);
    legend->SetBorderSize(1);
    legend->SetTextSize(0.020);
    legend->SetLineColor(0); // 0: white, 1: black
    legend->SetFillColor(0);
    legend->SetFillStyle(1001);
    legend->AddEntry(h_ditopmass_min0p25, WC_name + " = -0.25","l");
    legend->AddEntry(h_ditopmass_min0p2 , WC_name + " = -0.20","l");
    legend->AddEntry(h_ditopmass_min0p15, WC_name + " = -0.15","l");
    legend->AddEntry(h_ditopmass_min0p1 , WC_name + " = -0.10","l");
    legend->AddEntry(h_ditopmass_min0p05, WC_name + " = -0.05","l");
    legend->AddEntry(h_ditopmass_SM  ,    WC_name + " = 0.0 (SM)","l");
    legend->AddEntry(h_ditopmass_0p05,    WC_name + " = 0.05","l");
    legend->AddEntry(h_ditopmass_0p1 ,    WC_name + " = 0.10","l");
    legend->AddEntry(h_ditopmass_0p15,    WC_name + " = 0.15","l");
    legend->AddEntry(h_ditopmass_0p2 ,    WC_name + " = 0.20","l");
    legend->AddEntry(h_ditopmass_0p25,    WC_name + " = 0.25","l");
    //line at 0
    TLine* line;
    line = new TLine(0,0,4000,0);
    line->SetLineStyle(2);
    line->SetLineColor(kGray);

    // draw
    h_ditopmass_min0p25->Draw("hist");
    h_ditopmass_min0p2 ->Draw("hist same");
    h_ditopmass_min0p15->Draw("hist same");
    h_ditopmass_min0p1 ->Draw("hist same");
    h_ditopmass_min0p05->Draw("hist same");
    h_ditopmass_0p05   ->Draw("hist same");
    h_ditopmass_0p1    ->Draw("hist same");
    h_ditopmass_0p15   ->Draw("hist same");
    h_ditopmass_0p2    ->Draw("hist same");
    h_ditopmass_0p25   ->Draw("hist same");
    h_ditopmass_SM     ->Draw("hist same");
    legend             ->Draw("hist same");
    // line              ->Draw();

    // break;
    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/SMEFT/ditopmass_normalized_logscale_" + WilsonCoeff + ".pdf");
    c1->Close();
  }
}
