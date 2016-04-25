#include "../include/canvas_margin.h"

void draw(){

  gStyle->SetOptStat(0);

  TFile* file_GE11_MuonGun = new TFile("./plots/GE11_MuonGun.root");
  TFile* file_GE11_MinBias = new TFile("./plots/GE11_MinBias.root");
  vector<TString> var_GE11 = {"DelX_over_sigma_GE11", "DelY_over_sigma_GE11", "DelX_GE11", "DelY_GE11", "DelPhi_GE11", "DelTheta_GE11", "DotDir_GE11", "DotXDir_GE11", "DelThetaXZ_GE11"};

  for(unsigned int i=0; i<var_GE11.size(); i++){

    TCanvas* c1 = new TCanvas("c1", "", 800, 600);
    canvas_margin(c1);

    TH1F* hist_GE11_MuonGun = (TH1F*)file_GE11_MuonGun->Get(var_GE11.at(i)+"_onebin");
    TH1F* hist_GE11_MinBias = (TH1F*)file_GE11_MinBias->Get(var_GE11.at(i)+"_onebin");
    
    hist_GE11_MuonGun->DrawNormalized("hist",1);
    hist_GE11_MinBias->SetLineColor(kRed);
    hist_GE11_MinBias->DrawNormalized("histsame",1);

    TLegend lg(0.7, 0.7, 0.9, 0.90);
    lg.SetFillStyle(0);
    lg.SetBorderSize(0);

    lg.AddEntry(hist_GE11_MuonGun, "MuonGun", "l");
    lg.AddEntry(hist_GE11_MinBias, "MinBias", "l");
    lg.Draw();

    hist_GE11_MuonGun->SetTitle(var_GE11.at(i));
    c1->SaveAs("./plots/GE11_"+var_GE11.at(i)+".png");
    c1->Close();
    delete c1;
    

  }

  TFile* file_GE21_MuonGun = new TFile("./plots/GE21_MuonGun.root");
  TFile* file_GE21_MinBias = new TFile("./plots/GE21_MinBias.root");
  vector<TString> var_GE21 = {"DelX_over_sigma_GE21", "DelY_over_sigma_GE21", "DelX_GE21", "DelY_GE21", "DelPhi_GE21", "DelTheta_GE21", "DotDir_GE21", "DotXDir_GE21", "DelThetaXZ_GE21"};
  
  for(unsigned int i=0; i<var_GE21.size(); i++){
    
    TCanvas* c1 = new TCanvas("c1", "", 800, 600);
    canvas_margin(c1);
    
    TH1F* hist_GE21_MuonGun = (TH1F*)file_GE21_MuonGun->Get(var_GE21.at(i)+"_onebin");
    TH1F* hist_GE21_MinBias = (TH1F*)file_GE21_MinBias->Get(var_GE21.at(i)+"_onebin");
    
    hist_GE21_MuonGun->DrawNormalized("hist",1);
    hist_GE21_MinBias->SetLineColor(kRed);
    hist_GE21_MinBias->DrawNormalized("histsame",1);
    
    TLegend lg(0.7, 0.7, 0.9, 0.90);
    lg.SetFillStyle(0);
    lg.SetBorderSize(0);
    
    lg.AddEntry(hist_GE21_MuonGun, "MuonGun", "l");
    lg.AddEntry(hist_GE21_MinBias, "MinBias", "l");
    lg.Draw();
    
    hist_GE21_MuonGun->SetTitle(var_GE21.at(i));
    c1->SaveAs("./plots/GE21_"+var_GE21.at(i)+".png");
    c1->Close();
    delete c1;
    
    
  }
  
}
