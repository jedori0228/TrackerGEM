#include "../include/canvas_margin.h"

void merge_PU(){
  
  TFile *file_0 = new TFile("./plots/CMSSW_8_1_0_pre9/Flat_Pt_0PU/hists.root");
  TFile *file_140 = new TFile("./plots/CMSSW_8_1_0_pre9/Flat_Pt_140PU/hists.root");
  TFile *file_140_noGEM = new TFile("./plots/CMSSW_8_1_0_pre9/Flat_Pt_140PU_noGEM/hists.root");
  
  TString plotpath = "./plots/CMSSW_8_1_0_pre9/";
  gSystem->mkdir(plotpath, kTRUE);

  //==== Eta
  
  TString var[2] = {"Eta", "Pt"};
  TString xtitle[2] = {"|#eta|", "p_{T} [GeV]"};
  
  for(unsigned int i=0; i<2; i++){
    
    TString this_var = var[i];
    
    TCanvas *c1 = new TCanvas("c_"+this_var, "", 800, 600);
    canvas_margin(c1);
    c1->cd();
    TGraph *HitsEff_GEMMuon_0PU = (TGraph*)file_0->Get("HitsEff_GEMMuon_"+this_var);
    TGraph *HitsEff_GEMMuon_140PU = (TGraph*)file_140->Get("HitsEff_GEMMuon_"+this_var);
    TGraph *Eff_RecoMuon_140PU = (TGraph*)file_140->Get("HitsEff_RecoMuon_"+this_var);
    TGraph *Eff_RecoMuon_140PU_noGEM = (TGraph*)file_140_noGEM->Get("HitsEff_RecoMuon_"+this_var);
    //TGraph *Eff_NotGEMMuon_140PU = (TGraph*)file_140->Get("Eff_NotGEMMuon_"+this_var);
    
    HitsEff_GEMMuon_0PU->SetLineWidth(3);
    HitsEff_GEMMuon_140PU->SetLineWidth(3);
    Eff_RecoMuon_140PU->SetLineWidth(3);
    Eff_RecoMuon_140PU_noGEM->SetLineWidth(3);
    
    
    HitsEff_GEMMuon_0PU->Draw("ap");
    HitsEff_GEMMuon_0PU->SetLineColor(kBlack);
    HitsEff_GEMMuon_0PU->GetYaxis()->SetRangeUser(0.6, 1.1);
    HitsEff_GEMMuon_0PU->GetXaxis()->SetTitle(xtitle[i]);
    HitsEff_GEMMuon_140PU->Draw("psame");
    HitsEff_GEMMuon_140PU->SetLineColor(kRed);
    Eff_RecoMuon_140PU->Draw("psame");
    Eff_RecoMuon_140PU->SetLineColor(kBlue);
    Eff_RecoMuon_140PU_noGEM->Draw("psame");
    Eff_RecoMuon_140PU_noGEM->SetLineColor(kBlue);
    Eff_RecoMuon_140PU_noGEM->SetLineStyle(3);
    //Eff_NotGEMMuon_140PU->Draw("psame");
    //Eff_NotGEMMuon_140PU->SetLineColor(kViolet);
    
    TLegend* lg_Eta = new TLegend(0.5, 0.15, 0.95, 0.35);
    lg_Eta->SetFillStyle(0);
    lg_Eta->SetBorderSize(0);
    lg_Eta->AddEntry(Eff_RecoMuon_140PU, "(140PU) RecoMuon, use GEM", "l");
    lg_Eta->AddEntry(Eff_RecoMuon_140PU_noGEM, "(140PU) RecoMuon, no GEM", "l");
    lg_Eta->AddEntry(HitsEff_GEMMuon_0PU, "(0PU) GEMMuon", "l");
    lg_Eta->AddEntry(HitsEff_GEMMuon_140PU, "(140PU) GEMMuon", "l");
    //lg_Eta->AddEntry(Eff_NotGEMMuon_140PU, "(140PU) RecoMuon but NotGEMMuon", "l");
    lg_Eta->Draw();
    c1->SaveAs(plotpath+"Eff_"+this_var+"_all.png");
  }
  
  
}





