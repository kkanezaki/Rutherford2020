#include<stdio.h>
#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;


void expCS2(){

  string file;
  cout << "\nOutput Filename(.txt): ";
  cin >> file;
  ofstream ofs(file,ios::app);

  TString target,YesorNo;
  int angle; //angle[degree]
  double A; //mass number[g/mol]
  double Ah2=2, Ac=12, Rh=Ah2/(Ah2+Ac), Rc=Ac/(Ah2+Ac);
  double e=1.602*pow(10,-19); //electric charge[C]
  double dW=M_PI*pow(1.5,2)/pow(60,2); //solid angle[sr]
  double dW140=M_PI*pow(4,2)/pow(60,2);
  double d; //density of target[g/cm^3]
  double t; //thickness of target
  double Na=6.02*pow(10,23); //Avogadoro constant[/mol]
  double time=100; //mesurement time[s]
  double r=M_PI/180; //degree to radian
  static double CMangle[160],counts[160],I[160],Ierror[160]; 
  static double cross[160], CMcross[160],CSerror[160];



  cout << "Target(Au,C,H): ";
  cin >> target;

  if(target=="Au"){
	A=197;
	d=19.32;
	t=0.1611913031;
  }else if(target=="C"){
	A=12;
	d=0.797*Rc; 
	t=11.5; //μm
  }else if(target=="H"){
	A=1;
	d=0.797*Rh;  
	t=11.5; //μm
  }else{
	cout << "Target name is wrong! → " << target << endl;
	return 0;
  }

  t=t*pow(10,-4); //μm to cm



  for(int i=0;i<1000000;i++){
  
  cout << "\nangle[degree] (quit→1): ";
  cin >> angle;

   if(angle==1){
  	break;
	return 0;
   }
  cout << "proton counts: ";
  cin >> counts[angle];

  if(counts[angle]==0){
    continue;

  }if(angle==140){
  
  cout << "electric current[nA]: ";
  cin >> I[angle];
  I[angle] = I[angle]*pow(10,-9);

  cout << "current error[nA]: ";
  cin >> Ierror[angle];
  Ierror[angle] = Ierror[angle]*pow(10,-9);

  cross[angle]=counts[angle]*e*A/dW140/I[angle]/time/d/t/Na;
  CSerror[angle]=pow( pow(cross[angle],2)/counts[angle] + pow(cross[angle],2)*pow(I[angle],-2)*pow(Ierror[angle],2) ,0.5);

  CMangle[angle]=atan(sin(r*angle)/(cos(r*angle)-(1/A)))/r;
		if(CMangle[angle]<0){
			CMangle[angle]=180+CMangle[angle];
		}

  CMcross[angle]=(1+cos(CMangle[angle]*r)/A)/(pow(((2*(cos(CMangle[angle]*r))/A)+1+(1/(A*A))) ,1.5))*cross[angle];

  }else{
  
  cout << "electric current[nA]: ";
  cin >> I[angle];
  I[angle] = I[angle]*pow(10,-9);

  cout << "current error[nA]: ";
  cin >> Ierror[angle];
  Ierror[angle] = Ierror[angle]*pow(10,-9);

  cross[angle]=counts[angle]*e*A/dW/I[angle]/time/d/t/Na;
  CSerror[angle]=pow( pow(cross[angle],2)/counts[angle] + pow(cross[angle],2)*pow(I[angle],-2)*pow(Ierror[angle],2) ,0.5);

  CMangle[angle]=atan(sin(r*angle)/(cos(r*angle)-(1/A)))/r;
		if(CMangle[angle]<0){
			CMangle[angle]=180+CMangle[angle];
		}

  CMcross[angle]=(1+cos(CMangle[angle]*r)/A)/(pow(((2*(cos(CMangle[angle]*r))/A)+1+(1/(A*A))) ,1.5))*cross[angle]; 
  }

  cout << "cross-section(CM): " << " " << CMcross[angle] << " ± " << CSerror[angle] << " [cm^2/sr]"  << endl;
  

  for(int i=0;i<10000;i++){

	cout << "Do you wish to write this data? (yes/no) ";
  	cin >> YesorNo;

	if(YesorNo=="yes" || YesorNo=="Yes" || YesorNo=="YES"){
		ofs << CMangle[angle] << " " << CMcross[angle] << " "  << CSerror[angle] << "\n";
		break;
	}else if(YesorNo=="no" || YesorNo=="No" || YesorNo=="NO"){
		cout << "I stopped writting" << endl;
		break;
  	}else{
		cout << "Please input 'yes' or 'no'" << endl;
		continue;
	}
  }

  } 

  if(angle!=1){
	cout << "\nWrite in → " << file << "\n" << endl;
  }else{
	cout << "" <<endl;
  }

  return 0;
}
