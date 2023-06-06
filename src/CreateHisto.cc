// #include "CreateHisto.hh"

// class MakeHisto(){
//    public:
//     int Bins;
//     float IntialH;
//     float FinalH;
//     string NameCanvas; 
//     string Title;
//     string NameFile;
//     MakeHisto(int bins,float intialh,float finalh,string namecanvas,string title,string namefile){
//         Bins=bins;
//         IntialH=initialh;
//         FinalH=finalh;
//         NameCanvas=namecanvas; 
//         Title=title;
//         NameFile=namefile;
//     }
//     WriteHistoRoot(int Bins, float InitialH, float FinalH){
//         TH1F* NameCanvas = new TH1F(NameCanvas, Title, Bins, InitialH, FinalH);
//         TFile* NameFile=new TFile(NameFile+".root","recreate");
//         NameCanvas->Write();
//         NameFile->Write();
//         NameFile->Close();
//         cout<<"Canvas "<<NameCanvas<<" has been created and written inside the root file "<<NameFile<<".root"<<endl;

//     }

//     AnalysisPfoEvents(TVector EnMom){
//         double PpfoX=accumulate(pfoPx->begin(), pfoPx->end(),0.0);
//         double PpfoY=accumulate(pfoPy->begin(), pfoPy->end(),0.0);
//         double PpfoZ=accumulate(pfoPz->begin(), pfoPz->end(),0.0);
//         double Peventsq=pow(PpfoX,2)+pow(PpfoY,2)+pow(PpfoZ,2);
//         double Eneventsq=pow(pfoEnergyTotal,2);
//         double Energyevent_sumpfos=accumulate(pfoEnergies->begin(),pfoEnergies->end(),0.0);

//         cout << "energysq total of the event =" << Eneventsq<<endl;
//         cout << "momentumsq total of the event =" << Peventsq<<endl;
//         if (Eneventsq-Peventsq>thres) 
//         {
//           cout<<"masssq total of the event= "<<Eneventsq-Peventsq<<endl; 
//           ok++;
//           goodeventslist.push_back(jentry);
//         }
//         else 
//         {
//           cout<<"strange mass = "<<Eneventsq-Peventsq<<" for the event "<<jentry<<endl; 
//           ko++;
//         }
//         cout<<" energy total event = "<<pfoEnergyTotal<<" "<<Energyevent_sumpfos<<endl;
//         cout << endl;
    
    
    
//     if (ok==0) cout<<"no event with mass under "<<thres<<" GeV"<<endl;
//     else if (ok>0 && ok<20) 
//     {
//       cout<<ok<<" events "<<" have reasonable mass, all the others ("<<ko<<") don't"<<endl;  
//       cout<<" they are events: ";
//       for (auto i: goodeventslist) cout<< i << ' ';
//       cout<<endl;
//     }
//     else cout<<"there are "<<ok<<" reasonable mass events and "<<ko<<" unreasonable"<<endl;
  
//     }
// };
// // const char * RecommendMeAFood(char firstletter){
// //     if(firstletter=='a'||firstletter=='A')
// //         return "apple";
// //     else if(firstletter=='b')
// //         return "banana";
// //     else if(firstletter=='c')
// //         return "chocolate cake";
// //     else return "pizza";
// // }