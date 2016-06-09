#include "../include/canvas_margin.h"

void draw_each_layer(){
 
  TFile *file = new TFile("./rootfiles/OUTPUTTEMPLATE_MuonGun_noise_off.root");
  
  //==== each layer
  
  TString layers[7] = {"GE11_layer1", "GE11_layer2", "GE11_two", "GE21_layer1", "GE21_layer2", "GE21_two", "GEMSegment"};
  Color_t linecolor[7] = {kBlack, kBlack, kBlack, kRed, kRed, kRed, kBlue};
  Style_t linestyle[7] = {1, 2, 3, 1, 2, 3, 1};
  
  TLegend* lg = new TLegend(0.7, 0.25, 0.95, 0.50);
  lg->SetFillStyle(0);
  lg->SetBorderSize(0);
  
  TCanvas *c_Eta = new TCanvas("c_Eta", "", 800, 600);
  TCanvas *c_Pt = new TCanvas("c_Pt", "", 800, 600);
  canvas_margin(c_Eta);
  canvas_margin(c_Pt);
  TEfficiency* eff_Eta[7];
  TGraph* gr_Eta[7];
  TEfficiency* eff_Pt[7];
  TGraph* gr_Pt[7];
  
  for(int i=0; i<7; i++){
    
    TString histname_prefix = "Eff_GEMRecHit_"+layers[i];
    if(i==6) histname_prefix = "Eff_GEMSegment";
    
    c_Eta->cd();
    eff_Eta[i] = (TEfficiency*)file->Get(histname_prefix+"_Eta");
    gr_Eta[i] = eff_Eta[i]->CreateGraph();
    gr_Eta[i]->SetLineColor(linecolor[i]);
    gr_Eta[i]->SetLineStyle(linestyle[i]);
    gr_Eta[i]->SetLineWidth(3);
    if(i==0){
      gr_Eta[i]->Draw("ap");
      gr_Eta[i]->GetYaxis()->SetRangeUser(0, 1.2);
    }
    else gr_Eta[i]->Draw("psame");
    lg->AddEntry(gr_Eta[i], layers[i], "l");
    
    c_Pt->cd();
    eff_Pt[i] = (TEfficiency*)file->Get(histname_prefix+"_Pt");
    gr_Pt[i] = eff_Pt[i]->CreateGraph();
    gr_Pt[i]->SetLineColor(linecolor[i]);
    gr_Pt[i]->SetLineStyle(linestyle[i]);
    gr_Pt[i]->SetLineWidth(3);
    if(i==0){
      gr_Pt[i]->Draw("ap");
      gr_Pt[i]->GetYaxis()->SetRangeUser(0, 1.2);
    }
    else gr_Pt[i]->Draw("psame");
    
  }
  
  c_Eta->cd();
  lg->Draw();
  c_Eta->SaveAs("EachLayer_Eta.png");
  
  c_Pt->cd();
  lg->Draw();
  c_Pt->SaveAs("EachLayer_Pt.png");
  
  
}





