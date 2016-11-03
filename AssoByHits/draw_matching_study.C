#include "../include/setTDRStyle.C"
#include "../include/mylib.h"

std::string DoubleToString(double dd);
void fillmaxmin(double& max, double& min, TString cutvar, TString var);

void draw_matching_study(){
  setTDRStyle();
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2(true);

  vector<TString> cutvar = {"PullX", "DX", "PullY", "DY", "DotDir"};
  vector<TString> legend_prefix = {"#DeltaX/#sigma_{X} < ", "#DeltaX < ", "#DeltaY/#sigma_{Y} < ", "#DeltaY < ", "DotDir > "};
  vector<TString> legend_prefix_roc = {"Pull x: #DeltaX/#sigma_{X}", "Dist. x: #DeltaX", "Pull y: #DeltaY/#sigma_{Y}", "Dist. y: #DeltaY", "DotDir"};
  
  vector<TString> var = {"Pt", "Eta", "Phi"};
  vector<TString> xtitle = {"p_{T} [GeV]", "|#eta|", "#phi"};
  
  vector<Color_t> colors_X = {kBlack, kRed, kGreen, kBlue, kYellow-3, kOrange};
  vector<Color_t> colors_DY = {kBlack, kRed, kGreen, kBlue, kYellow-3, kRed-5, kOrange};
  vector<Color_t> colors_PullY = {kBlack, kRed, kGreen, kBlue, kRed-5, kRed+1, kYellow-3, kOrange};
  vector<Color_t> colors_DotDir = {kBlack, kRed, kYellow-3, kOrange};
  vector<Color_t> colors_roc = {kBlack, kRed, kBlue, kMagenta, kOrange, kBlack};
  
  TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre15/OUTPUT_Matching_RelValTenMuExtendedE_0_200_PU0.root");
  TString plotpath = "./plots/CMSSW_8_1_0_pre15/Matching_0PU/";

  gSystem->mkdir(plotpath, kTRUE);

  TCanvas *c_roc = new TCanvas("c_roc", "", 1000, 1000);
  c_roc->cd();
  TH1F *dummy = new TH1F("dummy", "", 1, 0, 1);
  dummy->SetMinimum(0.6);
  dummy->SetMaximum(1.);
  dummy->Draw("histsame");
  dummy->GetXaxis()->SetTitle("Efficiency");
  dummy->GetYaxis()->SetTitle("Fake per GEMMuon");
  
  TLegend lg_roc(0.77, 0.15, 0.92, 0.40);
  lg_roc.SetBorderSize(0);
  
  //==== which Cut Variable (PullX, DX, PullY, DY)
  for(unsigned int aaa=0; aaa<cutvar.size(); aaa++){
    TString this_cutvar = cutvar.at(aaa);
    //cout << "Cut Variable = " << this_cutvar << endl;
    TH1F *hist_cutvar = (TH1F*)file->Get(this_cutvar+"Values");

    //==== Which Kinematic Variable (Pt, Eta, Phi)
    for(unsigned int bbb=0; bbb<var.size(); bbb++){
      TString this_var = var.at(bbb);
      //cout << "  var = " << this_var << endl;
      
      TCanvas *c_eff = new TCanvas("c_eff", "", 1000, 1000);
      TCanvas *c_fake = new TCanvas("c_fake", "", 1000, 1000);
      
      TLegend lg_down(0.78, 0.15, 0.93, 0.50);
      lg_down.SetBorderSize(0);
      TLegend lg_up(0.78, 0.55, 0.93, 0.90);
      lg_up.SetBorderSize(0);
      TLegend lg_down_short(0.70, 0.15, 0.93, 0.40);
      lg_down_short.SetBorderSize(0);
      TLegend lg_up_short(0.70, 0.65, 0.93, 0.90);
      lg_up_short.SetBorderSize(0);
 
      //==== Cut crieria (0, 0.1, 0.2, ...)
      unsigned int n_cutvar_values = hist_cutvar->GetXaxis()->GetNbins();
      for(unsigned int ccc=0; ccc<n_cutvar_values; ccc++){
        int ddd = (n_cutvar_values-1)-ccc;
        double this_cutvar_value = hist_cutvar->GetBinContent(ddd+1);
        
        TString s_value = DoubleToString(this_cutvar_value);
        //cout << "  value = " << this_cutvar_value << endl;

        //==== Efficiency
        c_eff->cd();
        TEfficiency *this_eff = (TEfficiency*)file->Get("HitsEff_"+this_cutvar+"_"+this_var+"_"+s_value);
        TGraph *this_gr = this_eff->CreateGraph();
        Color_t thiscolor;
        if(this_cutvar == "PullX" || this_cutvar == "DX") thiscolor = colors_X.at(ccc);
        else if(this_cutvar == "PullY") thiscolor = colors_PullY.at(ccc);
        else if(this_cutvar == "DY") thiscolor = colors_DY.at(ccc);
        else if(this_cutvar == "DotDir") thiscolor = colors_DotDir.at(ccc);
        this_gr->SetLineColor(thiscolor);
        this_gr->SetLineWidth(2);
        this_gr->SetMarkerStyle(21);
        this_gr->SetMarkerColor(thiscolor);
        this_gr->SetMarkerSize(1);
        this_gr->GetXaxis()->SetTitle(xtitle.at(bbb));
        this_gr->GetYaxis()->SetTitle("Efficiency");
        if(ccc==0){
          this_gr->Draw("alp");
          this_gr->GetYaxis()->SetRangeUser(0, 1.2);
          if(this_var=="Eta") this_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") this_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else this_gr->Draw("lpsame");
        lg_down.AddEntry(this_gr, legend_prefix.at(aaa)+s_value, "l");
        lg_down_short.AddEntry(this_gr, legend_prefix.at(aaa)+s_value, "l");
        
        //==== Fake
        c_fake->cd();
        TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatched"+this_cutvar+"_"+this_var+"_"+s_value)->Clone();
        TH1F *total;
        if(this_var=="Pt") total = (TH1F*)file->Get("N_GEMMuon_"+this_cutvar+"_h_"+s_value);
        else total = (TH1F*)file->Get("N_GEMMuon_ptcut_"+this_cutvar+"_h_"+s_value);
        double n_total = total->GetBinContent(1);
        Unmatched->Scale(1./n_total);
        TGraphAsymmErrors *Unmatched_gr;
        if(this_var=="Eta") Unmatched_gr = hist_to_graph(Unmatched, true);
        else Unmatched_gr = hist_to_graph(Unmatched);
        Unmatched_gr->SetLineColor(thiscolor);
        Unmatched_gr->SetLineWidth(2);
        Unmatched_gr->SetMarkerStyle(21);
        Unmatched_gr->SetMarkerColor(thiscolor);
        Unmatched_gr->SetMarkerSize(1);
        Unmatched_gr->SetTitle("");
        if(ccc==0){
          Unmatched_gr->GetXaxis()->SetTitle(xtitle.at(bbb));
          Unmatched_gr->GetYaxis()->SetTitle("Fake per GEMMuon");
          Unmatched_gr->Draw("alp");
          double thismax, thismin;
          fillmaxmin(thismax, thismin, this_cutvar, this_var);
          //cout << "    Max = " << thismax << ", Min = " << thismin << endl;
          Unmatched_gr->GetYaxis()->SetRangeUser(thismin, thismax);
          if(this_var=="Eta") Unmatched_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") Unmatched_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else Unmatched_gr->Draw("lpsame");
        lg_up.AddEntry(Unmatched_gr, legend_prefix.at(aaa)+s_value, "l");
        lg_up_short.AddEntry(Unmatched_gr, legend_prefix.at(aaa)+s_value, "l");
      }
      
      c_eff->cd();
      if(this_cutvar=="DotDir") lg_down_short.Draw();
      else lg_down.Draw();
      c_eff->SaveAs(plotpath+"Eff_"+this_cutvar+"_"+this_var+".png");
      c_eff->Close();
      delete c_eff;
      
      c_fake->cd();
      if(this_cutvar=="DotDir"){
        if(this_var=="Pt") lg_up_short.Draw();
        else lg_down_short.Draw();
      }
      else{
        if(this_var=="Pt") lg_up.Draw();
        else lg_down.Draw();
      }
      gPad->SetLogy(1);
      c_fake->SaveAs(plotpath+"Fake_"+this_cutvar+"_"+this_var+".png");
      gPad->SetLogy(0);
      c_fake->Close();
      delete c_fake;
  
    } // END of Kinematic variable loop
    
    //==========
    //==== ROC
    //==========
    
    unsigned int n_cutvar_values = hist_cutvar->GetXaxis()->GetNbins();
    double effs[n_cutvar_values], fakes[n_cutvar_values];
    
    //==== Cut crieria (0, 0.1, 0.2, ...)
    for(unsigned int ccc=0; ccc<n_cutvar_values; ccc++){
      double this_cutvar_value = hist_cutvar->GetBinContent(ccc+1);
      TString s_value = DoubleToString(this_cutvar_value);
      //cout << "  value = " << this_cutvar_value << endl;
      
      TH1F *tp = (TH1F*)file->Get("TPMuon_Eta");
      TH1F *Matched = (TH1F*)file->Get("HitsMatched"+this_cutvar+"_Eta_"+s_value);
      TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatched"+this_cutvar+"_Eta_"+s_value)->Clone();
      TH1F *total = (TH1F*)file->Get("N_GEMMuon_ptcut_"+this_cutvar+"_h_"+s_value);
      double n_total = total->GetBinContent(1);

      effs[ccc] = (Matched->Integral())/(tp->Integral());
      fakes[ccc] = (Unmatched->Integral())/(n_total);
      //cout << "=================" << endl;
      //cout << "Matched->Integral() = " << (Matched->Integral()) << endl;
      //cout << "tp->Integral() = " << tp->Integral() << endl;
      //cout << "Unmatched->Integral() = " << Unmatched->Integral() << endl;
      //cout << "Eff = " << effs[ccc] << ", Fake = " << fakes[ccc] << endl;
    }
    
    c_roc->cd();
    TGraph* gr_roc = new TGraph(n_cutvar_values, effs, fakes);
    gr_roc->SetName(this_cutvar);
    gr_roc->SetMarkerStyle(21);
    gr_roc->SetMarkerColor(colors_roc.at(aaa));
    //gr_roc->GetYaxis()->SetRangeUser(0.00001, 1.0);
    gr_roc->SetLineColor(colors_roc.at(aaa));
    gr_roc->SetLineWidth(2);
    gr_roc->SetMarkerSize(1);
    gr_roc->Draw("lpsame");
    lg_roc.AddEntry(gr_roc, legend_prefix_roc.at(aaa), "l");
    
  } // END of Cut Variable loop

  c_roc->cd();
  lg_roc.Draw();
  //gPad->SetLogy();
  c_roc->SaveAs(plotpath+"ROC.png");
  c_roc->Close();
  delete c_roc;
  

}

std::string DoubleToString(double dd){
  std::ostringstream os;
  os << dd;
  return os.str();
}

void fillmaxmin(double& max, double& min, TString cutvar, TString var){
  
  //"PullX", "DX", "PullY", "DY", "DotDir"
  //"Pt", "Eta", "Phi"
  if(cutvar=="PullX"){
    if(var=="Eta"){
      max = 1.;
      min = 0.01;
    }
    else if(var=="Phi"){
      max = 1.;
      min = 0.001;
    }
    else if(var=="Pt"){
      max = 1.;
      min = 0.0001;
    }
    else{
      max = 1.;
      min = 0.00001;
    }
  }
  else if(cutvar=="DX"){
    if(var=="Eta"){
      max = 1.;
      min = 0.01;
    }
    else if(var=="Phi"){
      max = 1.;
      min = 0.001;
    }
    else if(var=="Pt"){
      max = 1.;
      min = 0.0001;
    }
    else{
      max = 1.;
      min = 0.00001;
    }
  }
  else if(cutvar=="PullY"){
    if(var=="Eta"){
      max = 1.;
      min = 0.01;
    }
    else if(var=="Phi"){
      max = 1.;
      min = 0.001;
    }
    else if(var=="Pt"){
      max = 1.;
      min = 0.00001;
    }
    else{
      max = 1.;
      min = 0.00001;
    }
  }
  else if(cutvar=="DY"){
    if(var=="Eta"){
      max = 1.;
      min = 0.01;
    }
    else if(var=="Phi"){
      max = 1.;
      min = 0.001;
    }
    else if(var=="Pt"){
      max = 1.;
      min = 0.00001;
    }
    else{
      max = 1.;
      min = 0.00001;
    }
  }
  else if(cutvar=="DotDir"){
    if(var=="Eta"){
      max = 1.;
      min = 0.01;
    }
    else if(var=="Phi"){
      max = 1.;
      min = 0.001;
    }
    else if(var=="Pt"){
      max = 1.;
      min = 0.000001;
    }
    else{
      max = 1.;
      min = 0.00001;
    }
  }
  else{
    max = 1.;
    min = 0.00001;
  }
}
