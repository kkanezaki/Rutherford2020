#include<cmath>
#include<iostream>
#include<fstream>


using namespace std;

int main(){
	double Z=8/3; //Atomic Number of PE
	double A=14/3; //Mass Number of PE
	double E,p,v,I,Is;
	double E1,E2,dE1,dE2,X,x;
	double m=1.67*pow(10,-27);
	double e=1.6*pow(10,-19);
	double c=2.99792458*pow(10,8);


	cout << "E[MeV] = ";
	cin >> E;
	cout << "p(density)[g/cm^3] = ";
	cin >> p;
	cout << "x[um] = ";
	cin >> x;

	double IN=E;

	I=65*pow(10,-6);

	for(int i=1;i<1000000;i++){
		v=pow(E*pow(10,6)*e*2/m,0.5)/c;
		E1=0.307075*p*Z/(A*v*v)*(log(1.022*v*v/(I*(1-v*v)))-v*v);
		dE1=E1*pow(10,-6);

		E=E-dE1;

		X=0.01*i; //(um)

		cout << E1 << endl;

		if(X>x){
			break;}
	}
	//cout << R << endl;
	cout << E << "MeV" << "\t" << X << "μm" << endl;
	cout << IN-E;
	return 0;
}
