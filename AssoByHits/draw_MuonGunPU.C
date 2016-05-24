#include "../include/canvas_margin.h"

void draw_MuonGunPU(int x){
 
  TString n_PU = TString::Itoa(x, 10);
 
  TFile* file_MuonGunPU = new TFile("./rootfiles/OUTPUTTEMPLATE_MuonGun_PU_"+n_PU+".root");
  
  TH1F* GenMuon_Eta = (TH1F*)file_MuonGunPU->Get("GenMuon_Eta");
  TH1F* GenMuon_Pt = (TH1F*)file_MuonGunPU->Get("GenMuon_Pt");
  TH1F* MatchedGEMMuon_Eta = (TH1F*)file_MuonGunPU->Get("MatchedGEMMuon_Eta");
  TH1F* MatchedGEMMuon_Pt = (TH1F*)file_MuonGunPU->Get("MatchedGEMMuon_Pt");
  
  TEfficiency* Eff_Eta = (TEfficiency*)file_MuonGunPU->Get("Eff_Eta");
  TEfficiency* Eff_Pt = (TEfficiency*)file_MuonGunPU->Get("Eff_Pt");
  TGraph* gr_Eff_Eta = Eff_Eta->CreateGraph();
  gr_Eff_Eta->SetName("Eff_Eta");
  TGraph* gr_Eff_Pt = Eff_Pt->CreateGraph();
  gr_Eff_Pt->SetName("Eff_Pt");
  
  TFile* file_hists = new TFile("./plots/Hist_PU_"+n_PU+".root", "RECREATE");
  file_hists->cd();
  
  TCanvas* c_GenMuon_Eta = new TCanvas("c_GenMuon_Eta", "", 800, 600);
  canvas_margin(c_GenMuon_Eta);
  c_GenMuon_Eta->cd();
  GenMuon_Eta->Draw("");
  GenMuon_Eta->Write();
  GenMuon_Eta->SetTitle("GenMuon |#eta|");
  GenMuon_Eta->GetXaxis()->SetTitle("|#eta|");
  c_GenMuon_Eta->SaveAs("./plots/MuonGunPU_GenMuon_Eta.png");
  c_GenMuon_Eta->Close();
  
  TCanvas* c_GenMuon_Pt = new TCanvas("c_GenMuon_Pt", "", 800, 600);
  canvas_margin(c_GenMuon_Pt);
  c_GenMuon_Pt->cd();
  GenMuon_Pt->Draw("");
  GenMuon_Pt->Write();
  GenMuon_Pt->SetTitle("GenMuon p_{T}");
  GenMuon_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  c_GenMuon_Pt->SaveAs("./plots/MuonGunPU_GenMuon_Pt.png");
  c_GenMuon_Pt->Close();
  
  TCanvas* c_Eff_Eta = new TCanvas("c_Eff_Eta", "", 800, 600);
  canvas_margin(c_Eff_Eta);
  c_Eff_Eta->cd();
  gr_Eff_Eta->Draw("ap");
  gr_Eff_Eta->Write();
  gr_Eff_Eta->GetYaxis()->SetRangeUser(0, 1.2);
  gr_Eff_Eta->GetXaxis()->SetTitle("|#eta|");
  c_Eff_Eta->SaveAs("./plots/MuonGunPU_Eff_Eta.png");
  c_Eff_Eta->Close();
  
  TCanvas* c_Eff_Pt = new TCanvas("c_Eff_Pt", "", 800, 600);
  canvas_margin(c_Eff_Pt);
  c_Eff_Pt->cd();
  gr_Eff_Pt->Draw("ap");
  gr_Eff_Pt->Write();
  gr_Eff_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  gPad->SetLogx();
  gr_Eff_Pt->GetYaxis()->SetRangeUser(0, 1.2);
  c_Eff_Pt->SaveAs("./plots/MuonGunPU_Eff_Pt.png");
  gPad->SetLogx(kFALSE);
  c_Eff_Pt->Close();
  
  /* Eff by AssoByHits */
  
  TH1F* TPMuon_Eta = (TH1F*)file_MuonGunPU->Get("TPMuon_Eta");
  TH1F* TPMuon_Pt = (TH1F*)file_MuonGunPU->Get("TPMuon_Pt");
  TH1F* HitsMatchedGEMMuon_Eta = (TH1F*)file_MuonGunPU->Get("HitsMatchedGEMMuon_Eta");
  TH1F* HitsMatchedGEMMuon_Pt = (TH1F*)file_MuonGunPU->Get("HitsMatchedGEMMuon_Pt");
  
  TEfficiency* HitsEff_Eta = (TEfficiency*)file_MuonGunPU->Get("HitsEff_Eta");
  TEfficiency* HitsEff_Pt = (TEfficiency*)file_MuonGunPU->Get("HitsEff_Pt");
  TGraph* gr_HitsEff_Eta = HitsEff_Eta->CreateGraph();
  gr_HitsEff_Eta->SetName("HitsEff_Eta");
  TGraph* gr_HitsEff_Pt = HitsEff_Pt->CreateGraph();
  gr_HitsEff_Pt->SetName("HitsEff_Pt");
  
  TCanvas* c_TPMuon_Eta = new TCanvas("c_TPMuon_Eta", "", 800, 600);
  canvas_margin(c_TPMuon_Eta);
  c_TPMuon_Eta->cd();
  TPMuon_Eta->Draw("");
  TPMuon_Eta->Write();
  TPMuon_Eta->SetTitle("TPMuon |#eta|");
  TPMuon_Eta->GetXaxis()->SetTitle("|#eta|");
  c_TPMuon_Eta->SaveAs("./plots/MuonGunPU_TPMuon_Eta.png");
  c_TPMuon_Eta->Close();
  
  TCanvas* c_TPMuon_Pt = new TCanvas("c_TPMuon_Pt", "", 800, 600);
  canvas_margin(c_TPMuon_Pt);
  c_TPMuon_Pt->cd();
  TPMuon_Pt->Draw("");
  TPMuon_Pt->Write();
  TPMuon_Pt->SetTitle("TPMuon p_{T}");
  TPMuon_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  c_TPMuon_Pt->SaveAs("./plots/MuonGunPU_TPMuon_Pt.png");
  c_TPMuon_Pt->Close();
  
  TCanvas* c_HitsEff_Eta = new TCanvas("c_HitsEff_Eta", "", 800, 600);
  canvas_margin(c_HitsEff_Eta);
  c_HitsEff_Eta->cd();
  gr_HitsEff_Eta->Draw("ap");
  gr_HitsEff_Eta->Write();
  gr_HitsEff_Eta->GetYaxis()->SetRangeUser(0, 1.2);
  gr_HitsEff_Eta->GetXaxis()->SetTitle("|#eta|");
  c_HitsEff_Eta->SaveAs("./plots/MuonGunPU_HitsEff_Eta.png");
  c_HitsEff_Eta->Close();
  
  TCanvas* c_HitsEff_Pt = new TCanvas("c_HitsEff_Pt", "", 800, 600);
  canvas_margin(c_HitsEff_Pt);
  c_HitsEff_Pt->cd();
  gr_HitsEff_Pt->Draw("ap");
  gr_HitsEff_Pt->Write();
  gr_HitsEff_Pt->GetXaxis()->SetTitle("p_{T} [GeV]");
  gPad->SetLogx();
  gr_HitsEff_Pt->GetYaxis()->SetRangeUser(0, 1.2);
  c_HitsEff_Pt->SaveAs("./plots/MuonGunPU_HitsEff_Pt.png");
  gPad->SetLogx(kFALSE);
  c_HitsEff_Pt->Close();
  
  /* Fake */
  
  TH1F* Nevents_h = (TH1F*)file_MuonGunPU->Get("Nevents_h");
  int Nevents = Nevents_h->GetBinContent(2);
  
  TH1F* HitsUnmatchedGEMMuon_Eta = (TH1F*)file_MuonGunPU->Get("HitsUnmatchedGEMMuon_Eta");
  TH1F* HitsUnmatchedGEMMuon_Pt = (TH1F*)file_MuonGunPU->Get("HitsUnmatchedGEMMuon_Pt");
  
  TCanvas* c_HitsUnmatchedGEMMuon_Eta = new TCanvas("HitsUnmatchedGEMMuon_Eta", "", 800, 600);
  canvas_margin(c_HitsUnmatchedGEMMuon_Eta);
  c_HitsUnmatchedGEMMuon_Eta->cd();
  HitsUnmatchedGEMMuon_Eta->Draw("");
  HitsUnmatchedGEMMuon_Eta->SetTitle(TString::Itoa(Nevents/1000., 10)+"k MinBias Events");
  HitsUnmatchedGEMMuon_Eta->SetXTitle("|#eta|");
  gPad->SetLogy();
  c_HitsUnmatchedGEMMuon_Eta->SaveAs("./plots/MuonGunPU_HitsUnmatchedGEMMuon_Eta.png");
  HitsUnmatchedGEMMuon_Eta->Scale(1./Nevents);
  HitsUnmatchedGEMMuon_Eta->Draw("");
  c_HitsUnmatchedGEMMuon_Eta->SaveAs("./plots/MuonGunPU_HitsUnmatchedGEMMuon_Eta_per_event.png");
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
  c_HitsUnmatchedGEMMuon_Pt->SaveAs("./plots/MuonGunPU_HitsUnmatchedGEMMuon_Pt.png");
  HitsUnmatchedGEMMuon_Pt->Scale(1./Nevents);
  HitsUnmatchedGEMMuon_Pt->Draw("");
  c_HitsUnmatchedGEMMuon_Pt->SaveAs("./plots/MuonGunPU_HitsUnmatchedGEMMuon_Pt_per_event.png");
  gPad->SetLogx(kFALSE);
  gPad->SetLogy(kFALSE);
  c_HitsUnmatchedGEMMuon_Pt->Close();
  
  
  file_hists->Close();
  
}
