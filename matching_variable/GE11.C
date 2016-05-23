#define GE11_cxx
#include "GE11.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void GE11::Loop()
{
  TH1::StatOverflows();
  gStyle->SetOptStat("eio");
  
  TFile* outputfile = new TFile(outputfile_name, "RECREATE");
  
  Long64_t nentries = fChain->GetEntriesFast();
  
  vector<double> etabins = {1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4};
  int n_eta_bin = (int)etabins.size()-1;
  //cout << "n_eta_bin = " << n_eta_bin << endl;
  
  TH1F* hist_DelX_over_sigma_GE11[n_eta_bin+1];
  TH1F* hist_DelY_over_sigma_GE11[n_eta_bin+1];
  TH1F* hist_DelX_GE11[n_eta_bin+1];
  TH1F* hist_DelY_GE11[n_eta_bin+1];
  TH1F* hist_DelPhi_GE11[n_eta_bin+1];
  TH1F* hist_DelTheta_GE11[n_eta_bin+1];
  TH1F* hist_DelThetaXZ_GE11[n_eta_bin+1];
  TH1F* hist_DotDir_GE11[n_eta_bin+1];
  TH1F* hist_DotXDir_GE11[n_eta_bin+1];
  for(int i=0; i<n_eta_bin+1; i++){
    if(i<n_eta_bin){
      TString suffix = "_"+TString::Itoa(16+i,10);
      hist_DelX_over_sigma_GE11[i] = new TH1F("DelX_over_sigma_GE11"+suffix, "", 5./0.1, 0., 5.);
      hist_DelY_over_sigma_GE11[i] = new TH1F("DelY_over_sigma_GE11"+suffix, "", 5./0.1, 0., 5.);
      hist_DelX_GE11[i] = new TH1F("DelX_GE11"+suffix, "", 5./0.1, 0., 5.);
      hist_DelY_GE11[i] = new TH1F("DelY_GE11"+suffix, "", 20./0.1, 0., 20.);
      hist_DelPhi_GE11[i] = new TH1F("DelPhi_GE11"+suffix, "", 4/0.1, -2.0, 2.0);
      hist_DelTheta_GE11[i] = new TH1F("DelTheta_GE11"+suffix, "", 4/0.1, -2.0, 2.0);
      hist_DelThetaXZ_GE11[i] = new TH1F("DelThetaXZ_GE11"+suffix, "", 4/0.1, -2.0, 2.0);
      hist_DotDir_GE11[i] = new TH1F("DotDir_GE11"+suffix, "", 1.5/0.01, 0., 1.5);
      hist_DotXDir_GE11[i] = new TH1F("DotXDir_GE11"+suffix, "", 0.6/0.01, -0.3, 0.3);
    }
    else{
      hist_DelX_over_sigma_GE11[i] = new TH1F("DelX_over_sigma_GE11_onebin", "", 5./0.1, 0., 5.);
      hist_DelY_over_sigma_GE11[i] = new TH1F("DelY_over_sigma_GE11_onebin", "", 5./0.1, 0., 5.);
      hist_DelX_GE11[i] = new TH1F("DelX_GE11_onebin", "", 5./0.1, 0., 5.);
      hist_DelY_GE11[i] = new TH1F("DelY_GE11_onebin", "", 20./0.1, 0., 20.);
      hist_DelPhi_GE11[i] = new TH1F("DelPhi_GE11_onebin", "", 4/0.1, -2.0, 2.0);
      hist_DelTheta_GE11[i] = new TH1F("DelTheta_GE11_onebin", "", 4/0.1, -2.0, 2.0);
      hist_DelThetaXZ_GE11[i] = new TH1F("DelThetaXZ_GE11_onebin", "", 4/0.1, -2.0, 2.0);
      hist_DotDir_GE11[i] = new TH1F("DotDir_GE11_onebin", "", 1.5/0.01, 0., 1.5);
      hist_DotXDir_GE11[i] = new TH1F("DotXDir_GE11_onebin", "", 0.6/0.01, -0.3, 0.3);
    }
  }
  
  //nentries = 10;
  
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    fChain->GetEntry(jentry);
    
    if(TrackEta_GE11 >= 2.4) continue;
    
    int this_eta_bin;
    if( TrackEta_GE11 >= etabins[n_eta_bin] ) this_eta_bin = n_eta_bin;
    else{
      for(int i=0; i<n_eta_bin; i++){
        if( etabins[i] <= fabs(TrackEta_GE11) && fabs(TrackEta_GE11) < etabins[i+1] ){
          this_eta_bin = i;
          break;
        }
      }
    }
    //cout << "Eta = " << fabs(TrackEta_GE11) << " => eta bin = " << this_eta_bin << endl;
    
    TString suffix = "_"+TString::Itoa(this_eta_bin, 10);
    //cout << "suffix = " << suffix << endl;
    hist_DelX_over_sigma_GE11[this_eta_bin]->Fill(DelX_over_sigma_GE11);
    hist_DelY_over_sigma_GE11[this_eta_bin]->Fill(DelY_over_sigma_GE11);
    hist_DelX_GE11[this_eta_bin]->Fill(DelX_GE11);
    hist_DelY_GE11[this_eta_bin]->Fill(DelY_GE11);
    hist_DelPhi_GE11[this_eta_bin]->Fill(DelPhi_GE11);
    hist_DelTheta_GE11[this_eta_bin]->Fill(DelTheta_GE11);
    hist_DelThetaXZ_GE11[this_eta_bin]->Fill(DelThetaXZ_GE11);
    hist_DotDir_GE11[this_eta_bin]->Fill(DotDir_GE11);
    hist_DotXDir_GE11[this_eta_bin]->Fill(DotXDir_GE11);
    
    hist_DelX_over_sigma_GE11[n_eta_bin]->Fill(DelX_over_sigma_GE11);
    hist_DelY_over_sigma_GE11[n_eta_bin]->Fill(DelY_over_sigma_GE11);
    hist_DelX_GE11[n_eta_bin]->Fill(DelX_GE11);
    hist_DelY_GE11[n_eta_bin]->Fill(DelY_GE11);
    hist_DelPhi_GE11[n_eta_bin]->Fill(DelPhi_GE11);
    hist_DelTheta_GE11[n_eta_bin]->Fill(DelTheta_GE11);
    hist_DelThetaXZ_GE11[n_eta_bin]->Fill(DelThetaXZ_GE11);
    hist_DotDir_GE11[n_eta_bin]->Fill(DotDir_GE11);
    hist_DotXDir_GE11[n_eta_bin]->Fill(DotXDir_GE11);
    
  }
  
  outputfile->cd();
  
  for(int i=0; i<n_eta_bin+1; i++){
    hist_DelX_over_sigma_GE11[i]->Write();
    hist_DelY_over_sigma_GE11[i]->Write();
    hist_DelX_GE11[i]->Write();
    hist_DelY_GE11[i]->Write();
    hist_DelPhi_GE11[i]->Write();
    hist_DelTheta_GE11[i]->Write();
    hist_DelThetaXZ_GE11[i]->Write();
    hist_DotDir_GE11[i]->Write();
    hist_DotXDir_GE11[i]->Write();
    
  }
  outputfile->Close();
  
}
