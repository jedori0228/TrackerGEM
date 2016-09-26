#include "../include/canvas_margin.h"

void merge_PU(){
  
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  //TFile *file_0 = new TFile("./plots/CMSSW_8_1_0_pre11/RelValTenMuE_0_200_0PU/hists.root");
  //TFile *file_140 = new TFile("./plots/CMSSW_8_1_0_pre11/RelValTenMuE_0_200_140PU/hists.root");
  TFile *file_0 = new TFile("./plots/CMSSW_8_1_0_pre11/RelValSingleMuPt100_0PU/hists.root");
  TFile *file_140 = new TFile("./plots/CMSSW_8_1_0_pre11/RelValSingleMuPt100_140PU/hists.root");
  TFile *file_200 = new TFile("./plots/CMSSW_8_1_0_pre11/RelValSingleMuPt100_200PU/hists.root");
  
  TString plotpath = "./plots/CMSSW_8_1_0_pre11/";
  gSystem->mkdir(plotpath, kTRUE);
  
  vector<TString> MuonObjectType_hits = {"GEMMuon", "RecoMuon", "LooseMuon", "MediumMuon", "TightMuon"};
  vector<TString> var = {"Eta", "Pt", "Phi"};
  vector<TString> xtitle = {"|#eta|", "p_{T} [GeV]", "#phi"};
  
  vector<double> y_maxes_for_fake = {10, 10, 10};
  
  for(unsigned int i=0; i<var.size(); i++){
    TString this_var = var.at(i);
    TString this_xtitle = xtitle.at(i);
    
    for(unsigned int j=0; j<MuonObjectType_hits.size(); j++){
      TString this_obj = MuonObjectType_hits.at(j);
      
      //==== Efficiency
      
      TCanvas *c1 = new TCanvas("c1_"+this_var, "", 800, 600);
      canvas_margin(c1);
      c1->cd();
      
      TGraph *Eff_0PU = (TGraph*)file_0->Get("HitsEff_"+this_obj+"_"+this_var);
      TGraph *Eff_140PU = (TGraph*)file_140->Get("HitsEff_"+this_obj+"_"+this_var);
      TGraph *Eff_200PU = (TGraph*)file_200->Get("HitsEff_"+this_obj+"_"+this_var);
      
      Eff_0PU->SetLineWidth(3);
      Eff_140PU->SetLineWidth(3);
      Eff_200PU->SetLineWidth(3);
      
      Eff_0PU->Draw("ap");
      Eff_0PU->SetLineColor(kBlack);
      Eff_0PU->GetYaxis()->SetRangeUser(0, 1.2);
      Eff_0PU->GetXaxis()->SetTitle(this_xtitle);
      Eff_140PU->Draw("psame");
      Eff_140PU->SetLineColor(kBlue);
      Eff_200PU->Draw("psame");
      Eff_200PU->SetLineColor(kRed);
      
      TLegend* lg = new TLegend(0.5, 0.15, 0.95, 0.35);
      lg->SetFillStyle(0);
      lg->SetBorderSize(0);
      lg->AddEntry(Eff_0PU, "(0PU) "+this_obj, "l");
      lg->AddEntry(Eff_140PU, "(140PU) "+this_obj, "l");
      lg->AddEntry(Eff_200PU, "(200PU) "+this_obj, "l");
      lg->Draw();
      c1->SaveAs(plotpath+"Eff_"+this_obj+"_"+this_var+"_all.png");
      c1->Close();
      delete c1;
      
      
      //==== Fake
      
      TCanvas *c2 = new TCanvas("c2_"+this_var, "", 800, 600);
      canvas_margin(c2);
      c2->cd();
      
      
      TH1F *Fake_0PU = (TH1F*)file_0->Get("HitsUnmatched"+this_obj+"_"+this_var);
      TH1F *Fake_140PU = (TH1F*)file_140->Get("HitsUnmatched"+this_obj+"_"+this_var);
      TH1F *Fake_200PU = (TH1F*)file_200->Get("HitsUnmatched"+this_obj+"_"+this_var);

      Fake_0PU->SetLineWidth(3);
      Fake_140PU->SetLineWidth(3);
      Fake_200PU->SetLineWidth(3);
 
      
      Fake_0PU->SetMinimum(0.00001);
      Fake_140PU->SetMinimum(0.00001);
      Fake_200PU->SetMinimum(0.00001);
     
      Fake_200PU->Draw("histsame");
      Fake_200PU->SetLineColor(kRed);
      Fake_200PU->GetXaxis()->SetTitle(this_xtitle);
      Fake_200PU->SetMaximum(y_maxes_for_fake.at(i));
      Fake_140PU->Draw("histsame");
      Fake_140PU->SetLineColor(kBlue);
      Fake_0PU->Draw("histsame");
      Fake_0PU->SetLineColor(kBlack);
 
      TLegend* lg2 = new TLegend(0.5, 0.3, 0.95, 0.5);
      lg2->SetFillStyle(0);
      lg2->SetBorderSize(0);
      lg2->AddEntry(Fake_200PU, "(200PU) "+this_obj, "l");
      lg2->AddEntry(Fake_140PU, "(140PU) "+this_obj, "l");
      lg2->AddEntry(Fake_0PU, "(0PU) "+this_obj, "l");
      lg2->Draw();
      gPad->SetLogy(1);
      c2->SaveAs(plotpath+"Fake_"+this_obj+"_"+this_var+"_all.png");
      gPad->SetLogy(0);
      c2->Close();
      delete c2;

      
    }
  }

}




