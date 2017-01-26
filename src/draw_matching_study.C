#include "setTDRStyle.C"
#include "mylib.h"

std::string DoubleToString(double dd);
void fillmaxmin(double& max, double& min, TString cutvar, TString var);

void draw_matching_study(int sampletype=0){
  
  TString sample;
  if(sampletype==0) sample = "RelValZMM_14";
  else if(sampletype==1) sample = "RelValZEE_14";
  else if(sampletype==2) sample = "RelValTenMuExtendedE_0_200";
  else{
    sample = "RelValZMM_14";
  }
  
  setTDRStyle();
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2(true);

  vector<TString> cutvar = {"PullX", "DX", "PullY", "DY", "DotDir"};
  vector<TString> legend_prefix = {"#DeltaX/#sigma_{X} < ", "#DeltaX < ", "#DeltaY/#sigma_{Y} < ", "#DeltaY < ", "DotDir > "};
  vector<TString> legend_prefix_roc = {"Pull x: #DeltaX/#sigma_{X}", "Dist. x: #DeltaX", "Pull y: #DeltaY/#sigma_{Y}", "Dist. y: #DeltaY", "DotDir"};
  
  vector<TString> var = {"Pt", "Eta", "Phi"};
  vector<TString> xtitle = {"p_{T} [GeV]", "|#eta|", "#phi"};
  
  vector<Color_t> colors_PullX = {kBlack, kRed, kGreen, kBlue, kYellow-3, kRed-5, kOrange};
  vector<Color_t> colors_DX = {kBlack, kRed, kGreen, kBlue, kOrange};
  vector<Color_t> colors_PullY = {kBlack, kRed, kGreen, kBlue, kRed-5, kRed+1, kYellow-3, kOrange};
  vector<Color_t> colors_DY = {kBlack, kRed, kGreen, kBlue, kYellow-3, kRed-5, kOrange};
  vector<Color_t> colors_DotDir = {kBlack, kRed, kYellow-3, kOrange};
  
  vector<Color_t> colors_roc = {kBlack, kRed, kBlue, kMagenta, kOrange, kBlack};
  
  TString cmssw_version = getenv("CMSSW_RELEASE");
  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString filepath = WORKING_DIR+"/rootfiles/"+cmssw_version+"/";
  TString plotpath = WORKING_DIR+"/plots/"+cmssw_version+"/"+sample+"/Matching_PU200/";
  
  TFile *file = new TFile(filepath+"/"+sample+"_PU200_Matching.root");
  
  TH1F *Nevents_h = (TH1F*)file->Get("Nevents_h")->Clone();
  double n_events = Nevents_h->GetBinContent(2);

  gSystem->mkdir(plotpath, kTRUE);

  
  //======================================
  //==== Eff/Fake for each cut variables
  //======================================
  
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
        //cout << "    value = " << this_cutvar_value << endl;

        //==== Efficiency
        //cout << "  Drawing Eff plot" << endl;
        c_eff->cd();
        TEfficiency *this_eff = (TEfficiency*)file->Get("HitsEff_"+this_cutvar+"_"+this_var+"_"+s_value);
        TGraphAsymmErrors *this_gr_tmp = this_eff->CreateGraph();
        TGraphAsymmErrors *this_gr;
        if(this_var=="Eta") this_gr = hist_to_graph(this_gr_tmp, 1.6, 2.4, true);
        else this_gr = hist_to_graph(this_gr_tmp, -9999, 9999, true);
        Color_t thiscolor;
        if(this_cutvar == "PullX") thiscolor = colors_PullX.at(ccc);
        else if(this_cutvar == "DX") thiscolor = colors_DX.at(ccc);
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
        //cout << "  Drawing Fake plot" << endl;
        c_fake->cd();
        TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatched"+this_cutvar+"_"+this_var+"_"+s_value)->Clone();
        for(unsigned int it_bin=1; it_bin<=Unmatched->GetXaxis()->GetNbins(); it_bin++){
          Unmatched->SetBinContent( it_bin, Unmatched->GetBinContent(it_bin)/n_events );
          Unmatched->SetBinError( it_bin, Unmatched->GetBinError(it_bin)/n_events );
        }
        //Unmatched->Scale(1./n_events);
        TGraphAsymmErrors *Unmatched_gr;
        if(this_var=="Eta") Unmatched_gr = hist_to_graph(Unmatched, 1.6, 2.4, true);
        else if(this_var=="Pt") Unmatched_gr = hist_to_graph(Unmatched, 0., 10., true);
        else Unmatched_gr = hist_to_graph(Unmatched, -9999, 9999, true);
        Unmatched_gr->SetLineColor(thiscolor);
        Unmatched_gr->SetLineWidth(2);
        Unmatched_gr->SetMarkerStyle(21);
        Unmatched_gr->SetMarkerColor(thiscolor);
        Unmatched_gr->SetMarkerSize(1);
        Unmatched_gr->SetTitle("");
        if(ccc==0){
          Unmatched_gr->GetXaxis()->SetTitle(xtitle.at(bbb));
          Unmatched_gr->GetYaxis()->SetTitle("Fake per Event");
          Unmatched_gr->Draw("alp");
          double thismax, thismin;
          fillmaxmin(thismax, thismin, this_cutvar, this_var);
          //cout << "    Max = " << thismax << ", Min = " << thismin << endl;
          Unmatched_gr->GetYaxis()->SetRangeUser(0., thismax);
          //Unmatched_gr->GetYaxis()->SetRangeUser(0, 1.2);
          if(this_var=="Eta") Unmatched_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") Unmatched_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else Unmatched_gr->Draw("lpsame");
        lg_up.AddEntry(Unmatched_gr, legend_prefix.at(aaa)+s_value, "l");
        lg_up_short.AddEntry(Unmatched_gr, legend_prefix.at(aaa)+s_value, "l");
      }
      
      //cout << "  Saving Eff plot" << endl;
      c_eff->cd();
      if(this_cutvar=="DotDir") lg_down_short.Draw();
      else lg_down.Draw();
      c_eff->SaveAs(plotpath+"Eff_"+this_cutvar+"_"+this_var+".png");
      c_eff->Close();
      delete c_eff;
      
      //cout << "  Saving Fake plot" << endl;
      c_fake->cd();
      if(this_cutvar=="DotDir"){
        if(this_var=="Pt") lg_up_short.Draw();
        else lg_down_short.Draw();
      }
      else{
        if(this_var=="Pt") lg_up.Draw();
        else lg_down.Draw();
      }
      //gPad->SetLogy(1);
      c_fake->SaveAs(plotpath+"Fake_"+this_cutvar+"_"+this_var+".png");
      //gPad->SetLogy(0);
      c_fake->Close();
      delete c_fake;
  
      //cout << "  Done" << endl;
      
    } // END of Kinematic variable loop
    
  } // END of Cut Variable loop
  
  //==========
  //==== ROC
  //==========
  
  //cout << "#### ROC ####" << endl;
  
  //==== Which Kinematic Variable (Pt, Eta, Phi)
  for(unsigned int bbb=0; bbb<var.size(); bbb++){
    TString this_var = var.at(bbb);
    //cout << "  var = " << this_var << endl;

    TCanvas *c_roc = new TCanvas("c_roc", "", 1000, 1000);
    c_roc->cd();
    TH1F *dummy = new TH1F("dummy", "", 1, 0, 1);
    dummy->SetMinimum(0.);
    if(this_var == "Eta") dummy->SetMaximum(2.);
    else if(this_var == "Pt") dummy->SetMaximum(200.);
    else if(this_var == "Phi") dummy->SetMaximum(2.);
    else{}
    dummy->Draw("histsame");
    dummy->GetXaxis()->SetTitle("Efficiency");
    dummy->GetYaxis()->SetTitle("Fake per Event");
    
    //TLegend lg_roc(0.77, 0.15, 0.92, 0.40);
    TLegend lg_roc(0.17, 0.15, 0.32, 0.40);
    lg_roc.SetBorderSize(0);
    
    //==== which Cut Variable (PullX, DX, PullY, DY)
    for(unsigned int aaa=0; aaa<cutvar.size(); aaa++){
      TString this_cutvar = cutvar.at(aaa);
      //cout << "Cut Variable = " << this_cutvar << endl;
      TH1F *hist_cutvar = (TH1F*)file->Get(this_cutvar+"Values");
      
      unsigned int n_cutvar_values = hist_cutvar->GetXaxis()->GetNbins();
      double effs[n_cutvar_values], fakes[n_cutvar_values];
      
      //==== Cut crieria (0, 0.1, 0.2, ...)
      for(unsigned int ccc=0; ccc<n_cutvar_values; ccc++){
        double this_cutvar_value = hist_cutvar->GetBinContent(ccc+1);
        TString s_value = DoubleToString(this_cutvar_value);
        //cout << "  value = " << this_cutvar_value << endl;
        
        TH1F *tp = (TH1F*)file->Get("TPMuon_"+this_var);
        TH1F *Matched = (TH1F*)file->Get("HitsMatched"+this_cutvar+"_"+this_var+"_"+s_value);
        TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatched"+this_cutvar+"_"+this_var+"_"+s_value)->Clone();
        
        effs[ccc] = (Matched->Integral())/(tp->Integral());
        fakes[ccc] = (Unmatched->Integral())/(n_events);
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
      gr_roc->SetLineColor(colors_roc.at(aaa));
      gr_roc->SetLineWidth(2);
      gr_roc->SetMarkerSize(1);
      gr_roc->Draw("lpsame");
      lg_roc.AddEntry(gr_roc, legend_prefix_roc.at(aaa), "l");
      
    }
    
    c_roc->cd();
    lg_roc.Draw();
    //gPad->SetLogy();
    c_roc->SaveAs(plotpath+"/ROC_"+this_var+".png");
    c_roc->Close();
    delete c_roc;
    delete dummy;
    
    
  }

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
      max = 0.3;
      min = 0.1;
    }
    else if(var=="Phi"){
      max = 0.07;
      min = 0.01;
    }
    else if(var=="Pt"){
      max = 130.;
      min = 0.001;
    }
    else{
      max = 10.;
      min = 0.0001;
    }
  }
  else if(cutvar=="DX"){
    if(var=="Eta"){
      max = 0.3;
      min = 0.1;
    }
    else if(var=="Phi"){
      max = 0.07;
      min = 0.01;
    }
    else if(var=="Pt"){
      max = 130.;
      min = 0.001;
    }
    else{
      max = 10.;
      min = 0.0001;
    }
  }
  else if(cutvar=="PullY"){
    if(var=="Eta"){
      max = 0.3;
      min = 0.1;
    }
    else if(var=="Phi"){
      max = 0.06;
      min = 0.01;
    }
    else if(var=="Pt"){
      max = 130.;
      min = 0.0001;
    }
    else{
      max = 10.;
      min = 0.0001;
    }
  }
  else if(cutvar=="DY"){
    if(var=="Eta"){
      max = 0.1;
      min = 0.1;
    }
    else if(var=="Phi"){
      max = 0.03;
      min = 0.01;
    }
    else if(var=="Pt"){
      max = 80.;
      min = 0.0001;
    }
    else{
      max = 10.;
      min = 0.0001;
    }
  }
  else if(cutvar=="DotDir"){
    if(var=="Eta"){
      max = 0.3;
      min = 0.1;
    }
    else if(var=="Phi"){
      max = 0.07;
      min = 0.01;
    }
    else if(var=="Pt"){
      max = 130.;
      min = 0.00001;
    }
    else{
      max = 10.;
      min = 0.0001;
    }
  }
  else{
    max = 10.;
    min = 0.0001;
  }
}
