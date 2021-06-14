#include<stdio.h>
#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

void CMCS(){

	TString file;
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
	double terror; //thickness error[g/cm^3]
	double Na=6.02214076*pow(10,23); //Avogadoro constant[/mol]
	double time=100; //mesurement time[s]
	double r=M_PI/180.; //degree to radian
	static double CMangle[160],counts[160],I[160],Ierror[160]; 
	static double cross[160], CMcross[160],CSerror[160];



	cout << "Target(Au,C,H): ";
	cin >> target;

	if(target=="Au"){
		A=197;
		d=19.32;
		t=0.1611913031;
		terror=0.01;
	}else if(target=="C"){
		A=12;
		d=0.797*Rc; 
		t=11.5; //μm
		terror=0.5;
	}else if(target=="H"){
		A=1;
		d=0.797*Rh;  
		t=11.5; //μm
		terror=0.5;
	}else{
		cout << "Target name is wrong! → " << target << endl;
		return 0;
	}

	t=t*pow(10,-4); //μm to cm
	terror=terror*pow(10,-4);


	for(int i=0;i<1000000;i++){
	
		cout << "\nangle(lab)[degree] (quit→1): ";
		cin >> angle;
		
		if(angle==1){
		  break;	

			if(i>=2){
				cout << "\nWrite in " << file << "\n" << endl;
			}

		  return 0;
		}




		//lab to CM (bisection method)		
		double error=10e-20,CMmin=0,CMmax,CMmid;

		if(angle>90){
    		CMmax=200;
    	}else if(angle<90){
    		CMmax=350;
    	}else if(angle==90){
			CMmid=(acos((-1.)/A))/r;
		}
    
    
    	while((CMmax-CMmin)*(CMmax-CMmin)>=error){

			if(angle==90){
				break;
			}

    		CMmid = (CMmax+CMmin)/2;
    		double func = sin(r*CMmid)/(cos(r*CMmid)+(1./A)) - sin(r*angle)/cos(r*angle);
    
   			//cout << "CMmid: " << CMmid << " func: " << func << endl;
 
    		if(func>0){
    			CMmax = CMmid;
    
    		}else if(func<0){
    			CMmin = CMmid;
    
    		}else if(func==0){
    			break;
    		}
    
		}
    
    	CMangle[angle]=CMmid;

    	if(CMangle[angle]>185){
    		CMangle[angle]=CMangle[angle]-180;
    	}
    	
	cout << "angle(CM)[degree]: " << CMangle[angle] << " ± 1e-20" << endl;



	cout << "proton counts: ";
	cin >> counts[angle];



	if(counts[angle]==0){
	  continue;
	}



	if(angle==140){
		//θ=140
		cout << "electric current[nA]: ";
		cin >> I[angle];
		I[angle] = I[angle]*pow(10,-9);

		cout << "current error[nA]: ";
		cin >> Ierror[angle];
		Ierror[angle] = Ierror[angle]*pow(10,-9);

		cross[angle]=counts[angle]*e*A/dW140/I[angle]/time/d/t/Na;
		CSerror[angle]=pow( pow(cross[angle],2)/counts[angle] + pow(cross[angle],2)*pow(I[angle],-2)*pow(Ierror[angle],2) + pow(cross[angle],2)*terror*terror/(t*t) ,0.5);


		CMcross[angle]=(1+cos(CMangle[angle]*r)/A)/(pow(((2*(cos(CMangle[angle]*r))/A)+1+(1/(A*A))) ,1.5))*cross[angle];

		}



		else{
		//θ≠140	

		cout << "electric current[nA]: ";
		cin >> I[angle];
		I[angle] = I[angle]*pow(10,-9);

		cout << "current error[nA]: ";
		cin >> Ierror[angle];
		Ierror[angle] = Ierror[angle]*pow(10,-9);

		cross[angle]=counts[angle]*e*A/dW/I[angle]/time/d/t/Na;
		CSerror[angle]=pow( pow(cross[angle],2)/counts[angle] + pow(cross[angle],2)*pow(I[angle],-2)*pow(Ierror[angle],2) + pow(cross[angle],2)*terror*terror/(t*t) ,0.5);


		CMcross[angle]=(1+cos(CMangle[angle]*r)/A)/(pow(((2*(cos(CMangle[angle]*r))/A)+1+(1/(A*A))) ,1.5))*cross[angle]; 
		}



		//command line output
		cout << "cross-section(CM): " << " " << CMcross[angle] 
			<< " ± " << CSerror[angle] << " [cm^2/sr]"  << endl;
		



		//file output 
		for(int i=0;i<10000;i++){

				cout << "Do you wish to write this data? (yes/no) ";
				cin >> YesorNo;

				if(YesorNo=="yes" || YesorNo=="Yes" || YesorNo=="YES"){
				  ofs << CMangle[angle] << " " << CMcross[angle] << " "  << CSerror[angle] << "\n";
				  break;
				}else if(YesorNo=="no" || YesorNo=="No" || YesorNo=="NO"){
				  cout << "writting interrupted" << endl;
				  break;
				}else{
				  cout << "Please input 'yes' or 'no'" << endl;
				  continue;
				}
		}

	} 


	return 0;
}

