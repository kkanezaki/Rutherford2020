#include <iostream>
#include <math.h>

using namespace std;

int main(){

  double p;//=0.797;//(g/cm3)
  double E; //(MeV)
  double E1,E2,E3,E4,E5,E6,E7,dE1,dE2;//(MeV)
  double X,x;
  double Zh=1,Zc=6,Ah=1,Ac=12;
  double Nh=2;
  double Nc=1;
  //double rc=;
  //double rh=1-rc;
  double e=1.6*pow(10,-19);//(C)
  double mp=1.67*pow(10,-27);
  double c=2.99792458*pow(10,8);

  cout << "proton energy (MeV) = ";
  cin >> E;
  
  cout << "density (g/cm^3) =";
  cin >> p;
  
  cout << "x[um] = "; 
  cin >> x;

  double IN=E;
 
  for(int i=1; i<1000000; i++)
   {
     double Ic=16*pow(Zc,0.9)*pow(10,-6);

     double Ih=16*pow(Zh,0.9)*pow(10,-6);
    
     double v=pow(E*pow(10,6)*e*2/mp,0.5)/c;

     //E1=p*D*1000*ZA;
     E1=(Nh/(Nh+Nc))*0.307075*p*Zh/(Ah*v*v)*(log(1.022*v*v/(Ih*(1-v*v)))-v*v);
     E2=(Nc/(Nh+Nc))*0.307075*p*Zc/(Ac*v*v)*(log(1.022*v*v/(Ic*(1-v*v)))-v*v);
     //E3=log(1.022*v*v/(Ih*(1-v*v)))-v*v;
     //E4=log(1.022*v*v/(Ic*(1-v*v)))-v*v;
     //E5=(2/3)*p*E1*E3; 
     //E6=(1/3)*p*E2*E4;

     dE1=E1*pow(10,-6);
     dE2=E2*pow(10,-6);
     
     E=E-dE1-dE2;//MeV
	
	//cout << E << endl;

     X=0.01*i;//um
   
     if(X>x){
	     break;}       
   }
   cout << E << "MeV" << "\t" << X << "um" << endl;
   cout << IN-E;
   return 0;
  }

