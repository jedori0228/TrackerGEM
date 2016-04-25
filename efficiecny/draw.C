#include "../include/canvas_margin.h"

void draw(){

  TFile* file = new TFile("eff.root");
  
  vector<TString> variable = {"onebin", "eta", "pt"};

  vector<TString> object = {"standalone_trackerGEM", "SAMuon", "TrackerMuon"};
  vector<Color_t> color = {kRed, kBlack, kBlue};

  for(unsigned int it_var=0; it_var<variable.size(); it_var++){

    TCanvas* c1 = new TCanvas("c1", "", 800, 600);
    canvas_margin(c1);
    c1->cd(); 
    TLegend lg(0.2, 0.25, 0.9, 0.60);
    lg.SetFillStyle(0);
    lg.SetBorderSize(0);

    for(unsigned int it_obj=0; it_obj<object.size(); it_obj++){
    
      TEfficiency* eff = (TEfficiency*)file->Get(object.at(it_obj)+"_eff_"+variable.at(it_var));
      TGraph* gr = eff->CreateGraph();
      gr->SetLineColor(color.at(it_obj));
      if(it_obj==0){
        gr->Draw("ap");
        gr->GetYaxis()->SetRangeUser(0, 1.2);
        gr->SetTitle(variable.at(it_var));
      }
      else gr->Draw("psame");

    lg.AddEntry(gr, object.at(it_obj), "l");
    
    }
    
    lg.Draw();
    c1->SaveAs(variable.at(it_var)+".png");    
    c1->Close();
    delete c1;

  }

}
