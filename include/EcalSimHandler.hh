//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May 21 23:55:53 2023 by ROOT version 6.24/06
// from TTree PfoAnalysisTree/PfoAnalysisTree
// found on file: ../data/myreco_PfoAnalysis.root
//////////////////////////////////////////////////////////

#ifndef EcalSimHandler_h
#define EcalSimHandler_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class EcalSimHandler {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           nPfosTotal;
   Int_t           nPfosNeutralHadrons;
   Int_t           nPfosPhotons;
   Int_t           nPfosTracks;
   Float_t         pfoEnergyTotal;
   Float_t         pfoEnergyNeutralHadrons;
   Float_t         pfoEnergyPhotons;
   Float_t         pfoEnergyTracks;
   Float_t         pfoECalToEmEnergy;
   Float_t         pfoECalToHadEnergy;
   Float_t         pfoHCalToEmEnergy;
   Float_t         pfoHCalToHadEnergy;
   Float_t         pfoOtherEnergy;
   Float_t         pfoMuonToEnergy;
   Float_t         pfoMassTotal;
   vector<float>   *pfoEnergies;
   vector<float>   *pfoPx;
   vector<float>   *pfoPy;
   vector<float>   *pfoPz;
   vector<float>   *pfoCosTheta;
   vector<float>   *pfoTargetEnergies;
   vector<float>   *pfoTargetPx;
   vector<float>   *pfoTargetPy;
   vector<float>   *pfoTargetPz;
   vector<float>   *pfoTargetCosTheta;
   vector<int>     *pfoPdgCodes;
   vector<int>     *pfoTargetPdgCodes;
   Int_t           nPfoTargetsTotal;
   Int_t           nPfoTargetsNeutralHadrons;
   Int_t           nPfoTargetsPhotons;
   Int_t           nPfoTargetsTracks;
   Float_t         pfoTargetsEnergyTotal;
   Float_t         pfoTargetsEnergyNeutralHadrons;
   Float_t         pfoTargetsEnergyPhotons;
   Float_t         pfoTargetsEnergyTracks;
   Float_t         mcEnergyENu;
   Float_t         mcEnergyFwd;
   Float_t         eQQ;
   Float_t         eQ1;
   Float_t         eQ2;
   Float_t         costQQ;
   Float_t         costQ1;
   Float_t         costQ2;
   Float_t         mQQ;
   Float_t         thrust;
   Int_t           qPdg;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_nPfosTotal;   //!
   TBranch        *b_nPfosNeutralHadrons;   //!
   TBranch        *b_nPfosPhotons;   //!
   TBranch        *b_nPfosTracks;   //!
   TBranch        *b_pfoEnergyTotal;   //!
   TBranch        *b_pfoEnergyNeutralHadrons;   //!
   TBranch        *b_pfoEnergyPhotons;   //!
   TBranch        *b_pfoEnergyTracks;   //!
   TBranch        *b_pfoECalToEmEnergy;   //!
   TBranch        *b_pfoECalToHadEnergy;   //!
   TBranch        *b_pfoHCalToEmEnergy;   //!
   TBranch        *b_pfoHCalToHadEnergy;   //!
   TBranch        *b_pfoOtherEnergy;   //!
   TBranch        *b_pfoMuonToEnergy;   //!
   TBranch        *b_pfoMassTotal;   //!
   TBranch        *b_pfoEnergies;   //!
   TBranch        *b_pfoPx;   //!
   TBranch        *b_pfoPy;   //!
   TBranch        *b_pfoPz;   //!
   TBranch        *b_pfoCosTheta;   //!
   TBranch        *b_pfoTargetEnergies;   //!
   TBranch        *b_pfoTargetPx;   //!
   TBranch        *b_pfoTargetPy;   //!
   TBranch        *b_pfoTargetPz;   //!
   TBranch        *b_pfoTargetCosTheta;   //!
   TBranch        *b_pfoPdgCodes;   //!
   TBranch        *b_pfoTargetPdgCodes;   //!
   TBranch        *b_nPfoTargetsTotal;   //!
   TBranch        *b_nPfoTargetsNeutralHadrons;   //!
   TBranch        *b_nPfoTargetsPhotons;   //!
   TBranch        *b_nPfoTargetsTracks;   //!
   TBranch        *b_pfoTargetsEnergyTotal;   //!
   TBranch        *b_pfoTargetsEnergyNeutralHadrons;   //!
   TBranch        *b_pfoTargetsEnergyPhotons;   //!
   TBranch        *b_pfoTargetsEnergyTracks;   //!
   TBranch        *b_mcEnergyENu;   //!
   TBranch        *b_mcEnergyFwd;   //!
   TBranch        *b_eQQ;   //!
   TBranch        *b_eQ1;   //!
   TBranch        *b_eQ2;   //!
   TBranch        *b_costQQ;   //!
   TBranch        *b_costQ1;   //!
   TBranch        *b_costQ2;   //!
   TBranch        *b_mQQ;   //!
   TBranch        *b_thrust;   //!
   TBranch        *b_qPdg;   //!

   EcalSimHandler(TTree *tree=0);
   virtual ~EcalSimHandler();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef EcalSimHandler_cxx
EcalSimHandler::EcalSimHandler(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../data/myreco_PfoAnalysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../data/myreco_PfoAnalysis.root");
      }
      f->GetObject("PfoAnalysisTree",tree);

   }
   Init(tree);
}

EcalSimHandler::~EcalSimHandler()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EcalSimHandler::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t EcalSimHandler::LoadTree(Long64_t entry)
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

void EcalSimHandler::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pfoEnergies = 0;
   pfoPx = 0;
   pfoPy = 0;
   pfoPz = 0;
   pfoCosTheta = 0;
   pfoTargetEnergies = 0;
   pfoTargetPx = 0;
   pfoTargetPy = 0;
   pfoTargetPz = 0;
   pfoTargetCosTheta = 0;
   pfoPdgCodes = 0;
   pfoTargetPdgCodes = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nPfosTotal", &nPfosTotal, &b_nPfosTotal);
   fChain->SetBranchAddress("nPfosNeutralHadrons", &nPfosNeutralHadrons, &b_nPfosNeutralHadrons);
   fChain->SetBranchAddress("nPfosPhotons", &nPfosPhotons, &b_nPfosPhotons);
   fChain->SetBranchAddress("nPfosTracks", &nPfosTracks, &b_nPfosTracks);
   fChain->SetBranchAddress("pfoEnergyTotal", &pfoEnergyTotal, &b_pfoEnergyTotal);
   fChain->SetBranchAddress("pfoEnergyNeutralHadrons", &pfoEnergyNeutralHadrons, &b_pfoEnergyNeutralHadrons);
   fChain->SetBranchAddress("pfoEnergyPhotons", &pfoEnergyPhotons, &b_pfoEnergyPhotons);
   fChain->SetBranchAddress("pfoEnergyTracks", &pfoEnergyTracks, &b_pfoEnergyTracks);
   fChain->SetBranchAddress("pfoECalToEmEnergy", &pfoECalToEmEnergy, &b_pfoECalToEmEnergy);
   fChain->SetBranchAddress("pfoECalToHadEnergy", &pfoECalToHadEnergy, &b_pfoECalToHadEnergy);
   fChain->SetBranchAddress("pfoHCalToEmEnergy", &pfoHCalToEmEnergy, &b_pfoHCalToEmEnergy);
   fChain->SetBranchAddress("pfoHCalToHadEnergy", &pfoHCalToHadEnergy, &b_pfoHCalToHadEnergy);
   fChain->SetBranchAddress("pfoOtherEnergy", &pfoOtherEnergy, &b_pfoOtherEnergy);
   fChain->SetBranchAddress("pfoMuonToEnergy", &pfoMuonToEnergy, &b_pfoMuonToEnergy);
   fChain->SetBranchAddress("pfoMassTotal", &pfoMassTotal, &b_pfoMassTotal);
   fChain->SetBranchAddress("pfoEnergies", &pfoEnergies, &b_pfoEnergies);
   fChain->SetBranchAddress("pfoPx", &pfoPx, &b_pfoPx);
   fChain->SetBranchAddress("pfoPy", &pfoPy, &b_pfoPy);
   fChain->SetBranchAddress("pfoPz", &pfoPz, &b_pfoPz);
   fChain->SetBranchAddress("pfoCosTheta", &pfoCosTheta, &b_pfoCosTheta);
   fChain->SetBranchAddress("pfoTargetEnergies", &pfoTargetEnergies, &b_pfoTargetEnergies);
   fChain->SetBranchAddress("pfoTargetPx", &pfoTargetPx, &b_pfoTargetPx);
   fChain->SetBranchAddress("pfoTargetPy", &pfoTargetPy, &b_pfoTargetPy);
   fChain->SetBranchAddress("pfoTargetPz", &pfoTargetPz, &b_pfoTargetPz);
   fChain->SetBranchAddress("pfoTargetCosTheta", &pfoTargetCosTheta, &b_pfoTargetCosTheta);
   fChain->SetBranchAddress("pfoPdgCodes", &pfoPdgCodes, &b_pfoPdgCodes);
   fChain->SetBranchAddress("pfoTargetPdgCodes", &pfoTargetPdgCodes, &b_pfoTargetPdgCodes);
   fChain->SetBranchAddress("nPfoTargetsTotal", &nPfoTargetsTotal, &b_nPfoTargetsTotal);
   fChain->SetBranchAddress("nPfoTargetsNeutralHadrons", &nPfoTargetsNeutralHadrons, &b_nPfoTargetsNeutralHadrons);
   fChain->SetBranchAddress("nPfoTargetsPhotons", &nPfoTargetsPhotons, &b_nPfoTargetsPhotons);
   fChain->SetBranchAddress("nPfoTargetsTracks", &nPfoTargetsTracks, &b_nPfoTargetsTracks);
   fChain->SetBranchAddress("pfoTargetsEnergyTotal", &pfoTargetsEnergyTotal, &b_pfoTargetsEnergyTotal);
   fChain->SetBranchAddress("pfoTargetsEnergyNeutralHadrons", &pfoTargetsEnergyNeutralHadrons, &b_pfoTargetsEnergyNeutralHadrons);
   fChain->SetBranchAddress("pfoTargetsEnergyPhotons", &pfoTargetsEnergyPhotons, &b_pfoTargetsEnergyPhotons);
   fChain->SetBranchAddress("pfoTargetsEnergyTracks", &pfoTargetsEnergyTracks, &b_pfoTargetsEnergyTracks);
   fChain->SetBranchAddress("mcEnergyENu", &mcEnergyENu, &b_mcEnergyENu);
   fChain->SetBranchAddress("mcEnergyFwd", &mcEnergyFwd, &b_mcEnergyFwd);
   fChain->SetBranchAddress("eQQ", &eQQ, &b_eQQ);
   fChain->SetBranchAddress("eQ1", &eQ1, &b_eQ1);
   fChain->SetBranchAddress("eQ2", &eQ2, &b_eQ2);
   fChain->SetBranchAddress("costQQ", &costQQ, &b_costQQ);
   fChain->SetBranchAddress("costQ1", &costQ1, &b_costQ1);
   fChain->SetBranchAddress("costQ2", &costQ2, &b_costQ2);
   fChain->SetBranchAddress("mQQ", &mQQ, &b_mQQ);
   fChain->SetBranchAddress("thrust", &thrust, &b_thrust);
   fChain->SetBranchAddress("qPdg", &qPdg, &b_qPdg);
   Notify();
}

Bool_t EcalSimHandler::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EcalSimHandler::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t EcalSimHandler::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef EcalSimHandler_cxx
