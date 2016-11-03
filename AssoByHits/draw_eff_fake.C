#include "../include/setTDRStyle.C"
#include "../include/mylib.h"

std::string DoubleToString(double dd);

void draw_eff_fake(bool DoGeom=false){
  setTDRStyle();
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString plotpath = "./plots/CMSSW_8_1_0_pre11/";
  
  gSystem->mkdir(plotpath, kTRUE);
  
  //======================
  //==== Scattered plots
  //======================
  
  if(DoGeom){
    TFile *file_geom = new TFile("rootfiles/CMSSW_8_1_0_pre11/Geometry.root");
    TString obj[2] = {"GEMRecHit", "GEMSegment"};
    TString stations[2] = {"GE11", "GE21"};
    TString coordi[4] = {"GlobalPosition_scattered", "LocalPosition_scattered", "odd_XZplane", "even_XZplane"};
    for(int i=0; i<2; i++){
      for(int j=0; j<2; j++){
        for(int k=0; k<4; k++){
          //cout << obj[i]+"_"+stations[j]+"_"+coordi[j]+"_scattered" << endl;
          if(obj[i]=="GEMSegment" && k>=2) continue;
          TH2F *hist_scattered = (TH2F*)file_geom->Get(obj[i]+"_"+stations[j]+"_"+coordi[k]);
          TCanvas *c_scattered = new TCanvas("c_scattered", "", 1000, 1000);
          c_scattered->cd();
          hist_scattered->Draw();
          hist_scattered->SetTitle(obj[i]+" "+stations[j]+" "+coordi[k]);
          c_scattered->SaveAs(plotpath+"/Geometry/"+obj[i]+"_"+stations[j]+"_"+coordi[k]+".png");
          c_scattered->Close();
          delete c_scattered;
        }
      }
    }
  }
  
  //===============
  //==== Eff/Fake
  //===============
  
  vector<TString> var = {"Pt", "Eta", "Phi"};
  vector<TString> xtitle = {"p_{T} [GeV]", "|#eta|", "#phi"};
  vector<double> fake_ymaxs = {100., 100., 100.};
  double FakeYMin = 0.001;

  vector<TString> MuonObj = {"GEMMuon", "RecoMuon", "LooseMuon", "MediumMuon", "TightMuon"};
  vector<Color_t> color_Obj = {kBlack, kGreen, kOrange, kBlue, kRed};
  
  vector<TString> PU = {"0", "140", "200"};
  vector<Color_t> color_PU = {kRed, kBlue, kBlack};
  
  //==== Which Kinematic Variable (Pt, Eta, Phi)
  for(unsigned int it_var=0; it_var<var.size(); it_var++){
    TString this_var = var.at(it_var);
    //cout << "This MuonObj = " << this_var << endl;

    //==== PU (0, 140, 200)
    for(unsigned int it_PU=0; it_PU<PU.size(); it_PU++){
      TString this_PU = PU.at(it_PU);
      //cout <<"  This PU = " << this_PU << endl;
      
      TCanvas *c_eff = new TCanvas("c_eff", "", 1000, 1000);
      TCanvas *c_fake = new TCanvas("c_fake", "", 1000, 1000);
      
      TLegend lg_down(0.65, 0.15, 0.93, 0.45);
      lg_down.SetBorderSize(0);
      TLegend lg_up(0.65, 0.70, 0.93, 0.92);
      lg_up.SetBorderSize(0);
      
      TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre11/OUTPUT_RelValZMM_13_"+this_PU+"PU.root");
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
        Unmatched->Divide(total);
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
      c_eff->SaveAs(this_plotpath+"Eff_"+this_PU+"_"+this_var+".png");
      c_eff->Close();
      delete c_eff;
      
      c_fake->cd();
      lg_up.Draw();
      //if(this_var=="Pt") gPad->SetLogx(1);
      gPad->SetLogy(1);
      c_fake->SaveAs(this_plotpath+"Fake_"+this_PU+"_"+this_var+".png");
      gPad->SetLogy(0);
      c_fake->Close();
      delete c_fake;
      
      
    } // END PU
    

    //==== Muon Obj (RecoMuon, TightMuon, GEMMuon ..)
    for(unsigned int it_MuonObj=0; it_MuonObj<MuonObj.size(); it_MuonObj++){
      TString this_MuonObj = MuonObj.at(it_MuonObj);
      
      TCanvas *c_eff = new TCanvas("c_eff", "", 1000, 1000);
      TCanvas *c_fake = new TCanvas("c_fake", "", 1000, 1000);
      
      TLegend lg_down(0.63, 0.18, 0.93, 0.40);
      lg_down.SetBorderSize(0);
      TLegend lg_up(0.65, 0.70, 0.93, 0.92);
      lg_up.SetBorderSize(0);
      
      TString this_plotpath = plotpath+"EffFake_PUs/";
      
      //==== PU (0, 140, 200)
      for(unsigned int it_PU=0; it_PU<PU.size(); it_PU++){
        TString this_PU = PU.at(it_PU);
        Color_t thiscolor = color_PU.at(it_PU);
        //cout <<"  This PU = " << this_PU << endl;
        
        TFile *file = new TFile("rootfiles/CMSSW_8_1_0_pre11/OUTPUT_RelValZMM_13_"+this_PU+"PU.root");
        
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
        if(it_PU==0){
          this_gr->Draw("alp");
          this_gr->GetYaxis()->SetRangeUser(0, 1.2);
          if(this_var=="Eta") this_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") this_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else this_gr->Draw("lpsame");
        lg_down.AddEntry(this_gr, "<PU> = "+this_PU, "l");
        lg_up.AddEntry(this_gr, "<PU> = "+this_PU, "l");
        
        //==== Fake
        c_fake->cd();
        TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatched"+this_MuonObj+"_"+this_var)->Clone();
        TH1F *total = (TH1F*)file->Get("Hits"+this_MuonObj+"_"+this_var)->Clone();
        Unmatched->Divide(total);
        TGraphAsymmErrors *Unmatched_gr;
        if(this_var=="Eta") Unmatched_gr = hist_to_graph(Unmatched, true);
        else Unmatched_gr = hist_to_graph(Unmatched);
        Unmatched_gr->SetLineColor(thiscolor);
        Unmatched_gr->SetLineWidth(2);
        Unmatched_gr->SetMarkerStyle(21);
        Unmatched_gr->SetMarkerColor(thiscolor);
        Unmatched_gr->SetMarkerSize(1);
        Unmatched_gr->SetTitle("");
        if(it_PU==0){
          Unmatched_gr->GetXaxis()->SetTitle(xtitle.at(it_var));
          Unmatched_gr->GetYaxis()->SetTitle("Fake per "+this_MuonObj);
          Unmatched_gr->Draw("alp");
          Unmatched_gr->GetYaxis()->SetRangeUser(FakeYMin, fake_ymaxs.at(it_var));
          if(this_var=="Eta") Unmatched_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") Unmatched_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else Unmatched_gr->Draw("lpsame");
        
      } // END PU

      gSystem->mkdir(this_plotpath, kTRUE);
 
      c_eff->cd();
      lg_down.Draw();
      c_eff->SaveAs(this_plotpath+"Eff_"+this_MuonObj+"_"+this_var+".png");
      c_eff->Close();
      delete c_eff;
      
      c_fake->cd();
      lg_up.Draw();
      gPad->SetLogy(1);
      c_fake->SaveAs(this_plotpath+"Fake_"+this_MuonObj+"_"+this_var+".png");
      gPad->SetLogy(0);
      c_fake->Close();
      delete c_fake;
      
      
    } // END MuonObj

    
    
    
  } // END of Cut Variable loop


}


