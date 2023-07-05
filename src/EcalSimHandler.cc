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
  int h_ymin=1750;
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
  float enemin;
  float enemax;
  float timemin;
  float timemax;

  float h_xmin3Dtot;
  float h_xmax3Dtot;
  float h_ymin3Dtot;
  float h_ymax3Dtot;
  float h_zmin3Dtot;
  float h_zmax3Dtot;
  float enemintot;
  float enemaxtot;
  float timemintot;
  float timemaxtot;

  // declaring other external variables
  // bool just_once=true;
  int tothits = 0;
  // double energyevent;


  // Declaring histograms, lines, etc.
  // declaration histograms 1D
  TH1F *h1htime; //histogram of the hits time
  // TH1F *h1henergy; //histogram of the hits energy
  // TH1F *h1hx; //histogram of the hits in the x plane
  // TH1F *h1hy; //histogram of the hits in the y plane
  // TH1F *h1hz; //histogram of the hits in the z plane
  // declaration histograms 2D
  TH2F *h2hxytime[nbin]; //projection of the hits in the xy plane
  TH2F *h2hyztime[nbin]; //projection of the hits in the yz plane
  TH2F *h2hxztime[nbin]; //projection of the hits in the xz plane
  TH2F *h2hxypos;
  TH2F *h2hyzpos;
  TH2F *h2hxzpos;
  // declaration histograms 3D
  TH3D *h3hpos; //cumulative histogram all hits
  TH3D *h3hpostime[nbin]; //histogram all hits in bin time
  // TH3D *h3hposenergy[nbin]; //histogram all hits in bin energy
  //declaring lines for the histogram
  // TLine *myline1; 
  // TLine *myline2;
  // TLine *myline3;
  // TLine *myline4;
  TLine myline1xy;
  TLine myline2xy;
  TLine myline3xy;
  TLine myline4xy;
  TLine myline1yz;
  TLine myline2yz;
  TLine myline3yz;
  TLine myline4yz;
  // Creating the binning for the time and energy division
  for (int i=0;i<nbinlowedge;i++)
  {
    int ipowt=i-10;
    int ipowe=i-nbinlowedge;
    tbinlowedge[i]=std::pow(2,ipowt);    
    ebinlowedge[i]=std::pow(2,ipowe);
  }

  // // Setting the names of the histograms and initializing them
  // for (int i=0;i<nbin;i++)
  // {
  //   TString h2hxytime_name=TString::Format("h2hxytime_bin%d",i);
  //   TString h2hxytime_title=TString::Format("h2hxytime_bin%d_(%f-%f);X;Y",i,tbinlowedge[i],tbinlowedge[i+1]);
  //   TString h2hyztime_name=TString::Format("h2hyztime_bin%d",i);
  //   TString h2hyztime_title=TString::Format("h2hyztime_bin%d_(%f-%f);Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]);
  //   TString h2hxztime_name=TString::Format("h2hxztime_bin%d",i);
  //   TString h2hxztime_title=TString::Format("h2hxztime_bin%d_(%f-%f);X;Z",i,tbinlowedge[i],tbinlowedge[i+1]);

  //   TString h3hpostime_name=TString::Format("h3hpostime_bin%d",i);
  //   TString h3hpostime_title=TString::Format("h3hpostime_bin%d_(%f-%f);X;Y;Z",i,tbinlowedge[i],tbinlowedge[i+1]);
    
  //   TString h3hposenergy_name=TString::Format("h3hposenergy_bin%d",i);
  //   TString h3hposenergy_title=TString::Format("h3hposenergy_bin%d_(%f-%f);X;Y;Z",i,ebinlowedge[i],ebinlowedge[i+1]);
  // }


  TFile *storemyfile = new TFile("myfileh3h.root", "recreate");
  // TDirectory *dir_h1 = storemyfile->mkdir("h1");
  // TDirectory *dir_h2 = storemyfile->mkdir("h2");
  // TDirectory *dir_h3 = storemyfile->mkdir("h3");
  // TDirectory *dir_h2_xy = dir_h2->mkdir("xy");
  // TDirectory *dir_h2_yz = dir_h2->mkdir("yz");
  // TDirectory *dir_h2_xz = dir_h2->mkdir("xz"); 
  

    // gErrorIgnoreLevel = kWarning;
    //-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
    std::string PARTICLETYPE="Electrons";
    int NUMERO=38; //6 for pions, 34 for electrons
    std::string MIOCOLORE="nero"; //"nero" for kBlack, "arcobaleno" for tcolor::krainbow
    Color_t mycolor;
    float MISURA=1;
    //-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
    int JUSTONCE=0;
    cout<<"Event\tHits\ttime(s)\ttot(s)\tremaining"<<endl;
    
    
    const char *PARTICLETYPE_TITLE=PARTICLETYPE.c_str();
    std::string GIFDIRECTORY = "gif/";
    std::string BASEDIRECTORY = GIFDIRECTORY+PARTICLETYPE+"/";
    std::string BASEDIRECTORY1 = BASEDIRECTORY+"1/";
    std::string BASEDIRECTORYxy = BASEDIRECTORY+"2xy/";
    std::string BASEDIRECTORYyz = BASEDIRECTORY+"2yz/";
    std::string BASEDIRECTORYxz = BASEDIRECTORY+"2xz/";
    std::string BASEDIRECTORY3 = BASEDIRECTORY+"3/";

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
    

    std::string DIRECTORY1=BASEDIRECTORY1+std::to_string(jentry)+"_"+MIOCOLORE+"/";
    std::string DIRECTORYxy=BASEDIRECTORYxy+std::to_string(jentry)+"_"+MIOCOLORE+"/";
    std::string DIRECTORYyz=BASEDIRECTORYyz+std::to_string(jentry)+"_"+MIOCOLORE+"/";
    std::string DIRECTORYxz=BASEDIRECTORYxz+std::to_string(jentry)+"_"+MIOCOLORE+"/";
    std::string DIRECTORY3=BASEDIRECTORY3+std::to_string(jentry)+"_"+MIOCOLORE+"/";


    if (JUSTONCE==0)
    {
      if (std::filesystem::exists(GIFDIRECTORY))
      {
        cout<<"MY: The folder "<< GIFDIRECTORY <<" exists"<<endl;
        if (std::filesystem::exists(BASEDIRECTORY)&&std::filesystem::exists(BASEDIRECTORY1)&&std::filesystem::exists(BASEDIRECTORYxy)&&std::filesystem::exists(BASEDIRECTORYyz)&&std::filesystem::exists(BASEDIRECTORYxz)&&std::filesystem::exists(BASEDIRECTORY3))
        {
          cout<<"MY: The folder "<< BASEDIRECTORY <<" and the subfolders already exist"<<endl;
        }
        else
        {
          cout<<"MY: The folder "<< BASEDIRECTORY <<" does not exist or it's incomplete, the program is going to remove everything and create it"<<endl;
          std::filesystem::remove_all(BASEDIRECTORY);
          std::filesystem::create_directory(BASEDIRECTORY);
          std::filesystem::create_directory(BASEDIRECTORY1);
          std::filesystem::create_directory(BASEDIRECTORYxy);
          std::filesystem::create_directory(BASEDIRECTORYyz);
          std::filesystem::create_directory(BASEDIRECTORYxz);
          std::filesystem::create_directory(BASEDIRECTORY3);
        }
      }
      else
      {
        cout<<"MY: The folder "<< GIFDIRECTORY <<" does not exist, the program is going to create it"<<endl;
        std::filesystem::create_directory(GIFDIRECTORY);
        std::filesystem::create_directory(BASEDIRECTORY);
        std::filesystem::create_directory(BASEDIRECTORY1);
        std::filesystem::create_directory(BASEDIRECTORYxy);
        std::filesystem::create_directory(BASEDIRECTORYyz);
        std::filesystem::create_directory(BASEDIRECTORYxz);
        std::filesystem::create_directory(BASEDIRECTORY3);
      }
        // if (std::filesystem::is_empty("gif"))
        // {
        //   cout<<"The folder gif is empty, the program is going to create gifs"<<endl;
        // }
        // else 
        // {
        //   cout<<"The folder contains already some gifs, the program is going to remove them and recreate them"<<endl;
          // gSystem->Exec("rm -r gif/"+PARTICLETYPE+"/*");
        // std::filesystem::remove_all(BASEDIRECTORY);
        // std::filesystem::create_directory(BASEDIRECTORY);
        // std::filesystem::create_directory(BASEDIRECTORY1);
        // std::filesystem::create_directory(BASEDIRECTORYxy);
        // std::filesystem::create_directory(BASEDIRECTORYyz);
        // std::filesystem::create_directory(BASEDIRECTORYxz);
        // std::filesystem::create_directory(BASEDIRECTORY3);


        // std::filesystem::create_directory("gif/1");
        // std::filesystem::create_directory("gif/2xy");
        // std::filesystem::create_directory("gif/2yz");
        // std::filesystem::create_directory("gif/2xz");
        // std::filesystem::create_directory("gif/3");

        // // }
      
      // else 
      // {
      //   cout<<"MY: The folder gif doesn't exist, the program is going to create the folder and to fill it with the gif"<<endl;
      //   std::filesystem::create_directory(BASEDIRECTORY);
      //   std::filesystem::create_directory(BASEDIRECTORY1);
      //   std::filesystem::create_directory(BASEDIRECTORYxy);
      //   std::filesystem::create_directory(BASEDIRECTORYyz);
      //   std::filesystem::create_directory(BASEDIRECTORYxz);
      //   std::filesystem::create_directory(BASEDIRECTORY3);
      // }
      JUSTONCE=1;
    }

    // cout<<"Event "<<jentry<<"Hits "<<nsch<<endl;

    // char jentryname=("%lld",jentry);
    // int jentryname=(int)jentry;
    // const char* gifxyjentry;

    std::filesystem::create_directory(DIRECTORY1);
    std::filesystem::create_directory(DIRECTORYxy);
    std::filesystem::create_directory(DIRECTORYyz);
    std::filesystem::create_directory(DIRECTORYxz);
    std::filesystem::create_directory(DIRECTORY3);


    // cout<<"MY: The folder "<< DIRECTORY1 <<" exists"<<endl;
    // cout<<"MY: The folder "<< DIRECTORYxy <<" exists"<<endl;
    // cout<<"MY: The folder "<< DIRECTORYyz <<" exists"<<endl;
    // cout<<"MY: The folder "<< DIRECTORYxz <<" exists"<<endl;
    // cout<<"MY: The folder "<< DIRECTORY3 <<" exists"<<endl;



    // std::string folderName1 = BASEDIRECTORY1 + std::to_string(jentry);
    // std::string folderNamexy = BASEDIRECTORYxy + std::to_string(jentry);
    // std::string folderNameyz = BASEDIRECTORYyz + std::to_string(jentry);
    // std::string folderNamexz = BASEDIRECTORYxz + std::to_string(jentry);
    // std::string folderName3 = BASEDIRECTORY3 + std::to_string(jentry);

    // if (!std::filesystem::exists(folderName1)) 
    // {
    //     std::filesystem::create_directory(folderName1);
    // }
    // if (!std::filesystem::exists(folderNamexy)) 
    // {
    //     std::filesystem::create_directory(folderNamexy);
    // }
    //     else 
    // {
    //   std::cout << "xy esiste già"  << std::endl;
    // }
    // if (!std::filesystem::exists(folderNameyz))
    // {
    //     std::filesystem::create_directory(folderNameyz);
    // }
    //     else 
    // {
    //   std::cout << "yz esiste già"  << std::endl;
    // }
    // if (!std::filesystem::exists(folderNamexz))
    // {
    //     std::filesystem::create_directory(folderNamexz);
    // }
    // if (!std::filesystem::exists(folderName3))
    // {
    //   std::filesystem::create_directory(folderName3);
    // }
    // else 
    // {
    //   std::cout << "qualcosa esiste già, problemi"  << std::endl;
    // }
   

    TCanvas *c_1time=new TCanvas(TString::Format("eve%lld_1time",jentry),TString::Format("c%lld_1time",jentry),1000,1000);
    TCanvas *c_2timexy=new TCanvas(TString::Format("eve%lld_2timexy",jentry),TString::Format("%lld_2timexy",jentry),1000,1000);
    TCanvas *c_2timeyz=new TCanvas(TString::Format("eve%lld_2timeyz",jentry),TString::Format("%lld_2timeyz",jentry),1000,1000);
    TCanvas *c_2timexz=new TCanvas(TString::Format("eve%lld_2timexz",jentry),TString::Format("%lld_2timexz",jentry),1000,1000);
    
    TCanvas *c_2xy=new TCanvas(TString::Format("eve%lld_2xy",jentry),TString::Format("c%lld_2xy",jentry),1000,1000);
    TCanvas *c_2yz=new TCanvas(TString::Format("eve%lld_2yz",jentry),TString::Format("c%lld_2yz",jentry),1000,1000);
    TCanvas *c_2xz=new TCanvas(TString::Format("eve%lld_2xz",jentry),TString::Format("c%lld_2xz",jentry),1000,1000);

    TCanvas *c_3time=new TCanvas(TString::Format("eve%lld_3time",jentry),TString::Format("c%lld_3time",jentry),1000,1000);
    TCanvas *c_3time_tot=new TCanvas(TString::Format("eve%lld_3time_tot",jentry),TString::Format("c%lld_3time_tot",jentry),1000,1000);
    TCanvas *c_3energy=new TCanvas(TString::Format("eve%lld_3energy",jentry),TString::Format("c%lld_3energy",jentry),1000,1000);
    TCanvas *c_3pos=new TCanvas(TString::Format("eve%lld_3pos",jentry),TString::Format("c%lld_3pos",jentry),1000,1000);


    if (jentry==NUMERO)
    {
          
      h_xmin3D=TMath::MinElement(nsch, scpox);
      h_xmax3D=TMath::MaxElement(nsch, scpox);
      h_ymin3D=TMath::MinElement(nsch, scpoy);
      h_ymax3D=TMath::MaxElement(nsch, scpoy);
      h_zmin3D=TMath::MinElement(nsch, scpoz);
      h_zmax3D=TMath::MaxElement(nsch, scpoz);
      enemax=TMath::MaxElement(nsch, scene);
      enemin=TMath::MinElement(nsch, scene);
      timemax=TMath::MaxElement(nsch, sctime);
      timemin=TMath::MinElement(nsch, sctime);



      // Initializing the histogram for the position of the hits in 3D (valid all events, all single ones)  
      h3hpos=new TH3D(TString::Format("h3hpos_%lld",jentry),"Hist in 3D", 
        100, h_xmin, h_xmax, 
        100, h_ymin, h_ymax, 
        100, h_zmin, h_zmax);

      
      // Initializing the histogram for the time of the hits in 1D (valid all events, all single ones)
      h1htime=new TH1F(TString::Format("h1htime_%lld",jentry), 
      TString::Format("h1htime_%lld; time (ns); counts",jentry),
      nbin, tbinlowedge);

      h2hxypos=new TH2F(TString::Format("h2hxypos_%lld",jentry),"Hist in 2D", 
        100, h_xmin, h_xmax, 
        100, h_ymin, h_ymax);
            h2hyzpos=new TH2F(TString::Format("h2hyzpos_%lld",jentry),"Hist in 2D", 
        100, h_ymin, h_ymax, 
        100, h_zmin, h_zmax);
              h2hxzpos=new TH2F(TString::Format("h2hxzpos_%lld",jentry),"Hist in 2D", 
        100, h_xmin, h_xmax,  
        100, h_zmin, h_zmax);
      
      // Initializing the histogram for the energy of the hits in 1D (valid all events, all single ones)
      // h1henergy=new TH1F(TString::Format("h1henergy_%lld",jentry),
      // TString::Format("h1henergy_%lld; energy (keV); counts",jentry),
      // nbin, ebinlowedge);


      for (int ibin=0; ibin<nbin; ibin++)
      {
        TString h2hxytime_name=TString::Format("Event_%lld_h2hxytime_bin%d",jentry,ibin);
        TString h2hyztime_name=TString::Format("Event_%lld_h2hyztime_bin%d",jentry,ibin);
        TString h2hxztime_name=TString::Format("Event_%lld_h2hxztime_bin%d",jentry,ibin);
        TString h3hpostime_name=TString::Format("Event_%lld_h3hpostime_bin%d",jentry,ibin);
        // TString h3hposenergy_name=TString::Format("Event_%lld_h3hposenergy_bin%d",jentry,ibin);

        TString h1htime_title=TString::Format("#splitline{%s Time}{Event %lld};Time (ns); Counts",PARTICLETYPE_TITLE,jentry);
        TString h2hxytime_title=TString::Format("#splitline{%s XY}{#splitline{Event %lld}{Interval %d (%.3fns-%.3fns)}};X (mm);Y (mm)",PARTICLETYPE_TITLE,jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);
        TString h2hyztime_title=TString::Format("#splitline{%s YZ}{#splitline{Event %lld}{Interval %d (%.3fns-%.3fns)}};Y  (mm);Z (mm)",PARTICLETYPE_TITLE,jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);
        TString h2hxztime_title=TString::Format("#splitline{%s XZ}{#splitline{Event %lld}{Interval %d (%.3fns-%.3fns)}};X (mm);Z (mm)",PARTICLETYPE_TITLE,jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);
        TString h3hpostime_title=TString::Format("#splitline{%s 3D}{#splitline{Event %lld}{Interval %d (%.3fns-%.3fns)}};X (mm);Y (mm);Z (mm)",PARTICLETYPE_TITLE,jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);
        // TString h3hposenergy_title=TString::Format("#splitline{%s 3D}{#splitline{Event %lld}{Interval %d (%.3fns-%.3fns)}};X;Y;Z",PARTICLETYPE,jentry,ibin,tbinlowedge[ibin],tbinlowedge[ibin+1]);
        TString h3hpos_title=TString::Format("#splitline{%s 3D}{Event %lld};X (mm);Y (mm);Z (mm)",PARTICLETYPE_TITLE,jentry);

        h1htime->SetTitle(h1htime_title);
        h3hpos->SetTitle(h3hpos_title);
        h3hpostime[ibin]= new TH3D(h3hpostime_name,h3hpostime_title,
          100,h_xmin,h_xmax,
          100,h_ymin,h_ymax,
          100,h_zmin,h_zmax);  


        // h3hposenergy[ibin]= new TH3D(h3hposenergy_name,h3hposenergy_title,
        //   100,h_xmin3D,h_xmax3D,
        //   100,h_ymin3D,h_ymax3D,
        //   100,h_zmin3D,h_zmax3D);
        

        h2hxytime[ibin]=new TH2F(h2hxytime_name,h2hxytime_title,
          100,h_xmin,h_xmax,100,h_ymin,h_ymax);
        
        h2hyztime[ibin]=new TH2F(h2hyztime_name,h2hyztime_title,
          100,h_ymin,h_ymax,100,h_zmin,h_zmax);
        h2hxztime[ibin]=new TH2F(h2hxztime_name,h2hxztime_title,
          100,h_xmin,h_xmax,100,h_zmin,h_zmax);


        for (int ihit=0; ihit<nsch;ihit++)
        {
          if (sctime[ihit]>tbinlowedge[ibin]&&sctime[ihit]<tbinlowedge[ibin+1])
          {
            h1htime->Fill(sctime[ihit]);
            h3hpos->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
            h2hxypos->Fill(scpox[ihit],scpoy[ihit]);           
            h2hyzpos->Fill(scpoy[ihit],scpoz[ihit]);            
            h2hxzpos->Fill(scpox[ihit],scpoz[ihit]);


            h2hxytime[ibin]->Fill(scpox[ihit],scpoy[ihit]);
            h2hyztime[ibin]->Fill(scpoy[ihit],scpoz[ihit]);
            h2hxztime[ibin]->Fill(scpox[ihit],scpoz[ihit]);
            h3hpostime[ibin]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
            // continue;
          }
          // if (scene[ihit]>ebinlowedge[ibin]&&scene[ihit]<ebinlowedge[ibin+1])
          // {
          //   h1henergy->Fill(scene[ihit]);
          //   h3hposenergy[ibin]->Fill(scpox[ihit],scpoy[ihit],scpoz[ihit]);
          // }  
            
        }
        // TH2D* h2hxytime[ibin]=h3hpostime[ibin]->Project3D("xy");
        // TH2D* h2hyztime[ibin]=h3hpostime[ibin]->Project3D("yz");
        // TH2D* h2hxztime[ibin]=h3hpostime[ibin]->Project3D("xz");

        gStyle->SetPalette(kRainBow);
        gStyle->SetTitleFontSize(0.02);
        // gStyle->SetLabelOffset(0.001);
        gStyle->SetOptStat("emr");
        // gStyle->SetX1NDC(0.1);
        // gStyle->SetX2NDC(0.9);
        // gStyle->SetOptStat(0);

        gStyle->SetTextSize(1);
        // auto* legend = new TLegend(0.1,0.1,0.2,0.2);
        // legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
        // legend->AddEntry(h2hxytime[ibin],"Histogram filled with random numbers","f");

        // legend->Draw();

        // dir_h2_xy->cd();
        //   h2hxytime[ibin]->Write();
        if (MIOCOLORE=="nero") 
        {
          mycolor=kBlack;
        }
        else if (MIOCOLORE=="arcobaleno") 
        {
          mycolor=TColor::GetColorPalette(ibin*(254/nbin));
        }
        else 
        {
          cout<<"ATTENZIONE ne nero ne arco"<<endl;
        }

        c_2timexy->cd();
          h2hxytime[ibin]->SetMarkerStyle(20);
          h2hxytime[ibin]->SetMarkerSize(MISURA);
          h2hxytime[ibin]->SetMarkerColor(mycolor);
          // h2hxytime[ibin]->GetXaxis()->SetTitle("X (mm)");
          // h2hxytime[ibin]->GetYaxis()->SetTitle("Y (mm)");
          h2hxytime[ibin]->GetYaxis()->SetTitleOffset(1.5);
          // h2hxytime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          // myline1=new TLine(h_xmin, h_yECALmin, h_xmax, h_yECALmin);
          // myline3=new TLine(h_xmin, h_yHCALmin, h_xmax, h_yHCALmin);
          // myline2=new TLine(h_xmin, h_yHCALmax, 1400, h_yHCALmax);
          // myline4=new TLine(h_xmin, h_yECALmax, h_xmax, h_yECALmax);
          myline1xy=TLine(h_xmin, h_yECALmin, h_xmax, h_yECALmin);
          myline3xy=TLine(h_xmin, h_yHCALmin, h_xmax, h_yHCALmin);
          myline2xy=TLine(h_xmin, h_yHCALmax, 1400, h_yHCALmax);
          myline4xy=TLine(h_xmin, h_yECALmax, h_xmax, h_yECALmax);
          h2hxytime[ibin]->Draw();    
          myline1xy.Draw("SAME");
          myline2xy.Draw("SAME");
          myline3xy.Draw("SAME");
          myline4xy.Draw("SAME");
          TLatex *text_ecalxy=new TLatex(-1900,1830,"ECAL");
          text_ecalxy->SetTextSize(0.03);
          text_ecalxy->SetTextAngle(90);
          text_ecalxy->Draw("SAME");
          TLatex *text_hcalxy=new TLatex(-1900,2650,"HCAL");
          text_hcalxy->SetTextSize(0.03);
          text_hcalxy->SetTextAngle(90);
          text_hcalxy->Draw("SAME");
          c_2timexy->SaveAs(TString::Format("%s%lld_2timexy_%d.pdf",DIRECTORYxy.c_str(),jentry,ibin));
          h2hxytime[ibin]->SetMarkerColor(mycolor);
          // h2hxytime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          // dir_h2_xy->cd();
          c_2timexy->Print(TString::Format("%s%lld_2timexy_gif.gif+40",BASEDIRECTORYxy.c_str(),jentry));  
        // c_2xy->cd();
        //   h2hxypos->SetMarkerColor(kBlack);
        //   // h2hxypos->SetTitleSize(2);
        //   h2hxypos->GetYaxis()->SetTitleOffset(1);
        //   h2hxypos->SetLabelSize(0.02,"xy");
        //   h2hxypos->SetTitle(TString::Format("#splitline{%s XY}{Event %lld};X (mm);Y (mm)",PARTICLETYPE_TITLE,jentry));
        //   h2hxypos->Draw("SAME");
        //   myline1xy.Draw("SAME");
        //   myline2xy.Draw("SAME");
        //   myline3xy.Draw("SAME");
        //   myline4xy.Draw("SAME");
        //   text_ecalxy->Draw("SAME");
        //   text_hcalxy->Draw("SAME");
        c_2xy->cd();
          h2hxytime[ibin]->SetMarkerColor(mycolor);
          // h2hxytime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          h2hxytime[ibin]->GetYaxis()->SetTitleOffset(1);
          h2hxytime[ibin]->SetLabelSize(0.02,"xy");
          h2hxytime[ibin]->SetTitle(TString::Format("#splitline{%s XY}{Event %lld};X (mm);Y (mm)",PARTICLETYPE_TITLE,jentry));
          h2hxytime[ibin]->Draw("SAME");
          myline1xy.Draw("SAME");
          myline2xy.Draw("SAME");
          myline3xy.Draw("SAME");
          myline4xy.Draw("SAME");
      
        // delete myline1;
        // delete myline2;
        // delete myline3;
        // delete myline4;


        // dir_h2_yz->cd();
        //   h2hyztime[ibin]->Write();
        c_2timeyz->cd();
          h2hyztime[ibin]->SetMarkerStyle(20);
          h2hyztime[ibin]->SetMarkerSize(MISURA);
          // h2hyztime[ibin]->SetMarkerColor(kBlack);
          // h2hyztime[ibin]->GetXaxis()->SetTitle("Y (mm)");
          // h2hyztime[ibin]->GetYaxis()->SetTitle("Z (mm)");
          h2hyztime[ibin]->GetYaxis()->SetTitleOffset(1.5);
          // h2hyztime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          h2hyztime[ibin]->SetMarkerColor(mycolor);
          // h2hyztime[ibin]->SetMarkerColor(kBlack);
          myline1yz=TLine(h_yECALmin,h_zmin, h_yECALmin, h_zmax);
          myline2yz=TLine(h_yHCALmax,h_zmin, h_yHCALmax, 1750);
          myline3yz=TLine(h_yHCALmin,h_zmin, h_yHCALmin, h_zmax);
          myline4yz=TLine(h_yECALmax,h_zmin, h_yECALmax, h_zmax);
          h2hyztime[ibin]->Draw();    
          // myline1yz->Draw("SAME");
          // myline2yz->Draw("SAME");
          // myline3yz->Draw("SAME");
          // myline4yz->Draw("SAME");
          myline1yz.Draw("SAME");
          myline2yz.Draw("SAME");
          myline3yz.Draw("SAME");
          myline4yz.Draw("SAME");
          TLatex *text_ecalyz=new TLatex(1830,3000,"ECAL");
          text_ecalyz->SetTextSize(0.03);
          text_ecalyz->Draw("SAME");
          TLatex *text_hcalyz=new TLatex(2700,3000,"HCAL");
          text_hcalyz->SetTextSize(0.03);
          text_hcalyz->Draw("SAME");
          c_2timeyz->SaveAs(TString::Format("%s%lld_2timeyz_%d.pdf",DIRECTORYyz.c_str(),jentry,ibin));
          h2hyztime[ibin]->SetMarkerColor(mycolor);
          // h2hyztime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          // dir_h2_yz->cd();
          c_2timeyz->Print(TString::Format("%s%lld_2timeyz_gif.gif+40",BASEDIRECTORYyz.c_str(),jentry));  
        // c_2yz->cd();
        //   h2hyzpos->SetMarkerColor(kBlack);
        //   h2hyzpos->GetYaxis()->SetTitleOffset(1);
        //   h2hyzpos->SetLabelSize(0.02,"xy");
        //   h2hyzpos->SetTitle(TString::Format("#splitline{%s YZ}{Event %lld};Y (mm);Z (mm)",PARTICLETYPE_TITLE,jentry));
        //   h2hyzpos->Draw("SAME");
        //   myline1yz.Draw("SAME");
        //   myline2yz.Draw("SAME");
        //   myline3yz.Draw("SAME");
        //   myline4yz.Draw("SAME");
        //   text_ecalyz->Draw("SAME");
        //   text_hcalyz->Draw("SAME");
        c_2yz->cd();
          h2hyztime[ibin]->SetMarkerColor(mycolor);
          // h2hyztime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          h2hyztime[ibin]->GetYaxis()->SetTitleOffset(1);
          h2hyztime[ibin]->SetLabelSize(0.02,"xy");
          h2hyztime[ibin]->SetTitle(TString::Format("#splitline{%s YZ}{Event %lld};Y (mm);Z (mm)",PARTICLETYPE_TITLE,jentry));
          h2hyztime[ibin]->Draw("SAME");
          myline1yz.Draw("SAME");
          myline2yz.Draw("SAME");
          myline3yz.Draw("SAME");
          myline4yz.Draw("SAME");
          text_ecalyz->Draw("SAME");
          text_hcalyz->Draw("SAME");
      



        // dir_h2_xz->cd();
        // h2hxztime[ibin]->Write();
        c_2timexz->cd();
          h2hxztime[ibin]->SetMarkerStyle(20);
          h2hxztime[ibin]->SetMarkerSize(MISURA);
          h2hxztime[ibin]->SetMarkerColor(mycolor);
          // h2hxztime[ibin]->SetMarkerColor(kBlack);
          // h2hxztime[ibin]->GetXaxis()->SetTitle("X (mm)");
          // h2hxztime[ibin]->GetYaxis()->SetTitle("Z (mm)");
          h2hxztime[ibin]->GetYaxis()->SetTitleOffset(1.5);
          h2hxztime[ibin]->Draw();
          // h2hxztime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          h2hxztime[ibin]->SetMarkerColor(mycolor);
          // h2hxztime[ibin]->SetMarkerColor(kBlack);
          c_2timexz->SaveAs(TString::Format("%s%lld_2timexz_%d.pdf",DIRECTORYxz.c_str(),jentry,ibin));
          // h2hxztime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          h2hxztime[ibin]->SetMarkerColor(mycolor);
          // h2hxztime[ibin]->SetMarkerColor(kBlack);
          c_2timexz->Print(TString::Format("%s%lld_2timexz_gif.gif+40",BASEDIRECTORYxz.c_str(),jentry));  
        // c_2xz->cd();
        //   h2hxzpos->SetMarkerColor(kBlack);
        //   h2hxzpos->GetYaxis()->SetTitleOffset(1);
        //   h2hxzpos->SetLabelSize(0.02,"xy");
        //   h2hxzpos->SetTitle(TString::Format("#splitline{%s XZ}{Event %lld};X (mm);Z (mm)",PARTICLETYPE_TITLE,jentry));
        //   h2hxzpos->Draw("SAME");
        c_2xz->cd();
          h2hxztime[ibin]->SetMarkerColor(mycolor);
          // h2hxztime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
          h2hxztime[ibin]->GetYaxis()->SetTitleOffset(1);
          h2hxztime[ibin]->SetLabelSize(0.02,"xy");
          h2hxztime[ibin]->SetTitle(TString::Format("#splitline{%s XZ}{Event %lld};X (mm);Z (mm)",PARTICLETYPE_TITLE,jentry));
          h2hxztime[ibin]->Draw("SAME");


        // dir_h3->cd();
        // h3hpostime[ibin]->Write(); 
        c_3time->cd();
        h3hpostime[ibin]->SetMarkerStyle(20);
        h3hpostime[ibin]->SetMarkerSize(MISURA);
        h3hpostime[ibin]->SetMarkerColor(kBlack);
        h3hpostime[ibin]->SetMarkerColor(mycolor);
        // h3hpostime[ibin]->SetMarkerColor(kBlack);
        // h3hpostime[ibin]->GetXaxis()->SetTitle("X (mm)");
        // h3hpostime[ibin]->GetYaxis()->SetTitle("Y (mm)");
        // h3hpostime[ibin]->GetZaxis()->SetTitle("Z (mm)");
        h3hpostime[ibin]->SetLabelSize(0.02,"xyz");
        h3hpostime[ibin]->GetXaxis()->SetTitleOffset(1.5);
        h3hpostime[ibin]->GetYaxis()->SetTitleOffset(2);
        h3hpostime[ibin]->GetZaxis()->SetTitleOffset(1.5);
        h3hpostime[ibin]->Draw();
        c_3time->SaveAs(TString::Format("%s%lld_3time_%d.pdf",DIRECTORY3.c_str(),jentry,ibin));
        c_3time->Print(TString::Format("%s%lld_3time_gif.gif+40",BASEDIRECTORY3.c_str(),jentry,ibin));
        c_3time_tot->cd();
        h3hpostime[ibin]->SetLabelSize(0.02,"xyz");
        h3hpostime[ibin]->GetXaxis()->SetTitleOffset(1.5);
        h3hpostime[ibin]->GetYaxis()->SetTitleOffset(2);
        h3hpostime[ibin]->GetZaxis()->SetTitleOffset(1.5);
        h3hpostime[ibin]->SetMarkerColor(mycolor);
        // h3hpostime[ibin]->SetMarkerColor(TColor::GetColorPalette(ibin*(254/nbin)));
        h3hpostime[ibin]->SetTitle(TString::Format("#splitline{%s 3D}{Event %lld};X (mm);Y (mm);Z (mm)",PARTICLETYPE_TITLE,jentry));

        h3hpostime[ibin]->Draw("SAME");  

        
        // c_3time_tot->Close();

        // delete h2hxytime[ibin];
        // delete h2hyztime[ibin];
        // delete h2hxztime[ibin];
        // delete h3hpostime[ibin];
        // c_3energy->cd();
        //   h3hposenergy[ibin]->SetMarkerStyle(20);
        //   h3hposenergy[ibin]->SetMarkerSize(MISURA);
        //   h3hposenergy[ibin]->SetMarkerColor(ibin);
        //   h3hposenergy[ibin]->Draw(" SAME");

      } // end of loop over bins
      

      c_2xy->SaveAs(TString::Format("%s%lld_2xy.pdf",BASEDIRECTORYxy.c_str(),jentry));
      delete h2hxypos;
      c_2yz->SaveAs(TString::Format("%s%lld_2yz.pdf",BASEDIRECTORYyz.c_str(),jentry));
      delete h2hyzpos;
      c_2xz->SaveAs(TString::Format("%s%lld_2xz.pdf",BASEDIRECTORYxz.c_str(),jentry));
      delete h2hxzpos;


      c_2timexy->Print(TString::Format("%s%lld_2timexy_gif.gif++",BASEDIRECTORYxy.c_str(),jentry));
      c_2timeyz->Print(TString::Format("%s%lld_2timeyz_gif.gif++",BASEDIRECTORYyz.c_str(),jentry));
      c_2timexz->Print(TString::Format("%s%lld_2timexz_gif.gif++",BASEDIRECTORYxz.c_str(),jentry));
      
      c_3time->Print(TString::Format("%s%lld_3time_gif.gif++",BASEDIRECTORY3.c_str(),jentry));
      c_3time_tot->SaveAs(TString::Format("%s%lld_3time.pdf",BASEDIRECTORY3.c_str(),jentry));
      
      
      for (int ibin=0; ibin<nbin; ibin++)        
      {           
        delete h2hxytime[ibin];
        delete h2hyztime[ibin];
        delete h2hxztime[ibin];
        delete h3hpostime[ibin];
      }
      // c_3time->Write();
      // c_3energy->Write();     
      


      // dir_h1->cd();
      // h1htime->Write();
      c_1time->cd();
      // h1htime->SetTitle(h1htime_title);
      h1htime->Draw();
      c_1time->SaveAs(TString::Format("%s%lld_1time.pdf",BASEDIRECTORY1.c_str(),jentry));
      c_1time->Clear();
      // h1htime->Setlogx();
      h1htime->Draw();
      c_1time->SetLogx();
      c_1time->SaveAs(TString::Format("%s%lld_1time_log.pdf",BASEDIRECTORY1.c_str(),jentry));
      delete h1htime;
      // h1henergy->Write();
      // delete h1henergy;
      // dir_h3->cd();
      c_3pos->cd();
      h3hpos->SetLabelSize(0.02,"xyz");
      h3hpos->GetXaxis()->SetTitleOffset(1.5);
      h3hpos->GetYaxis()->SetTitleOffset(2);
      h3hpos->GetZaxis()->SetTitleOffset(1.5);

      // h3hpos->SetTitle(h3hpos_title);
      h3hpos->Draw();
      c_3pos->SaveAs(TString::Format("%s%lld_3pos.pdf",BASEDIRECTORY3.c_str(),jentry));

      delete h3hpos;
      

      
      

    } // end if for the specific event
    
    // delete all the canvas gif and static
    delete c_2timexy;
    delete c_2timeyz;
    delete c_2timexz;
    delete c_2xy;
    delete c_2yz;
    delete c_2xz;
    delete c_3time;
    delete c_3time_tot;
    delete c_3energy;
    delete c_1time;
    delete c_3pos;


    

    auto stopevent = high_resolution_clock::now(); 
    auto durationevent = duration_cast <seconds>(stopevent - startevent);
    auto duration = duration_cast <seconds>(stopevent - start);    
    cout << jentry<<"\t"<<nsch<<
    "\t"<< durationevent.count() << 
    "\t"<< duration.count() <<  
    "\t"<< ((duration.count()/(jentry+1))*(nentries-jentry-1))/60 << "' " <<
    ((duration.count()/(jentry+1))*(nentries-jentry-1))%60 << "\"" << endl;;




  } // end loop over the events


  storemyfile->Close();
  // delete storemyfile;

  // gSystem->Exec("rootbrowse myfileh3h.root"); // execute the root file
  
  // time check
  auto stop= high_resolution_clock::now(); 
  auto duration = duration_cast<seconds>(stop - start);
  cout << "Time taken by program: "<< duration.count() << " seconds" << endl;
  
} // end of main function

