#include "setTDRStyle.C"
#include "mylib.h"

std::string DoubleToString(double dd);

void draw_eff_fake(int sampletype=0, bool DoGeom=false){

  TString sample;
  if(sampletype==0) sample = "RelValZMM_14";
  else if(sampletype==1) sample = "RelValZEE_14";
  else if(sampletype==2) sample = "RelValTenMuExtendedE_0_200";
  else{
    sample = "RelValZMM_14";
  }

  setTDRStyle();
  TH1::SetDefaultSumw2(true);
  TH1::AddDirectory(kFALSE);

  TString cmssw_version = getenv("CMSSW_RELEASE");

  TString WORKING_DIR = getenv("PLOTTER_WORKING_DIR");
  TString filepath = WORKING_DIR+"/rootfiles/"+cmssw_version+"/";
  TString plotpath = WORKING_DIR+"/plots/"+cmssw_version+"/";

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

  plotpath += sample+"/";
  gSystem->mkdir(plotpath, kTRUE);

  vector<TString> var = {"Pt", "Eta", "Phi"};
  vector<TString> xtitle = {"p_{T} [GeV]", "|#eta|", "#phi"};
  vector<double> fake_ymaxs = {200., 10., 10.}, bkg_ymaxs = {200., 10., 10.};
  double FakeYMin = 0.00005, BkgYMin = 0.00005;
  //vector<double> fake_ymaxs = {1.2, 1.2, 1.2}, bkg_ymaxs = {200., 10., 10.};
  //double FakeYMin = 0., BkgYMin = 0.00005;


  //vector<TString> MuonObj = {"GEMMuon", "RecoMuon", "LooseMuon", "MediumMuon", "TightMuon"};
  vector<TString> MuonObj = {"GEMMuon"};
  vector<Color_t> color_Obj = {kBlack, kGreen, kOrange, kBlue, kRed};
 
  vector<TString> PU = {"0", "200"};
  vector<Color_t> color_PU = {kRed, kBlack};
  if(sample=="RelValZEE_14"){
    PU = {"200"};
    color_PU = {kBlack};
  }

  //==== Which Kinematic Variable (Pt, Eta, Phi)
  for(unsigned int it_var=0; it_var<var.size(); it_var++){
    TString this_var = var.at(it_var);
    //cout << "This MuonObj = " << this_var << endl;

    //==== Muon Obj (RecoMuon, TightMuon, GEMMuon ..)
    for(unsigned int it_MuonObj=0; it_MuonObj<MuonObj.size(); it_MuonObj++){
      TString this_MuonObj = MuonObj.at(it_MuonObj);
      
      TCanvas *c_eff = new TCanvas("c_eff", "", 1000, 1000);
      TCanvas *c_bkg = new TCanvas("c_bkg", "", 1000, 1000);
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
        
        TFile *file = new TFile(filepath+"/"+sample+"_PU"+this_PU+".root");
        
        //==== Efficiency
        c_eff->cd();
        //cout << "HitsEff_"+this_MuonObj+"_"+this_var << endl;
        TEfficiency *this_eff = (TEfficiency*)file->Get("HitsEff_"+this_MuonObj+"_"+this_var);
        TGraphAsymmErrors *this_gr_tmp = this_eff->CreateGraph();
        TGraphAsymmErrors *this_gr;
        if(this_var=="Eta") this_gr = hist_to_graph(this_gr_tmp, 1.6, 2.4, true);
        else this_gr = hist_to_graph(this_gr_tmp, -9999, 9999, true);

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

        //==== Bkg
        c_bkg->cd();
        TH1F *Bkg = (TH1F*)file->Get("HitsBkgMatched"+this_MuonObj+"_"+this_var)->Clone();
        TH1F *Nevents_h = (TH1F*)file->Get("Nevents_h")->Clone();
        double n_events = Nevents_h->GetBinContent(2);
        for(unsigned int it_bin=1; it_bin<=Bkg->GetXaxis()->GetNbins(); it_bin++){
          Bkg->SetBinContent( it_bin, Bkg->GetBinContent(it_bin)/n_events );
          Bkg->SetBinError( it_bin, Bkg->GetBinError(it_bin)/n_events );
        }
        //Bkg->Scale(1./n_events);
        TGraphAsymmErrors *Bkg_gr;
        if(this_var=="Eta") Bkg_gr = hist_to_graph(Bkg, 1.6, 2.4, true);
        else Bkg_gr = hist_to_graph(Bkg, -9999, 9999, true);
        Bkg_gr->SetLineColor(thiscolor);
        Bkg_gr->SetLineWidth(2);
        Bkg_gr->SetMarkerStyle(21);
        Bkg_gr->SetMarkerColor(thiscolor);
        Bkg_gr->SetMarkerSize(1);
        Bkg_gr->SetTitle("");
        if(it_PU==0){
          Bkg_gr->GetXaxis()->SetTitle(xtitle.at(it_var));
          Bkg_gr->GetYaxis()->SetTitle("Bkg "+this_MuonObj+" per Event");
          Bkg_gr->Draw("alp");
          Bkg_gr->GetYaxis()->SetRangeUser(BkgYMin, bkg_ymaxs.at(it_var));
          if(this_var=="Eta") Bkg_gr->GetXaxis()->SetRangeUser(1.6, 2.4);
          if(this_var=="Pt") Bkg_gr->GetXaxis()->SetRangeUser(0., 100.);
        }
        else Bkg_gr->Draw("lpsame");
        
        //==== Fake
        c_fake->cd();
        TH1F *Unmatched = (TH1F*)file->Get("HitsUnmatched"+this_MuonObj+"_"+this_var)->Clone();
        for(unsigned int it_bin=1; it_bin<=Unmatched->GetXaxis()->GetNbins(); it_bin++){
          Unmatched->SetBinContent( it_bin, Unmatched->GetBinContent(it_bin)/n_events );
          Unmatched->SetBinError( it_bin, Unmatched->GetBinError(it_bin)/n_events );
        }
        //Unmatched->Scale(1./n_events);
        TGraphAsymmErrors *Unmatched_gr;
        if(this_var=="Eta") Unmatched_gr = hist_to_graph(Unmatched, 1.6, 2.4, true);
        else Unmatched_gr = hist_to_graph(Unmatched, -9999, 9999, true);
        Unmatched_gr->SetLineColor(thiscolor);
        Unmatched_gr->SetLineWidth(2);
        Unmatched_gr->SetMarkerStyle(21);
        Unmatched_gr->SetMarkerColor(thiscolor);
        Unmatched_gr->SetMarkerSize(1);
        Unmatched_gr->SetTitle("");
        if(it_PU==0){
          Unmatched_gr->GetXaxis()->SetTitle(xtitle.at(it_var));
          //Unmatched_gr->GetYaxis()->SetTitle("Fake per "+this_MuonObj);
          Unmatched_gr->GetYaxis()->SetTitle("Fake per Event");
          Unmatched_gr->GetYaxis()->SetRangeUser(0, 1.2);
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
      
      c_bkg->cd();
      lg_up.Draw();
      gPad->SetLogy(1);
      c_bkg->SaveAs(this_plotpath+"Bkg_"+this_MuonObj+"_"+this_var+".png");
      gPad->SetLogy(0);
      c_bkg->Close();
      delete c_bkg;
      
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


