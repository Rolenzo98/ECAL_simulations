#define EcalSimHandler_cxx
#include "EcalSimHandler.hh"
#include "CreateHisto.hh"




void EcalSimHandler::Loop()
{

  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;


  // float binsize_h1htime=0.001;

  // Declaring numbers, parameters and variables
  // declaring the number of binning for the time and energy division
  int nbin=24;
  int nbinlowedge=nbin+1;
  double tbinlowedge[nbinlowedge];
  double ebinlowedge[nbinlowedge];
  // declaring the limits of the histogram
  // declaring the limits of the histogram 2D
  int h_xmin=-2000;
  int h_xmax=2000;
  int h_ymin=1800;
  int h_ymax=3500;
  int h_zmin=-3000;
  int h_zmax=3000;
  int h_yECALmin=1808;
  int h_yECALmax=2028;
  int h_yHCALmin=h_yECALmax;
  int h_yHCALmax=3440;
  // declaring the limits of the histogram 3D
  float h_xmin3D;
  float h_xmax3D;
  float h_ymin3D;
  float h_ymax3D;
  float h_zmin3D;
  float h_zmax3D;
  // declaring other external variables
  bool just_once=true;
  int tothits = 0;
  double energyevent;


  // Declaring histograms, lines, etc.
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
  //declaring lines for the histogram
  TLine *myline1;
  TLine *myline2;
  TLine *myline3;
  TLine *myline4;

  // Creating the binning for the time and energy division
  for (int i=0;i<nbinlowedge;i++)
  {
    int ipowt=i-10;
    int ipowe=i-nbinlowedge;
    tbinlowedge[i]=std::pow(2,ipowt);    
    ebinlowedge[i]=std::pow(2,ipowe);
    // cout<<"Bin "<<i<<":\ttime: "<<tbinlowedge[i]<<"\tenergy: "<<ebinlowedge[i]<<endl;
  }

  // // Setting the names of the histograms and initializing them
  for (int i=0;i<nbin;i++)
  {
    TString h2hxytime_name=TString::Format("h2hxytime_bin%d",i);
    TString h2hyztime_name=TString::Format("h2hyztime_bin%d",i);
    TString h2hxztime_name=TString::Format("h2hxztime_bin%d",i);
    TString h3hpostime_name=TString::Format("h3hpostime_bin%d",i);
    TString h3hposenergy_name=TString::Format("h3hposenergy_bin%d",i);

    h2hxytime[i]=new TH2F(h2hxytime_name,h2hxytime_name,
      100,h_xmin,h_xmax,100,h_ymin,h_ymax);
    h2hyztime[i]=new TH2F(h2hyztime_name,h2hyztime_name,
      100,h_ymin,h_ymax,100,h_zmin,h_zmax);
    h2hxztime[i]=new TH2F(h2hxztime_name,h2hxztime_name,
      100,h_xmin,h_xmax,100,h_zmin,h_zmax);

    h3hpostime[i]= new TH3D(h3hpostime_name,h3hpostime_name,
      100,-2000,2000,
      100,-1000,5000,
      100,-3000,3000);    
    h3hposenergy[i]= new TH3D(h3hposenergy_name,h3hposenergy_name,
      100,-2000,2000,
      100,-1000,5000,
      100,-3000,3000);
  }



  // MAIN` LOOP - Loop over the events (100 times)
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


    // h_xmin3D=TMath::MinElement(nsch, scpox);
    // h_xmax3D=TMath::MaxElement(nsch, scpox);
    // h_ymin3D=TMath::MinElement(nsch, scpoy);
    // h_ymax3D=TMath::MaxElement(nsch, scpoy);
    // h_zmin3D=TMath::MinElement(nsch, scpoz);
    // h_zmax3D=TMath::MaxElement(nsch, scpoz);

    // for (int i=0;i<nbin;i++)
    // {
    //   TString h2hxytime_name=TString::Format("h2hxytime_bin%d",i);
    //   TString h2hyztime_name=TString::Format("h2hyztime_bin%d",i);
    //   TString h2hxztime_name=TString::Format("h2hxztime_bin%d",i);
    //   TString h3hpostime_name=TString::Format("h3hpostime_bin%d",i);
    //   TString h3hposenergy_name=TString::Format("h3hposenergy_bin%d",i);

    //   h2hxytime[i]=new TH2F(h2hxytime_name,h2hxytime_name,
    //     100,h_xmin,h_xmax,100,h_ymin,h_ymax);
    //   h2hyztime[i]=new TH2F(h2hyztime_name,h2hyztime_name,
    //     100,h_ymin,h_ymax,100,h_zmin,h_zmax);
    //   h2hxztime[i]=new TH2F(h2hxztime_name,h2hxztime_name,
    //     100,h_xmin,h_xmax,100,h_zmin,h_zmax);

    //   h3hpostime[i]= new TH3D(h3hpostime_name,h3hpostime_name,
    //     100,h_xmin3D,h_xmax3D,
    //     100,h_ymin3D,h_ymax3D,
    //     100,h_zmin3D,h_zmax3D);
    //   h3hposenergy[i]= new TH3D(h3hposenergy_name,h3hposenergy_name,
    //     100,h_xmin3D,h_xmax3D,
    //     100,h_ymin3D,h_ymax3D,
    //     100,h_zmin3D,h_zmax3D);
    // }



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
    
    // Selecting a specific event (back to 1 time)
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

      // for (int ibin=0; ibin<nbin; ibin++)
      // {
      //   for (int ihit=0; ihit<nsch;ihit++)
      //   {
      //     if (sctime[ihit]>tbinlowedge[ibin]&&sctime[ihit]<tbinlowedge[ibin+1])
      //     {
      //       h3hpostime[ibin]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
      //       continue;
      //     }
      //   }
      //   h3hpostime[ibin]->Draw();
      //   delete h3hpostime[ibin];
      //   c_3time_gif->Print("gif/c_3time_gif.gif+20"); 
      // }
      // c_3time_gif->Print("gif/c_3time_gif.gif++");
      
      
      
      // Loop over the hits of the event (1*665=665 times)
      for (int ihit=0; ihit<nsch;ihit++)
      {
        cout<<ihit<<"\t"<<sctime[ihit]<<"\t\t"<<scene[ihit]<<"\tx "<<scpox[ihit]<<" y "<<scpoy[ihit]<<" z "<<scpoz[ihit]<<endl;
        // cout<< "hit: " << ihit << "\t time : " << sctime[ihit] << "\t energy: " << scene[ihit] << endl;
        h3hpos->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
        
        // Loop over all the bins for the time and energy (1*665*24=15960 times)  
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
    cout<<"The folder gif exists"<<endl;
    if (std::filesystem::is_empty("gif"))
    {
      cout<<"The folder gif is empty, the program is going to create gifs"<<endl;
    }
    else 
    {
      cout<<"The folder contains already some gifs, the program is going to remove them and recreate them"<<endl;
      gSystem->Exec("rm gif/*.gif");
    }
  }
  else 
  {
    cout<<"The folder gif doesn't exist, the program is going to create the folder and to fill it with the gif"<<endl;
    std::filesystem::create_directory("gif");
  }




  TFile *storemyfile = new TFile("myfileh3h.root", "recreate");

  TDirectory *dir = storemyfile->mkdir("h3hpos");
  dir->cd();
  h3hpos->Write();
  storemyfile->cd();



  // Gif of the 2D plots of the time vs x and y 
  TCanvas *c_2timexy_gif=new TCanvas("c_2timexy_gif","c_2timexy_gif",500,500);
  for (int i=0;i<nbin;i++)
  {
    gStyle->SetOptStat(0);
    // if (h2hxytime[i]->GetEntries()==0)
    //   continue;
    h2hxytime[i]->SetTitle(TString::Format("h2hxytime_bin%d_(%f-%f);X;Y",i,tbinlowedge[i],tbinlowedge[i+1]));
    h2hxytime[i]->SetMarkerStyle(20);
    h2hxytime[i]->SetMarkerSize(0.5);
    // h2hxytime[i]->SetMarkerColor(i);;
    h2hxytime[i]->Draw();    
    myline1=new TLine(h_xmin, h_yECALmin, h_xmax, h_yECALmin);
    myline2=new TLine(h_xmin, h_yHCALmax, h_xmax, h_yHCALmax);
    myline3=new TLine(h_xmin, h_yHCALmin, h_xmax, h_yHCALmin);
    myline4=new TLine(h_xmin, h_yECALmax, h_xmax, h_yECALmax);
    myline1->Draw("same");
    myline2->Draw("same");
    myline3->Draw("same");
    myline4->Draw("same");
    TLatex *text_ecal=new TLatex(-1900,1830,"ECAL");
    text_ecal->SetTextSize(0.03);
    text_ecal->SetTextAngle(90);
    text_ecal->Draw("same");
    TLatex *text_hcal=new TLatex(-1900,2650,"HCAL");
    text_hcal->SetTextSize(0.03);
    text_hcal->SetTextAngle(90);
    text_hcal->Draw("same");
    c_2timexy_gif->Print("gif/c_2timexy_gif.gif+20");  
  }
  c_2timexy_gif->Print("gif/c_2timexy_gif.gif++");  

  // Gif of the 2D plots of the time vs y and z 
  TCanvas *c_2timeyz_gif=new TCanvas("c_2timeyz_gif","c_2timeyz_gif",500,500);
  for (int i=0;i<nbin;i++)
  {
    gStyle->SetOptStat(0);
    // if (h2hyztime[i]->GetEntries()==0)
    //   continue;
    h2hyztime[i]->SetTitle(TString::Format("h2hyztime_bin%d_(%f-%f);Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]));
    h2hyztime[i]->SetMarkerStyle(20);
    h2hyztime[i]->SetMarkerSize(0.5);
    // h2hyztime[i]->SetMarkerColor(i);
    h2hyztime[i]->Draw();

    myline1=new TLine(h_yECALmin,h_zmin, h_yECALmin, h_zmax);
    myline2=new TLine(h_yHCALmax,h_zmin, h_yHCALmax, h_zmax);
    myline3=new TLine(h_yHCALmin,h_zmin, h_yHCALmin, h_zmax);
    myline4=new TLine(h_yECALmax,h_zmin, h_yECALmax, h_zmax);
    myline1->Draw("same");
    myline2->Draw("same");
    myline3->Draw("same");
    myline4->Draw("same");

    TLatex *text_ecal=new TLatex(1830,3000,"ECAL");
    text_ecal->SetTextSize(0.03);
    text_ecal->Draw("same");
    TLatex *text_hcal=new TLatex(2700,3000,"HCAL");
    text_hcal->SetTextSize(0.03);
    text_hcal->Draw("same");

    c_2timeyz_gif->Print("gif/c_2timeyz_gif.gif+20");
  }
  c_2timeyz_gif->Print("gif/c_2timeyz_gif.gif++");

  // Gif of the 2D plots of the time vs x and z  
  TCanvas *c_2timexz_gif=new TCanvas("c_2timexz_gif","c_2timexz_gif",500,500);
  for (int i=0;i<nbin;i++)
  {
    gStyle->SetOptStat(0);
    // if (h2hxztime[i]->GetEntries()==0)
    //   continue;
    h2hxztime[i]->SetTitle(TString::Format("h2hxztime%d_(%f-%f);X;Z",i,tbinlowedge[i],tbinlowedge[i+1]));
    h2hxztime[i]->SetMarkerStyle(20);
    h2hxztime[i]->SetMarkerSize(0.5);
    // h2hxztime[i]->SetMarkerColor(i);
    h2hxztime[i]->Draw();
    c_2timexz_gif->Print("gif/c_2timexz_gif.gif+20");  
  }
  c_2timexz_gif->Print("gif/c_2timexz_gif.gif++");  

  // 3D plots of the time event with different color for each time bin
  TCanvas *c_3time=new TCanvas("c_3time","c_3time",500,500);
  for (int i=0;i<nbin;i++)
  {
    h3hpostime[i]->SetTitle(TString::Format("h3hpostime_bin%d_(%f-%f);X;Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]));
    h3hpostime[i]->SetMarkerStyle(20);
    h3hpostime[i]->SetMarkerSize(0.5);
    h3hpostime[i]->SetMarkerColor(i);
    h3hpostime[i]->Draw("BOX SAME");    
  }
  c_3time->Write();

  TCanvas *c_3time_gif=new TCanvas("c_3time_gif","c_3time_gif",500,500);
  for (int i=0;i<nbin;i++)
  {
    h3hpostime[i]->SetTitle(TString::Format("h3hpostime_bin%d_(%f-%f);X;Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]));
    h3hpostime[i]->SetMarkerStyle(20);
    h3hpostime[i]->SetMarkerSize(0.5);
    h3hpostime[i]->SetMarkerColor(1);
    h3hpostime[i]->Draw();
    c_3time_gif->Print("gif/c_3time_gif.gif+20");    
  }
  c_3time_gif->Print("gif/c_3time_gif.gif++");

  // 3D plots of the energy event with different color for each energy bin
  TCanvas *c_3energy=new TCanvas("c_3energy","c_3energy",500,500);
  for (int i=0;i<nbin;i++)
  {
    h3hposenergy[i]->SetTitle(TString::Format("h3hposenergy_bin%d_(%f-%f)",i,ebinlowedge[i],ebinlowedge[i+1])+";X;Y;Z");
    h3hposenergy[i]->SetMarkerStyle(20);
    h3hposenergy[i]->SetMarkerSize(0.5);
    h3hposenergy[i]->SetMarkerColor(i);
    h3hposenergy[i]->Draw("BOX SAME");  
  }
  c_3energy->Write();

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

  // every 3D plot of the time event
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

  // write all the remaining histograms
  // h3hpos->Write();
  h1htime->Write();
  h1henergy->Write();


  storemyfile->Close();

  gSystem->Exec("root -l myfileh3h.root"); // execute the root file
  
  // time check
  auto stop = high_resolution_clock::now(); 
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken by program: "<< duration.count() << " microseconds" << endl;
  
} // end of main function

