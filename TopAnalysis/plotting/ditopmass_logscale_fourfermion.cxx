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


    //rebinning
    h_ditopmass_min5p0->Rebin(4);
    h_ditopmass_min4p0->Rebin(4);
    h_ditopmass_min3p0->Rebin(4);
    h_ditopmass_min2p0->Rebin(4);
    h_ditopmass_min1p0->Rebin(4);
    h_ditopmass_SM    ->Rebin(4);
    h_ditopmass_1p0   ->Rebin(4);
    h_ditopmass_2p0   ->Rebin(4);
    h_ditopmass_3p0   ->Rebin(4);
    h_ditopmass_4p0   ->Rebin(4);
    h_ditopmass_5p0   ->Rebin(4);
    // line color
    // h_ditopmass_min5p0->SetLineColor(kOrange);
    // h_ditopmass_min4p0->SetLineColor(kGreen);
    // h_ditopmass_min3p0->SetLineColor(kCyan);
    // h_ditopmass_min2p0->SetLineColor(kBlue+1);
    // h_ditopmass_min1p0->SetLineColor(kBlue);
    // h_ditopmass_SM    ->SetLineColor(kBlack);
    // h_ditopmass_1p0   ->SetLineColor(kRed);
    // h_ditopmass_2p0   ->SetLineColor(kRed+1);
    // h_ditopmass_3p0   ->SetLineColor(kPink-9);
    // h_ditopmass_4p0   ->SetLineColor(kMagenta);
    // h_ditopmass_5p0   ->SetLineColor(kMagenta+2);
    // different color scheme
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
    //line style
    // h_ditopmass_min5p0->SetLineStyle(2);
    // h_ditopmass_min4p0->SetLineStyle(2);
    // h_ditopmass_min3p0->SetLineStyle(2);
    // h_ditopmass_min2p0->SetLineStyle(2);
    // h_ditopmass_min1p0->SetLineStyle(2);
    // h_ditopmass_SM    ->SetLineStyle(1);
    // h_ditopmass_1p0   ->SetLineStyle(2);
    // h_ditopmass_2p0   ->SetLineStyle(2);
    // h_ditopmass_3p0   ->SetLineStyle(2);
    // h_ditopmass_4p0   ->SetLineStyle(2);
    // h_ditopmass_5p0   ->SetLineStyle(2);


    // x axis
    h_ditopmass_min5p0->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
    h_ditopmass_min5p0->GetXaxis()->SetTitleOffset(1.5);
    // h_ditopmass_min5p0->SetAxisRange(0,4000,"X");
    // y axis
    h_ditopmass_min5p0->GetYaxis()->SetTitle("events");
    h_ditopmass_min5p0->GetYaxis()->SetTitleOffset(2.5);
    h_ditopmass_min5p0->SetAxisRange(8.0E-01,9.0E+04,"Y");
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
    legend->AddEntry(h_ditopmass_min5p0, WC_name + " = -5.0","l");
    legend->AddEntry(h_ditopmass_min4p0, WC_name + " = -4.0","l");
    legend->AddEntry(h_ditopmass_min3p0, WC_name + " = -3.0","l");
    legend->AddEntry(h_ditopmass_min2p0, WC_name + " = -2.0","l");
    legend->AddEntry(h_ditopmass_min1p0, WC_name + " = -1.0","l");
    legend->AddEntry(h_ditopmass_SM , WC_name + " = 0.0 (SM)","l");
    legend->AddEntry(h_ditopmass_1p0, WC_name + " = 1.0","l");
    legend->AddEntry(h_ditopmass_2p0, WC_name + " = 2.0","l");
    legend->AddEntry(h_ditopmass_3p0, WC_name + " = 3.0","l");
    legend->AddEntry(h_ditopmass_4p0, WC_name + " = 4.0","l");
    legend->AddEntry(h_ditopmass_5p0, WC_name + " = 5.0","l");

    //line at 0 events
    TLine* line;
    line = new TLine(0,0,4000,0);
    line->SetLineStyle(2);
    line->SetLineColor(kGray);


    // draw
    h_ditopmass_min5p0->Draw("hist");
    h_ditopmass_min4p0->Draw("hist same");
    h_ditopmass_min3p0->Draw("hist same");
    h_ditopmass_min2p0->Draw("hist same");
    h_ditopmass_min1p0->Draw("hist same");
    h_ditopmass_1p0   ->Draw("hist same");
    h_ditopmass_2p0   ->Draw("hist same");
    h_ditopmass_3p0   ->Draw("hist same");
    h_ditopmass_4p0   ->Draw("hist same");
    h_ditopmass_5p0   ->Draw("hist same");
    h_ditopmass_SM    ->Draw("hist same");
    legend            ->Draw("hist same");
    // line              ->Draw();

    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/ditopmass_logscale_" + WilsonCoeff + ".pdf");
    // break;
    c1->Close();

  }
}
