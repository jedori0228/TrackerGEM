//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 19 14:45:17 2016 by ROOT version 6.06/00
// from TTree tree_GE21/
// found on file: histogram_MuonGun.root
//////////////////////////////////////////////////////////

#ifndef GE21_h
#define GE21_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class GE21 {
  public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Fixed size dimensions of array or collections stored in the TTree if any.
  
  // Declaration of leaf types
  Double_t        DelX_GE21;
  Double_t        DelY_GE21;
  Double_t        DelPhi_GE21;
  Double_t        DelTheta_GE21;
  Double_t        DelThetaXZ_GE21;
  Double_t        DotDir_GE21;
  Double_t        DotXDir_GE21;
  Double_t        DelX_over_sigma_GE21;
  Double_t        DelY_over_sigma_GE21;
  Double_t        TrackEta_GE21;
  
  // List of branches
  TBranch        *b_DelX_GE21;   //!
  TBranch        *b_DelY_GE21;   //!
  TBranch        *b_DelPhi_GE21;   //!
  TBranch        *b_DelTheta_GE21;   //!
  TBranch        *b_DelThetaXZ_GE21;   //!
  TBranch        *b_DotDir_GE21;   //!
  TBranch        *b_DotXDir_GE21;   //!
  TBranch        *b_DelX_over_sigma_GE21;   //!
  TBranch        *b_DelY_over_sigma_GE21;   //!
  TBranch        *b_TrackEta_GE21;   //!
  
  GE21(TString filename, TTree *tree=0);
  virtual ~GE21();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  TString outputfile_name;
};

#endif

#ifdef GE21_cxx
GE21::GE21(TString filename, TTree *tree) : fChain(0)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
    if (!f || !f->IsOpen()) {
      f = new TFile(filename);
    }
    f->GetObject("tree_GE21",tree);
    
  }
  Init(tree);
}

GE21::~GE21()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t GE21::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t GE21::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void GE21::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  
  fChain->SetBranchAddress("DelX_GE21", &DelX_GE21, &b_DelX_GE21);
  fChain->SetBranchAddress("DelY_GE21", &DelY_GE21, &b_DelY_GE21);
  fChain->SetBranchAddress("DelPhi_GE21", &DelPhi_GE21, &b_DelPhi_GE21);
  fChain->SetBranchAddress("DelTheta_GE21", &DelTheta_GE21, &b_DelTheta_GE21);
  fChain->SetBranchAddress("DelThetaXZ_GE21", &DelThetaXZ_GE21, &b_DelThetaXZ_GE21);
  fChain->SetBranchAddress("DotDir_GE21", &DotDir_GE21, &b_DotDir_GE21);
  fChain->SetBranchAddress("DotXDir_GE21", &DotXDir_GE21, &b_DotXDir_GE21);
  fChain->SetBranchAddress("DelX_over_sigma_GE21", &DelX_over_sigma_GE21, &b_DelX_over_sigma_GE21);
  fChain->SetBranchAddress("DelY_over_sigma_GE21", &DelY_over_sigma_GE21, &b_DelY_over_sigma_GE21);
  fChain->SetBranchAddress("TrackEta_GE21", &TrackEta_GE21, &b_TrackEta_GE21);
  Notify();
}

Bool_t GE21::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  
  return kTRUE;
}

void GE21::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t GE21::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef GE21_cxx
