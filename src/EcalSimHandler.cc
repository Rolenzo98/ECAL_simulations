#define EcalSimHandler_cxx
#include "EcalSimHandler.hh"

void EcalSimHandler::Loop()
{
//   In a ROOT session, you can do:
//      root> .L EcalSimHandler.C
//      root> EcalSimHandler t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  // MODIFY FROM HERE

  TH1F * hist = new TH1F("hist","hist",100,0,2);

  // TIL HERE

  Long64_t nbytes = 0, nb = 0;

  // Event Loop
  int ok=0;
  int ko=0;
  float thres=0.1;

  vector<int> goodeventslist;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;

    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;

    // MODIFY FROM HERE

    // cout << "Number of PFO : " << nPfosTotal << " = " << pfoEnergies->size() << endl;
    // hist->Fill(nPfosPhotons);

    // check if the vector size of pfoEnergies (along with all the other vectors e.g. pfoPx) is consistent with nPfosTotal
    if (nPfosTotal == pfoEnergies->size()) {
      // cout << "print energy ";
      //  for ( int ipfo=0; ipfo < nPfosTotal; ipfo++ ){
      //   cout << pfoEnergies->at(ipfo) << " ";
       double PpfoX=accumulate(pfoPx->begin(), pfoPx->end(),0.0);
       double PpfoY=accumulate(pfoPy->begin(), pfoPy->end(),0.0);
       double PpfoZ=accumulate(pfoPz->begin(), pfoPz->end(),0.0);
       double Peventsq=pow(PpfoX,2)+pow(PpfoY,2)+pow(PpfoZ,2);
       double Eneventsq=pow(pfoEnergyTotal,2);
       double Energyevent_sumpfos=accumulate(pfoEnergies->begin(),pfoEnergies->end(),0.0);



      //     double masssq=pow(pfoEnergies->at(ipfo),2)-totPsq;
      //     double energysq=pow(pfoEnergies->at(ipfo),2);
      //     cout<<"the particle is = "<<pfoPdgCodes->at(ipfo)<<endl;        
      //     cout << "energysq of the pfo =" << energysq<<endl;
      //     cout << "momentumsq of the pfo =" << Psq<<endl;
      //     cout<<"masssq of the pfo= "<<masssq<<endl;
      //     cout<<"- . - . - "<<endl;
      //     hist->Fill(sqrt(masssq));
      //   }


      //  cout<<PpfoX<<" "<<PpfoY<<" "<<PpfoZ<<endl;
      //  cout<<Ppfox<<" "<<Ppfoy<<" "<<Ppfoz<<endl;

        // cout<<"on x: "<<Ppfox-PpfoX<<" on y: "<<Ppfoy-PpfoY<<" on z: "<<Ppfoz-PpfoZ<<endl;
        cout << "energysq total of the event =" << Eneventsq<<endl;
        cout << "momentumsq total of the event =" << Peventsq<<endl;
        if (Eneventsq-Peventsq>thres) 
        {
          cout<<"masssq total of the event= "<<Eneventsq-Peventsq<<endl; 
          ok++;
          goodeventslist.push_back(jentry);
        }
        else 
        {
          cout<<"strange mass = "<<Eneventsq-Peventsq<<" for the event "<<jentry<<endl; 
          ko++;
        }
        cout<<" energy total event = "<<pfoEnergyTotal<<" "<<Energyevent_sumpfos<<endl;
        cout << endl;
    }

    // switch (ok)
    // {
    //   case 0:
    //   cout<<"no event under "<<thres<<" GeV"<<end;
    //   case <20:
    //   cout<<"events "<<ok<<" are reasonable, all the others ("<<ko<<") aren't"<<endl;  
    //   default:
    //   cout<<"there are "<<ok<<" reasonable events and "<<ko<<" unreasonable"<<endl;
    // }

 


    // TIL HERE

  }



  // MODIFY FROM HERE
  TFile *storemyfile=new TFile("myfile.root","recreate");

  hist->Write();
  storemyfile->Write();
  storemyfile->Close();
  
    if (ok==0) cout<<"no event with mass under "<<thres<<" GeV"<<endl;
    else if (ok>0 && ok<20) 
    {
      cout<<ok<<" events "<<" have reasonable mass, all the others ("<<ko<<") don't"<<endl;  
      cout<<" they are events: ";
      for (auto i: goodeventslist) cout<< i << ' ';
      cout<<endl;
    }
    else cout<<"there are "<<ok<<" reasonable mass events and "<<ko<<" unreasonable"<<endl;
  
  
  // TIL HERE


}
