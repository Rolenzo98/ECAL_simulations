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
  // bool just_once=true;
  int tothits = 0;
  // double energyevent;


  // Declaring histograms, lines, etc.
  // declaration histograms 1D
  TH1F *h1htime; //histogram of the hits time
  TH1F *h1henergy; //histogram of the hits energy
  // TH1F *h1hx; //histogram of the hits in the x plane
  // TH1F *h1hy; //histogram of the hits in the y plane
  // TH1F *h1hz; //histogram of the hits in the z plane
  // declaration histograms 2D
  TH2F *h2hxytime[nbin]; //projection of the hits in the xy plane
  TH2F *h2hyztime[nbin]; //projection of the hits in the yz plane
  TH2F *h2hxztime[nbin]; //projection of the hits in the xz plane
  // declaration histograms 3D
  TH3D *h3hpos; //cumulative histogram all hits
  TH3D *h3hpostime[nbin]; //histogram all hits in bin time
  TH3D *h3hposenergy[nbin]; //histogram all hits in bin energy
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
  }

  // // Setting the names of the histograms and initializing them
  for (int i=0;i<nbin;i++)
  {
    TString h2hxytime_name=TString::Format("h2hxytime_bin%d",i);
    TString h2hxytime_title=TString::Format("h2hxytime_bin%d_(%f-%f);X;Y",i,tbinlowedge[i],tbinlowedge[i+1]);
    TString h2hyztime_name=TString::Format("h2hyztime_bin%d",i);
    TString h2hyztime_title=TString::Format("h2hyztime_bin%d_(%f-%f);Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]);
    TString h2hxztime_name=TString::Format("h2hxztime_bin%d",i);
    TString h2hxztime_title=TString::Format("h2hxztime_bin%d_(%f-%f);X;Z",i,tbinlowedge[i],tbinlowedge[i+1]);

    TString h3hpostime_name=TString::Format("h3hpostime_bin%d",i);
    TString h3hpostime_title=TString::Format("h3hpostime_bin%d_(%f-%f);X;Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]);
    
    TString h3hposenergy_name=TString::Format("h3hposenergy_bin%d",i);
    TString h3hposenergy_title=TString::Format("h3hposenergy_bin%d_(%f-%f);X;Y;Z",i,ebinlowedge[i],ebinlowedge[i+1]);
  }


  TFile *storemyfile = new TFile("myfileh3h.root", "recreate");
  TDirectory *dir_h1 = storemyfile->mkdir("h1");
  TDirectory *dir_h2 = storemyfile->mkdir("h2");
  TDirectory *dir_h3 = storemyfile->mkdir("h3");
  TDirectory *canvases = storemyfile->mkdir("canvases"); 
  TDirectory *dir_h2_xy = dir_h2->mkdir("xy");
  TDirectory *dir_h2_yz = dir_h2->mkdir("yz");
  TDirectory *dir_h2_xz = dir_h2->mkdir("xz"); 
 



    if (std::filesystem::exists("gif"))
    {
      cout<<"The folder gif exists"<<endl;
      // if (std::filesystem::is_empty("gif"))
      // {
      //   cout<<"The folder gif is empty, the program is going to create gifs"<<endl;
      // }
      // else 
      // {
      //   cout<<"The folder contains already some gifs, the program is going to remove them and recreate them"<<endl;
      //   gSystem->Exec("rm gif/*.gif");
      // }
    }
    else 
    {
      cout<<"The folder gif doesn't exist, the program is going to create the folder and to fill it with the gif"<<endl;
      std::filesystem::create_directory("gif");
      std::filesystem::create_directory("gif/2xy");
      std::filesystem::create_directory("gif/2yz");
      std::filesystem::create_directory("gif/2xz");
      std::filesystem::create_directory("gif/3");
      

    }

  // MAIN` LOOP - Loop over the events (100 times)
  for (Long64_t jentry =0; jentry<nentries; jentry++)
  {
    auto startevent = high_resolution_clock::now();
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;

    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (Cut(ientry) < 0)
      continue;

    // energyevent=0;
    tothits+=nsch;

    TString::Format("h1htime_%d",jentry);
    TCanvas *c_2timexy_gif=new TCanvas(TString::Format("c%lld_2timexy_gif",jentry),TString::Format("c%lld_2timexy_gif",jentry),500,500);
    TCanvas *c_2timeyz_gif=new TCanvas(TString::Format("c%lld_2timeyz_gif",jentry),TString::Format("c%lld_2timeyz_gif",jentry),500,500);
    TCanvas *c_2timexz_gif=new TCanvas(TString::Format("c%lld_2timexz_gif",jentry),TString::Format("c%lld_2timexz_gif",jentry),500,500);
    TCanvas *c_3time_gif=new TCanvas(TString::Format("c%lld_3time_gif",jentry),TString::Format("c%lld_3time_gif",jentry),500,500);
    TCanvas *c_3energy_gif=new TCanvas(TString::Format("c%lld_3energy_gif",jentry),TString::Format("c%lld_3energy_gif",jentry),500,500);

    // TCanvas *c_2timeyz_gif=new TCanvas("c_2timeyz_gif","c_2timeyz_gif",500,500);
    // TCanvas *c_2timexz_gif=new TCanvas("c_2timexz_gif","c_2timexz_gif",500,500);
    // TCanvas *c_3time_gif=new TCanvas("c_3time_gif","c_3time_gif",500,500); 

    TCanvas *c_3time=new TCanvas(TString::Format("c%lld_3time",jentry),TString::Format("c%d_3time",jentry),500,500);

    
    TCanvas *c_3energy=new TCanvas(TString::Format("c%lld_3energy",jentry),TString::Format("c%d_3energy",jentry),500,500);


    
    /*
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
    */
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
    /*
    for (int ihit=0; ihit<nsch;ihit++)
      {
        // cout<<"energy of hit is "<<scene[ihit]<<endl;
        energyevent+=scene[ihit];
      }
    */
    
    // Selecting a specific event (back to 1 time)
    // EVENTUALLY THIS CONDITION WILL BE REMOVED
      cout<<"Event: "<<jentry<<" Hits: "<<nsch;

    // if (jentry==58)
    // {
      // cout<<"Event "<<jentry<<"analysis:\n"<<"Hit\tTime\t\tEnergy\tPosition"<<endl;
          
      h_xmin3D=TMath::MinElement(nsch, scpox);
      h_xmax3D=TMath::MaxElement(nsch, scpox);
      h_ymin3D=TMath::MinElement(nsch, scpoy);
      h_ymax3D=TMath::MaxElement(nsch, scpoy);
      h_zmin3D=TMath::MinElement(nsch, scpoz);
      h_zmax3D=TMath::MaxElement(nsch, scpoz);
      
      
      // Initializing the histogram for the position of the hits in 3D (valid all events, all single ones)  
      h3hpos=new TH3D(TString::Format("h3hpos_%lld",jentry),"Hist in 3D", 
        100, h_xmin3D, h_xmax3D, 
        100, h_ymin3D, h_ymax3D, 
        100, h_zmin3D, h_zmax3D);
      // h3hpos->SetDirectory(dir_h3);
      
      // Initializing the histogram for the time of the hits in 1D (valid all events, all single ones)
      h1htime=new TH1F(TString::Format("h1htime_%lld",jentry), 
      TString::Format("h1htime_%lld; time (ns); counts",jentry),
      nbin, tbinlowedge);
      h1htime->SetDirectory(dir_h1);

      // Initializing the histogram for the energy of the hits in 1D (valid all events, all single ones)
      h1henergy=new TH1F(TString::Format("h1henergy_%lld",jentry),
      TString::Format("h1henergy_%lld; energy (keV); counts",jentry),
      nbin, ebinlowedge);
      h1henergy->SetDirectory(dir_h1);

      for (int ibin=0; ibin<nbin; ibin++)
      {
        TString h2hxytime_name=TString::Format("Event_%lld_h2hxytime_bin%d",jentry,ibin);
        TString h2hxytime_title=TString::Format("Event_%lld_xy_bin%d_(%f-%f);X;Y",jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);
        TString h2hyztime_name=TString::Format("Event_%lld_h2hyztime_bin%d",jentry,ibin);
        TString h2hyztime_title=TString::Format("Event_%lld_yz_bin%d_(%f-%f);Y;Z",jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);
        TString h2hxztime_name=TString::Format("Event_%lld_h2hxztime_bin%d",jentry,ibin);
        TString h2hxztime_title=TString::Format("Event_%lld_xz_bin%d_(%f-%f);X;Z",jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);

        TString h3hpostime_name=TString::Format("Event_%lld_h3hpostime_bin%d",jentry,ibin);
        TString h3hpostime_title=TString::Format("Event_%lld_time_bin%d_(%f-%f);X;Y;Z",jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);
        
        TString h3hposenergy_name=TString::Format("Event_%lld_h3hposenergy_bin%d",jentry,ibin);
        TString h3hposenergy_title=TString::Format("Event_%lld_energy_bin%d_(%f-%f);X;Y;Z",jentry,ibin,ebinlowedge[ibin],ebinlowedge[ibin+1]);

        h3hpostime[ibin]= new TH3D(h3hpostime_name,h3hpostime_title,
          100,h_xmin3D,h_xmax3D,
          100,h_ymin3D,h_ymax3D,
          100,h_zmin3D,h_zmax3D);  
        h3hpostime[ibin]->SetDirectory(dir_h3);

        h3hposenergy[ibin]= new TH3D(h3hposenergy_name,h3hposenergy_title,
          100,h_xmin3D,h_xmax3D,
          100,h_ymin3D,h_ymax3D,
          100,h_zmin3D,h_zmax3D);
        h3hposenergy[ibin]->SetDirectory(dir_h3);

        h2hxytime[ibin]=new TH2F(h2hxytime_name,h2hxytime_title,
          100,h_xmin,h_xmax,100,h_ymin,h_ymax);
        h2hxytime[ibin]->SetDirectory(dir_h2);

        h2hyztime[ibin]=new TH2F(h2hyztime_name,h2hyztime_title,
          100,h_ymin,h_ymax,100,h_zmin,h_zmax);
        h2hyztime[ibin]->SetDirectory(dir_h2);

        h2hxztime[ibin]=new TH2F(h2hxztime_name,h2hxztime_title,
          100,h_xmin,h_xmax,100,h_zmin,h_zmax);
        h2hxztime[ibin]->SetDirectory(dir_h2);

        for (int ihit=0; ihit<nsch;ihit++)
        {
          if (sctime[ihit]>tbinlowedge[ibin]&&sctime[ihit]<tbinlowedge[ibin+1])
          {
            h1htime->Fill(sctime[ihit]);
            h3hpos->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);

            h2hxytime[ibin]->Fill(scpox[ihit],scpoy[ihit]);
            h2hyztime[ibin]->Fill(scpoy[ihit],scpoz[ihit]);
            h2hxztime[ibin]->Fill(scpox[ihit],scpoz[ihit]);
            h3hpostime[ibin]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
            // continue;
          }
          if (scene[ihit]>ebinlowedge[ibin]&&scene[ihit]<ebinlowedge[ibin+1])
          {
            h1henergy->Fill(scene[ihit]);
            h3hposenergy[ibin]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
          }  
            
        }

        // gStyle->SetOptStat(0);

        // dir_h2_xy->cd();
        // h2hxytime[ibin]->Write();
        // dir_h2_yz->cd();
        // h2hyztime[ibin]->Write();
        // dir_h2_xz->cd();
        // h2hxztime[ibin]->Write();

        // dir_h3->cd();
        // h3hpostime[ibin]->Write();
        c_3time_gif->cd();
        h3hpostime[ibin]->Draw();
        c_3time_gif->Print(TString::Format("gif/3/c%lld_3time_gif.gif+20",jentry)); 


        h2hxytime[ibin]->SetMarkerStyle(20);
        h2hxytime[ibin]->SetMarkerSize(0.5);
        h2hyztime[ibin]->SetMarkerStyle(20);
        h2hyztime[ibin]->SetMarkerSize(0.5);
        h2hxztime[ibin]->SetMarkerStyle(20);
        h2hxztime[ibin]->SetMarkerSize(0.5);
        
        h3hpostime[ibin]->SetMarkerStyle(20);
        h3hpostime[ibin]->SetMarkerSize(0.5);
        h3hposenergy[ibin]->SetMarkerStyle(20);
        h3hposenergy[ibin]->SetMarkerSize(0.5);



        h3hpostime[ibin]->SetMarkerColor(ibin);
        h3hposenergy[ibin]->SetMarkerColor(ibin);


        c_2timexy_gif->cd();
        h2hxytime[ibin]->Draw();    
        myline1=new TLine(h_xmin, h_yECALmin, h_xmax, h_yECALmin);
        myline2=new TLine(h_xmin, h_yHCALmax, h_xmax, h_yHCALmax);
        myline3=new TLine(h_xmin, h_yHCALmin, h_xmax, h_yHCALmin);
        myline4=new TLine(h_xmin, h_yECALmax, h_xmax, h_yECALmax);
        myline1->Draw("same");
        myline2->Draw("same");
        myline3->Draw("same");
        myline4->Draw("same");
        c_2timexy_gif->Print(TString::Format("gif/2xy/c%lld_2timexy_gif.gif+20",jentry));  
        delete myline1;
        delete myline2;
        delete myline3;
        delete myline4;
        delete h2hxytime[ibin];

        c_2timeyz_gif->cd();
        h2hyztime[ibin]->Draw();
        myline1=new TLine(h_yECALmin,h_zmin, h_yECALmin, h_zmax);
        myline2=new TLine(h_yHCALmax,h_zmin, h_yHCALmax, h_zmax);
        myline3=new TLine(h_yHCALmin,h_zmin, h_yHCALmin, h_zmax);
        myline4=new TLine(h_yECALmax,h_zmin, h_yECALmax, h_zmax);
        myline1->Draw("same");
        myline2->Draw("same");
        myline3->Draw("same");
        myline4->Draw("same");
        c_2timeyz_gif->Print(TString::Format("gif/2yz/c%lld_2timeyz_gif.gif+20",jentry));
        delete myline1;
        delete myline2;
        delete myline3;
        delete myline4;
        delete h2hyztime[ibin];

        c_2timexz_gif->cd();
        h2hxztime[ibin]->Draw();
        c_2timexz_gif->Print(TString::Format("gif/2xz/c%lld_2timexz_gif.gif+20",jentry));  
        delete h2hxztime[ibin];

        c_3time->cd();
        h3hpostime[ibin]->Draw("SAME");   


        c_3energy->cd();
        h3hposenergy[ibin]->Draw(" SAME");
      }
      
      c_2timexy_gif->Print(TString::Format("gif/2xy/c%lld_2timexy_gif.gif++", jentry));
      c_2timeyz_gif->Print(TString::Format("gif/2yz/c%lld_2timeyz_gif.gif++", jentry));
      c_2timexz_gif->Print(TString::Format("gif/2xz/c%lld_2timexz_gif.gif++", jentry));
      c_3time_gif->Print(TString::Format("gif/3/c%lld_3time_gif.gif++", jentry));
      c_3time->Write();
      c_3energy->Write();     
      for (int ibin=0;ibin<nbin;ibin++)
      {
      delete h3hpostime[ibin];
      delete h3hposenergy[ibin];
      }

      dir_h1->cd();
      h1htime->Write();
      h1henergy->Write();
      dir_h3->cd();
      // h3hpos->SetDirectory(dir_h3);
      h3hpos->Write();
      
      delete h1htime;
      delete h1henergy;
      delete h3hpos;
      

    // } // end if for the specific event
    delete c_2timexy_gif;
    delete c_2timeyz_gif;
    delete c_2timexz_gif;
    delete c_3time_gif;
    delete c_3time;
    delete c_3energy;
    

    auto stopevent = high_resolution_clock::now(); 
    auto durationevent = duration_cast <milliseconds>(stopevent - startevent);
    auto duration = duration_cast <seconds>(stopevent - start);
    cout << "\tdone it: "<< durationevent.count() << " ms\t" << 
    "Time total ("<<jentry<<"/"<<nentries<<"): "<< duration.count() << " s" << 
    // "\testimated time: "<<(duration/jentry)*(nentries-jentry)<<
    endl;



  } // end loop over the events


  storemyfile->Close();
  // delete storemyfile;

  gSystem->Exec("root -l myfileh3h.root"); // execute the root file
  
  // time check
  auto stop= high_resolution_clock::now(); 
  auto duration = duration_cast<seconds>(stop - start);
  cout << "Time taken by program: "<< duration.count() << " seconds" << endl;
  
} // end of main function

