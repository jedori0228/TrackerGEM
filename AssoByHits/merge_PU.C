#include "../include/canvas_margin.h"

void merge_PU(){
  
  TFile *file_0 = new TFile("./plots/CMSSW_8_1_0_pre9/Flat_Pt_0PU/hists.root");
  TFile *file_140 = new TFile("./plots/CMSSW_8_1_0_pre9/Flat_Pt_140PU/hists.root");
  TFile *file_140_noGEM = new TFile("./plots/CMSSW_8_1_0_pre9/Flat_Pt_140PU_noGEM/hists.root");
  
  TString plotpath = "./plots/CMSSW_8_1_0_pre9/";
  gSystem->mkdir(plotpath, kTRUE);
  
  vector<TString> MuonObjectType_hits = {"GEMMuon", "RecoMuon", "LooseMuon", "MediumMuon", "TightMuon"};
  vector<TString> var = {"Eta", "Pt", "Phi"};
  vector<TString> xtitle = {"|#eta|", "p_{T} [GeV]", "#phi"};
  
  for(unsigned int i=0; i<var.size(); i++){
    TString this_var = var.at(i);
    TString this_xtitle = xtitle.at(i);
    
    for(unsigned int j=0; j<MuonObjectType_hits.size(); j++){
      TString this_obj = MuonObjectType_hits.at(j);
      
      TCanvas *c1 = new TCanvas("c_"+this_var, "", 800, 600);
      canvas_margin(c1);
      c1->cd();
      
      TGraph *Eff_0PU = (TGraph*)file_0->Get("HitsEff_"+this_obj+"_"+this_var);
      TGraph *Eff_140PU = (TGraph*)file_140->Get("HitsEff_"+this_obj+"_"+this_var);
      TGraph *Eff_140PU_noGEM = (TGraph*)file_140_noGEM->Get("HitsEff_"+this_obj+"_"+this_var);
      
      Eff_0PU->SetLineWidth(3);
      Eff_140PU->SetLineWidth(3);
      Eff_140PU_noGEM->SetLineWidth(3);
      
      Eff_0PU->Draw("ap");
      Eff_0PU->SetLineColor(kBlack);
      Eff_0PU->GetYaxis()->SetRangeUser(0, 1.2);
      Eff_0PU->GetXaxis()->SetTitle(this_xtitle);
      Eff_140PU->Draw("psame");
      Eff_140PU->SetLineColor(kRed);
      Eff_140PU->Draw("psame");
      Eff_140PU->SetLineColor(kBlue);
      Eff_140PU_noGEM->Draw("psame");
      Eff_140PU_noGEM->SetLineColor(kBlue);
      Eff_140PU_noGEM->SetLineStyle(3);
      
      TLegend* lg = new TLegend(0.5, 0.15, 0.95, 0.35);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);
      lg->AddEntry(Eff_140PU, "(140PU) "+this_obj+", with GEM", "l");
      lg->AddEntry(Eff_140PU_noGEM, "(140PU) "+this_obj+", without GEM", "l");
      lg->AddEntry(Eff_0PU, "(0PU) "+this_obj, "l");
      lg->Draw();
      c1->SaveAs(plotpath+"Eff_"+this_obj+"_"+this_var+"_all.png");
      c1->Close();
      delete c1;
    }
  }

}





