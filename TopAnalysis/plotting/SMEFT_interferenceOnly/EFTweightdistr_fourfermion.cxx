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
    TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/SMEFT_interferenceOnly/";
    TFile *rootfile = TFile::Open(dir + "SMEFT_" + WilsonCoeff + ".root", "READ");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min5p0"); TH1F* h_EFTweight_min5p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min4p0"); TH1F* h_EFTweight_min4p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min3p0"); TH1F* h_EFTweight_min3p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min2p0"); TH1F* h_EFTweight_min2p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_min1p0"); TH1F* h_EFTweight_min1p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_SM");                         TH1F* h_EFTweight_SM  = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_1p0");    TH1F* h_EFTweight_1p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_2p0");    TH1F* h_EFTweight_2p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_3p0");    TH1F* h_EFTweight_3p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_4p0");    TH1F* h_EFTweight_4p0 = (TH1F*) gDirectory->Get("EFTweight");
    rootfile->cd("rwgt_" + WilsonCoeff + "_5p0");    TH1F* h_EFTweight_5p0 = (TH1F*) gDirectory->Get("EFTweight");


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

    // // rescaling
    // h_EFTweight_min5p0->Scale(1./(h_EFTweight_min5p0->Integral()));
    // h_EFTweight_min4p0->Scale(1./(h_EFTweight_min4p0->Integral()));
    // h_EFTweight_min3p0->Scale(1./(h_EFTweight_min3p0->Integral()));
    // h_EFTweight_min2p0->Scale(1./(h_EFTweight_min2p0->Integral()));
    // h_EFTweight_min1p0->Scale(1./(h_EFTweight_min1p0->Integral()));
    // h_EFTweight_SM    ->Scale(1./(h_EFTweight_SM->Integral()));
    // h_EFTweight_1p0   ->Scale(1./(h_EFTweight_1p0->Integral()));
    // h_EFTweight_2p0   ->Scale(1./(h_EFTweight_2p0->Integral()));
    // h_EFTweight_3p0   ->Scale(1./(h_EFTweight_3p0->Integral()));
    // h_EFTweight_4p0   ->Scale(1./(h_EFTweight_4p0->Integral()));
    // h_EFTweight_5p0   ->Scale(1./(h_EFTweight_5p0->Integral()));

    //rebinning
    // h_EFTweight_min5p0->Rebin(4);
    // h_EFTweight_min4p0->Rebin(4);
    // h_EFTweight_min3p0->Rebin(4);
    // h_EFTweight_min2p0->Rebin(4);
    // h_EFTweight_min1p0->Rebin(4);
    // h_EFTweight_SM    ->Rebin(4);
    // h_EFTweight_1p0   ->Rebin(4);
    // h_EFTweight_2p0   ->Rebin(4);
    // h_EFTweight_3p0   ->Rebin(4);
    // h_EFTweight_4p0   ->Rebin(4);
    // h_EFTweight_5p0   ->Rebin(4);
    // line color
    // h_EFTweight_min5p0->SetLineColor(kOrange);
    // h_EFTweight_min4p0->SetLineColor(kGreen);
    // h_EFTweight_min3p0->SetLineColor(kCyan);
    // h_EFTweight_min2p0->SetLineColor(kBlue+1);
    // h_EFTweight_min1p0->SetLineColor(kBlue);
    // h_EFTweight_SM   ->SetLineColor(kBlack);
    // h_EFTweight_1p0   ->SetLineColor(kRed);
    // h_EFTweight_2p0   ->SetLineColor(kRed+1);
    // h_EFTweight_3p0   ->SetLineColor(kPink-9);
    // h_EFTweight_4p0   ->SetLineColor(kMagenta);
    // h_EFTweight_5p0   ->SetLineColor(kMagenta+2);
    // different color scheme
    h_EFTweight_min5p0->SetLineColorAlpha(kBlue,1.0);
    h_EFTweight_min4p0->SetLineColorAlpha(kBlue,0.8);
    h_EFTweight_min3p0->SetLineColorAlpha(kBlue,0.6);
    h_EFTweight_min2p0->SetLineColorAlpha(kBlue,0.4);
    h_EFTweight_min1p0->SetLineColorAlpha(kBlue,0.2);
    h_EFTweight_SM    ->SetLineColor(kBlack);
    h_EFTweight_1p0   ->SetLineColorAlpha(kRed,0.2);
    h_EFTweight_2p0   ->SetLineColorAlpha(kRed,0.4);
    h_EFTweight_3p0   ->SetLineColorAlpha(kRed,0.6);
    h_EFTweight_4p0   ->SetLineColorAlpha(kRed,0.8);
    h_EFTweight_5p0   ->SetLineColorAlpha(kRed,1.0);
    //rebinning
    h_EFTweight_min5p0->SetLineWidth(2);
    h_EFTweight_min4p0->SetLineWidth(2);
    h_EFTweight_min3p0->SetLineWidth(2);
    h_EFTweight_min2p0->SetLineWidth(2);
    h_EFTweight_min1p0->SetLineWidth(2);
    h_EFTweight_SM    ->SetLineWidth(2);
    h_EFTweight_1p0   ->SetLineWidth(2);
    h_EFTweight_2p0   ->SetLineWidth(2);
    h_EFTweight_3p0   ->SetLineWidth(2);
    h_EFTweight_4p0   ->SetLineWidth(2);
    h_EFTweight_5p0   ->SetLineWidth(2);


    // x axis
    h_EFTweight_min5p0->GetXaxis()->SetTitle("EFT weight");
    h_EFTweight_min5p0->GetXaxis()->SetTitleOffset(1.4);
    h_EFTweight_min5p0->SetAxisRange(-5,5,"X");
    // y axis
    h_EFTweight_min5p0->GetYaxis()->SetTitle("cross section #sigma [pb]");
    h_EFTweight_min5p0->GetYaxis()->SetTitleOffset(1.7);
    h_EFTweight_min5p0->SetAxisRange(-30,30,"Y");

    //legend
    TLegend* legend;
    double xpos   = 0.20;
    double xwidth = 0.20;
    double ypos   = 0.52;
    double ywidth = 0.40;
    legend = new TLegend(xpos,ypos,xpos+xwidth,ypos+ywidth);
    legend->SetBorderSize(1);
    legend->SetTextSize(0.020);
    legend->SetLineColor(0); // 0: white, 1: black
    legend->SetFillColor(0);
    legend->SetFillStyle(1001);
    legend->AddEntry(h_EFTweight_min5p0, WC_name + " = -5.0","l");
    legend->AddEntry(h_EFTweight_min4p0, WC_name + " = -4.0","l");
    legend->AddEntry(h_EFTweight_min3p0, WC_name + " = -3.0","l");
    legend->AddEntry(h_EFTweight_min2p0, WC_name + " = -2.0","l");
    legend->AddEntry(h_EFTweight_min1p0, WC_name + " = -1.0","l");
    legend->AddEntry(h_EFTweight_SM , WC_name + " = 0.0 (SM)","l");
    legend->AddEntry(h_EFTweight_1p0, WC_name + " = 1.0","l");
    legend->AddEntry(h_EFTweight_2p0, WC_name + " = 2.0","l");
    legend->AddEntry(h_EFTweight_3p0, WC_name + " = 3.0","l");
    legend->AddEntry(h_EFTweight_4p0, WC_name + " = 4.0","l");
    legend->AddEntry(h_EFTweight_5p0, WC_name + " = 5.0","l");

    // draw
    h_EFTweight_min5p0->Draw("hist");
    h_EFTweight_min4p0->Draw("hist same");
    h_EFTweight_min3p0->Draw("hist same");
    h_EFTweight_min2p0->Draw("hist same");
    h_EFTweight_min1p0->Draw("hist same");
    h_EFTweight_1p0   ->Draw("hist same");
    h_EFTweight_2p0   ->Draw("hist same");
    h_EFTweight_3p0   ->Draw("hist same");
    h_EFTweight_4p0   ->Draw("hist same");
    h_EFTweight_5p0   ->Draw("hist same");
    h_EFTweight_SM    ->Draw("hist same");
    legend            ->Draw("hist same");


    // // TEST
    // //legend
    // TLegend* legend;
    // double xpos   = 0.20;
    // double xwidth = 0.20;
    // double ypos   = 0.52;
    // double ywidth = 0.40;
    // legend = new TLegend(xpos,ypos,xpos+xwidth,ypos+ywidth);
    // legend->SetBorderSize(1);
    // legend->SetTextSize(0.020);
    // legend->SetLineColor(0); // 0: white, 1: black
    // legend->SetFillColor(0);
    // legend->SetFillStyle(1001);
    // // legend->AddEntry(h_EFTweight_min5p0, WC_name + " = -5.0","l");
    // // legend->AddEntry(h_EFTweight_min4p0, WC_name + " = -4.0","l");
    // // legend->AddEntry(h_EFTweight_min3p0, WC_name + " = -3.0","l");
    // // legend->AddEntry(h_EFTweight_min2p0, WC_name + " = -2.0","l");
    // // legend->AddEntry(h_EFTweight_min1p0, WC_name + " = -1.0","l");
    // // legend->AddEntry(h_EFTweight_SM , WC_name + " = 0.0 (SM)","l");
    // // legend->AddEntry(h_EFTweight_1p0, WC_name + " = 1.0","l");
    // // legend->AddEntry(h_EFTweight_2p0, WC_name + " = 2.0","l");
    // // legend->AddEntry(h_EFTweight_3p0, WC_name + " = 3.0","l");
    // // legend->AddEntry(h_EFTweight_4p0, WC_name + " = 4.0","l");
    // legend->AddEntry(h_EFTweight_5p0, WC_name + " = 5.0","l");
    // // gPad->SetLogy();
    // // x axis
    // h_EFTweight_5p0->GetXaxis()->SetTitle("EFT weight");
    // h_EFTweight_5p0->GetXaxis()->SetTitleOffset(1.4);
    // h_EFTweight_5p0->SetAxisRange(-4,6,"X");
    // // y axis
    // h_EFTweight_5p0->GetYaxis()->SetTitle("fraction of events");
    // h_EFTweight_5p0->GetYaxis()->SetTitleOffset(1.7);
    // h_EFTweight_5p0->SetAxisRange(0,1,"Y");
    // h_EFTweight_5p0->Draw("hist");
    // legend         ->Draw("hist same");
    // // break;


    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/SMEFT_interferenceOnly/EFTweightdistr_" + WilsonCoeff + ".pdf");
    c1->Close();
  }
}
