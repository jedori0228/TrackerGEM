#include "../include/canvas_margin.h"

void draw_recseggem(){
  
  //TFile* file_MuonGunPU = new TFile("rootfiles/OUTPUTTEMPLATE_MuonGun_PU_140.root");
  TFile* file_MuonGunPU = new TFile("rootfiles/OUTPUTTEMPLATE_MuonGun_noise_off.root");
  
  //==== Eta
 
  TEfficiency* Eff_GEMRecHit_Eta = (TEfficiency*)file_MuonGunPU->Get("Eff_GEMRecHit_Eta");
  TEfficiency* Eff_TwoGEMRecHit_Eta = (TEfficiency*)file_MuonGunPU->Get("Eff_TwoGEMRecHit_Eta");
  TEfficiency* Eff_GEMSegment_Eta = (TEfficiency*)file_MuonGunPU->Get("Eff_GEMSegment_Eta");
  TEfficiency* Eff_Eta = (TEfficiency*)file_MuonGunPU->Get("Eff_Eta");
  
  TGraph* gr_Eff_GEMRecHit_Eta = Eff_GEMRecHit_Eta->CreateGraph();
  TGraph* gr_Eff_TwoGEMRecHit_Eta = Eff_TwoGEMRecHit_Eta->CreateGraph();
  TGraph* gr_Eff_GEMSegment_Eta = Eff_GEMSegment_Eta->CreateGraph();
  TGraph* gr_Eff_Eta = Eff_Eta->CreateGraph();
  
  gr_Eff_GEMRecHit_Eta->SetLineColor(kBlack);
  gr_Eff_TwoGEMRecHit_Eta->SetLineColor(kGreen);
  gr_Eff_GEMSegment_Eta->SetLineColor(kBlue);
  gr_Eff_Eta->SetLineColor(kRed);
  
  TCanvas* c_Eta = new TCanvas("c_Eta", "", 800, 600);
  canvas_margin(c_Eta);
  c_Eta->cd();
  gr_Eff_GEMRecHit_Eta->Draw("ap");
  gr_Eff_GEMRecHit_Eta->GetYaxis()->SetRangeUser(0, 1.2);
  gr_Eff_GEMRecHit_Eta->GetXaxis()->SetTitle("|#eta|");
  gr_Eff_TwoGEMRecHit_Eta->Draw("psame");
  gr_Eff_GEMSegment_Eta->Draw("psame");
  gr_Eff_Eta->Draw("psame");
  
  TLegend* lg_Eta = new TLegend(0.5, 0.15, 0.95, 0.30);
  lg_Eta->SetFillStyle(0);
  lg_Eta->SetBorderSize(0);
  lg_Eta->AddEntry(gr_Eff_GEMRecHit_Eta, "GEMRecHit", "l");
  lg_Eta->AddEntry(gr_Eff_TwoGEMRecHit_Eta, "GEMRecHit, both layer 1/2 matched", "l");
  lg_Eta->AddEntry(gr_Eff_GEMSegment_Eta, "GEMSegment", "l");
  lg_Eta->AddEntry(gr_Eff_Eta, "isGEMMuon() AND isTrackerMuon()", "l");
  lg_Eta->Draw();
  c_Eta->SaveAs("./plots/RecHitSegmentGEMMuon_Eta.png");
  
  //==== Pt
  
  TEfficiency* Eff_GEMRecHit_Pt = (TEfficiency*)file_MuonGunPU->Get("Eff_GEMRecHit_Pt");
  TEfficiency* Eff_TwoGEMRecHit_Pt = (TEfficiency*)file_MuonGunPU->Get("Eff_TwoGEMRecHit_Pt");
  TEfficiency* Eff_GEMSegment_Pt = (TEfficiency*)file_MuonGunPU->Get("Eff_GEMSegment_Pt");
  TEfficiency* Eff_Pt = (TEfficiency*)file_MuonGunPU->Get("Eff_Pt");
  
  TGraph* gr_Eff_GEMRecHit_Pt = Eff_GEMRecHit_Pt->CreateGraph();
  TGraph* gr_Eff_TwoGEMRecHit_Pt = Eff_TwoGEMRecHit_Pt->CreateGraph();
  TGraph* gr_Eff_GEMSegment_Pt = Eff_GEMSegment_Pt->CreateGraph();
  TGraph* gr_Eff_Pt = Eff_Pt->CreateGraph();
  
  gr_Eff_GEMRecHit_Pt->SetLineColor(kBlack);
  gr_Eff_TwoGEMRecHit_Pt->SetLineColor(kGreen);
  gr_Eff_GEMSegment_Pt->SetLineColor(kBlue);
  gr_Eff_Pt->SetLineColor(kRed);
  
  TCanvas* c_Pt = new TCanvas("c_Pt", "", 800, 600);
  canvas_margin(c_Pt);
  c_Pt->cd();
  gr_Eff_GEMRecHit_Pt->Draw("ap");
  gr_Eff_GEMRecHit_Pt->GetYaxis()->SetRangeUser(0, 1.2);
  gr_Eff_GEMRecHit_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  gr_Eff_TwoGEMRecHit_Pt->Draw("psame");
  gr_Eff_GEMSegment_Pt->Draw("psame");
  gr_Eff_Pt->Draw("psame");
  
  TLegend* lg_Pt = new TLegend(0.5, 0.15, 0.95, 0.30);
  lg_Pt->SetFillStyle(0);
  lg_Pt->SetBorderSize(0);
  lg_Pt->AddEntry(gr_Eff_GEMRecHit_Pt, "GEMRecHit", "l");
  lg_Pt->AddEntry(gr_Eff_TwoGEMRecHit_Pt, "GEMRecHit, both layer 1/2 matched", "l");
  lg_Pt->AddEntry(gr_Eff_GEMSegment_Pt, "GEMSegment", "l");
  lg_Pt->AddEntry(gr_Eff_Pt, "isGEMMuon() AND isTrackerMuon()", "l");
  lg_Pt->Draw();
  c_Pt->SaveAs("./plots/RecHitSegmentGEMMuon_Pt.png");

}
