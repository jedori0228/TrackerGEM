#include "../include/canvas_margin.h"

std::string DoubleToString(std::string prefix, double dd);

void draw(){
  
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2(true);
  
  TFile* file_MuonGun = new TFile("OUTPUTTEMPLATE_MuonGun.root");
  TFile* file_MinBias = new TFile("OUTPUTTEMPLATE_MinBias.root");
  
  /* Eff by gen-reco deltaR matching */
  
  TH1F* GenMuon_Eta = (TH1F*)file_MuonGun->Get("GenMuon_Eta");
  TH1F* GenMuon_Pt = (TH1F*)file_MuonGun->Get("GenMuon_Pt");
  TH1F* MatchedGEMMuon_Eta = (TH1F*)file_MuonGun->Get("MatchedGEMMuon_Eta");
  TH1F* MatchedGEMMuon_Pt = (TH1F*)file_MuonGun->Get("MatchedGEMMuon_Pt");
  
  TEfficiency* Eff_Eta = new TEfficiency(*MatchedGEMMuon_Eta, *GenMuon_Eta);
  TEfficiency* Eff_Pt = new TEfficiency(*MatchedGEMMuon_Pt, *GenMuon_Pt);
  TGraph* gr_Eff_Eta = Eff_Eta->CreateGraph();
  TGraph* gr_Eff_Pt = Eff_Pt->CreateGraph();
  
  TCanvas* c_GenMuon_Eta = new TCanvas("c_GenMuon_Eta", "", 800, 600);
  canvas_margin(c_GenMuon_Eta);
  c_GenMuon_Eta->cd();
  GenMuon_Eta->Draw("");
  GenMuon_Eta->SetTitle("GenMuon |#eta|");
  GenMuon_Eta->GetXaxis()->SetTitle("|#eta|");
  c_GenMuon_Eta->SaveAs("GenMuon_Eta.png");
  c_GenMuon_Eta->Close();
  
  TCanvas* c_GenMuon_Pt = new TCanvas("c_GenMuon_Pt", "", 800, 600);
  canvas_margin(c_GenMuon_Pt);
  c_GenMuon_Pt->cd();
  GenMuon_Pt->Draw("");
  GenMuon_Pt->SetTitle("GenMuon p_{T}");
  GenMuon_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  c_GenMuon_Pt->SaveAs("GenMuon_Pt.png");
  c_GenMuon_Pt->Close();
  
  TCanvas* c_Eff_Eta = new TCanvas("c_Eff_Eta", "", 800, 600);
  canvas_margin(c_Eff_Eta);
  c_Eff_Eta->cd();
  gr_Eff_Eta->Draw("ap");
  gr_Eff_Eta->GetYaxis()->SetRangeUser(0, 1.2);
  gr_Eff_Eta->GetXaxis()->SetTitle("|#eta|");
  c_Eff_Eta->SaveAs("Eff_Eta.png");
  c_Eff_Eta->Close();
  
  TCanvas* c_Eff_Pt = new TCanvas("c_Eff_Pt", "", 800, 600);
  canvas_margin(c_Eff_Pt);
  c_Eff_Pt->cd();
  gr_Eff_Pt->Draw("ap");
  gr_Eff_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  gPad->SetLogx();
  gr_Eff_Pt->GetYaxis()->SetRangeUser(0, 1.2);
  c_Eff_Pt->SaveAs("Eff_Pt.png");
  gPad->SetLogx(kFALSE);
  c_Eff_Pt->Close();
  
  /* Eff by AssoByHits */
  
  TH1F* TPMuon_Eta = (TH1F*)file_MuonGun->Get("TPMuon_Eta");
  TH1F* TPMuon_Pt = (TH1F*)file_MuonGun->Get("TPMuon_Pt");
  TH1F* HitsMatchedGEMMuon_Eta = (TH1F*)file_MuonGun->Get("HitsMatchedGEMMuon_Eta");
  TH1F* HitsMatchedGEMMuon_Pt = (TH1F*)file_MuonGun->Get("HitsMatchedGEMMuon_Pt");
  
  TEfficiency* HitsEff_Eta = new TEfficiency(*HitsMatchedGEMMuon_Eta, *TPMuon_Eta);
  TEfficiency* HitsEff_Pt = new TEfficiency(*HitsMatchedGEMMuon_Pt, *TPMuon_Pt);
  TGraph* gr_HitsEff_Eta = HitsEff_Eta->CreateGraph();
  TGraph* gr_HitsEff_Pt = HitsEff_Pt->CreateGraph();
  
  TCanvas* c_TPMuon_Eta = new TCanvas("c_TPMuon_Eta", "", 800, 600);
  canvas_margin(c_TPMuon_Eta);
  c_TPMuon_Eta->cd();
  TPMuon_Eta->Draw("");
  TPMuon_Eta->SetTitle("TPMuon |#eta|");
  TPMuon_Eta->GetXaxis()->SetTitle("|#eta|");
  c_TPMuon_Eta->SaveAs("TPMuon_Eta.png");
  c_TPMuon_Eta->Close();
  
  TCanvas* c_TPMuon_Pt = new TCanvas("c_TPMuon_Pt", "", 800, 600);
  canvas_margin(c_TPMuon_Pt);
  c_TPMuon_Pt->cd();
  TPMuon_Pt->Draw("");
  TPMuon_Pt->SetTitle("TPMuon p_{T}");
  TPMuon_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  c_TPMuon_Pt->SaveAs("TPMuon_Pt.png");
  c_TPMuon_Pt->Close();
  
  TCanvas* c_HitsEff_Eta = new TCanvas("c_HitsEff_Eta", "", 800, 600);
  canvas_margin(c_HitsEff_Eta);
  c_HitsEff_Eta->cd();
  gr_HitsEff_Eta->Draw("ap");
  gr_HitsEff_Eta->GetYaxis()->SetRangeUser(0, 1.2);
  gr_HitsEff_Eta->GetXaxis()->SetTitle("|#eta|");
  c_HitsEff_Eta->SaveAs("HitsEff_Eta.png");
  c_HitsEff_Eta->Close();
  
  TCanvas* c_HitsEff_Pt = new TCanvas("c_HitsEff_Pt", "", 800, 600);
  canvas_margin(c_HitsEff_Pt);
  c_HitsEff_Pt->cd();
  gr_HitsEff_Pt->Draw("ap");
  gr_HitsEff_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  gPad->SetLogx();
  gr_HitsEff_Pt->GetYaxis()->SetRangeUser(0, 1.2);
  c_HitsEff_Pt->SaveAs("HitsEff_Pt.png");
  gPad->SetLogx(kFALSE);
  c_HitsEff_Pt->Close();
  
  /* Fake */
  
  TH1F* Nevents_h = (TH1F*)file_MinBias->Get("Nevents_h");
  int Nevents = Nevents_h->GetBinContent(2);
  
  TH1F* HitsUnmatchedGEMMuon_Eta = (TH1F*)file_MinBias->Get("HitsUnmatchedGEMMuon_Eta");
  TH1F* HitsUnmatchedGEMMuon_Pt = (TH1F*)file_MinBias->Get("HitsUnmatchedGEMMuon_Pt");
  
  TCanvas* c_HitsUnmatchedGEMMuon_Eta = new TCanvas("HitsUnmatchedGEMMuon_Eta", "", 800, 600);
  canvas_margin(c_HitsUnmatchedGEMMuon_Eta);
  c_HitsUnmatchedGEMMuon_Eta->cd();
  HitsUnmatchedGEMMuon_Eta->Draw("");
  HitsUnmatchedGEMMuon_Eta->SetTitle(TString::Itoa(Nevents/1000., 10)+"k MinBias Events");
  HitsUnmatchedGEMMuon_Eta->SetXTitle("|#eta|");
  gPad->SetLogy();
  c_HitsUnmatchedGEMMuon_Eta->SaveAs("HitsUnmatchedGEMMuon_Eta.png");
  HitsUnmatchedGEMMuon_Eta->Scale(1./Nevents);
  HitsUnmatchedGEMMuon_Eta->Draw("");
  c_HitsUnmatchedGEMMuon_Eta->SaveAs("HitsUnmatchedGEMMuon_Eta_per_event.png");
  gPad->SetLogy(kFALSE);
  c_HitsUnmatchedGEMMuon_Eta->Close();
  
  TCanvas* c_HitsUnmatchedGEMMuon_Pt = new TCanvas("HitsUnmatchedGEMMuon_Pt", "", 800, 600);
  canvas_margin(c_HitsUnmatchedGEMMuon_Pt);
  c_HitsUnmatchedGEMMuon_Pt->cd();
  HitsUnmatchedGEMMuon_Pt->Draw("");
  HitsUnmatchedGEMMuon_Pt->SetTitle(TString::Itoa(Nevents/1000., 10)+"k MinBias Events");
  HitsUnmatchedGEMMuon_Pt->SetXTitle("p_{T} [GeV]");
  gPad->SetLogx();
  gPad->SetLogy();
  c_HitsUnmatchedGEMMuon_Pt->SaveAs("HitsUnmatchedGEMMuon_Pt.png");
  HitsUnmatchedGEMMuon_Pt->Scale(1./Nevents);
  HitsUnmatchedGEMMuon_Pt->Draw("");
  c_HitsUnmatchedGEMMuon_Pt->SaveAs("HitsUnmatchedGEMMuon_Pt_per_event.png");
  gPad->SetLogx(kFALSE);
  gPad->SetLogy(kFALSE);
  c_HitsUnmatchedGEMMuon_Pt->Close();
  
  
  /* matching eff/rejection study */

  TH1F* maxPull_values = (TH1F*)file_MuonGun->Get("maxPull_values");
  TH1F* maxX_GE11_values = (TH1F*)file_MuonGun->Get("maxX_GE11_values");
  TH1F* maxY_GE11_values = (TH1F*)file_MuonGun->Get("maxY_GE11_values");
  TH1F* maxX_GE21_values = (TH1F*)file_MuonGun->Get("maxX_GE21_values");
  TH1F* maxY_GE21_values = (TH1F*)file_MuonGun->Get("maxY_GE21_values");
  TH1F* minDotDir_values = (TH1F*)file_MuonGun->Get("minDotDir_values");
  
  vector<double> maxPull, maxX_GE11, maxY_GE11, maxX_GE21, maxY_GE21, minDotDir;
  for(int i=1; i<=30; i++){
    if(maxPull_values->GetBinContent(i) != 0) maxPull.push_back( maxPull_values->GetBinContent(i) );
    if(maxX_GE11_values->GetBinContent(i) != 0) maxX_GE11.push_back( maxX_GE11_values->GetBinContent(i) );
    if(maxY_GE11_values->GetBinContent(i) != 0) maxY_GE11.push_back( maxY_GE11_values->GetBinContent(i) );
    if(maxX_GE21_values->GetBinContent(i) != 0) maxX_GE21.push_back( maxX_GE21_values->GetBinContent(i) );
    if(maxY_GE21_values->GetBinContent(i) != 0) maxY_GE21.push_back( maxY_GE21_values->GetBinContent(i) );
    if(minDotDir_values->GetBinContent(i) != 0) minDotDir.push_back( minDotDir_values->GetBinContent(i) );
  }
  
  // Pull plots //
  const int n_maxPull = maxPull.size();
  double eff_maxXPull_GE11[n_maxPull], mis_maxXPull_GE11[n_maxPull];
  double eff_maxYPull_GE11[n_maxPull], mis_maxYPull_GE11[n_maxPull];
  double eff_maxXPull_GE21[n_maxPull], mis_maxXPull_GE21[n_maxPull];
  double eff_maxYPull_GE21[n_maxPull], mis_maxYPull_GE21[n_maxPull];
  for(int aaa=0; aaa<n_maxPull; aaa++){
    TH1F* h_maxXPull_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxXPull_GE11", maxPull.at(aaa)).data());
    TH1F* h_maxXPull_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxXPull_GE11", maxPull.at(aaa)).data());
    eff_maxXPull_GE11[aaa] = h_maxXPull_GE11_MuonGun->GetMean();
    mis_maxXPull_GE11[aaa] = h_maxXPull_GE11_MinBias->GetMean();
    TH1F* h_maxYPull_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxYPull_GE11", maxPull.at(aaa)).data());
    TH1F* h_maxYPull_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxYPull_GE11", maxPull.at(aaa)).data());
    eff_maxYPull_GE11[aaa] = h_maxYPull_GE11_MuonGun->GetMean();
    mis_maxYPull_GE11[aaa] = h_maxYPull_GE11_MinBias->GetMean();
    TH1F* h_maxXPull_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxXPull_GE21", maxPull.at(aaa)).data());
    TH1F* h_maxXPull_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxXPull_GE21", maxPull.at(aaa)).data());
    eff_maxXPull_GE21[aaa] = h_maxXPull_GE21_MuonGun->GetMean();
    mis_maxXPull_GE21[aaa] = h_maxXPull_GE21_MinBias->GetMean();
    TH1F* h_maxYPull_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxYPull_GE21", maxPull.at(aaa)).data());
    TH1F* h_maxYPull_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxYPull_GE21", maxPull.at(aaa)).data());
    eff_maxYPull_GE21[aaa] = h_maxYPull_GE21_MuonGun->GetMean();
    mis_maxYPull_GE21[aaa] = h_maxYPull_GE21_MinBias->GetMean();
  }

  TGraph* gr_maxXPull_GE11 = new TGraph(n_maxPull, eff_maxXPull_GE11, mis_maxXPull_GE11);
  TGraph* gr_maxYPull_GE11 = new TGraph(n_maxPull, eff_maxYPull_GE11, mis_maxYPull_GE11);
  TGraph* gr_maxXPull_GE21 = new TGraph(n_maxPull, eff_maxXPull_GE21, mis_maxXPull_GE21);
  TGraph* gr_maxYPull_GE21 = new TGraph(n_maxPull, eff_maxYPull_GE21, mis_maxYPull_GE21);
  
  TCanvas* mis_vs_eff_Pull = new TCanvas("mis_vs_eff_Pull", "", 800, 600);
  gPad->SetLogy();
  canvas_margin(mis_vs_eff_Pull);
  mis_vs_eff_Pull->cd();
  // att settings
  gr_maxXPull_GE11->SetLineColor(kRed);
  gr_maxYPull_GE11->SetLineColor(kBlue);
  gr_maxXPull_GE21->SetLineColor(kRed);
  gr_maxYPull_GE21->SetLineColor(kBlue);
  gr_maxXPull_GE11->SetLineWidth(2);
  gr_maxYPull_GE11->SetLineWidth(2);
  gr_maxXPull_GE21->SetLineWidth(2);
  gr_maxYPull_GE21->SetLineWidth(2);
  gr_maxXPull_GE21->SetLineStyle(2);
  gr_maxYPull_GE21->SetLineStyle(2);
  // drawing
  gr_maxXPull_GE11->Draw("al");
  gr_maxXPull_GE11->SetTitle("mis_vs_eff_Pull");
  gr_maxXPull_GE11->GetXaxis()->SetRangeUser(0, 1.0);
  gr_maxXPull_GE11->GetYaxis()->SetRangeUser(0.0001, 1.0);
  gr_maxXPull_GE11->GetXaxis()->SetTitle("Signal Efficiency");
  gr_maxXPull_GE11->GetYaxis()->SetTitle("Misidentification probability");
  gr_maxYPull_GE11->Draw("lsame");
  gr_maxXPull_GE21->Draw("lsame");
  gr_maxYPull_GE21->Draw("lsame");
  // legend
  TLegend lg_maxXPull(0.7, 0.15, 0.95, 0.40);
  lg_maxXPull.SetFillStyle(0);
  lg_maxXPull.SetBorderSize(0);
  lg_maxXPull.AddEntry(gr_maxXPull_GE11, "X/GE11", "l");
  lg_maxXPull.AddEntry(gr_maxYPull_GE11, "Y/GE11", "l");
  lg_maxXPull.AddEntry(gr_maxXPull_GE21, "X/GE21", "l");
  lg_maxXPull.AddEntry(gr_maxYPull_GE21, "Y/GE21", "l");
  lg_maxXPull.Draw();
  // save
  mis_vs_eff_Pull->SaveAs("mis_vs_eff_Pull.png");
  mis_vs_eff_Pull->Close();
  
  // maxX //
  const int n_maxX_GE11 = maxX_GE11.size();
  const int n_maxX_GE21 = maxX_GE21.size();
  double eff_maxX_GE11[n_maxX_GE11], mis_maxX_GE11[n_maxX_GE11];
  double eff_maxX_GE21[n_maxX_GE21], mis_maxX_GE21[n_maxX_GE21];

  for(int aaa=0; aaa<n_maxX_GE11; aaa++){
    TH1F* h_maxX_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxX_GE11", maxX_GE11.at(aaa)).data());
    TH1F* h_maxX_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxX_GE11", maxX_GE11.at(aaa)).data());
    eff_maxX_GE11[aaa] = h_maxX_GE11_MuonGun->GetMean();
    mis_maxX_GE11[aaa] = h_maxX_GE11_MinBias->GetMean();
  }
  for(int aaa=0; aaa<n_maxX_GE21; aaa++){
    TH1F* h_maxX_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxX_GE21", maxX_GE21.at(aaa)).data());
    TH1F* h_maxX_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxX_GE21", maxX_GE21.at(aaa)).data());
    eff_maxX_GE21[aaa] = h_maxX_GE21_MuonGun->GetMean();
    mis_maxX_GE21[aaa] = h_maxX_GE21_MinBias->GetMean();
  }

  TGraph* gr_maxX_GE11 = new TGraph(n_maxX_GE11, eff_maxX_GE11, mis_maxX_GE11);
  TGraph* gr_maxX_GE21 = new TGraph(n_maxX_GE21, eff_maxX_GE21, mis_maxX_GE21);

  TCanvas* mis_vs_eff_maxX = new TCanvas("mis_vs_eff_maxX", "", 800, 600);
  gPad->SetLogy();
  canvas_margin(mis_vs_eff_maxX);
  mis_vs_eff_maxX->cd();
  // att settings
  gr_maxX_GE11->SetLineColor(kRed);
  gr_maxX_GE21->SetLineColor(kRed);
  gr_maxX_GE11->SetLineWidth(2);
  gr_maxX_GE21->SetLineWidth(2);
  gr_maxX_GE21->SetLineStyle(2);
  // drawing
  gr_maxX_GE11->Draw("al");
  gr_maxX_GE11->SetTitle("mis_vs_eff_maxX");
  gr_maxX_GE11->GetXaxis()->SetRangeUser(0, 1.0);
  gr_maxX_GE11->GetYaxis()->SetRangeUser(0.0001, 1.0);
  gr_maxX_GE11->GetXaxis()->SetTitle("Signal Efficiency");
  gr_maxX_GE11->GetYaxis()->SetTitle("Misidentification probability");
  gr_maxX_GE21->Draw("lsame");
  // legend
  TLegend lg_maxX(0.7, 0.15, 0.95, 0.40);
  lg_maxX.SetFillStyle(0);
  lg_maxX.SetBorderSize(0);
  lg_maxX.AddEntry(gr_maxX_GE11, "X/GE11", "l");
  lg_maxX.AddEntry(gr_maxX_GE21, "X/GE21", "l");
  lg_maxX.Draw();
  // save
  mis_vs_eff_maxX->SaveAs("mis_vs_eff_maxX.png");
  mis_vs_eff_maxX->Close();
  
  // maxY //
  const int n_maxY_GE11 = maxY_GE11.size();
  const int n_maxY_GE21 = maxY_GE21.size();
  double eff_maxY_GE11[n_maxY_GE11], mis_maxY_GE11[n_maxY_GE11];
  double eff_maxY_GE21[n_maxY_GE21], mis_maxY_GE21[n_maxY_GE21];
  
  for(int aaa=0; aaa<n_maxY_GE11; aaa++){
    TH1F* h_maxY_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxY_GE11", maxY_GE11.at(aaa)).data());
    TH1F* h_maxY_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxY_GE11", maxY_GE11.at(aaa)).data());
    eff_maxY_GE11[aaa] = h_maxY_GE11_MuonGun->GetMean();
    mis_maxY_GE11[aaa] = h_maxY_GE11_MinBias->GetMean();
  }
  for(int aaa=0; aaa<n_maxY_GE21; aaa++){
    TH1F* h_maxY_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxY_GE21", maxY_GE21.at(aaa)).data());
    TH1F* h_maxY_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxY_GE21", maxY_GE21.at(aaa)).data());
    eff_maxY_GE21[aaa] = h_maxY_GE21_MuonGun->GetMean();
    mis_maxY_GE21[aaa] = h_maxY_GE21_MinBias->GetMean();
  }
  
  TGraph* gr_maxY_GE11 = new TGraph(n_maxY_GE11, eff_maxY_GE11, mis_maxY_GE11);
  TGraph* gr_maxY_GE21 = new TGraph(n_maxY_GE21, eff_maxY_GE21, mis_maxY_GE21);
  
  TCanvas* mis_vs_eff_maxY = new TCanvas("mis_vs_eff_maxY", "", 800, 600);
  gPad->SetLogy();
  canvas_margin(mis_vs_eff_maxY);
  mis_vs_eff_maxY->cd();
  // att settings
  gr_maxY_GE11->SetLineColor(kBlue);
  gr_maxY_GE21->SetLineColor(kBlue);
  gr_maxY_GE11->SetLineWidth(2);
  gr_maxY_GE21->SetLineWidth(2);
  gr_maxY_GE21->SetLineStyle(2);
  // drawing
  gr_maxY_GE11->Draw("al");
  gr_maxY_GE11->SetTitle("mis_vs_eff_maxY");
  gr_maxY_GE11->GetXaxis()->SetRangeUser(0, 1.0);
  gr_maxY_GE11->GetYaxis()->SetRangeUser(0.0001, 1.0);
  gr_maxY_GE11->GetXaxis()->SetTitle("Signal Efficiency");
  gr_maxY_GE11->GetYaxis()->SetTitle("Misidentification probability");
  gr_maxY_GE21->Draw("lsame");
  // legend
  TLegend lg_maxY(0.7, 0.15, 0.95, 0.40);
  lg_maxY.SetFillStyle(0);
  lg_maxY.SetBorderSize(0);
  lg_maxY.AddEntry(gr_maxY_GE11, "Y/GE11", "l");
  lg_maxY.AddEntry(gr_maxY_GE21, "Y/GE21", "l");
  lg_maxY.Draw();
  // save
  mis_vs_eff_maxY->SaveAs("mis_vs_eff_maxY.png");
  mis_vs_eff_maxY->Close();

  // DotDir //
  const int n_minDotDir = minDotDir.size();
  double eff_minDotDir_GE11[n_minDotDir], mis_minDotDir_GE11[n_minDotDir];
  double eff_minDotDir_GE21[n_minDotDir], mis_minDotDir_GE21[n_minDotDir];
  
  for(int aaa=0; aaa<n_minDotDir; aaa++){
    TH1F* h_minDotDir_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("minDotDir_GE11", minDotDir.at(aaa)).data());
    TH1F* h_minDotDir_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("minDotDir_GE11", minDotDir.at(aaa)).data());
    eff_minDotDir_GE11[aaa] = h_minDotDir_GE11_MuonGun->GetMean();
    mis_minDotDir_GE11[aaa] = h_minDotDir_GE11_MinBias->GetMean();
    TH1F* h_minDotDir_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("minDotDir_GE21", minDotDir.at(aaa)).data());
    TH1F* h_minDotDir_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("minDotDir_GE21", minDotDir.at(aaa)).data());
    eff_minDotDir_GE21[aaa] = h_minDotDir_GE21_MuonGun->GetMean();
    mis_minDotDir_GE21[aaa] = h_minDotDir_GE21_MinBias->GetMean();
  }
  
  TGraph* gr_minDotDir_GE11 = new TGraph(n_minDotDir, eff_minDotDir_GE11, mis_minDotDir_GE11);
  TGraph* gr_minDotDir_GE21 = new TGraph(n_minDotDir, eff_minDotDir_GE21, mis_minDotDir_GE21);
  
  TCanvas* mis_vs_eff_minDotDir = new TCanvas("mis_vs_eff_minDotDir", "", 800, 600);
  gPad->SetLogy();
  canvas_margin(mis_vs_eff_minDotDir);
  mis_vs_eff_minDotDir->cd();
  // att settings
  gr_minDotDir_GE11->SetLineColor(kBlack);
  gr_minDotDir_GE21->SetLineColor(kBlack);
  gr_minDotDir_GE21->SetLineStyle(2);
  // drawing
  gr_minDotDir_GE11->Draw("al");
  gr_minDotDir_GE11->SetTitle("mis_vs_eff_minDotDir");
  gr_minDotDir_GE11->GetXaxis()->SetRangeUser(0, 1.0);
  gr_minDotDir_GE11->GetYaxis()->SetRangeUser(0.0001, 1.0);
  gr_minDotDir_GE11->GetXaxis()->SetTitle("Signal Efficiency");
  gr_minDotDir_GE11->GetYaxis()->SetTitle("Misidentification probability");
  gr_minDotDir_GE21->Draw("lsame");
  // legend
  TLegend lg_minDotDir(0.7, 0.15, 0.95, 0.40);
  lg_minDotDir.SetFillStyle(0);
  lg_minDotDir.SetBorderSize(0);
  lg_minDotDir.AddEntry(gr_minDotDir_GE11, "DotDir/GE11", "l");
  lg_minDotDir.AddEntry(gr_minDotDir_GE21, "DotDir/GE21", "l");
  lg_minDotDir.Draw();
  // save
  mis_vs_eff_minDotDir->SaveAs("mis_vs_eff_minDotDir.png");
  mis_vs_eff_minDotDir->Close();

  

  
}


std::string DoubleToString(std::string prefix, double dd){
  std::ostringstream os;
  os << dd;
  return prefix+"_"+os.str();
}









