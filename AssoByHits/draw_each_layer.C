#include "../include/canvas_margin.h"

void draw_each_layer(){
 
  TFile *file = new TFile("./rootfiles/OUTPUTTEMPLAT_140PU_dBunchX_1_file4.root");
  
  //==== each layer
  
  TString stations[2] = {"GE11", "GE21"};
  TString layers[4] = {"layer1", "layer2", "two", "segment"};
  TString legend_name[4] = {"layer1", "layer2", "Both layer", "Segment"};
  Color_t linecolor[4] = {kBlack, kBlack, kBlue, kRed};
  Style_t linestyle[4] = {1, 2, 3, 1};
  


  for(int i_station=0; i_station<2; i_station++){
    
    TLegend *lg = new TLegend(0.7, 0.25, 0.95, 0.50);
    lg->SetFillStyle(0);
    lg->SetBorderSize(0);
    
    TCanvas *c_Eta = new TCanvas("c_Eta", "", 800, 600);
    TCanvas *c_Pt = new TCanvas("c_Pt", "", 800, 600);
    canvas_margin(c_Eta);
    canvas_margin(c_Pt);
    TEfficiency* eff_Eta[4];
    TGraph* gr_Eta[4];
    TEfficiency* eff_Pt[4];
    TGraph* gr_Pt[4];
    
    for(int i=0; i<4; i++){
      
      TString histname_prefix = "Eff_GEMRecHit_"+stations[i_station]+"_"+layers[i];
      if(i==3) histname_prefix = "Eff_GEMSegment_"+stations[i_station];
      
      c_Eta->cd();
      eff_Eta[i] = (TEfficiency*)file->Get(histname_prefix+"_Eta");
      gr_Eta[i] = eff_Eta[i]->CreateGraph();
      gr_Eta[i]->SetLineColor(linecolor[i]);
      gr_Eta[i]->SetLineStyle(linestyle[i]);
      gr_Eta[i]->SetLineWidth(3);
      if(i==0){
        gr_Eta[i]->Draw("ap");
        gr_Eta[i]->SetTitle(stations[i_station]);
        gr_Eta[i]->GetYaxis()->SetRangeUser(0, 1.2);
      }
      else gr_Eta[i]->Draw("psame");
      lg->AddEntry(gr_Eta[i], legend_name[i], "l");
      
      c_Pt->cd();
      eff_Pt[i] = (TEfficiency*)file->Get(histname_prefix+"_Pt");
      gr_Pt[i] = eff_Pt[i]->CreateGraph();
      gr_Pt[i]->SetLineColor(linecolor[i]);
      gr_Pt[i]->SetLineStyle(linestyle[i]);
      gr_Pt[i]->SetLineWidth(3);
      if(i==0){
        gr_Pt[i]->Draw("ap");
        gr_Pt[i]->SetTitle(stations[i_station]);
        gr_Pt[i]->GetYaxis()->SetRangeUser(0, 1.2);
      }
      else gr_Pt[i]->Draw("psame");
      
    }
    
    c_Eta->cd();
    lg->Draw();
    c_Eta->SaveAs(stations[i_station]+"_EachLayer_Eta.png");
    c_Eta->Close();
    delete c_Eta;
    
    c_Pt->cd();
    lg->Draw();
    c_Pt->SaveAs(stations[i_station]+"_EachLayer_Pt.png");
    c_Pt->Close();
    delete c_Pt;
    
  }
  

  
  
}





