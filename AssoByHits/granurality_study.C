#include "../include/setTDRStyle.C"
#include "../include/mylib.h"

void granurality_study(){
  
  setTDRStyle();
  TH1::SetDefaultSumw2(true);
  
  TString plotpath = "./plots/CMSSW_6_2_0_SLHC27/Granurality/";
  gSystem->mkdir(plotpath, kTRUE);
  
  vector<TString> gran = {
    "w_GE21_w_ME21_5mm",
    "w_GE21_w_ME21_1mm",
    "w_GE21_w_ME21_500um",
    "w_GE21_w_ME21_250um",
    "w_GE21_w_ME21_100um",
    "w_GE21_wo_ME21_5mm",
    "w_GE21_wo_ME21_1mm",
    "w_GE21_wo_ME21_500um",
    "w_GE21_wo_ME21_250um",
    "w_GE21_wo_ME21_100um",
  };
  vector<Color_t> colors = {
    kBlack, kRed, kBlue, kYellow-3, kOrange,
    kBlack, kRed, kBlue, kYellow-3, kOrange
  };
  
  vector<TString> var = {"Eta", "Pt", "Phi"};
  vector<TString> xtitle = {"|#eta|", "p_{T} [GeV]", "#phi"};
  
  for(unsigned int j=0; j<var.size(); j++){
    TString this_var = var.at(j);

    TCanvas *c_eff = new TCanvas("c_eff_"+this_var, "", 800, 800);
    TCanvas *c_fake = new TCanvas("c_fake_"+this_var, "", 800, 800);
    
    TLegend lg_eff(0.65, 0.2, 0.93, 0.6);
    lg_eff.SetBorderSize(0);
    TLegend lg_fake(0.65, 0.5, 0.93, 0.9);
    lg_fake.SetBorderSize(0);
    
    for(unsigned int i=0; i<gran.size(); i++){
      TString this_gran = gran.at(i);
    
      TFile *file = new TFile("./rootfiles/CMSSW_6_2_0_SLHC27/"+this_gran+".root");
      
      //==== Efficiency
      c_eff->cd();
      TEfficiency *eff = (TEfficiency*)file->Get("HitsEff_GEMMuon_"+this_var);
      TGraph *gr = eff->CreateGraph();
      gr->SetLineColor(colors.at(i));
      if(this_gran.Contains("wo_ME21")) gr->SetLineStyle(2);
      lg_eff.AddEntry(gr, this_gran, "l");
      if(i==0){
        gr->Draw("alp");
        gr->GetYaxis()->SetRangeUser(0, 1.2);
      }
      else gr->Draw("lpsame");
      
      //==== Fake
      c_fake->cd();
      TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatchedGEMMuon_"+this_var)->Clone();
      TH1F *total = (TH1F*)file->Get("HitsGEMMuon_"+this_var)->Clone();
    
      Unmatched->Divide(total);
      TGraphAsymmErrors *Unmatched_gr;
      if(this_var=="Eta") Unmatched_gr = hist_to_graph(Unmatched, true);
      else Unmatched_gr = hist_to_graph(Unmatched);
      Unmatched_gr->SetLineColor(colors.at(i));
      Unmatched_gr->SetLineWidth(2);
      Unmatched_gr->SetMarkerStyle(21);
      Unmatched_gr->SetMarkerColor(colors.at(i));
      Unmatched_gr->SetMarkerSize(1);
      Unmatched_gr->SetTitle("");
      lg_fake.AddEntry(Unmatched_gr, this_gran, "l");
      if(this_gran.Contains("wo_ME21")) Unmatched_gr->SetLineStyle(2);
      if(i==0){
        Unmatched_gr->GetXaxis()->SetTitle(xtitle.at(j));
        Unmatched_gr->GetYaxis()->SetTitle("Fake per GEMMuon");
        Unmatched_gr->Draw("alp");
        double fake_min(0.00001), fake_max(0.01);
        if(this_var=="Pt"){
          fake_min = 0.01;
          fake_max = 10.;
        }
        else if(this_var=="Phi"){
          fake_min = 0.0001;
        }
        Unmatched_gr->GetYaxis()->SetRangeUser(fake_min, fake_max);
        if(this_var=="Eta") Unmatched_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
        if(this_var=="Pt") Unmatched_gr->GetXaxis()->SetRangeUser(0., 100.);
      }
      else Unmatched_gr->Draw("lpsame");
      
    }
    
    c_eff->cd();
    lg_eff.Draw();
    c_eff->SaveAs(plotpath+"gran_eff_"+this_var+".png");
    c_eff->Close();
    delete c_eff;

    c_fake->cd();
    lg_fake.Draw();
    gPad->SetLogy(1);
    c_fake->SaveAs(plotpath+"gran_fake_"+this_var+".png");
    gPad->SetLogy(0);
    c_fake->Close();
    delete c_fake;
    
    
  }
  
  
  
  
  
}
