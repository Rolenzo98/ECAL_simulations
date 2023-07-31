#define EcalSimHandler_cxx
#include "EcalSimHandler.hh"
#include "CreateHisto.hh"
#include "Initial_Variables.hh"

void EcalSimHandler::Loop()
{

  if (fChain == 0)
    return;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;


  // float binsize_h1htime=0.001;

  // Declaring numbers, parameters and variables
  // declaring the number of binning for the time and energy division

  double tbinlowedge[nbinlowedge];
  // Creating the binning for the time and energy division
  for (int i=0;i<nbinlowedge;i++)
  {
    int ipowt=i-10;
    tbinlowedge[i]=std::pow(2,ipowt);    
  }
  float tmin=100;
  float tmax=0;
  float emin=100;
  float emax=0;

  cout<<"Event\tHits\ttime(s)\ttot(s)\tremaining"<<endl;

  // Declaring histograms, lines, etc.
  // declaration histograms 1D
  TH1F *h1htime = new TH1F(TString::Format("h1htime_%d",NUMBER), 
    TString::Format("#splitline{%s Time}{Event %d};Time (ns); Counts",PARTICLETYPE_TITLE,NUMBER),
    nbin, tbinlowedge); //histogram of the hits time

  TH1F *h1henergytime[nbin_10]; 
  for (int ibin=0; ibin<nbin_10; ibin++)
  {
    h1henergytime[ibin]= new TH1F(TString::Format("h1henergytime_bin%d",ibin),
      TString::Format("#splitline{%s Energy at time}{%.3fns-%.3fns)};Energy (GeV); Counts",PARTICLETYPE_TITLE,tbinlowedge_10[ibin],tbinlowedge_10[ibin+1]),
      1000,0,0.06);  
  }

  // declaration histograms 2D
  TH2D *h2henergytime=new TH2D("h2henergytime",
    "h2henergytime;Time (ns);Energy (GeV)",
    nbin_10,0,tbinlowedge_10[nbin_10],
    1000,0,0.06);  
  TH2D *h2henergytimebin=new TH2D("h2henergytimebin",
    "h2henergytimebin;Time (ns);Energy (GeV)",
    1000,0,32000,
    1000,0,0.06);
  // declaration histograms 3D
  TH3D *h3hpos=new TH3D(TString::Format("h3hpos_%d",NUMBER),
    TString::Format("#splitline{%s 3D}{Event %d};X (mm);Y (mm);Z (mm)",PARTICLETYPE_TITLE,NUMBER), 
    100, h_xmin, h_xmax, 
    100, h_ymin, h_ymax, 
    100, h_zmin, h_zmax); //cumulative histogram all hits

  TH3D *h3hpostime[nbin]; //histogram all hits in bin time
  for(int ibin=0; ibin<nbin; ibin++){
    h3hpostime[ibin]= new TH3D(TString::Format("h3hpostime_%d_bin%d",NUMBER,ibin),
      TString::Format("#splitline{%s 3D}{#splitline{Event %d}{Interval %d (%.3fns-%.3fns)}};X (mm);Y (mm);Z (mm)",PARTICLETYPE_TITLE,NUMBER,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]),
      100,h_xmin,h_xmax,
      100,h_ymin,h_ymax,
      100,h_zmin,h_zmax);  
  }


  TFile *storemyfile = new TFile("myfileh3h.root", "recreate");
    
  // MAIN` LOOP - Loop over the events (100 times)
  for (Long64_t jentry=0; jentry<nentries; jentry++)
  {
    auto startevent = high_resolution_clock::now();
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0)
      break;

    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (Cut(ientry) < 0)
      continue;

    for (int ihit=0; ihit<nsch;ihit++)
    {
      if (scene[ihit]>energy_threshold)
      {
      if (sctime[ihit]<tmin) tmin=sctime[ihit];
      if (sctime[ihit]>tmax) tmax=sctime[ihit];
      if (scene[ihit]<emin) emin=scene[ihit];
      if (scene[ihit]>emax) emax=scene[ihit];
        h2henergytime->Fill(sctime[ihit],scene[ihit]);
      for (int ibin=0; ibin<nbin_10; ibin++)
      {
        if (sctime[ihit]>tbinlowedge_10[ibin]&&sctime[ihit]<tbinlowedge_10[ibin+1])
        {
          h1henergytime[ibin]->Fill(scene[ihit]);
        }
      }
      }
    }


    if (jentry==NUMBER)
    {  

      for (int ibin=0; ibin<nbin; ibin++)
      {        
        for (int ihit=0; ihit<nsch;ihit++)
        {
          // fill all the time interval
          h1htime->Fill(sctime[ihit]);
          h3hpos->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);

          // splits with different time interval
          if (sctime[ihit]>tbinlowedge[ibin]&&sctime[ihit]<tbinlowedge[ibin+1])
          {
            h3hpostime[ibin]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
          }
            
        } // end of hit loop

      } // end of time loop
    } // end if for the specific event
    
    auto stopevent = high_resolution_clock::now(); 
    auto durationevent = duration_cast <seconds>(stopevent - startevent);
    auto duration = duration_cast <seconds>(stopevent - start);    
    cout << jentry<<"\t"<<nsch<<
    "\t"<< durationevent.count() << 
    "\t"<< duration.count() <<  
    "\t"<< ((duration.count()/(jentry+1))*(nentries-jentry-1))/60 << "' " <<
    ((duration.count()/(jentry+1))*(nentries-jentry-1))%60 << "\"" << endl;;

  } // end loop over the events

  cout<<" emin "<<emin<<" emax "<<emax<<" tmin "<<tmin<<" tmax "<<tmax<<endl;

  storemyfile->cd();
  h1htime->Write();
  h2henergytime->Write();

  TDirectory *dir_h3hpostime = storemyfile->mkdir("h3hpostime");
  dir_h3hpostime->cd();
  h3hpos->Write();
  for (int ibin=0; ibin<nbin; ibin++)
  {
    h3hpostime[ibin]->Write();
  }

  TDirectory *dir_h1henergytime = storemyfile->mkdir(TString::Format("h1henergytime_%s",PARTICLETYPE_TITLE));
  // TDirectory *dir_h1henergytime = storemyfile->mkdir("h1henergytime");
  dir_h1henergytime->cd();
  for (int ibin=0; ibin<nbin_10; ibin++)
  {
    h1henergytime[ibin]->Write();
  }

  storemyfile->cd();

  storemyfile->Close();
  
  // time check
  auto stop= high_resolution_clock::now(); 
  auto duration = duration_cast<seconds>(stop - start);
  cout << "Total time taken by program: "<< duration.count() << " seconds" << endl;
  cout<<"End of the program"<<endl;
  
} // end of main function

