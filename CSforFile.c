#include<stdio.h>
#include<iostream>
#include<cmath>
#include<fstream>

using namespace std;

void CSforFile(){


	TString inputfile;
	cout << "Input Filename: ";
	cin >> inputfile;
	ifstream ifs(inputfile);

	TString outputfile;
	cout << "Output Filename: ";
	cin >> outputfile;
	ofstream ofs(outputfile,ios::app);


	TString target,YesorNo;
	double A; //mass number[g/mol]
	double Ah2=2, Ac=12, Rh=Ah2/(Ah2+Ac), Rc=Ac/(Ah2+Ac);
	double e=1.602*pow(10,-19); //electric charge[C]
	double dW=M_PI*pow(1.5,2)/pow(60,2); //solid angle[sr]
	double dW140=M_PI*pow(4,2)/pow(60,2);
	double d_t; //density of target[g/cm^3] * thickness[μm]
	double d_terror; //density * thickness [g*μm/cm^3]
	double Na=6.02214076*pow(10,23); //Avogadoro constant[/mol]
	double time=100; //mesurement time[s]
	double r=M_PI/180.; //degree to radian



	//vector<int> angle;
	vector<double> angle,CMangle,counts,I,Ierror,CS,CMCS,CSerror;



	cout << "Target(Au,C,H): ";
	cin >> target;

	if(target=="Au"){
		A=197;
		d_t=19.32*0.1611913031*pow(10,-4);
		d_terror=0.01;
	}else if(target=="C"){
		A=12;
		d_t=1.607005e-3*(12./14.); 
		d_terror=1.631240e-5;
	}else if(target=="H"){
		A=1;
		d_t=1.607005e-3*(2./14); 
   		d_terror=1.631240e-5;
	}else{
		cout << "Target name is wrong! → " << target << endl;
		return 0;
	}



	while(!ifs.eof()){
		double bufA,bufI,bufIE,bufC;
		ifs >> bufA >> bufI >> bufIE >> bufC;
		angle.push_back(bufA);
		I.push_back(bufI);
		Ierror.push_back(bufIE);
		counts.push_back(bufC);
	}
		
	/*
	cout << counts.size() << endl;
	for(int i=0;i<counts.size()-1;i++){
		cout << counts.at(i) << endl;
		CS.push_back(counts.at(i));
		cout << CS.at(i) << endl;
	}
	*/

	for(int i=0; i<angle.size(); i++){

		//lab to CM (bisection method)		
		double error=10e-20,CMmin=0,CMmax,CMmid;

		if(angle[i]>90){
    		CMmax=200;
    	}else if(angle[i]<90){
    		CMmax=350;
    	}else if(angle[i]==90){
			CMmid=(acos((-1.)/A))/r;
		}
    
    
    	while((CMmax-CMmin)*(CMmax-CMmin)>=error){

			if(angle[i]==90){
				break;
			}

    		CMmid = (CMmax+CMmin)/2;
    		double func = sin(r*CMmid)/(cos(r*CMmid)+(1./A)) - sin(r*angle[i])/cos(r*angle[i]);

 
    		if(func>0){
    			CMmax = CMmid;
    
    		}else if(func<0){
    			CMmin = CMmid;
    
    		}else if(func==0){
    			break;
    		}
    
		}
    
    	CMangle.push_back(CMmid);

    	if(CMangle[i]>185){
    		CMangle[i]=CMangle[i]-180;
    	}
    	
	cout << " angle(CM)[degree]: " << CMangle[i] << " ± 1e-20" << endl;


	if(angle[i]==140){
		//θ=140
		I[i] = I[i]*pow(10,-9);
		Ierror[i] = Ierror[i]*pow(10,-9);

		CS.push_back(counts[i]*e*A/dW140/I[i]/time/d_t/Na);
		CSerror.push_back(pow( pow(CS[i],2)/counts[i] + pow(CS[i],2)*pow(I[i],-2)*pow(Ierror[i],2) + pow(CS[i],2)*d_terror*d_terror/(d_t*d_t) ,0.5));


		//CMCS.push_back((1+cos(CMangle[i]*r)/A)/(pow(((2*(cos(CMangle[i]*r))/A)+1+(1/(A*A))) ,1.5))*CS[i]);

		}



		else{
		//θ≠140	

		I[i] = I[i]*pow(10,-9);
		Ierror[i] = Ierror[i]*pow(10,-9);

		CS.push_back(counts[i]*e*A/dW/I[i]/time/d_t/Na);
		CSerror.push_back(pow( pow(CS[i],2)/counts[i] + pow(CS[i],2)*pow(I[i],-2)*pow(Ierror[i],2) + pow(CS[i],2)*d_terror*d_terror/(d_t*d_t) ,0.5));


		//CMCS.push_back((1+cos(CMangle[i]*r)/A)/(pow(((2*(cos(CMangle[i]*r))/A)+1+(1/(A*A))) ,1.5))*CS[i]); 
		}



		//command line output
		cout <<  CMangle[i] << "\t"  << CS[i] << " ± " << CSerror[i] << " [cm^2/sr]\n"  << endl;



		//file output 
		ofs << CMangle[i] << " " << CS[i] << " "  << CSerror[i] << "\n";
	
	}

	return 0;
}

