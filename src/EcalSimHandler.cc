#define EcalSimHandler_cxx
#include "EcalSimHandler.hh"
#include "CreateHisto.hh"




void EcalSimHandler::Loop()
{

  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;


  int tothits = 0;
  // float binsize_h1htime=0.001;

  // Declaring the number of binning for the time and energy division
  int nbin=24;
  int nbinlowedge=nbin+1;
  double tbinlowedge[nbinlowedge];
  double ebinlowedge[nbinlowedge];
  double pippo[10]={0.0001,0.001,0.01,0.1,1,10,100,1000,10000,100000};

  //declaring lines for the histogram
  TLine *myline1;
  TLine *myline2;
  TLine *myline3;

  // Declaring histograms
  // declaration histograms 1D
  TH1F *h1htime;
  TH1F *h1henergy;
  TH1F *h1hx;
  TH1F *h1hy;
  TH1F *h1hz;
  // declaration histograms 2D
  TH2F *h2hxytime[nbin];
  TH2F *h2hyztime[nbin];
  TH2F *h2hxztime[nbin];
  // declaration histograms 3D
  TH3D *h3hpos;
  TH3D *h3hpostime[nbin];
  TH3D *h3hposenergy[nbin];

  // Creating the binning for the time and energy division
  for (int i=0;i<nbinlowedge;i++)
  {
    int ipowt=i-10;
    int ipowe=i-nbinlowedge;
    tbinlowedge[i]=std::pow(2,ipowt);    
    ebinlowedge[i]=std::pow(2,ipowe);
    // cout<<"Bin "<<i<<":\ttime: "<<tbinlowedge[i]<<"\tenergy: "<<ebinlowedge[i]<<endl;
  }

  // Setting the names of the histograms and initializing them
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

  // Main
  double energyevent;
  // Loop over the events
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
    // cout << "Event : " <<jentry << "\tHits: " << nsch << "\tSize array: " << sizeof(scpox) / sizeof(Float_t) << endl;
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
    
    // Selecting a specific event
    if (jentry==10)
    {
      cout<<"Event "<<jentry<<"analysis:\n"<<"Hit\tTime\t\tEnergy\tPosition"<<endl;
      // Initializing the histogram for the position of the hits in 3D      
      h3hpos=new TH3D(TString::Format("h3hpos_%lld",jentry),"Hist in 3D",
      100,TMath::MinElement(nsch, scpox),TMath::MaxElement(nsch, scpox),
      100,TMath::MinElement(nsch, scpoy),TMath::MaxElement(nsch, scpoy),
      100,TMath::MinElement(nsch, scpoz),TMath::MaxElement(nsch, scpoz));
      // cout<<"min element in sctime "<<TMath::MinElement(nbinlowedge, tbinlowedge)<<endl;
      // cout<<"max element in sctime "<<TMath::MaxElement(nbinlowedge, tbinlowedge)<<endl;
      h1htime=new TH1F(TString::Format("h1htime_%lld",jentry), 
      TString::Format("h1htime_%lld; time (ns); counts",jentry),
      nbin, tbinlowedge);

      h1henergy=new TH1F(TString::Format("h1henergy_%lld",jentry),
      TString::Format("h1henergy_%lld; energy (keV); counts",jentry),
      nbin, ebinlowedge);

      // Loop over the hits of the event
      for (int ihit=0; ihit<nsch;ihit++)
      {
        cout<<ihit<<"\t"<<sctime[ihit]<<"\t\t"<<scene[ihit]<<"\tx "<<scpox[ihit]<<" y "<<scpoy[ihit]<<" z "<<scpoz[ihit]<<endl;
        // cout<< "hit: " << ihit << "\t time : " << sctime[ihit] << "\t energy: " << scene[ihit] << endl;
        h3hpos->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
        
        // Loop over all the bins for the time and energy     
        for (int i=0;i<nbin;i++)
        {
          // Control and fill the histograms in the time bins          
          if (sctime[ihit]>tbinlowedge[i]&&sctime[ihit]<tbinlowedge[i+1])
          {
            h1htime->Fill(sctime[ihit]);
            h2hxytime[i]->Fill(scpox[ihit],scpoy[ihit]);
            h2hyztime[i]->Fill(scpoy[ihit],scpoz[ihit]);
            h2hxztime[i]->Fill(scpox[ihit],scpoz[ihit]);
            h3hpostime[i]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
            // break; // condition to exit the loop to make it faster
          }
          
          // Control and fill the histograms in the energy bins
          if (scene[ihit]>ebinlowedge[i]&&scene[ihit]<ebinlowedge[i+1])
          {
            h1henergy->Fill(scene[ihit]);
            h3hposenergy[i]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
            // break;
          }
        } // end loop over the bins
      } // end loop over the hits of the event
      // break;
    } // end if for the specific event
  } // end loop over the events

  // cout<<"energy of the event is "<<energyevent<<endl;
  cout<<"\nTotal hits: "<<tothits<<"\nTotal energy: "<<energyevent<<endl<<endl;
  if (std::filesystem::exists("gif"))
  {
    cout<<"THE folder exists"<<endl;
    if (std::filesystem::is_empty("gif"))
    {
      cout<<"THEY don't exist, crete them"<<endl;
    }
    else 
    {
      cout<<"THEY exist, remove them and recreate"<<endl;
      gSystem->Exec("rm gif/*.gif");
    }
  }
  else 
  {
    cout<<"THE folder don't exist, create gif folder and create them"<<endl;
    std::filesystem::create_directory("gif");
  }

  TFile *storemyfile = new TFile("myfileh3h.root", "recreate");

  TCanvas *c_2timexy=new TCanvas("c_2timexy","c_2timexy",500,500);
  for (int i=0;i<nbin;i++)
  {
    // if (h2hxytime[i]->GetEntries()==0)
    //   continue;
    h2hxytime[i]->SetTitle(TString::Format("h2hxytime_bin%d_(%f-%f);X;Y",i,tbinlowedge[i],tbinlowedge[i+1]));
    h2hxytime[i]->SetMarkerStyle(20);
    h2hxytime[i]->SetMarkerSize(0.5);
    // h2hxytime[i]->SetMarkerColor(i);;
    h2hxytime[i]->Draw();    
    c_2timexy->Print("gif/c_2timexy.gif+20");  
  }
  c_2timexy->Print("gif/c_2timexy.gif++");  

  TCanvas *c_2timeyz=new TCanvas("c_2timeyz","c_2timeyz",500,500);
  for (int i=0;i<nbin;i++)
  {
    // if (h2hyztime[i]->GetEntries()==0)
    //   continue;
    h2hyztime[i]->SetTitle(TString::Format("h2hyztime_bin%d_(%f-%f);Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]));
    h2hyztime[i]->SetMarkerStyle(20);
    h2hyztime[i]->SetMarkerSize(0.5);
    // h2hyztime[i]->SetMarkerColor(i);
    myline1=new TLine(1808,0, 1808, 3000);
    myline2=new TLine(2028,0, 2028, 3000);
    myline3=new TLine(34400,0, 34400, 3000);
    myline1->Draw("same");
    myline2->Draw("same");
    myline3->Draw("same");
    h2hyztime[i]->Draw();    
    c_2timeyz->Print("gif/c_2timeyz.gif+20");
  }
  c_2timeyz->Print("gif/c_2timeyz.gif++");
    
  TCanvas *c_2timexz=new TCanvas("c_2timexz","c_2timexz",500,500);
  for (int i=0;i<nbin;i++)
  {
    // if (h2hxztime[i]->GetEntries()==0)
    //   continue;
    h2hxztime[i]->SetTitle(TString::Format("h2hxztime%d_(%f-%f);X;Z",i,tbinlowedge[i],tbinlowedge[i+1]));
    h2hxztime[i]->SetMarkerStyle(20);
    h2hxztime[i]->SetMarkerSize(0.5);
    // h2hxztime[i]->SetMarkerColor(i);
    h2hxztime[i]->Draw();
    c_2timexz->Print("gif/c_2timexz.gif+20");  
  }
  c_2timexz->Print("gif/c_2timexz.gif++");  


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
  h1htime->Write();
  h1henergy->Write();
  storemyfile->Close();


  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  gSystem->Exec("root -l myfileh3h.root");
  cout << "Time taken by program: "<< duration.count() << " microseconds" << endl;
  
} // end of main function
  // gSystem->Exec("root myfileh3h.root");
