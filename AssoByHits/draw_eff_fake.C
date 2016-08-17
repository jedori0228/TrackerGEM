#include "../include/canvas_margin.h"

std::string DoubleToString(std::string prefix, double dd);

void draw_eff_fake(int xxx=1){
  
  //==== xxx = 0 : use MuonGun(0PU) and MinBias
  //==== xxx = 1 : use MuonGun(140PU)
  
  
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2(true);
  
  TFile *file_MuonGun;
  TFile *file_MinBias;
  TFile *file_output;
  
  TString plotpath = "./plots/";
  
  if(xxx==0){
    file_MuonGun = new TFile("./rootfiles/OUTPUTTEMPLAT_0PU_dBunchX_1.root");
    file_MinBias = new TFile("./rootfiles/OUTPUTTEMPLATE_MinBias.root");
    plotpath = "./plots/MuonGun_0PU_and_MinBias/";
  }
  if(xxx==1){
    file_MuonGun = new TFile("./rootfiles/CMSSW_8_1_0_pre9/OUTPUT_RelValTenMuE_0_200_2023tiltedPU200.root");
    file_MinBias = new TFile("./rootfiles/CMSSW_8_1_0_pre9/OUTPUT_RelValTenMuE_0_200_2023tiltedPU200.root");
    plotpath = "plots/CMSSW_8_1_0_pre9/RelValTenMuE_0_200_2023tiltedPU200/";
  }
  
  gSystem->mkdir(plotpath, kTRUE);
  file_output = new TFile(plotpath+"hists.root", "RECREATE");
  
  
  //======================
  //==== Scattered plots
  //======================
  
  TString obj[2] = {"GEMRecHit", "GEMSegment"};
  TString stations[2] = {"GE11", "GE21"};
  TString coordi[4] = {"GlobalPosition_scattered", "LocalPosition_scattered", "odd_XZplane", "even_XZplane"};
  for(int i=0; i<2; i++){
    for(int j=0; j<2; j++){
      for(int k=0; k<4; k++){
        //cout << obj[i]+"_"+stations[j]+"_"+coordi[j]+"_scattered" << endl;
        if(obj[i]=="GEMSegment" && k>=2) continue;
        TH2F *hist_scattered = (TH2F*)file_MuonGun->Get(obj[i]+"_"+stations[j]+"_"+coordi[k]);
        TCanvas *c_scattered = new TCanvas("c_scattered", "", 800, 600);
        c_scattered->cd();
        hist_scattered->Draw();
        hist_scattered->SetTitle(obj[i]+" "+stations[j]+" "+coordi[k]);
        c_scattered->SaveAs(plotpath+obj[i]+"_"+stations[j]+"_"+coordi[k]+".png");
        file_output->cd();
        hist_scattered->Write();
        c_scattered->Close();
        delete c_scattered;
      }
    }
  }
  
  //======================================
  //==== Eff by gen-reco deltaR matching
  //======================================
  
  vector<TString> MuonObjectType_deltaR = {"GEMMuon", "RecoMuon", "NotGEMMuon", "NotGEMMuon_no_gemseg", "GEMRecHit", "GEMSegment"};
  vector<TString> var_deltaR = {"Pt", "Eta", "Phi"};
  vector<TString> xtitle_deltaR = {"p_{T}", "|#eta|", "#phi"};
  
  for(unsigned int i=0; i<var_deltaR.size(); i++){
    TString this_var = var_deltaR.at(i);
    TString this_xtitle = xtitle_deltaR.at(i);
    
    //==== GenMuon(=Denominator)
    TH1F *GenMuon = (TH1F*)file_MuonGun->Get("GenMuon_"+this_var);
    TCanvas *c_GenMuon = new TCanvas("c_GenMuon_"+this_var, "", 800, 600);
    canvas_margin(c_GenMuon);
    c_GenMuon->cd();
    GenMuon->Draw("");
    GenMuon->SetTitle("GenMuon "+this_xtitle);
    GenMuon->GetXaxis()->SetTitle(this_xtitle);
    c_GenMuon->SaveAs(plotpath+"GenMuon_"+this_var+".png");
    file_output->cd();
    GenMuon->Write();
    c_GenMuon->Close();
    delete c_GenMuon;
    
    //==== Efficiencies
    for(unsigned int i=0; i<MuonObjectType_deltaR.size(); i++){
      TString this_MuonObjectType_deltaR = MuonObjectType_deltaR.at(i);
      
      TEfficiency *Eff = (TEfficiency *)file_MuonGun->Get("Eff_"+this_MuonObjectType_deltaR+"_"+this_var);
      TGraph *gr_Eff = Eff->CreateGraph();
      gr_Eff->SetName("Eff_"+this_MuonObjectType_deltaR+"_"+this_var);
      
      TCanvas* c_Eff = new TCanvas("c_Eff_"+this_var, "", 800, 600);
      canvas_margin(c_Eff);
      c_Eff->cd();
      gr_Eff->Draw("ap");
      gr_Eff->GetYaxis()->SetRangeUser(0, 1.2);
      gr_Eff->GetXaxis()->SetTitle(this_xtitle);
      c_Eff->SaveAs(plotpath+"Eff_"+this_MuonObjectType_deltaR+"_"+this_var+".png");
      file_output->cd();
      gr_Eff->Write();
      c_Eff->Close();
    }
    
  }
  
  //========================
  //==== Eff by AssoByHits
  //========================
  
  vector<TString> MuonObjectType_hits = {"GEMMuon", "RecoMuon", "LooseMuon", "MediumMuon", "TightMuon"};
  vector<TString> var_hits = {"Pt", "Eta", "Phi"};
  vector<TString> xtitle_hits = {"p_{T}", "|#eta|", "#phi"};
  
  for(unsigned int i=0; i<var_hits.size(); i++){
    TString this_var = var_hits.at(i);
    TString this_xtitle = xtitle_hits.at(i);
    
    //==== Tracking Particle Muon(=Denominator)
    TH1F *TPMuon = (TH1F*)file_MuonGun->Get("TPMuon_"+this_var);
    TCanvas *c_TPMuon = new TCanvas("c_TPMuon_"+this_var, "", 800, 600);
    canvas_margin(c_TPMuon);
    c_TPMuon->cd();
    TPMuon->Draw("");
    TPMuon->SetTitle("TPMuon "+this_xtitle);
    TPMuon->GetXaxis()->SetTitle(this_xtitle);
    c_TPMuon->SaveAs(plotpath+"TPMuon_"+this_var+".png");
    file_output->cd();
    TPMuon->Write();
    c_TPMuon->Close();
    delete c_TPMuon;
    
    //==== Efficiencies
    for(unsigned int i=0; i<MuonObjectType_hits.size(); i++){
      TString this_MuonObjectType_hits = MuonObjectType_hits.at(i);
      
      TEfficiency *Eff = (TEfficiency *)file_MuonGun->Get("HitsEff_"+this_MuonObjectType_hits+"_"+this_var);
      TGraph *gr_Eff = Eff->CreateGraph();
      gr_Eff->SetName("HitsEff_"+this_MuonObjectType_hits+"_"+this_var);
      
      TCanvas* c_Eff = new TCanvas("c_HitsEff_"+this_var, "", 800, 600);
      canvas_margin(c_Eff);
      c_Eff->cd();
      gr_Eff->Draw("ap");
      gr_Eff->GetYaxis()->SetRangeUser(0, 1.2);
      gr_Eff->GetXaxis()->SetTitle(this_xtitle);
      c_Eff->SaveAs(plotpath+"HitsEff_"+this_MuonObjectType_hits+"_"+this_var+".png");
      file_output->cd();
      gr_Eff->Write();
      c_Eff->Close();
    }
    
  }
  
  //===========
  //==== Fake
  //===========
  
  TH1F* Nevents_h = (TH1F*)file_MinBias->Get("Nevents_h");
  int Nevents = Nevents_h->GetBinContent(2);
  
  for(unsigned int i=0; i<var_hits.size(); i++){
    TString this_var = var_hits.at(i);
    TString this_xtitle = xtitle_hits.at(i);
  
    TH1F *HitsUnmatchedGEMMuon = (TH1F *)file_MinBias->Get("HitsUnmatchedGEMMuon_"+this_var);
    TCanvas *c_HitsUnmatchedGEMMuon = new TCanvas("HitsUnmatchedGEMMuon_"+this_var, "", 800, 600);
    canvas_margin(c_HitsUnmatchedGEMMuon);
    c_HitsUnmatchedGEMMuon->cd();
    HitsUnmatchedGEMMuon->Draw("");
    HitsUnmatchedGEMMuon->SetTitle(TString::Itoa(Nevents/1000., 10)+"k MinBias Events");
    HitsUnmatchedGEMMuon->SetXTitle(this_xtitle);
    gPad->SetLogy();
    c_HitsUnmatchedGEMMuon->SaveAs(plotpath+"HitsUnmatchedGEMMuon_"+this_var+".png");
    HitsUnmatchedGEMMuon->Scale(1./Nevents);
    HitsUnmatchedGEMMuon->Draw("");
    c_HitsUnmatchedGEMMuon->SaveAs(plotpath+"HitsUnmatchedGEMMuon_"+this_var+"_per_event.png");
    file_output->cd();
    c_HitsUnmatchedGEMMuon->Write();
    gPad->SetLogy(kFALSE);
    c_HitsUnmatchedGEMMuon->Close();
    delete c_HitsUnmatchedGEMMuon;
  }
  
  //======================================
  //==== Matching Variable Distributions
  //======================================
  
  TString var_Matching[5] = {"DelX", "DelX_over_sigma", "DelY", "DelY_over_sigma", "DotDir"};
  
  for(int i=0; i<5; i++){
    for(int j=0; j<2; j++){
      TH1F *hist_matching_var = (TH1F*)file_MuonGun->Get(var_Matching[i]+"_"+stations[j]);
      TCanvas *c_matching_var = new TCanvas("c_matching_var", "", 800, 600);
      c_matching_var->cd();
      hist_matching_var->Draw();
      hist_matching_var->SetMinimum(0);
      hist_matching_var->SetTitle(var_Matching[i]+"_"+stations[j]);
      c_matching_var->SaveAs(plotpath+var_Matching[i]+"_"+stations[j]+".png");
      file_output->cd();
      hist_matching_var->Write();
      c_matching_var->Close();
      delete c_matching_var;
    }
  }
  
  //===================================
  //==== matching eff/rejection study
  //===================================
  
  if(xxx==1) return;
  
  TH1F* maxPull_values = (TH1F*)file_MuonGun->Get("maxPull_values");
  TH1F* maxX_GE11_values = (TH1F*)file_MuonGun->Get("maxX_GE11_values");
  TH1F* maxY_GE11_values = (TH1F*)file_MuonGun->Get("maxY_GE11_values");
  TH1F* maxX_GE21_values = (TH1F*)file_MuonGun->Get("maxX_GE21_values");
  TH1F* maxY_GE21_values = (TH1F*)file_MuonGun->Get("maxY_GE21_values");
  TH1F* minDotDir_values = (TH1F*)file_MuonGun->Get("minDotDir_values");
  
  vector<double> maxPull, maxX_GE11, maxY_GE11, maxX_GE21, maxY_GE21, minDotDir;
  for(int i=1; i<=50; i++){
    if(maxPull_values->GetBinContent(i) != 0) maxPull.push_back( maxPull_values->GetBinContent(i) );
    if(maxX_GE11_values->GetBinContent(i) != 0) maxX_GE11.push_back( maxX_GE11_values->GetBinContent(i) );
    if(maxY_GE11_values->GetBinContent(i) != 0) maxY_GE11.push_back( maxY_GE11_values->GetBinContent(i) );
    if(maxX_GE21_values->GetBinContent(i) != 0) maxX_GE21.push_back( maxX_GE21_values->GetBinContent(i) );
    if(maxY_GE21_values->GetBinContent(i) != 0) maxY_GE21.push_back( maxY_GE21_values->GetBinContent(i) );
    if(minDotDir_values->GetBinContent(i) != 0) minDotDir.push_back( minDotDir_values->GetBinContent(i) );
  }
  
  //==== Pull plots
  
  const int n_maxPull = maxPull.size();
  double eff_maxXPull_GE11[n_maxPull], mis_maxXPull_GE11[n_maxPull];
  double eff_maxYPull_GE11[n_maxPull], mis_maxYPull_GE11[n_maxPull];
  double eff_maxXPull_GE21[n_maxPull], mis_maxXPull_GE21[n_maxPull];
  double eff_maxYPull_GE21[n_maxPull], mis_maxYPull_GE21[n_maxPull];
  for(int aaa=0; aaa<n_maxPull; aaa++){
    //cout << DoubleToString("maxXPull_GE11", maxPull.at(aaa)).data() << endl;
    TH1F* h_maxXPull_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxXPull_GE11", maxPull.at(aaa)).data());
    TH1F* h_maxXPull_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxXPull_GE11", maxPull.at(aaa)).data());
    eff_maxXPull_GE11[aaa] = h_maxXPull_GE11_MuonGun->GetMean();
    mis_maxXPull_GE11[aaa] = h_maxXPull_GE11_MinBias->GetMean();
    TH1F* h_maxYPull_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxYPull_GE11", maxPull.at(aaa)).data());
    TH1F* h_maxYPull_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxYPull_GE11", maxPull.at(aaa)).data());
    eff_maxYPull_GE11[aaa] = h_maxYPull_GE11_MuonGun->GetMean();
    mis_maxYPull_GE11[aaa] = h_maxYPull_GE11_MinBias->GetMean();
    TH1F* h_maxXPull_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxXPull_GE21", maxPull.at(aaa)).data());
    TH1F* h_maxXPull_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxXPull_GE21", maxPull.at(aaa)).data());
    eff_maxXPull_GE21[aaa] = h_maxXPull_GE21_MuonGun->GetMean();
    mis_maxXPull_GE21[aaa] = h_maxXPull_GE21_MinBias->GetMean();
    TH1F* h_maxYPull_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxYPull_GE21", maxPull.at(aaa)).data());
    TH1F* h_maxYPull_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxYPull_GE21", maxPull.at(aaa)).data());
    eff_maxYPull_GE21[aaa] = h_maxYPull_GE21_MuonGun->GetMean();
    mis_maxYPull_GE21[aaa] = h_maxYPull_GE21_MinBias->GetMean();
  }

  TGraph* gr_maxXPull_GE11 = new TGraph(n_maxPull, eff_maxXPull_GE11, mis_maxXPull_GE11);
  TGraph* gr_maxYPull_GE11 = new TGraph(n_maxPull, eff_maxYPull_GE11, mis_maxYPull_GE11);
  TGraph* gr_maxXPull_GE21 = new TGraph(n_maxPull, eff_maxXPull_GE21, mis_maxXPull_GE21);
  TGraph* gr_maxYPull_GE21 = new TGraph(n_maxPull, eff_maxYPull_GE21, mis_maxYPull_GE21);
  
  TCanvas* mis_vs_eff_Pull = new TCanvas("mis_vs_eff_Pull", "", 800, 600);
  gPad->SetLogy();
  canvas_margin(mis_vs_eff_Pull);
  mis_vs_eff_Pull->cd();
  //==== att settings
  gr_maxXPull_GE11->SetLineColor(kRed);
  gr_maxYPull_GE11->SetLineColor(kBlue);
  gr_maxXPull_GE21->SetLineColor(kRed);
  gr_maxYPull_GE21->SetLineColor(kBlue);
  gr_maxXPull_GE11->SetLineWidth(2);
  gr_maxYPull_GE11->SetLineWidth(2);
  gr_maxXPull_GE21->SetLineWidth(2);
  gr_maxYPull_GE21->SetLineWidth(2);
  gr_maxXPull_GE21->SetLineStyle(2);
  gr_maxYPull_GE21->SetLineStyle(2);
  //==== drawing
  gr_maxXPull_GE11->Draw("al");
  gr_maxXPull_GE11->SetTitle("mis_vs_eff_Pull");
  gr_maxXPull_GE11->GetXaxis()->SetRangeUser(0, 1.0);
  gr_maxXPull_GE11->GetYaxis()->SetRangeUser(0.0001, 1.0);
  gr_maxXPull_GE11->GetXaxis()->SetTitle("Signal Efficiency");
  gr_maxXPull_GE11->GetYaxis()->SetTitle("Misidentification probability");
  gr_maxYPull_GE11->Draw("lsame");
  gr_maxXPull_GE21->Draw("lsame");
  gr_maxYPull_GE21->Draw("lsame");
  //==== legend
  TLegend lg_maxXPull(0.7, 0.15, 0.95, 0.40);
  lg_maxXPull.SetFillStyle(0);
  lg_maxXPull.SetBorderSize(0);
  lg_maxXPull.AddEntry(gr_maxXPull_GE11, "X/GE11", "l");
  lg_maxXPull.AddEntry(gr_maxYPull_GE11, "Y/GE11", "l");
  lg_maxXPull.AddEntry(gr_maxXPull_GE21, "X/GE21", "l");
  lg_maxXPull.AddEntry(gr_maxYPull_GE21, "Y/GE21", "l");
  lg_maxXPull.Draw();
  //==== save
  mis_vs_eff_Pull->SaveAs(plotpath+"mis_vs_eff_Pull.png");
  mis_vs_eff_Pull->Close();
  
  //==== diff X
  
  const int n_maxX_GE11 = maxX_GE11.size();
  const int n_maxX_GE21 = maxX_GE21.size();
  double eff_maxX_GE11[n_maxX_GE11], mis_maxX_GE11[n_maxX_GE11];
  double eff_maxX_GE21[n_maxX_GE21], mis_maxX_GE21[n_maxX_GE21];

  for(int aaa=0; aaa<n_maxX_GE11; aaa++){
    TH1F* h_maxX_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxX_GE11", maxX_GE11.at(aaa)).data());
    TH1F* h_maxX_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxX_GE11", maxX_GE11.at(aaa)).data());
    eff_maxX_GE11[aaa] = h_maxX_GE11_MuonGun->GetMean();
    mis_maxX_GE11[aaa] = h_maxX_GE11_MinBias->GetMean();
  }
  for(int aaa=0; aaa<n_maxX_GE21; aaa++){
    TH1F* h_maxX_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxX_GE21", maxX_GE21.at(aaa)).data());
    TH1F* h_maxX_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxX_GE21", maxX_GE21.at(aaa)).data());
    eff_maxX_GE21[aaa] = h_maxX_GE21_MuonGun->GetMean();
    mis_maxX_GE21[aaa] = h_maxX_GE21_MinBias->GetMean();
  }

  TGraph* gr_maxX_GE11 = new TGraph(n_maxX_GE11, eff_maxX_GE11, mis_maxX_GE11);
  TGraph* gr_maxX_GE21 = new TGraph(n_maxX_GE21, eff_maxX_GE21, mis_maxX_GE21);

  TCanvas* mis_vs_eff_maxX = new TCanvas("mis_vs_eff_maxX", "", 800, 600);
  gPad->SetLogy();
  canvas_margin(mis_vs_eff_maxX);
  mis_vs_eff_maxX->cd();
  //==== att settings
  gr_maxX_GE11->SetLineColor(kRed);
  gr_maxX_GE21->SetLineColor(kRed);
  gr_maxX_GE11->SetLineWidth(2);
  gr_maxX_GE21->SetLineWidth(2);
  gr_maxX_GE21->SetLineStyle(2);
  //==== drawing
  gr_maxX_GE11->Draw("al");
  gr_maxX_GE11->SetTitle("mis_vs_eff_maxX");
  gr_maxX_GE11->GetXaxis()->SetRangeUser(0, 1.0);
  gr_maxX_GE11->GetYaxis()->SetRangeUser(0.0001, 1.0);
  gr_maxX_GE11->GetXaxis()->SetTitle("Signal Efficiency");
  gr_maxX_GE11->GetYaxis()->SetTitle("Misidentification probability");
  gr_maxX_GE21->Draw("lsame");
  //==== legend
  TLegend lg_maxX(0.7, 0.15, 0.95, 0.40);
  lg_maxX.SetFillStyle(0);
  lg_maxX.SetBorderSize(0);
  lg_maxX.AddEntry(gr_maxX_GE11, "X/GE11", "l");
  lg_maxX.AddEntry(gr_maxX_GE21, "X/GE21", "l");
  lg_maxX.Draw();
  //==== save
  mis_vs_eff_maxX->SaveAs(plotpath+"mis_vs_eff_maxX.png");
  mis_vs_eff_maxX->Close();
  
  //==== diff Y
  
  const int n_maxY_GE11 = maxY_GE11.size();
  const int n_maxY_GE21 = maxY_GE21.size();
  double eff_maxY_GE11[n_maxY_GE11], mis_maxY_GE11[n_maxY_GE11];
  double eff_maxY_GE21[n_maxY_GE21], mis_maxY_GE21[n_maxY_GE21];
  
  for(int aaa=0; aaa<n_maxY_GE11; aaa++){
    TH1F* h_maxY_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxY_GE11", maxY_GE11.at(aaa)).data());
    TH1F* h_maxY_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxY_GE11", maxY_GE11.at(aaa)).data());
    eff_maxY_GE11[aaa] = h_maxY_GE11_MuonGun->GetMean();
    mis_maxY_GE11[aaa] = h_maxY_GE11_MinBias->GetMean();
  }
  for(int aaa=0; aaa<n_maxY_GE21; aaa++){
    TH1F* h_maxY_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("maxY_GE21", maxY_GE21.at(aaa)).data());
    TH1F* h_maxY_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("maxY_GE21", maxY_GE21.at(aaa)).data());
    eff_maxY_GE21[aaa] = h_maxY_GE21_MuonGun->GetMean();
    mis_maxY_GE21[aaa] = h_maxY_GE21_MinBias->GetMean();
  }
  
  TGraph* gr_maxY_GE11 = new TGraph(n_maxY_GE11, eff_maxY_GE11, mis_maxY_GE11);
  TGraph* gr_maxY_GE21 = new TGraph(n_maxY_GE21, eff_maxY_GE21, mis_maxY_GE21);
  
  TCanvas* mis_vs_eff_maxY = new TCanvas("mis_vs_eff_maxY", "", 800, 600);
  gPad->SetLogy();
  canvas_margin(mis_vs_eff_maxY);
  mis_vs_eff_maxY->cd();
  //==== att settings
  gr_maxY_GE11->SetLineColor(kBlue);
  gr_maxY_GE21->SetLineColor(kBlue);
  gr_maxY_GE11->SetLineWidth(2);
  gr_maxY_GE21->SetLineWidth(2);
  gr_maxY_GE21->SetLineStyle(2);
  //==== drawing
  gr_maxY_GE11->Draw("al");
  gr_maxY_GE11->SetTitle("mis_vs_eff_maxY");
  gr_maxY_GE11->GetXaxis()->SetRangeUser(0, 1.0);
  gr_maxY_GE11->GetYaxis()->SetRangeUser(0.0001, 1.0);
  gr_maxY_GE11->GetXaxis()->SetTitle("Signal Efficiency");
  gr_maxY_GE11->GetYaxis()->SetTitle("Misidentification probability");
  gr_maxY_GE21->Draw("lsame");
  //==== legend
  TLegend lg_maxY(0.7, 0.15, 0.95, 0.40);
  lg_maxY.SetFillStyle(0);
  lg_maxY.SetBorderSize(0);
  lg_maxY.AddEntry(gr_maxY_GE11, "Y/GE11", "l");
  lg_maxY.AddEntry(gr_maxY_GE21, "Y/GE21", "l");
  lg_maxY.Draw();
  //==== save
  mis_vs_eff_maxY->SaveAs(plotpath+"mis_vs_eff_maxY.png");
  mis_vs_eff_maxY->Close();

  //==== DotDir
  const int n_minDotDir = minDotDir.size();
  double eff_minDotDir_GE11[n_minDotDir], mis_minDotDir_GE11[n_minDotDir];
  double eff_minDotDir_GE21[n_minDotDir], mis_minDotDir_GE21[n_minDotDir];
  
  for(int aaa=0; aaa<n_minDotDir; aaa++){
    TH1F* h_minDotDir_GE11_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("minDotDir_GE11", minDotDir.at(aaa)).data());
    TH1F* h_minDotDir_GE11_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("minDotDir_GE11", minDotDir.at(aaa)).data());
    eff_minDotDir_GE11[aaa] = h_minDotDir_GE11_MuonGun->GetMean();
    mis_minDotDir_GE11[aaa] = h_minDotDir_GE11_MinBias->GetMean();
    TH1F* h_minDotDir_GE21_MuonGun = (TH1F*)file_MuonGun->Get(DoubleToString("minDotDir_GE21", minDotDir.at(aaa)).data());
    TH1F* h_minDotDir_GE21_MinBias = (TH1F*)file_MinBias->Get(DoubleToString("minDotDir_GE21", minDotDir.at(aaa)).data());
    eff_minDotDir_GE21[aaa] = h_minDotDir_GE21_MuonGun->GetMean();
    mis_minDotDir_GE21[aaa] = h_minDotDir_GE21_MinBias->GetMean();
  }
  
  TGraph* gr_minDotDir_GE11 = new TGraph(n_minDotDir, eff_minDotDir_GE11, mis_minDotDir_GE11);
  TGraph* gr_minDotDir_GE21 = new TGraph(n_minDotDir, eff_minDotDir_GE21, mis_minDotDir_GE21);
  
  TCanvas* mis_vs_eff_minDotDir = new TCanvas("mis_vs_eff_minDotDir", "", 800, 600);
  gPad->SetLogy();
  canvas_margin(mis_vs_eff_minDotDir);
  mis_vs_eff_minDotDir->cd();
  //==== att settings
  gr_minDotDir_GE11->SetLineColor(kBlack);
  gr_minDotDir_GE21->SetLineColor(kBlack);
  gr_minDotDir_GE21->SetLineStyle(2);
  //==== drawing
  gr_minDotDir_GE11->Draw("al");
  gr_minDotDir_GE11->SetTitle("mis_vs_eff_minDotDir");
  gr_minDotDir_GE11->GetXaxis()->SetRangeUser(0, 1.0);
  gr_minDotDir_GE11->GetYaxis()->SetRangeUser(0.0001, 1.0);
  gr_minDotDir_GE11->GetXaxis()->SetTitle("Signal Efficiency");
  gr_minDotDir_GE11->GetYaxis()->SetTitle("Misidentification probability");
  gr_minDotDir_GE21->Draw("lsame");
  //==== legend
  TLegend lg_minDotDir(0.7, 0.15, 0.95, 0.40);
  lg_minDotDir.SetFillStyle(0);
  lg_minDotDir.SetBorderSize(0);
  lg_minDotDir.AddEntry(gr_minDotDir_GE11, "DotDir/GE11", "l");
  lg_minDotDir.AddEntry(gr_minDotDir_GE21, "DotDir/GE21", "l");
  lg_minDotDir.Draw();
  //==== save
  mis_vs_eff_minDotDir->SaveAs(plotpath+"mis_vs_eff_minDotDir.png");
  mis_vs_eff_minDotDir->Close();

  
  file_output->Close();
  
}


std::string DoubleToString(std::string prefix, double dd){
  std::ostringstream os;
  os << dd;
  return prefix+"_"+os.str();
}









