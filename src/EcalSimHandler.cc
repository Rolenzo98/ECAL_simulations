#define EcalSimHandler_cxx
#include "EcalSimHandler.hh"
#include "CreateHisto.hh"




void EcalSimHandler::Loop()
{

  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();

  // MODIFY FROM HERE

  // TH3F * hist = new TH3F("hist","hist",100,-2000,2000,100,1000,5000,100,-2000,2000);

  // TIL HERE

  Long64_t nbytes = 0, nb = 0;

  // Event Loop
  int tothits = 0;

  TH3D *h3h;

  // TH1D 
  TFile *storemyfile = new TFile("myfileh3h.root", "recreate");

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
  {
    cout<<"jentry= "<<jentry<<endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;

    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (Cut(ientry) < 0)
      continue;

    // MODIFY FROM HERe
      // cout << "Event : " << jentry << "\tHits: " << nsch << "\tSize array: " << sizeof(scpox) / sizeof(Float_t) << endl;
      tothits+=nsch;

      /*
      // even if the number of hits is less than the size of the array, the remaining
      // entries are filled with numbers, thus the minimum (or max) o the values of the 
      // hits is not the same of the values of the array in its entireness

      cout<<"min element in scpox-size "<<TMath::MinElement(sizeof(scpox) / sizeof(Float_t), scpox)<<endl;
      cout<<"min element in scpox-hits "<<TMath::MinElement(nsch, scpox)<<endl;
      if (TMath::MinElement(sizeof(scpox) / sizeof(Float_t), scpox)-TMath::MinElement(nsch, scpox)!=0)
      {
        cout<<"sizelocmin: "<<TMath::LocMin(sizeof(scpox) / sizeof(Float_t), scpox)<<" hitslocmin: "<<TMath::LocMin(nsch, scpox)<<endl;
        for (int ihit=0; ihit<sizeof(scpox) / sizeof(Float_t);ihit++)
        {
          cout << "hit: " << ihit << "\t x: " << scpox[ihit] <<endl;
        }      
      }
      */

      if (jentry==10)
      {
        h3h = new TH3D(TString::Format("h3h_%lld",jentry),"Hist in 3D",
          100,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),
          200,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),
          300,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));

        // hists[jentry]=new TH3D(TString::Format("h3h_%d",jentry),"Hist in 3D",100,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),200,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),300,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));
        h3h->SetTitle("Hist in 3D;X;Y;Z");

        for (int ihit=0; ihit<nsch;ihit++)
        {
          // h3h->Fill((Double_t)scpox[ihit],(Double_t)scpoy[ihit],(Double_t)scpoz[ihit]);
          h3h->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
          // cout << "hit: " << ihit << "\t x: " << scpox[ihit] << "\t y: " << scpoy[ihit] << "\t z: " << scpoz[ihit] << endl;
        }
      }
    // TIL HERE
  }

  // MODIFY FROM HERE
  cout<<"\tTotal hits: "<<tothits<<endl;
  h3h->Write();
  storemyfile->Close();

  // TIL HERE
}
