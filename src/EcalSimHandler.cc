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

  int nbin=24;
  int nbinlowedge=nbin+1;
  double binlowedge[nbinlowedge];

  TH1F *h1htime;

  TH2F *h2htime[nbin];
  TH3D *h3hpostime[nbin];

  TH3D *h3hpos;
  TH3D *h3hpostimeTOT;

  for (int i=0;i<nbinlowedge;i++)
  {
    int ipow=i-10;
    binlowedge[i]=std::pow(2,ipow);
    cout<<"Bin "<<i<<" starts at time "<<binlowedge[i]<<endl;

  }

  for (int i=0;i<nbin;i++)
  {
    TString h2htime_name=TString::Format("h2htime_bin%d",i);
    TString h3hpostime_name=TString::Format("h3hpostime_bin%d",i);

    h2htime[i]=new TH2F(h2htime_name,h2htime_name,100,-500,500,100,-0,3000);

    
    h3hpostime[i]= new TH3D(h3hpostime_name,h3hpostime_name,
    100,-2000,2000,
    100,-1000,5000,
    100,-3000,3000);
  }


  
  for (Long64_t jentry =0; jentry<nentries; jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;

    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (Cut(ientry) < 0)
      continue;

    // MODIFY FROM HERe
      cout << "Event : " << jentry << "\tHits: " << nsch << "\tSize array: " << sizeof(scpox) / sizeof(Float_t) << endl;
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

        // h3hpos= new TH3D(TString::Format("h3hpos_%lld",jentry),"Hist in 3D",
        // 100,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),
        // 100,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),
        // 100,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));
        // h3hpos->SetTitle("Hist in 3D;X;Y;Z");        
        
        // h3hpostimeTOT= new TH3D(TString::Format("h3hpostimeTOT_%lld",jentry),"Hist in 3D",
        // 100,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),
        // 100,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),
        // 100,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));
        // h3hpostimeTOT->SetTitle("Hist in 3D;X;Y;Z");
        

        // int nbins=std::ceil((TMath::MaxElement(nsch,sctime)-TMath::MinElement(nsch,sctime))/binsize_h1htime);
        // h1htime = new TH1F(TString::Format("h1htime_%lld",jentry), 
        // "Hist 1D time of hits of event ", nbinsarr,  expvalarr);
        // h1htime->SetTitle("Hist 1D time of hits of event ;time (ns);counts");

       

        for (int ihit=0; ihit<nsch;ihit++)
        {
          // cout<<"hit "<<ihit<<" at time "<<sctime[ihit]<<endl;
          // h3hpos->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
          // h1htime->Fill(sctime[ihit]);

          for (int i=0;i<nbin;i++)
          {
            if (sctime[ihit]>binlowedge[i]&&sctime[ihit]<binlowedge[i+1])
            {
              h2htime[i]->Fill(scpox[ihit],scpoy[ihit]);
              h3hpostime[i]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
              break;
            }
          }

          // cout << "hit: " << ihit << "\t x: " << scpox[ihit] << "\t y: " << scpoy[ihit] << "\t z: " << scpoz[ihit] << endl;
        }
        // break;
      }
    // TIL HERE
  }

  // MODIFY FROM HERE
  cout<<"\tTotal hits: "<<tothits<<endl;
  TFile *storemyfile = new TFile("myfileh3h.root", "recreate");


  TCanvas *c1=new TCanvas("c1","c1",500,500);
  // h3hpostime[16]->SetMarkerStyle(20);
  // h3hpostime[11]->SetMarkerStyle(20);
  // h3hpostime[12]->SetMarkerStyle(20);
  // h3hpostime[16]->SetMarkerSize(2);
  // h3hpostime[11]->SetMarkerSize(2);
  // h3hpostime[12]->SetMarkerSize(2);
  //     h3hpostime[16]->SetMarkerColor(kRed);
  //   h3hpostime[11]->SetMarkerColor(kBlue);
  //   h3hpostime[12]->SetMarkerColor(kGreen);

    // h3hpostime[13]->SetMarkerColor();
    // h3hpostime[14]->SetMarkerColor(5);
    // h3hpostime[15]->SetMarkerColor(6);

    // h3hpostime[16]->Draw(" SAME");
    // h3hpostime[11]->Draw(" SAME");
    // h3hpostime[12]->Draw(" SAME");
    // h3hpostime[13]->Draw("BOX SAME");
    // h3hpostime[14]->Draw("BOX SAME");
    // h3hpostime[15]->Draw("BOX  SAME");
  for (int i=0;i<nbin;i++)
  {
    h3hpostime[i]->SetMarkerStyle(20);
    h3hpostime[11]->SetMarkerSize(0.2);
    h3hpostime[i]->SetMarkerColor(i);;
    h3hpostime[i]->Draw("SAME");
  }
  c1->Write();


  for (int i=0;i<nbin;i++)
  {
    h2htime[i]->SetTitle(TString::Format("h2htime_bin%d_(%f-%f)",i,binlowedge[i],binlowedge[i+1]));
    h2htime[i]->Write();

  }
  
    //   h3hpostime[16]->SetMarkerColor(kRed);
    // h3hpostime[11]->SetMarkerColor(kBlue);
    // h3hpostime[12]->SetMarkerColor(kGreen);
  for (int i=0;i<nbin;i++)
  {
    h3hpostime[i]->SetTitle(TString::Format("h3hpostime_bin%d_(%f-%f)",i,binlowedge[i],binlowedge[i+1]));
    h3hpostime[i]->Write();
  }

  // h3hpos->Write();
  // h1htime->Write();
  storemyfile->Close();

  // TIL HERE
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by program: "<< duration.count() << " microseconds" << endl;

}
