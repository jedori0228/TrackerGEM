#include "../include/canvas_margin.h"

void draw(){
  
  TFile* file = new TFile("fake.root");

  TH1F* hist_n_events = (TH1F*)file->Get("n_events");
  
  TCanvas *c_n_events = new TCanvas("c_n_events", "", 800, 600);
  c_n_events->cd();
  hist_n_events->Draw();
  c_n_events->SaveAs("n_events.png");
  c_n_events->Close();
  delete c_n_events;
  
  vector<TString> variable = {"onebin", "eta", "pt"};
  vector<double> y_max = {10000, 100000, 1000000};
  vector<double> y_min = {1, 0.00001, 0.01};

  vector<TString> object = {"TMOneStationTight", "standalone_trackerGEM", "SAMuon"};
  vector<Color_t> color = {kBlue, kRed, kBlack};

  gStyle->SetOptStat(0);
  
  for(unsigned int it_var=0; it_var<variable.size(); it_var++){

    TCanvas* c1 = new TCanvas("c1", "", 800, 600);
    canvas_margin(c1);
    c1->cd(); 
    TLegend lg(0.6, 0.7, 0.9, 0.9);
    lg.SetFillStyle(0);
    lg.SetBorderSize(0);

    for(unsigned int it_obj=0; it_obj<object.size(); it_obj++){
    
      TH1F* hist = (TH1F*)file->Get(object.at(it_obj)+"_fake_"+variable.at(it_var));
      hist->SetLineColor(color.at(it_obj));
      if(it_obj==0){
        hist->Draw("");
        hist->SetTitle(variable.at(it_var));
        hist->GetYaxis()->SetRangeUser( y_min.at(it_var),  y_max.at(it_var) );
        gPad->SetLogy();
      }
      else hist->Draw("same");

      lg.AddEntry(hist, object.at(it_obj), "l");
    
    }
    
    lg.Draw();
    c1->SaveAs(variable.at(it_var)+".png");    
    c1->Close();
    delete c1;

  }

}
