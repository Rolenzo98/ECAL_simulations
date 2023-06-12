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
  double tbinlowedge[nbinlowedge];
  double ebinlowedge[nbinlowedge];

  TH1F *h1htime;
  TH1F *h1hx;
  TH1F *h1hy;
  TH1F *h1hz;

  TH2F *h2hxytime[nbin];
  TH2F *h2hyztime[nbin];
  TH2F *h2hxztime[nbin];
  TH3D *h3hpostime[nbin];
  TH3D *h3hposenergy[nbin];

  TH3D *h3hpos;


  for (int i=0;i<nbinlowedge;i++)
  {
    int ipowt=i-10;
    int ipowe=i-nbinlowedge;
    tbinlowedge[i]=std::pow(2,ipowt);    
    ebinlowedge[i]=std::pow(2,ipowe);

    cout<<"Bin "<<i<<":\ttime: "<<tbinlowedge[i]<<"\tenergy: "<<ebinlowedge[i]<<endl;
  }


  for (int i=0;i<nbin;i++)
  {
    TString h2hxytime_name=TString::Format("h2hxytime_bin%d",i);
    TString h2hyztime_name=TString::Format("h2hyztime_bin%d",i);
    TString h2hxztime_name=TString::Format("h2hxztime_bin%d",i);
    TString h3hpostime_name=TString::Format("h3hpostime_bin%d",i);
    TString h3hposenergy_name=TString::Format("h3hposenergy_bin%d",i);

    h2hxytime[i]=new TH2F(h2hxytime_name,h2hxytime_name,100,-2000,2000,100,1800,3500);
    h2hyztime[i]=new TH2F(h2hyztime_name,h2hyztime_name,100,1800,3500,100,-3000,3000);
    h2hxztime[i]=new TH2F(h2hxztime_name,h2hxztime_name,100,-2000,2000,100,-3000,3000);

    
    h3hpostime[i]= new TH3D(h3hpostime_name,h3hpostime_name,
    100,-2000,2000,
    100,-1000,5000,
    100,-3000,3000);    
    h3hposenergy[i]= new TH3D(h3hposenergy_name,h3hposenergy_name,
    100,-2000,2000,
    100,-1000,5000,
    100,-3000,3000);
  }

  double energyevent;
  for (Long64_t jentry =0; jentry<nentries; jentry++)
  {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;

    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (Cut(ientry) < 0)
      continue;
energyevent=0;
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
       for (int ihit=0; ihit<nsch;ihit++)
          {
            // cout<<"energy of hit is "<<scene[ihit]<<endl;
            energyevent+=scene[ihit];
          }

      if (jentry==10)
      {
        h3hpos= new TH3D(TString::Format("h3hpos_%lld",jentry),"Hist in 3D",
        100,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),
        100,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),
        100,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));
        h3hpos->SetTitle("Hist in 3D;X;Y;Z");        
        
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
          // h1hx->
          h3hpos->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
          for (int i=0;i<nbin;i++)
          {
            if (sctime[ihit]>tbinlowedge[i]&&sctime[ihit]<tbinlowedge[i+1])
            {
              h2hxytime[i]->Fill(scpox[ihit],scpoy[ihit]);
              h2hyztime[i]->Fill(scpoy[ihit],scpoz[ihit]);
              h2hxztime[i]->Fill(scpox[ihit],scpoz[ihit]);
              h3hpostime[i]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
              break;
            }
            if (scene[ihit]>ebinlowedge[i]&&scene[ihit]<ebinlowedge[i+1])
            {
              h3hposenergy[i]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
              break;
            }
          }

          // cout << "hit: " << ihit << "\t x: " << scpox[ihit] << "\t y: " << scpoy[ihit] << "\t z: " << scpoz[ihit] << endl;
        }
        // break;
        
      }
    // TIL HERE
    // cout<<"energy of the event "<<jentry<<" is "<<energyevent*<<endl;
  }
cout<<"energy of the event is "<<energyevent<<endl;
  // MODIFY FROM HERE
  cout<<"\tTotal hits: "<<tothits<<endl;
  TFile *storemyfile = new TFile("myfileh3h.root", "recreate");

  TCanvas *c_2timexy=new TCanvas("c_2timexy","c_2timexy",500,500);

  for (int i=0;i<nbin;i++)
  {
    if (h2hxytime[i]->GetEntries()==0)
    {
      continue;
    }
    h2hxytime[i]->SetTitle(TString::Format("h2hxytime_bin%d_(%f-%f);X;Y",i,tbinlowedge[i],tbinlowedge[i+1]));

    h2hxytime[i]->SetMarkerStyle(20);
    h2hxytime[i]->SetMarkerSize(0.5);
    // h2hxytime[i]->SetMarkerColor(i);;
    h2hxytime[i]->Draw();    
  c_2timexy->Print("~/Desktop/c_2timexy.gif+20");  
  }
  c_2timexy->Print("~/Desktop/c_2timexy.gif++");  

    
  TCanvas *c_2timeyz=new TCanvas("c_2timeyz","c_2timeyz",500,500);
  for (int i=0;i<nbin;i++)
  {
    if (h2hyztime[i]->GetEntries()==0)
      continue;
    h2hyztime[i]->SetTitle(TString::Format("h2hyztime_bin%d_(%f-%f);Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]));

    h2hyztime[i]->SetMarkerStyle(20);
    h2hyztime[i]->SetMarkerSize(0.5);
    // h2hyztime[i]->SetMarkerColor(i);;
    h2hyztime[i]->Draw();    
  c_2timeyz->Print("~/Desktop/c_2timeyz.gif+20");
  }
  c_2timeyz->Print("~/Desktop/c_2timeyz.gif++");
    
  TCanvas *c_2timexz=new TCanvas("c_2timexz","c_2timexz",500,500);
  for (int i=0;i<nbin;i++)
  {
    if (h2hxztime[i]->GetEntries()==0)
      continue;
    h2hxztime[i]->SetTitle(TString::Format("h2hxztime%d_(%f-%f);X;Z",i,tbinlowedge[i],tbinlowedge[i+1]));

    h2hxztime[i]->SetMarkerStyle(20);
    h2hxztime[i]->SetMarkerSize(0.5);
    // h2hxztime[i]->SetMarkerColor(i);
    h2hxztime[i]->Draw();
  c_2timexz->Print("~/Desktop/c_2timexz.gif+20");  
  }
  c_2timexz->Print("~/Desktop/c_2timexz.gif++");  


  TCanvas *c_time=new TCanvas("ctime","ctime",500,500);
  for (int i=0;i<nbin;i++)
  {
    h3hpostime[i]->SetTitle(TString::Format("h3hpostime_bin%d_(%f-%f);X;Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]));

    h3hpostime[i]->SetMarkerStyle(20);
    h3hpostime[i]->SetMarkerSize(0.5);
    h3hpostime[i]->SetMarkerColor(i);;
    h3hpostime[i]->Draw("BOX SAME");    
  }
  c_time->Write();

  TCanvas *c_energy=new TCanvas("cenergy","cenergy",500,500);
  for (int i=0;i<nbin;i++)
  {
    h3hposenergy[i]->SetTitle(TString::Format("h3hposenergy_bin%d_(%f-%f)",i,ebinlowedge[i],ebinlowedge[i+1])+";X;Y;Z");

    h3hposenergy[i]->SetMarkerStyle(20);
    h3hposenergy[i]->SetMarkerSize(0.5);
    h3hposenergy[i]->SetMarkerColor(i);;
    h3hposenergy[i]->Draw("BOX SAME");  
  }
  c_energy->Write();

//   for (int i=0;i<nbin;i++)
//   {
//     h2hxytime[i]->SetTitle(TString::Format("h2hxytime_bin%d_(%f-%f);X;Y",i,tbinlowedge[i],tbinlowedge[i+1]));
//     h2hxytime[i]->Write();
//   }

//   for (int i=0;i<nbin;i++)
//   {
//     h2hyztime[i]->SetTitle(TString::Format("h2hyztime_bin%d_(%f-%f);Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]));
//     h2hyztime[i]->Write();
//   }

// for (int i=0;i<nbin;i++)
//   {
//     h2hxztime[i]->SetTitle(TString::Format("h2hxztime_bin%d_(%f-%f);X;Z",i,tbinlowedge[i],tbinlowedge[i+1]));
//     h2hxztime[i]->Write();
//   }
  
    // h3hpostime[16]->SetMarkerColor(kRed);
    // h3hpostime[11]->SetMarkerColor(kBlue);
    // h3hpostime[12]->SetMarkerColor(kGreen);
  for (int i=0;i<nbin;i++)
  {
    h3hpostime[i]->Write();
  }  
  
  // for (int i=0;i<nbin;i++)
  // {
  //   // h3hposenergy[i]->SetTitle(TString::Format("h3hposenergy_bin%d_(%f-%f);X;Y;Z",i,ebinlowedge[i],ebinlowedge[i+1]));
  //   // h3hposenergy[i]->SetTitle(TString::Format("h3hposenergy_bin;X;Y;Z"));
  //   h3hposenergy[i]->Write();
  // }


  h3hpos->Write();
  // h1htime->Write();
  storemyfile->Close();

  // TIL HERE
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by program: "<< duration.count() << " microseconds" << endl;

}
