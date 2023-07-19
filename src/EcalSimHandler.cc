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
  // Creating the binning for the time and energy division
  for (int i=0;i<nbinlowedge;i++)
  {
    int ipowt=i-10;
    tbinlowedge[i]=std::pow(2,ipowt);    
  }

  // double ebinlowedge[nbinlowedge];
  // declaring the limits of the histogram
  // declaring the limits of the histogram 2D
  int h_xmin=-2000;
  int h_xmax=2000;
  int h_ymin=1750;
  int h_ymax=3500;
  int h_zmin=-3000;
  int h_zmax=3000;
  int h_yECALmin=1808;
  int h_yECALmax=2028;
  int h_yHCALmin=h_yECALmax;
  int h_yHCALmax=3440;
  // declaring the limits of the histogram 3D
  // float h_xmin3D;
  // float h_xmax3D;
  // float h_ymin3D;
  // float h_ymax3D;
  // float h_zmin3D;
  // float h_zmax3D;
  // float enemin;
  // float enemax;
  // float timemin;
  // float timemax;

  // float h_xmin3Dtot;
  // float h_xmax3Dtot;
  // float h_ymin3Dtot;
  // float h_ymax3Dtot;
  // float h_zmin3Dtot;
  // float h_zmax3Dtot;
  // float enemintot;
  // float enemaxtot;
  // float timemintot;
  // float timemaxtot;

  float tmin=100;
  float tmax=0;
  float emin=100;
  float emax=0;

  // gErrorIgnoreLevel = kWarning;
  //-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
  std::string PARTICLETYPE="Pions";
  int NUMERO=58; //6 for pions, 34 for electrons
  std::string MIOCOLORE="arcobaleno"; //"nero" for kBlack, "arcobaleno" for tcolor::krainbow
  Color_t mycolor;
  float MISURA=1;
  //-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
  int JUSTONCE=0;
  cout<<"Event\tHits\ttime(s)\ttot(s)\tremaining"<<endl;




  // Declaring histograms, lines, etc.
  // declaration histograms 1D
  TH1F *h1htime = new TH1F(TString::Format("h1htime_%d",NUMERO), 
      TString::Format("h1htime_%d; time (ns); counts",NUMERO),
      nbin, tbinlowedge); //histogram of the hits time

  // declaration histograms 2D
  TH2D *h2henergytime=new TH2D("h2henergytime","h2henergytime;Time (ns);Energy (GeV)",
  1000,0,32000,
  1000,0,0.06);  
  // declaration histograms 3D
  TH3D *h3hpos=new TH3D(TString::Format("h3hpos_%d",NUMERO),"Hist in 3D", 
        100, h_xmin, h_xmax, 
        100, h_ymin, h_ymax, 
        100, h_zmin, h_zmax); //cumulative histogram all hits

  TH3D *h3hpostime[nbin]; //histogram all hits in bin time
  for(int ibin=0; ibin<nbin; ibin++){
    h3hpostime[ibin]= new TH3D(TString::Format("h3hpostime_%d_bin%d",NUMERO,ibin),
    TString::Format("h3hpostime_%d_bin%d;X (mm);Y (mm);Z (mm)",NUMERO,ibin),
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
      if (scene[ihit]>0.0001)
      {
      if (sctime[ihit]<tmin) tmin=sctime[ihit];
      if (sctime[ihit]>tmax) tmax=sctime[ihit];
      if (scene[ihit]<emin) emin=scene[ihit];
      if (scene[ihit]>emax) emax=scene[ihit];
        h2henergytime->Fill(sctime[ihit],scene[ihit]);
      }
    }

    if (jentry==NUMERO)
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

  TDirectory *dir_h3hpos = storemyfile->mkdir("h3hpos");
  dir_h3hpos->cd();
  h3hpos->Write();
  for (int ibin=0; ibin<nbin; ibin++)
  {
    h3hpostime[ibin]->Write();
  }
  storemyfile->cd();

  storemyfile->Close();
  
  // time check
  auto stop= high_resolution_clock::now(); 
  auto duration = duration_cast<seconds>(stop - start);
  cout << "Time taken by program: "<< duration.count() << " seconds" << endl;
  
} // end of main function

