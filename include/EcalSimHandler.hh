//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May 21 23:55:53 2023 by ROOT version 6.24/06
// from TTree PfoAnalysisTree/PfoAnalysisTree
// found on file: ../data/myreco_PfoAnalysis.root
//////////////////////////////////////////////////////////

#ifndef EcalSimHandler_h
// if not defined, then define
#define EcalSimHandler_h

/* Those are called #include guards.
Once the header is included, it checks if a unique value (in this case EcalSimHandler_h) is defined. 
Then if it's not defined, it defines it and continues to the rest of the page.
When the code is included again, the first ifndef fails, resulting in a blank file.
That prevents double declaration of any identifiers such as types, enums and static variables.
*/
#include <chrono>
using namespace std::chrono;
  auto start = high_resolution_clock::now();



#include <iostream>
// standard input-output stream

#include <TROOT.h>
// The TROOT object is the entry point to the ROOT system
#include <TChain.h>
/*A chain is a collection of files containing TTree objects.
When the chain is created, the first parameter is the default name for the Tree to be processed later on.
Enter a new element in the chain via the TChain::Add function. Once a chain is defined, 
one can use the normal TTree functions to Draw,Scan,etc.*/
#include <TFile.h>
/*A ROOT file is a suite of consecutive data records (TKey instances) with a well defined format.*/
#include <TSystemFile.h>
/*A TSystemFile describes an operating system file.
The information is used by the browser (see TBrowser).*/
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TCanvas.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include <numeric>
#include <TMath.h>

#include <TString.h>
#include <sstream>

using std::vector;
using std::cout;
using std::endl;


// initialising a class called EcalSimHandler
class EcalSimHandler {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types. At every variable corresponds a leaf
   Int_t           evevt;
   Int_t           evrun;
   Float_t         evwgt;
   Long64_t        evtim;
   Float_t         evsig;
   Float_t         evene;
   Float_t         evpoe;
   Float_t         evpop;
   Int_t           evnch;
   Char_t          evpro[1];   //[evnch]
   Int_t           nmcp;
   Int_t           mcori[30];   //[nmcp]
   Int_t           mcpdg[30];   //[nmcp]
   Int_t           mcgst[30];   //[nmcp]
   Int_t           mcsst[30];   //[nmcp]
   Float_t         mcvtx[30];   //[nmcp]
   Float_t         mcvty[30];   //[nmcp]
   Float_t         mcvtz[30];   //[nmcp]
   Float_t         mcepx[30];   //[nmcp]
   Float_t         mcepy[30];   //[nmcp]
   Float_t         mcepz[30];   //[nmcp]
   Float_t         mcmox[30];   //[nmcp]
   Float_t         mcmoy[30];   //[nmcp]
   Float_t         mcmoz[30];   //[nmcp]
   Float_t         mcmas[30];   //[nmcp]
   Float_t         mcene[30];   //[nmcp]
   Float_t         mccha[30];   //[nmcp]
   Float_t         mctim[30];   //[nmcp]
   Float_t         mcspx[30];   //[nmcp]
   Float_t         mcspy[30];   //[nmcp]
   Float_t         mcspz[30];   //[nmcp]
   Int_t           mccf0[30];   //[nmcp]
   Int_t           mccf1[30];   //[nmcp]
   Int_t           mcpa0[30];   //[nmcp]
   Int_t           mcpa1[30];   //[nmcp]
   Int_t           mcda0[30];   //[nmcp]
   Int_t           mcda1[30];   //[nmcp]
   Int_t           mcda2[30];   //[nmcp]
   Int_t           mcda3[30];   //[nmcp]
   Int_t           mcda4[30];   //[nmcp]
   Int_t           nrec;
   Int_t           rcori[1];   //[nrec]
   Int_t           rccid[1];   //[nrec]
   Int_t           rctyp[1];   //[nrec]
   Float_t         rccov[1][10];   //[nrec]
   Float_t         rcrpx[1];   //[nrec]
   Float_t         rcrpy[1];   //[nrec]
   Float_t         rcrpz[1];   //[nrec]
   Float_t         rcgpi[1];   //[nrec]
   Int_t           rcpiu[1];   //[nrec]
   Int_t           rcnpi[1];   //[nrec]
   Int_t           rcfpi[1];   //[nrec]
   Float_t         rcmox[1];   //[nrec]
   Float_t         rcmoy[1];   //[nrec]
   Float_t         rcmoz[1];   //[nrec]
   Float_t         rcmas[1];   //[nrec]
   Float_t         rcene[1];   //[nrec]
   Float_t         rccha[1];   //[nrec]
   Int_t           rcntr[1];   //[nrec]
   Int_t           rcncl[1];   //[nrec]
   Int_t           rcnrp[1];   //[nrec]
   Int_t           rcftr[1];   //[nrec]
   Int_t           rcvts[1];   //[nrec]
   Int_t           rcvte[1];   //[nrec]
   Int_t           rccom[1];   //[nrec]
   Int_t           npid;
   Int_t           pityp[1];   //[npid]
   Int_t           pipdg[1];   //[npid]
   Float_t         pillh[1];   //[npid]
   Int_t           pialg[1];   //[npid]
   Int_t           ntrk;
   Int_t           trori[1];   //[ntrk]
   Int_t           trtyp[1];   //[ntrk]
   Float_t         trch2[1];   //[ntrk]
   Int_t           trndf[1];   //[ntrk]
   Float_t         tredx[1];   //[ntrk]
   Float_t         trede[1];   //[ntrk]
   Float_t         trrih[1];   //[ntrk]
   Int_t           trshn[1][12];   //[ntrk]
   Int_t           trnts[1];   //[ntrk]
   Int_t           trfts[1];   //[ntrk]
   Int_t           trsip[1];   //[ntrk]
   Int_t           trsfh[1];   //[ntrk]
   Int_t           trslh[1];   //[ntrk]
   Int_t           trsca[1];   //[ntrk]
   Int_t           ntrst;
   Int_t           tsloc[1];   //[ntrst]
   Float_t         tsdze[1];   //[ntrst]
   Float_t         tsphi[1];   //[ntrst]
   Float_t         tsome[1];   //[ntrst]
   Float_t         tszze[1];   //[ntrst]
   Float_t         tstnl[1];   //[ntrst]
   Float_t         tscov[1][15];   //[ntrst]
   Float_t         tsrpx[1];   //[ntrst]
   Float_t         tsrpy[1];   //[ntrst]
   Float_t         tsrpz[1];   //[ntrst]
   Int_t           nsth;
   Int_t           stori[8749];   //[nsth]
   Int_t           stci0[8749];   //[nsth]
   Int_t           stci1[8749];   //[nsth]
   Double_t        stpox[8749];   //[nsth]
   Double_t        stpoy[8749];   //[nsth]
   Double_t        stpoz[8749];   //[nsth]
   Float_t         stedp[8749];   //[nsth]
   Float_t         sttim[8749];   //[nsth]
   Float_t         stmox[8749];   //[nsth]
   Float_t         stmoy[8749];   //[nsth]
   Float_t         stmoz[8749];   //[nsth]
   Float_t         stptl[8749];   //[nsth]
   Int_t           stmcp[8749];   //[nsth]
   Int_t           nsch;
   Int_t           scori[1342];   //[nsch]
   Int_t           scci0[1342];   //[nsch]
   Int_t           scci1[1342];   //[nsch]
   Float_t         scpox[1342];   //[nsch]
   Float_t         scpoy[1342];   //[nsch]
   Float_t         scpoz[1342];   //[nsch]
   Float_t         scene[1342];   //[nsch]
   Float_t         sctime[1342];   //[nsch]
   Int_t           r2mnrel;
   Int_t           r2mf[1];   //[r2mnrel]
   Int_t           r2mt[1];   //[r2mnrel]
   Float_t         r2mw[1];   //[r2mnrel]
  // I don't know what all these variables mean

  // List of branches (they are all pointers)
   TBranch        *b_evevt;   //!
   TBranch        *b_evrun;   //!
   TBranch        *b_evwgt;   //!
   TBranch        *b_evtim;   //!
   TBranch        *b_evsig;   //!
   TBranch        *b_evene;   //!
   TBranch        *b_evpoe;   //!
   TBranch        *b_evpop;   //!
   TBranch        *b_evnch;   //!
   TBranch        *b_evpro;   //!
   TBranch        *b_nmcp;   //!
   TBranch        *b_mcori;   //!
   TBranch        *b_mcpdg;   //!
   TBranch        *b_mcgst;   //!
   TBranch        *b_mcsst;   //!
   TBranch        *b_mcvtx;   //!
   TBranch        *b_mcvty;   //!
   TBranch        *b_mcvtz;   //!
   TBranch        *b_mcepx;   //!
   TBranch        *b_mcepy;   //!
   TBranch        *b_mcepz;   //!
   TBranch        *b_mcmox;   //!
   TBranch        *b_mcmoy;   //!
   TBranch        *b_mcmoz;   //!
   TBranch        *b_mcmas;   //!
   TBranch        *b_mcene;   //!
   TBranch        *b_mccha;   //!
   TBranch        *b_mctim;   //!
   TBranch        *b_mcspx;   //!
   TBranch        *b_mcspy;   //!
   TBranch        *b_mcspz;   //!
   TBranch        *b_mccf0;   //!
   TBranch        *b_mccf1;   //!
   TBranch        *b_mcpa0;   //!
   TBranch        *b_mcpa1;   //!
   TBranch        *b_mcda0;   //!
   TBranch        *b_mcda1;   //!
   TBranch        *b_mcda2;   //!
   TBranch        *b_mcda3;   //!
   TBranch        *b_mcda4;   //!
   TBranch        *b_nrec;   //!
   TBranch        *b_rcori;   //!
   TBranch        *b_rccid;   //!
   TBranch        *b_rctyp;   //!
   TBranch        *b_rccov;   //!
   TBranch        *b_rcrpx;   //!
   TBranch        *b_rcrpy;   //!
   TBranch        *b_rcrpz;   //!
   TBranch        *b_rcgpi;   //!
   TBranch        *b_rcpiu;   //!
   TBranch        *b_rcnpi;   //!
   TBranch        *b_rcfpi;   //!
   TBranch        *b_rcmox;   //!
   TBranch        *b_rcmoy;   //!
   TBranch        *b_rcmoz;   //!
   TBranch        *b_rcmas;   //!
   TBranch        *b_rcene;   //!
   TBranch        *b_rccha;   //!
   TBranch        *b_rcntr;   //!
   TBranch        *b_rcncl;   //!
   TBranch        *b_rcnrp;   //!
   TBranch        *b_rcftr;   //!
   TBranch        *b_rcvts;   //!
   TBranch        *b_rcvte;   //!
   TBranch        *b_rccom;   //!
   TBranch        *b_npid;   //!
   TBranch        *b_pityp;   //!
   TBranch        *b_pipdg;   //!
   TBranch        *b_pillh;   //!
   TBranch        *b_pialg;   //!
   TBranch        *b_ntrk;   //!
   TBranch        *b_trori;   //!
   TBranch        *b_trtyp;   //!
   TBranch        *b_trch2;   //!
   TBranch        *b_trndf;   //!
   TBranch        *b_tredx;   //!
   TBranch        *b_trede;   //!
   TBranch        *b_trrih;   //!
   TBranch        *b_trshn;   //!
   TBranch        *b_trnts;   //!
   TBranch        *b_trfts;   //!
   TBranch        *b_trsip;   //!
   TBranch        *b_trsfh;   //!
   TBranch        *b_trslh;   //!
   TBranch        *b_trsca;   //!
   TBranch        *b_ntrst;   //!
   TBranch        *b_tsloc;   //!
   TBranch        *b_tsdze;   //!
   TBranch        *b_tsphi;   //!
   TBranch        *b_tsome;   //!
   TBranch        *b_tszze;   //!
   TBranch        *b_tstnl;   //!
   TBranch        *b_tscov;   //!
   TBranch        *b_tsrpx;   //!
   TBranch        *b_tsrpy;   //!
   TBranch        *b_tsrpz;   //!
   TBranch        *b_nsth;   //!
   TBranch        *b_stori;   //!
   TBranch        *b_stci0;   //!
   TBranch        *b_stci1;   //!
   TBranch        *b_stpox;   //!
   TBranch        *b_stpoy;   //!
   TBranch        *b_stpoz;   //!
   TBranch        *b_stedp;   //!
   TBranch        *b_sttim;   //!
   TBranch        *b_stmox;   //!
   TBranch        *b_stmoy;   //!
   TBranch        *b_stmoz;   //!
   TBranch        *b_stptl;   //!
   TBranch        *b_stmcp;   //!
   TBranch        *b_nsch;   //!
   TBranch        *b_scori;   //!
   TBranch        *b_scci0;   //!
   TBranch        *b_scci1;   //!
   TBranch        *b_scpox;   //!
   TBranch        *b_scpoy;   //!
   TBranch        *b_scpoz;   //!
   TBranch        *b_scene;   //!
   TBranch        *b_sctime;   //!
   TBranch        *b_r2mnrel;   //!
   TBranch        *b_r2mf;   //!
   TBranch        *b_r2mt;   //!
   TBranch        *b_r2mw;   //!
  

  EcalSimHandler(TString tree_s);
  EcalSimHandler(TList *f=0);
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
// end the ifndef in the first part

#ifdef EcalSimHandler_cxx
// if defined, then...
EcalSimHandler::EcalSimHandler(TString tree_s) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  // if (tree == 0) {
  //    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../data/myreco_PfoAnalysis.root");
  //    if (!f || !f->IsOpen()) {
  //       f = new TFile("../data/myreco_PfoAnalysis.root");
  //    }
  //    f->GetObject("PfoAnalysisTree",tree);

  // }
  // TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(tree_s);
  TFile *f;
  if (!gSystem->AccessPathName(tree_s)) {
    f = new TFile(tree_s);
  }else{
    throw 1;
  }

  TTree *tree = (TTree*)f->Get("MyLCTuple");
  Init(tree);
}

EcalSimHandler::EcalSimHandler(TList *f) : fChain(0) 
{
   // if parameter tree is not specified (or zero), use a list of of files provided as input

   TIter next(f);
   TSystemFile *file;
   TString fname;
   while((file = (TSystemFile*)next())){
      fname = file->GetName();
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fname);
      TTree *tree=0;
      f->GetObject("MyLCTuple",tree);
      Init(tree);
   }
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
  // 
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evevt", &evevt, &b_evevt);
   fChain->SetBranchAddress("evrun", &evrun, &b_evrun);
   fChain->SetBranchAddress("evwgt", &evwgt, &b_evwgt);
   fChain->SetBranchAddress("evtim", &evtim, &b_evtim);
   fChain->SetBranchAddress("evsig", &evsig, &b_evsig);
   fChain->SetBranchAddress("evene", &evene, &b_evene);
   fChain->SetBranchAddress("evpoe", &evpoe, &b_evpoe);
   fChain->SetBranchAddress("evpop", &evpop, &b_evpop);
   fChain->SetBranchAddress("evnch", &evnch, &b_evnch);
   fChain->SetBranchAddress("evpro", &evpro, &b_evpro);
   fChain->SetBranchAddress("nmcp", &nmcp, &b_nmcp);
   fChain->SetBranchAddress("mcori", mcori, &b_mcori);
   fChain->SetBranchAddress("mcpdg", mcpdg, &b_mcpdg);
   fChain->SetBranchAddress("mcgst", mcgst, &b_mcgst);
   fChain->SetBranchAddress("mcsst", mcsst, &b_mcsst);
   fChain->SetBranchAddress("mcvtx", mcvtx, &b_mcvtx);
   fChain->SetBranchAddress("mcvty", mcvty, &b_mcvty);
   fChain->SetBranchAddress("mcvtz", mcvtz, &b_mcvtz);
   fChain->SetBranchAddress("mcepx", mcepx, &b_mcepx);
   fChain->SetBranchAddress("mcepy", mcepy, &b_mcepy);
   fChain->SetBranchAddress("mcepz", mcepz, &b_mcepz);
   fChain->SetBranchAddress("mcmox", mcmox, &b_mcmox);
   fChain->SetBranchAddress("mcmoy", mcmoy, &b_mcmoy);
   fChain->SetBranchAddress("mcmoz", mcmoz, &b_mcmoz);
   fChain->SetBranchAddress("mcmas", mcmas, &b_mcmas);
   fChain->SetBranchAddress("mcene", mcene, &b_mcene);
   fChain->SetBranchAddress("mccha", mccha, &b_mccha);
   fChain->SetBranchAddress("mctim", mctim, &b_mctim);
   fChain->SetBranchAddress("mcspx", mcspx, &b_mcspx);
   fChain->SetBranchAddress("mcspy", mcspy, &b_mcspy);
   fChain->SetBranchAddress("mcspz", mcspz, &b_mcspz);
   fChain->SetBranchAddress("mccf0", mccf0, &b_mccf0);
   fChain->SetBranchAddress("mccf1", mccf1, &b_mccf1);
   fChain->SetBranchAddress("mcpa0", mcpa0, &b_mcpa0);
   fChain->SetBranchAddress("mcpa1", mcpa1, &b_mcpa1);
   fChain->SetBranchAddress("mcda0", mcda0, &b_mcda0);
   fChain->SetBranchAddress("mcda1", mcda1, &b_mcda1);
   fChain->SetBranchAddress("mcda2", mcda2, &b_mcda2);
   fChain->SetBranchAddress("mcda3", mcda3, &b_mcda3);
   fChain->SetBranchAddress("mcda4", mcda4, &b_mcda4);
   fChain->SetBranchAddress("nrec", &nrec, &b_nrec);
   fChain->SetBranchAddress("rcori", &rcori, &b_rcori);
   fChain->SetBranchAddress("rccid", &rccid, &b_rccid);
   fChain->SetBranchAddress("rctyp", &rctyp, &b_rctyp);
   fChain->SetBranchAddress("rccov", &rccov, &b_rccov);
   fChain->SetBranchAddress("rcrpx", &rcrpx, &b_rcrpx);
   fChain->SetBranchAddress("rcrpy", &rcrpy, &b_rcrpy);
   fChain->SetBranchAddress("rcrpz", &rcrpz, &b_rcrpz);
   fChain->SetBranchAddress("rcgpi", &rcgpi, &b_rcgpi);
   fChain->SetBranchAddress("rcpiu", &rcpiu, &b_rcpiu);
   fChain->SetBranchAddress("rcnpi", &rcnpi, &b_rcnpi);
   fChain->SetBranchAddress("rcfpi", &rcfpi, &b_rcfpi);
   fChain->SetBranchAddress("rcmox", &rcmox, &b_rcmox);
   fChain->SetBranchAddress("rcmoy", &rcmoy, &b_rcmoy);
   fChain->SetBranchAddress("rcmoz", &rcmoz, &b_rcmoz);
   fChain->SetBranchAddress("rcmas", &rcmas, &b_rcmas);
   fChain->SetBranchAddress("rcene", &rcene, &b_rcene);
   fChain->SetBranchAddress("rccha", &rccha, &b_rccha);
   fChain->SetBranchAddress("rcntr", &rcntr, &b_rcntr);
   fChain->SetBranchAddress("rcncl", &rcncl, &b_rcncl);
   fChain->SetBranchAddress("rcnrp", &rcnrp, &b_rcnrp);
   fChain->SetBranchAddress("rcftr", &rcftr, &b_rcftr);
   fChain->SetBranchAddress("rcvts", &rcvts, &b_rcvts);
   fChain->SetBranchAddress("rcvte", &rcvte, &b_rcvte);
   fChain->SetBranchAddress("rccom", &rccom, &b_rccom);
   fChain->SetBranchAddress("npid", &npid, &b_npid);
   fChain->SetBranchAddress("pityp", &pityp, &b_pityp);
   fChain->SetBranchAddress("pipdg", &pipdg, &b_pipdg);
   fChain->SetBranchAddress("pillh", &pillh, &b_pillh);
   fChain->SetBranchAddress("pialg", &pialg, &b_pialg);
   fChain->SetBranchAddress("ntrk", &ntrk, &b_ntrk);
   fChain->SetBranchAddress("trori", &trori, &b_trori);
   fChain->SetBranchAddress("trtyp", &trtyp, &b_trtyp);
   fChain->SetBranchAddress("trch2", &trch2, &b_trch2);
   fChain->SetBranchAddress("trndf", &trndf, &b_trndf);
   fChain->SetBranchAddress("tredx", &tredx, &b_tredx);
   fChain->SetBranchAddress("trede", &trede, &b_trede);
   fChain->SetBranchAddress("trrih", &trrih, &b_trrih);
   fChain->SetBranchAddress("trshn", &trshn, &b_trshn);
   fChain->SetBranchAddress("trnts", &trnts, &b_trnts);
   fChain->SetBranchAddress("trfts", &trfts, &b_trfts);
   fChain->SetBranchAddress("trsip", &trsip, &b_trsip);
   fChain->SetBranchAddress("trsfh", &trsfh, &b_trsfh);
   fChain->SetBranchAddress("trslh", &trslh, &b_trslh);
   fChain->SetBranchAddress("trsca", &trsca, &b_trsca);
   fChain->SetBranchAddress("ntrst", &ntrst, &b_ntrst);
   fChain->SetBranchAddress("tsloc", &tsloc, &b_tsloc);
   fChain->SetBranchAddress("tsdze", &tsdze, &b_tsdze);
   fChain->SetBranchAddress("tsphi", &tsphi, &b_tsphi);
   fChain->SetBranchAddress("tsome", &tsome, &b_tsome);
   fChain->SetBranchAddress("tszze", &tszze, &b_tszze);
   fChain->SetBranchAddress("tstnl", &tstnl, &b_tstnl);
   fChain->SetBranchAddress("tscov", &tscov, &b_tscov);
   fChain->SetBranchAddress("tsrpx", &tsrpx, &b_tsrpx);
   fChain->SetBranchAddress("tsrpy", &tsrpy, &b_tsrpy);
   fChain->SetBranchAddress("tsrpz", &tsrpz, &b_tsrpz);
   fChain->SetBranchAddress("nsth", &nsth, &b_nsth);
   fChain->SetBranchAddress("stori", stori, &b_stori);
   fChain->SetBranchAddress("stci0", stci0, &b_stci0);
   fChain->SetBranchAddress("stci1", stci1, &b_stci1);
   fChain->SetBranchAddress("stpox", stpox, &b_stpox);
   fChain->SetBranchAddress("stpoy", stpoy, &b_stpoy);
   fChain->SetBranchAddress("stpoz", stpoz, &b_stpoz);
   fChain->SetBranchAddress("stedp", stedp, &b_stedp);
   fChain->SetBranchAddress("sttim", sttim, &b_sttim);
   fChain->SetBranchAddress("stmox", stmox, &b_stmox);
   fChain->SetBranchAddress("stmoy", stmoy, &b_stmoy);
   fChain->SetBranchAddress("stmoz", stmoz, &b_stmoz);
   fChain->SetBranchAddress("stptl", stptl, &b_stptl);
   fChain->SetBranchAddress("stmcp", stmcp, &b_stmcp);
   fChain->SetBranchAddress("nsch", &nsch, &b_nsch);
   fChain->SetBranchAddress("scori", scori, &b_scori);
   fChain->SetBranchAddress("scci0", scci0, &b_scci0);
   fChain->SetBranchAddress("scci1", scci1, &b_scci1);
   fChain->SetBranchAddress("scpox", scpox, &b_scpox);
   fChain->SetBranchAddress("scpoy", scpoy, &b_scpoy);
   fChain->SetBranchAddress("scpoz", scpoz, &b_scpoz);
   fChain->SetBranchAddress("scene", scene, &b_scene);
   fChain->SetBranchAddress("sctime", sctime, &b_sctime);
   fChain->SetBranchAddress("r2mnrel", &r2mnrel, &b_r2mnrel);
   fChain->SetBranchAddress("r2mf", &r2mf, &b_r2mf);
   fChain->SetBranchAddress("r2mt", &r2mt, &b_r2mt);
   fChain->SetBranchAddress("r2mw", &r2mw, &b_r2mw);
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
