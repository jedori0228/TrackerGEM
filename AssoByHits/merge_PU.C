#include "../include/canvas_margin.h"

void merge_PU(){
  
  TFile* file_0 = new TFile("Hist_PU_0.root");
  TFile* file_10 = new TFile("Hist_PU_10.root");
  TFile* file_50 = new TFile("Hist_PU_50.root");
  TFile* file_140 = new TFile("Hist_PU_140.root");

  //==== Eta
  
  TCanvas* c_Eta = new TCanvas("c_Eta", "", 800, 600);
  canvas_margin(c_Eta);
  c_Eta->cd();
  TGraph* Eff_Eta_0 = (TGraph*)file_0->Get("HitsEff_Eta");
  TGraph* Eff_Eta_10 = (TGraph*)file_10->Get("HitsEff_Eta");
  TGraph* Eff_Eta_50 = (TGraph*)file_50->Get("HitsEff_Eta");
  TGraph* Eff_Eta_140 = (TGraph*)file_140->Get("HitsEff_Eta");
  Eff_Eta_0->Draw("ap");
  Eff_Eta_0->SetLineColor(kBlack);
  Eff_Eta_0->GetYaxis()->SetRangeUser(0, 1.2);
  Eff_Eta_0->GetXaxis()->SetTitle("|#eta|");
  Eff_Eta_10->Draw("psame");
  Eff_Eta_10->SetLineColor(kOrange);
  Eff_Eta_50->Draw("psame");
  Eff_Eta_50->SetLineColor(kBlue);
  Eff_Eta_140->Draw("psame");
  Eff_Eta_140->SetLineColor(kRed);
  TLegend* lg_Eta = new TLegend(0.5, 0.15, 0.95, 0.30);
  lg_Eta->SetFillStyle(0);
  lg_Eta->SetBorderSize(0);
  lg_Eta->AddEntry(Eff_Eta_0, "MuonGun (No PU)", "l");
  lg_Eta->AddEntry(Eff_Eta_10, "MuonGun with PU 10", "l");
  lg_Eta->AddEntry(Eff_Eta_50, "MuonGun with PU 50", "l");
  lg_Eta->AddEntry(Eff_Eta_140, "MuonGun with PU 140", "l");
  lg_Eta->Draw();
  c_Eta->SaveAs("Eff_Eta_for_PUs.png");
  
  
  //==== Pt
  
  TCanvas* c_Pt = new TCanvas("c_Pt", "", 800, 600);
  canvas_margin(c_Pt);
  c_Pt->cd();
  TGraph* Eff_Pt_0 = (TGraph*)file_0->Get("HitsEff_Pt");
  TGraph* Eff_Pt_10 = (TGraph*)file_10->Get("HitsEff_Pt");
  TGraph* Eff_Pt_50 = (TGraph*)file_50->Get("HitsEff_Pt");
  TGraph* Eff_Pt_140 = (TGraph*)file_140->Get("HitsEff_Pt");
  Eff_Pt_0->Draw("ap");
  Eff_Pt_0->SetLineColor(kBlack);
  Eff_Pt_0->GetYaxis()->SetRangeUser(0, 1.2);
  Eff_Pt_0->GetXaxis()->SetTitle("|#Pt|");
  Eff_Pt_10->Draw("psame");
  Eff_Pt_10->SetLineColor(kOrange);
  Eff_Pt_50->Draw("psame");
  Eff_Pt_50->SetLineColor(kBlue);
  Eff_Pt_140->Draw("psame");
  Eff_Pt_140->SetLineColor(kRed);
  TLegend* lg_Pt = new TLegend(0.5, 0.15, 0.95, 0.30);
  lg_Pt->SetFillStyle(0);
  lg_Pt->SetBorderSize(0);
  lg_Pt->AddEntry(Eff_Pt_0, "MuonGun (No PU)", "l");
  lg_Pt->AddEntry(Eff_Pt_10, "MuonGun with PU 10", "l");
  lg_Pt->AddEntry(Eff_Pt_50, "MuonGun with PU 50", "l");
  lg_Pt->AddEntry(Eff_Pt_140, "MuonGun with PU 140", "l");
  lg_Pt->Draw();
  c_Pt->SaveAs("Eff_Pt_for_PUs.png");
  
  
  
}
