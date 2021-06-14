#include<cmath>
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>


using namespace std;

int main(){
	std::string target;
	double ZH=1; //Atomic Number
	double ZC=6; //C Atomic Number
	double AC=12; //C Mass Number
	double ZAu=79; //Au Atomic Number
	double AAu=197; //Au Mass Number
	double R1=ZH/(ZH+AC);
	double R2=AC/(ZH+AC);
	double Ih=0.0000136; //MeV
	double E,p,v,I;
	double rad_d,rad_t;
	double E1,E2,dE1,dE2,X,x;
	double m=1.67*pow(10,-27);
	double e=1.6*pow(10,-19);
	double c=3*pow(10,8);

	/*cout << "Z = ";
	cin >> Z;
	cout << "A = ";
	cin >> A;*/

	cout << "Target (Au or PE) =";
	cin >> target;
	cout << "E[MeV] = ";
	cin >> E;
	cout << "p(density)[g/cm^3] = ";
	cin >> p;
	cout << "x[μm] = ";
	cin >> x;
	cout << "detector degree[°] = ";
	cin >> rad_d;
	cout << "target degree[°] = ";
	cin >> rad_t;

	rad_d = M_PI*rad_d/180;
	rad_t = M_PI*rad_t/180;

	//x=0で散乱(透過型)
	x = x/(cos(rad_t - rad_d));

	//x=x/2で散乱(透過型)
	//x = (x/(2*cos(rad_t)))+ (x/(2*cos(rad_t - rad_d)));

	//x=xで散乱(透過型)
	//x = x/cos(rad_t);

	//x=0で散乱(反射型)
	//x=0;

	//x=x/2で散乱(反射型)
	//x = (x/(2*cos(rad_d - rad_t))) - (x/(2*cos(rad_t)));

	//x=xで散乱(反射型)
	//x = (x/(cos(rad_d - rad_t)))  - (x/(cos(rad_t)));

	double IN=E;

	I=16*pow(ZC,0.9)*pow(10,-6);

	for(int i=1;i<1000000;i++){
		v=pow(E*pow(10,6)*e*2/m,0.5)/c;
		E1=R1*0.307075*p*ZH/(ZH*v*v)*(log(1.022*v*v/(I*(1-v*v)))-v*v);
		E2=R2*0.307075*p*ZC/(AC*v*v)*(log(1.022*v*v/(I*(1-v*v)))-v*v);
		dE1=E1*pow(10,-6);
		dE2=E2*pow(10,-6);

		E=E-dE1-dE2;

		X=0.01*i; //(um)

		cout << E1 << endl;

		if(X>x){
			break;}
	}
	
	cout << E << "MeV" << "\t" << X << "μm" << endl;
	cout << IN-E;
	return 0;
}
