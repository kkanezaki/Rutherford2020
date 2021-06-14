void nazo(){

	double z; //atomic number
	double A; //mass number
	double c=3*pow(10,8); //[m/s]
	double E;
	double mp=1.67*pow(10,-27);//[kg]
	const double e=1.6*pow(10,-19); //[C]
	double betap; //=pow(E*pow(10,6)*e*2/mp,0.5)/c;
	double beta; //=pow(E*pow(10,6)*e*2/(z*mp),0.5)/c;
	double I=16*pow(14,0.9)*pow(10,-6); //[MeV] 
	double bete,betep; //part of dE/dx
	const double me=0.511; //[MeV/c^2]

	
	cout << "energy[MeV] ";
	cin >> E; 		
	
	cout << "Z ";
	cin >> z;

	cout << "A ";
	cin >> A;

	betap=pow(E*pow(10,6)*e*2/mp,0.5)/c;
	beta=pow(E*pow(10,6)*e*2/(A*mp),0.5)/c;

	betep=(1/(betap*betap))*(log(2*me*betap*betap/(I*(1-betap*betap)))-betap*betap);
	bete=(z*z/(beta*beta))*(log(2*me*beta*beta/(I*(1-beta*beta)))-beta*beta);

	cout << betap << "\t" << beta << endl;

	cout << betep << "\t" << bete << endl;
	
}
