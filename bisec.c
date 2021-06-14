void bisec(){

	double anglelab, anglecm;
	double error=1e-20;
	double CMmax, CMmin=0, CMmid;
	double A;
	double r=M_PI/180.;

	cout << "angle(lab): ";
	cin >> anglelab;

	cout << "Mass Number: ";
	cin >> A;

	if(anglelab>90){
		CMmax=200;
	}else if(anglelab<90){
		CMmax=350;
	}

	//cout << "\nCMangle" << "\t" << "func" << endl;


	while((CMmax-CMmin)*(CMmax-CMmin)>=error){

		CMmid = (CMmax+CMmin)/2;
		double func = sin(r*CMmid)/(cos(r*CMmid)+(1./A)) - sin(r*anglelab)/cos(r*anglelab);

		//cout << CMmid << "\t" << func <<endl;

		if(func>0){
			CMmax = CMmid;

		}else if(func<0){
			CMmin = CMmid;

		}else if(func==0){
			break;
		}

	}

	anglecm=CMmid;
	if(anglecm>185){
		anglecm=anglecm-180;
	}
	cout << "Estimated CMangle: " << anglecm << "±1e-20" << endl;

	return 0;
}
	
