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
  float binsize_h1htime=0.001;

  TH3D *h3hpos;
  TH3D *h3hpos1;
  TH1F *h1htime;

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
        //   h3hpos=new TH3D(TString::Format("h3hpos_%lld",jentry),"Hist in 3D",
        //   5,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),
        //   5,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),
        //   5,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));

        //   h3hpos1 = new TH3D(TString::Format("h3hpos1_%lld",jentry),"Hist in 3D",
        //   100,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),
        //   100,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),
        //   100,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));
        // int nbins=std::ceil((TMath::MaxElement(nsch,sctime)-TMath::MinElement(nsch,sctime))/binsize_h1htime);
        h1htime = new TH1F(TString::Format("h1htime_%lld",jentry), "Hist 1D time of hits of event ", 1000/0.01, 0, 100);
        // h1htime = new TH1F(TString::Format("h1htime_%lld",jentry), "Hist 1D time of hits of event ", nbins, 0, TMath::MaxElement(nsch,sctime));
        // h1htime = new TH1F(TString::Format("h1htime_%lld",jentry), "Hist 1D time of hits of event "+std::to_string(jentry), nbins, 0, TMath::MaxElement(nsch,sctime));
        // h1htime->SetTitle("Hist 1D time of hits of event "+std::to_string(jentry)+";time (ps);counts");
        h1htime->SetTitle("Hist 1D time of hits of event ;time (ps);counts");

        // hists[jentry]=new TH3D(TString::Format("h3hpos_%d",jentry),"Hist in 3D",100,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),200,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),300,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));
        // h3hpos->SetTitle("Hist in 3D;X;Y;Z");
        // h3hpos1->SetTitle("Hist in 3D;X;Y;Z");

        for (int ihit=0; ihit<nsch;ihit++)
        {
          cout<<"hit "<<ihit<<" at time "<<sctime[ihit]<<endl;
          // h3hpos->Fill((Double_t)scpox[ihit],(Double_t)scpoy[ihit],(Double_t)scpoz[ihit]);
          // h3hpos->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
          // h3hpos1->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
          h1htime->Fill(sctime[ihit]);
          // cout << "hit: " << ihit << "\t x: " << scpox[ihit] << "\t y: " << scpoy[ihit] << "\t z: " << scpoz[ihit] << endl;
        }
      }
    // TIL HERE
  }

  // MODIFY FROM HERE
  cout<<"\tTotal hits: "<<tothits<<endl;
  // h3hpos->Write();
  // h3hpos1->Write();
  h1htime->Write();
  storemyfile->Close();

  // TIL HERE
}
