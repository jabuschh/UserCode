{
  // specify the Wilson coefficient
  vector<TString> v_WilsonCoeff = {"CaG","CaPhi"};
  vector<TString> v_WC_name     = {"C_{aG}","C_{a#Phi}"};

  for(int n=0; n<v_WilsonCoeff.size(); n++){

    TString WilsonCoeff = v_WilsonCoeff.at(n);
    TString WC_name     = v_WC_name.at(n);

    cout << "Wilson coefficient: " << WilsonCoeff << endl;
    cout << "reading in histograms from root file..." << endl;

    TString dir = "/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/output/ALP/";

    TFile *rootfile_5 = TFile::Open(dir + "ALP_" + WilsonCoeff + "_5.root", "READ");
    rootfile_5->cd("analysis");
    TH1F *h_5 = (TH1F*) gDirectory->Get("mass_ditop");

    TFile *rootfile_4 = TFile::Open(dir + "ALP_" + WilsonCoeff + "_4.root", "READ");
    rootfile_4->cd("analysis");
    TH1F *h_4 = (TH1F*) gDirectory->Get("mass_ditop");

    TFile *rootfile_3 = TFile::Open(dir + "ALP_" + WilsonCoeff + "_3.root", "READ");
    rootfile_3->cd("analysis");
    TH1F *h_3 = (TH1F*) gDirectory->Get("mass_ditop");

    TFile *rootfile_2 = TFile::Open(dir + "ALP_" + WilsonCoeff + "_2.root", "READ");
    rootfile_2->cd("analysis");
    TH1F *h_2 = (TH1F*) gDirectory->Get("mass_ditop");

    TFile *rootfile_1 = TFile::Open(dir + "ALP_" + WilsonCoeff + "_1.root", "READ");
    rootfile_1->cd("analysis");
    TH1F *h_1 = (TH1F*) gDirectory->Get("mass_ditop");





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

    // rebin
    // h_5->Rebin(5);
    // h_4->Rebin(5);
    // h_3->Rebin(5);
    // h_2->Rebin(5);
    // h_1->Rebin(5);

    // color scheme
    h_5->SetLineColorAlpha(kBlack,0.2);
    h_4->SetLineColorAlpha(kBlack,0.4);
    h_3->SetLineColorAlpha(kBlack,0.6);
    h_2->SetLineColorAlpha(kBlack,0.8);
    h_1->SetLineColorAlpha(kBlack,1.0);

    //line width
    h_5->SetLineWidth(2);
    h_4->SetLineWidth(2);
    h_3->SetLineWidth(2);
    h_2->SetLineWidth(2);
    h_1->SetLineWidth(2);

    // x axis
    h_5->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
    h_5->GetXaxis()->SetTitleOffset(1.5);
    h_5->SetAxisRange(0,4000,"X");
    // y axis
    h_5->GetYaxis()->SetTitle("#sigma [pb]");
    h_5->GetYaxis()->SetTitleOffset(1.5);
    // h_5->SetAxisRange(0,15,"Y");

    //legend
    TLegend* legend;
    double xpos   = 0.70;
    double xwidth = 0.20;
    double ypos   = 0.52;
    double ywidth = 0.20;
    legend = new TLegend(xpos,ypos,xpos+xwidth,ypos+ywidth);
    legend->SetBorderSize(1);
    legend->SetTextSize(0.020);
    legend->SetLineColor(0); // 0: white, 1: black
    legend->SetFillColor(0);
    legend->SetFillStyle(1001);
    legend->AddEntry(h_1, WC_name + " = 1","l");
    legend->AddEntry(h_2, WC_name + " = 2","l");
    legend->AddEntry(h_3, WC_name + " = 3","l");
    legend->AddEntry(h_4, WC_name + " = 4","l");
    legend->AddEntry(h_5, WC_name + " = 5","l");

    // draw
    h_5->Draw("hist");
    h_4->Draw("hist same");
    h_3->Draw("hist same");
    h_2->Draw("hist same");
    h_1->Draw("hist same");
    legend->Draw("same");

    // break;
    // save
    c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/EFT_LO/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/ALP/ditopmass_" + WilsonCoeff + ".pdf");
    c1->Close();
  }







}
