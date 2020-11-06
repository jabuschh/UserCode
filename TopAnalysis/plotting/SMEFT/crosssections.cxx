{
  double xsec_SM[1] = {449.816480531};
  double err_SM[1]  = {12.8557486362};

  double value_SM[1]    = {0.0};
  double err_valueSM[1] = {0.0};

  double value_ff[10]  = {-5,-4,-3,-2,-1,1,2,3,4,5};
  double value_tG[10]  = {-0.25,-0.2,-0.15,-0.1,-0.05,0.05,0.1,0.15,0.2,0.25};
  double err_value[10] = {0,0,0,0,0,0,0,0,0,0};


  double xsecs_cQd8[10] = {435.456864259,438.328787513,441.200710767,444.072634022,446.944557276,452.688403785,455.560327039,458.432250294,461.304173548,464.176096802};
  double err_cQd8[10]   = {24.7095441675,21.751370342,18.959293453,16.4276538209,14.3135012813,12.3275915103,12.8633698935,14.3316911533,16.4597995955,19.007833152};

  double xsecs_cQq81[10] = {418.073447038,424.422053736,430.770660435,437.119267134,443.467873832,456.165087229,462.513693928,468.862300626,475.210907325,481.559514023};
  double err_cQq81[10]   = {30.8518124693,26.7345208756,22.7392488927,18.9507481515,15.5393755826,11.5162242557,12.0621056029,14.2605033163,17.4408579809,21.1298605704};

  double xsecs_cQq83[10] = {440.91449918,442.69489545,444.47529172,446.25568799,448.036084261,451.596876801,453.377273071,455.157669341,456.938065611,458.718461881};
  double err_cQq83[10]   = {30.916885055,26.6950249878,22.614673318,18.7770526487,15.3866130073,11.8447660683,12.7771611449,15.2628054774,18.6355782966,22.4698827232};

  double xsecs_cQu8[10] = {429.525075714,433.583356677,437.64163764,441.699918604,445.758199567,453.874761494,457.933042457,461.991323421,466.049604384,470.107885348};
  double err_cQu8[10]   = {30.5395345648,26.3800134472,22.3661333585,18.6015558303,15.2940253905,11.9268020323,12.8930032348,15.3655305332,18.7047830222,22.4997429566};

  double xsecs_ctG[10] = {418.982346402,425.149173228,431.316000054,437.482826879,443.649653705,455.983307356,462.150134182,468.316961007,474.483787833,480.650614659};
  double err_ctG[10]   = {12.9667914443,12.8622754473,12.7982038793,12.7755068321,12.794678154,12.9582843182,13.1014101243,13.2838559008,13.5040194107,13.760039444};

  double xsecs_ctd8[10] = {441.170324897,442.899556024,444.62878715,446.358018277,448.087249404,451.545711657,453.274942784,455.004173911,456.733405038,458.462636164};
  double err_ctd8[10]   = {18.00764296,16.6252967311,15.3759636354,14.2991162525,13.4421462925,12.5838241079,12.6501649189,13.0494289441,13.7492774589,14.701942225};

  double xsecs_ctq8[10] = {417.998667544,424.362230141,430.725792738,437.089355336,443.452917933,456.180043128,462.543605725,468.907168323,475.27073092,481.634293518};
  double err_ctq8[10]   = {33.6038185334,28.8594477374,24.2433540719,19.8533524074,15.8999541017,11.5978490097,12.7617040502,15.7711975409,19.7318470975,24.1482624943};

  double xsecs_ctu8[10] = {429.768840121,433.778368203,437.787896285,441.797424367,445.806952449,453.826008613,457.835536695,461.845064777,465.854592859,469.864120941};
  double err_ctu8[10]   = {30.017718411,25.9636271823,22.0571780176,18.4018684913,15.2022717236,11.9635292823,12.8826822419,15.2566881185,18.4842432055,22.1677695328};





  TGraphErrors* SMEFT_SM    = new TGraphErrors(1,value_SM,xsec_SM,err_valueSM,err_SM);
  TGraphErrors* SMEFT_cQd8  = new TGraphErrors(10,value_ff,xsecs_cQd8,err_value,err_cQd8);
  TGraphErrors* SMEFT_cQq81 = new TGraphErrors(10,value_ff,xsecs_cQq81,err_value,err_cQq81);
  TGraphErrors* SMEFT_cQq83 = new TGraphErrors(10,value_ff,xsecs_cQq83,err_value,err_cQq83);
  TGraphErrors* SMEFT_cQu8  = new TGraphErrors(10,value_ff,xsecs_cQu8,err_value,err_cQu8);
  TGraphErrors* SMEFT_ctG   = new TGraphErrors(10,value_tG,xsecs_ctG,err_value,err_ctG);
  TGraphErrors* SMEFT_ctd8  = new TGraphErrors(10,value_ff,xsecs_ctd8,err_value,err_ctd8);
  TGraphErrors* SMEFT_ctq8  = new TGraphErrors(10,value_ff,xsecs_ctq8,err_value,err_ctq8);
  TGraphErrors* SMEFT_ctu8  = new TGraphErrors(10,value_ff,xsecs_ctu8,err_value,err_ctu8);

  // line color
  SMEFT_SM   ->SetLineColorAlpha(kBlack,1.0);
  SMEFT_cQd8 ->SetLineColorAlpha(kBlue+1,1.0);
  SMEFT_cQq81->SetLineColorAlpha(kRed+1,1.0);
  SMEFT_cQq83->SetLineColorAlpha(kGreen+1,1.0);
  SMEFT_cQu8 ->SetLineColorAlpha(kOrange+1,1.0);
  SMEFT_ctG  ->SetLineColorAlpha(kMagenta+1,1.0);
  SMEFT_ctd8 ->SetLineColorAlpha(kCyan+1,1.0);
  SMEFT_ctq8 ->SetLineColorAlpha(kYellow+1,1.0);
  SMEFT_ctu8 ->SetLineColorAlpha(kGreen+3,1.0);

  // marker color
  SMEFT_SM   ->SetMarkerColorAlpha(kBlack,1.0);
  SMEFT_cQd8 ->SetMarkerColorAlpha(kBlue+1,1.0);
  SMEFT_cQq81->SetMarkerColorAlpha(kRed+1,1.0);
  SMEFT_cQq83->SetMarkerColorAlpha(kGreen+1,1.0);
  SMEFT_cQu8 ->SetMarkerColorAlpha(kOrange+1,1.0);
  SMEFT_ctG  ->SetMarkerColorAlpha(kMagenta+1,1.0);
  SMEFT_ctd8 ->SetMarkerColorAlpha(kCyan+1,1.0);
  SMEFT_ctq8 ->SetMarkerColorAlpha(kYellow+1,1.0);
  SMEFT_ctu8 ->SetMarkerColorAlpha(kGreen+3,1.0);

  // marker style
  SMEFT_SM   ->SetMarkerStyle(8);
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
  SMEFT_cQq83->GetYaxis()->SetRangeUser(350,550);

  //line at 0 pb
  TLine* line;
  line = new TLine(-6,0,6,0);
  line->SetLineStyle(1);
  line->SetLineColor(kBlack);

  //line at 47.7 pb (SM)
  TLine* lineSM;
  lineSM = new TLine(-6,449.816480531,6,449.816480531);
  lineSM->SetLineStyle(2);
  lineSM->SetLineColor(kBlack);

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
  legend->AddEntry(SMEFT_SM   ,"SM"          ,"ep");


  // draw
  SMEFT_cQq83->Draw("AP");
  line       ->Draw("same");
  lineSM     ->Draw("same");
  SMEFT_SM   ->Draw("P same");
  SMEFT_cQq81->Draw("P same");
  SMEFT_ctq8 ->Draw("P same");
  SMEFT_ctu8 ->Draw("P same");
  SMEFT_ctd8 ->Draw("P same");
  SMEFT_cQu8 ->Draw("P same");
  SMEFT_cQd8 ->Draw("P same");
  SMEFT_ctG  ->Draw("P same");
  legend     ->Draw("same");


  c1->SaveAs("/nfs/dust/cms/user/jabuschh/PhD/ttbar/genstudy/CMSSW_9_4_6/src/UserCode/TopAnalysis/plots/SMEFT/crosssections.pdf");
  c1->Close();
}
