#include <TLatex.h>
#include <TString.h>
#include <string>
#include <sstream>
#define Initial_Variables_h

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
float energy_threshold=0.0001;


int nbin=24;
int nbinlowedge=nbin+1;


float tbinlowedge_10[]={0, 1, 10,100,1000};//0 to 1 ps, 1ps to 1 ns, 1ns to 10 ns, 10ns to 100ns, 1 mus to 1 ms
int nbin_10=sizeof(tbinlowedge_10)/sizeof(tbinlowedge_10[1]);

// gErrorIgnoreLevel = kWarning;
//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
std::string PARTICLETYPE="Pions";
int NUMBER=58; //6 for pions, 34 for electrons
std::string MIOCOLORE="arcobaleno"; //"nero" for kBlack, "arcobaleno" for tcolor::krainbow
Color_t mycolor;
float MISURA=1;
//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//-//
int JUSTONCE=0;
