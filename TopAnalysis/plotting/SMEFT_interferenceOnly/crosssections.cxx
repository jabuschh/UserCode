{
  double value_ff[11]  = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
  double value_tG[11]  = {-0.25,-0.2,-0.15,-0.1,-0.05,0,0.05,0.1,0.15,0.2,0.25};
  double err_value[11] = {0,0,0,0,0,0,0,0,0,0,0};


  double xsecs_cQd8[11] = {-12.6274144751,-10.1019315801,-7.57644868508,-5.05096579006,-2.52548289503,0.0,2.52548289503,5.05096579006,7.57644868508,10.1019315801,12.6274144751};
  double err_cQd8[11]   = {7.52303117074,6.01842493659,4.51381870244,3.0092124683,1.50460623415,0.0,1.53116195631,3.06232391263,4.59348586894,6.12464782525,7.65580978156};

  double xsecs_cQq81[11] = {-47.1327280882,-37.7061824706,-28.2796368529,-18.8530912353,-9.42654561764,0.0,9.42654561764,18.8530912353,28.2796368529,37.7061824706,47.1327280882};
  double err_cQq81[11]   = {87.8255230306,70.2604184245,52.6953138183,35.1302092122,17.5651046061,0.0,17.6642257393,35.3284514786,52.9926772179,70.6569029572,88.3211286965};

  double xsecs_cQq83[11] = {4.01752552071,3.21402041657,2.41051531243,1.60701020828,0.803505104142,0.0,-0.803505104142,-1.60701020828,-2.41051531243,-3.21402041657,-4.01752552071};
  double err_cQq83[11]   = {88.4659471655,70.7727577324,53.0795682993,35.3863788662,17.6931894331,0.0,17.6847404912,35.3694809824,53.0542214736,70.7389619647,88.4237024559};

  double xsecs_cQu8[11] = {-18.8057048412,-15.0445638729,-11.2834229047,-7.52228193646,-3.76114096823,0.0,3.76114096823,7.52228193646,11.2834229047,15.0445638729,18.8057048412};
  double err_cQu8[11]   = {8.97986309029,7.18389047223,5.38791785418,3.59194523612,1.79597261806,0.0,1.83552141673,3.67104283347,5.5065642502,7.34208566694,9.17760708367};

  double xsecs_ctG[11] = {-30.546311278,-24.4370490224,-18.3277867668,-12.2185245112,-6.1092622556,0.0,6.1092622556,12.2185245112,18.3277867668,24.4370490224,30.546311278};
  double err_ctG[11]   = {5.86114690685,4.68891752548,3.51668814411,2.34445876274,1.17222938137,0.0,1.23646892598,2.47293785195,3.70940677793,4.94587570391,6.18234462988};

  double xsecs_ctd8[11] = {-11.3409079611,-9.07272636891,-6.80454477668,-4.53636318446,-2.26818159223,0.0,2.26818159223,4.53636318446,6.80454477668,9.07272636891,11.3409079611};
  double err_ctd8[11]   = {7.02101079687,5.6168086375,4.21260647812,2.80840431875,1.40420215937,0.0,1.42805233088,2.85610466176,4.28415699264,5.71220932352,7.1402616544};

  double xsecs_ctq8[11] = {-39.7636474841,-31.8109179873,-23.8581884905,-15.9054589937,-7.95272949683,0.0,7.95272949683,15.9054589937,23.8581884905,31.8109179873,39.7636474841};
  double err_ctq8[11]   = {12.4617091192,9.96936729534,7.47702547151,4.98468364767,2.49234182384,0.0,2.57596562322,5.15193124644,7.72789686967,10.3038624929,12.8798281161};

  double xsecs_ctu8[11] = {-21.330778837,-17.0646230696,-12.7984673022,-8.53231153479,-4.26615576739,0.0,4.26615576739,8.53231153479,12.7984673022,17.0646230696,21.330778837};
  double err_ctu8[11]   = {9.69814248447,7.75851398758,5.81888549068,3.87925699379,1.93962849689,0.0,1.98448758008,3.96897516016,5.95346274024,7.93795032032,9.9224379004};


  TGraphErrors* SMEFT_cQd8  = new TGraphErrors(11,value_ff,xsecs_cQd8,err_value,err_cQd8);
  TGraphErrors* SMEFT_cQq81 = new TGraphErrors(11,value_ff,xsecs_cQq81,err_value,err_cQq81);
  TGraphErrors* SMEFT_cQq83 = new TGraphErrors(11,value_ff,xsecs_cQq83,err_value,err_cQq83);
  TGraphErrors* SMEFT_cQu8  = new TGraphErrors(11,value_ff,xsecs_cQu8,err_value,err_cQu8);
  TGraphErrors* SMEFT_ctG   = new TGraphErrors(11,value_tG,xsecs_ctG,err_value,err_ctG);
  TGraphErrors* SMEFT_ctd8  = new TGraphErrors(11,value_ff,xsecs_ctd8,err_value,err_ctd8);
  TGraphErrors* SMEFT_ctq8  = new TGraphErrors(11,value_ff,xsecs_ctq8,err_value,err_ctq8);
  TGraphErrors* SMEFT_ctu8  = new TGraphErrors(11,value_ff,xsecs_ctu8,err_value,err_ctu8);

  // line color
  SMEFT_cQd8 ->SetLineColorAlpha(kBlue+1,1.0);
  SMEFT_cQq81->SetLineColorAlpha(kRed+1,1.0);
  SMEFT_cQq83->SetLineColorAlpha(kGreen+1,1.0);
  SMEFT_cQu8 ->SetLineColorAlpha(kOrange+1,1.0);
  SMEFT_ctG  ->SetLineColorAlpha(kMagenta+1,1.0);
  SMEFT_ctd8 ->SetLineColorAlpha(kCyan+1,1.0);
  SMEFT_ctq8 ->SetLineColorAlpha(kYellow+1,1.0);
  SMEFT_ctu8 ->SetLineColorAlpha(kBlack,1.0);

  // marker color
  SMEFT_cQd8 ->SetMarkerColorAlpha(kBlue+1,1.0);
  SMEFT_cQq81->SetMarkerColorAlpha(kRed+1,1.0);
  SMEFT_cQq83->SetMarkerColorAlpha(kGreen+1,1.0);
  SMEFT_cQu8 ->SetMarkerColorAlpha(kOrange+1,1.0);
  SMEFT_ctG  ->SetMarkerColorAlpha(kMagenta+1,1.0);
  SMEFT_ctd8 ->SetMarkerColorAlpha(kCyan+1,1.0);
  SMEFT_ctq8 ->SetMarkerColorAlpha(kYellow+1,1.0);
  SMEFT_ctu8 ->SetMarkerColorAlpha(kBlack,1.0);

  // marker style
  SMEFT_cQd8 ->SetMarkerStyle(8);
  SMEFT_cQq81->SetMarkerStyle(8);
  SMEFT_cQq83->SetMarkerStyle(8);
  SMEFT_cQu8 ->SetMarkerStyle(8);
  SMEFT_ctG  ->SetMarkerStyle(8);
  SMEFT_ctd8 ->SetMarkerStyle(8);
  SMEFT_ctq8 ->SetMarkerStyle(8);
  SMEFT_ctu8 ->SetMarkerStyle(8);




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

  // x axis
  SMEFT_cQq83->GetXaxis()->SetTitle("value");
  SMEFT_cQq83->GetXaxis()->SetTitleOffset(1.5);
  SMEFT_cQq83->GetXaxis()->SetLimits(-5.99,5.99);
  // y axis
  SMEFT_cQq83->GetYaxis()->SetTitle("#sigma [pb]");
  SMEFT_cQq83->GetYaxis()->SetTitleOffset(2.0);
  SMEFT_cQq83->GetYaxis()->SetRangeUser(-150,150);

  //line at 0 pb
  TLine* line;
  line = new TLine(-6,0,6,0);
  line->SetLineStyle(1);
  line->SetLineColor(kBlack);


  //legend
  TLegend* legend;
  double xpos   = 0.20;
  double xwidth = 0.30;
  double ypos   = 0.82;
  double ywidth = 0.10;
  legend = new TLegend(xpos,ypos,xpos+xwidth,ypos+ywidth);
  legend->SetBorderSize(1);
  legend->SetTextSize(0.020);
  legend->SetLineColor(0); // 0: white, 1: black
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetNColumns(4);
  legend->AddEntry(SMEFT_cQq83,"C_{Qq}^{3,8}","ep");
  legend->AddEntry(SMEFT_cQq81,"C_{Qq}^{1,8}","ep");
  legend->AddEntry(SMEFT_ctq8 ,"C_{tq}^{8}"  ,"ep");
  legend->AddEntry(SMEFT_ctu8 ,"C_{tu}^{8}"  ,"ep");
  legend->AddEntry(SMEFT_ctd8 ,"C_{td}^{8}"  ,"ep");
  legend->AddEntry(SMEFT_cQu8 ,"C_{Qu}^{8}"  ,"ep");
  legend->AddEntry(SMEFT_cQd8 ,"C_{Qd}^{8}"  ,"ep");
  legend->AddEntry(SMEFT_ctG  ,"C_{tG}"      ,"ep");


  // draw
  SMEFT_cQq83->Draw("AP");
  line       ->Draw("same");
  SMEFT_cQq81->Draw("P same");
  SMEFT_ctq8 ->Draw("P same");
  SMEFT_ctu8 ->Draw("P same");
  SMEFT_ctd8 ->Draw("P same");
  SMEFT_cQu8 ->Draw("P same");
  SMEFT_cQd8 ->Draw("P same");
  SMEFT_ctG  ->Draw("P same");
  legend     ->Draw("same");



  c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/SMEFT_interferenceOnly/crosssections.pdf");
  c1->Close();


}
