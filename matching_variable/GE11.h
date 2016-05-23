//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 19 14:45:17 2016 by ROOT version 6.06/00
// from TTree tree_GE11/
// found on file: histogram_MuonGun.root
//////////////////////////////////////////////////////////

#ifndef GE11_h
#define GE11_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class GE11 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        DelX_GE11;
   Double_t        DelY_GE11;
   Double_t        DelPhi_GE11;
   Double_t        DelTheta_GE11;
   Double_t        DelThetaXZ_GE11;
   Double_t        DotDir_GE11;
   Double_t        DotXDir_GE11;
   Double_t        DelX_over_sigma_GE11;
   Double_t        DelY_over_sigma_GE11;
   Double_t        TrackEta_GE11;

   // List of branches
   TBranch        *b_DelX_GE11;   //!
   TBranch        *b_DelY_GE11;   //!
   TBranch        *b_DelPhi_GE11;   //!
   TBranch        *b_DelTheta_GE11;   //!
   TBranch        *b_DelThetaXZ_GE11;   //!
   TBranch        *b_DotDir_GE11;   //!
   TBranch        *b_DotXDir_GE11;   //!
   TBranch        *b_DelX_over_sigma_GE11;   //!
   TBranch        *b_DelY_over_sigma_GE11;   //!
   TBranch        *b_TrackEta_GE11;   //!

   GE11(TString filename, TTree *tree=0);
   virtual ~GE11();
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

#ifdef GE11_cxx
GE11::GE11(TString filename, TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename);
      if (!f || !f->IsOpen()) {
         f = new TFile(filename);
      }
      f->GetObject("tree_GE11",tree);

   }
   Init(tree);
}

GE11::~GE11()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t GE11::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GE11::LoadTree(Long64_t entry)
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

void GE11::Init(TTree *tree)
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

   fChain->SetBranchAddress("DelX_GE11", &DelX_GE11, &b_DelX_GE11);
   fChain->SetBranchAddress("DelY_GE11", &DelY_GE11, &b_DelY_GE11);
   fChain->SetBranchAddress("DelPhi_GE11", &DelPhi_GE11, &b_DelPhi_GE11);
   fChain->SetBranchAddress("DelTheta_GE11", &DelTheta_GE11, &b_DelTheta_GE11);
   fChain->SetBranchAddress("DelThetaXZ_GE11", &DelThetaXZ_GE11, &b_DelThetaXZ_GE11);
   fChain->SetBranchAddress("DotDir_GE11", &DotDir_GE11, &b_DotDir_GE11);
   fChain->SetBranchAddress("DotXDir_GE11", &DotXDir_GE11, &b_DotXDir_GE11);
   fChain->SetBranchAddress("DelX_over_sigma_GE11", &DelX_over_sigma_GE11, &b_DelX_over_sigma_GE11);
   fChain->SetBranchAddress("DelY_over_sigma_GE11", &DelY_over_sigma_GE11, &b_DelY_over_sigma_GE11);
   fChain->SetBranchAddress("TrackEta_GE11", &TrackEta_GE11, &b_TrackEta_GE11);
   Notify();
}

Bool_t GE11::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GE11::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GE11::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef GE11_cxx
