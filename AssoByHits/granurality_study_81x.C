#include "../include/setTDRStyle.C"
#include "../include/mylib.h"

void granurality_study_81x(bool DoGeom=false){
  setTDRStyle();
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString plotpath = "./plots/CMSSW_8_1_0_pre16/Granularity/";
  
  gSystem->mkdir(plotpath, kTRUE);
  
  //===============
  //==== Eff/Fake
  //===============
  
  vector<TString> var = {"Pt", "Eta", "Phi"};
  vector<TString> xtitle = {"p_{T} [GeV]", "|#eta|", "#phi"};
  vector<double> fake_ymaxs = {1., 1., 1.};
  double FakeYMin = 0;

  vector<TString> MuonObj = {"GEMMuon", "RecoMuon", "LooseMuon", "MediumMuon", "TightMuon"};
  vector<Color_t> color_Obj = {kBlack, kGreen, kOrange, kBlue, kRed};
  
  vector<TString> nstrip = {"384", "768"};
  //vector<TString> nstrip = {"768"};
  vector<Color_t> color_nstrip = {kViolet, kBlue, kBlack, kRed};
  
  //==== Which Kinematic Variable (Pt, Eta, Phi)
  for(unsigned int it_var=0; it_var<var.size(); it_var++){
    TString this_var = var.at(it_var);
    //cout << "This MuonObj = " << this_var << endl;

    //==== nstrip
    for(unsigned int it_nstrip=0; it_nstrip<nstrip.size(); it_nstrip++){
      TString this_nstrip = nstrip.at(it_nstrip);
      //cout <<"  This nstrip = " << this_nstrip << endl;
      
      TCanvas *c_eff = new TCanvas("c_eff", "", 1000, 1000);
      TCanvas *c_fake = new TCanvas("c_fake", "", 1000, 1000);
      
      TLegend lg_down(0.65, 0.15, 0.93, 0.45);
      lg_down.SetBorderSize(0);
      TLegend lg_up(0.65, 0.70, 0.93, 0.92);
      lg_up.SetBorderSize(0);
      
      TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre16/OUTPUT_TenMu_Pt_0_100_step3_PU200_nstrip_"+this_nstrip+".root");
      //TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre16/OUTPUT_DoubleMu_Pt_0_100_step3_PU200_nstrip_"+this_nstrip+".root");
      //TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre11/OUTPUT_TenMu_nstrip_"+this_nstrip+"_200PU.root");
      TString this_plotpath = plotpath+"EffFake_MuonObjs/";
      
      //==== Muon Obj (RecoMuon, TightMuon, GEMMuon ..)
      for(unsigned int it_MuonObj=0; it_MuonObj<MuonObj.size(); it_MuonObj++){
        TString this_MuonObj = MuonObj.at(it_MuonObj);
        Color_t thiscolor = color_Obj.at(it_MuonObj);
        
        //==== Efficiency
        c_eff->cd();
        //cout << "HitsEff_"+this_MuonObj+"_"+this_var << endl;
        TEfficiency *this_eff = (TEfficiency*)file->Get("HitsEff_"+this_MuonObj+"_"+this_var);
        TGraph *this_gr = this_eff->CreateGraph();
        this_gr->SetLineColor(thiscolor);
        this_gr->SetLineWidth(2);
        this_gr->SetMarkerStyle(21);
        this_gr->SetMarkerColor(thiscolor);
        this_gr->SetMarkerSize(1);
        this_gr->GetXaxis()->SetTitle(xtitle.at(it_var));
        this_gr->GetYaxis()->SetTitle("Efficiency");
        if(it_MuonObj==0){
          this_gr->Draw("alp");
          this_gr->GetYaxis()->SetRangeUser(0, 1.2);
          if(this_var=="Eta") this_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") this_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else this_gr->Draw("lpsame");
        lg_down.AddEntry(this_gr, this_MuonObj, "l");
        lg_up.AddEntry(this_gr, this_MuonObj, "l");
        
        //==== Fake
        c_fake->cd();
        //cout << "HitsUnmatched"+this_MuonObj+"_"+this_var << endl;
        TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatched"+this_MuonObj+"_"+this_var)->Clone();
        TH1F *total = (TH1F*)file->Get("Hits"+this_MuonObj+"_"+this_var)->Clone();
        TH1F *Nevents_h = (TH1F*)file->Get("Nevents_h")->Clone();
        double n_events = Nevents_h->GetBinContent(2);
        //Unmatched->Divide(total);
        Unmatched->Scale(1./n_events);
        TGraphAsymmErrors *Unmatched_gr;
        if(this_var=="Eta") Unmatched_gr = hist_to_graph(Unmatched, true);
        else Unmatched_gr = hist_to_graph(Unmatched);
        Unmatched_gr->SetLineColor(thiscolor);
        Unmatched_gr->SetLineWidth(2);
        Unmatched_gr->SetMarkerStyle(21);
        Unmatched_gr->SetMarkerColor(thiscolor);
        Unmatched_gr->SetMarkerSize(1);
        Unmatched_gr->SetTitle("");
        if(it_MuonObj==0){
          Unmatched_gr->GetXaxis()->SetTitle(xtitle.at(it_var));
          Unmatched_gr->GetYaxis()->SetTitle("Fake per "+this_MuonObj);
          Unmatched_gr->Draw("alp");
          Unmatched_gr->GetYaxis()->SetRangeUser(FakeYMin, fake_ymaxs.at(it_var));
          if(this_var=="Eta") Unmatched_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") Unmatched_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else Unmatched_gr->Draw("lpsame");
        
      } // END MuonObj
      
      gSystem->mkdir(this_plotpath, kTRUE);

      c_eff->cd();
      lg_down.Draw();
      c_eff->SaveAs(this_plotpath+"Eff_"+this_nstrip+"_"+this_var+".png");
      c_eff->Close();
      delete c_eff;
      
      c_fake->cd();
      lg_up.Draw();
      c_fake->SaveAs(this_plotpath+"Fake_"+this_nstrip+"_"+this_var+".png");
      c_fake->Close();
      delete c_fake;
      
      
    } // END nstrip
    

    //==== Muon Obj (RecoMuon, TightMuon, GEMMuon ..)
    for(unsigned int it_MuonObj=0; it_MuonObj<MuonObj.size(); it_MuonObj++){
      TString this_MuonObj = MuonObj.at(it_MuonObj);
      
      TCanvas *c_eff = new TCanvas("c_eff", "", 1000, 1000);
      TCanvas *c_fake = new TCanvas("c_fake", "", 1000, 1000);
      
      TLegend lg_down(0.63, 0.18, 0.93, 0.40);
      lg_down.SetBorderSize(0);
      TLegend lg_up(0.65, 0.70, 0.93, 0.92);
      lg_up.SetBorderSize(0);
      
      TString this_plotpath = plotpath+"EffFake_nstrips/";
      
      //==== nstrip
      for(unsigned int it_nstrip=0; it_nstrip<nstrip.size(); it_nstrip++){
        TString this_nstrip = nstrip.at(it_nstrip);
        Color_t thiscolor = color_nstrip.at(it_nstrip);
        //cout <<"  This nstrip = " << this_nstrip << endl;

        TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre16/OUTPUT_TenMu_Pt_0_100_step3_PU200_nstrip_"+this_nstrip+".root");
        //TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre16/OUTPUT_DoubleMu_Pt_0_100_step3_PU200_nstrip_"+this_nstrip+".root");
        //TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre11/OUTPUT_TenMu_nstrip_"+this_nstrip+"_200PU.root");
        
        //==== Efficiency
        c_eff->cd();
        //cout << "HitsEff_"+this_MuonObj+"_"+this_var << endl;
        TEfficiency *this_eff = (TEfficiency*)file->Get("HitsEff_"+this_MuonObj+"_"+this_var);
        TGraph *this_gr = this_eff->CreateGraph();
        this_gr->SetLineColor(thiscolor);
        this_gr->SetLineWidth(2);
        this_gr->SetMarkerStyle(21);
        this_gr->SetMarkerColor(thiscolor);
        this_gr->SetMarkerSize(1);
        this_gr->GetXaxis()->SetTitle(xtitle.at(it_var));
        this_gr->GetYaxis()->SetTitle("Efficiency");
        if(it_nstrip==0){
          this_gr->Draw("alp");
          this_gr->GetYaxis()->SetRangeUser(0, 1.2);
          if(this_var=="Eta") this_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") this_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else this_gr->Draw("lpsame");
        lg_down.AddEntry(this_gr, "nstrip = "+this_nstrip, "l");
        lg_up.AddEntry(this_gr, "nstrip = "+this_nstrip, "l");
        
        //==== Fake
        c_fake->cd();
        TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatched"+this_MuonObj+"_"+this_var)->Clone();
        TH1F *total = (TH1F*)file->Get("Hits"+this_MuonObj+"_"+this_var)->Clone();
        TH1F *Nevents_h = (TH1F*)file->Get("Nevents_h")->Clone();
        double n_events = Nevents_h->GetBinContent(2);
        //Unmatched->Divide(total);
        Unmatched->Scale(1./n_events);
        TGraphAsymmErrors *Unmatched_gr;
        if(this_var=="Eta") Unmatched_gr = hist_to_graph(Unmatched, true);
        else Unmatched_gr = hist_to_graph(Unmatched);
        Unmatched_gr->SetLineColor(thiscolor);
        Unmatched_gr->SetLineWidth(2);
        Unmatched_gr->SetMarkerStyle(21);
        Unmatched_gr->SetMarkerColor(thiscolor);
        Unmatched_gr->SetMarkerSize(1);
        Unmatched_gr->SetTitle("");
        if(it_nstrip==0){
          Unmatched_gr->GetXaxis()->SetTitle(xtitle.at(it_var));
          Unmatched_gr->GetYaxis()->SetTitle("Fake per "+this_MuonObj);
          Unmatched_gr->Draw("alp");
          Unmatched_gr->GetYaxis()->SetRangeUser(FakeYMin, fake_ymaxs.at(it_var));
          if(this_var=="Eta") Unmatched_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") Unmatched_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else Unmatched_gr->Draw("lpsame");
        
      } // END nstrip

      gSystem->mkdir(this_plotpath, kTRUE);
 
      c_eff->cd();
      lg_down.Draw();
      c_eff->SaveAs(this_plotpath+"Eff_"+this_MuonObj+"_"+this_var+".png");
      c_eff->Close();
      delete c_eff;
      
      c_fake->cd();
      lg_up.Draw();
      c_fake->SaveAs(this_plotpath+"Fake_"+this_MuonObj+"_"+this_var+".png");
      c_fake->Close();
      delete c_fake;
      
      
    } // END MuonObj

    
    
    
  } // END of Cut Variable loop


}


