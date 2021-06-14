#include <math.h>
using namespace std;

	TString filename;
	TString target;
	double Z; //Atomic Number
	double A; //Mass Number
	double e = 1.60217662*pow(10,-19); //Elementary Charge[C]
	double E = 3*pow(10,6)*e; //Proton Energy[J]
	double ep0 = 8.8541878128*pow(10,-12); //Permittivity of vacuum[s^4*A^2/m^3*kg]
	double r = M_PI/180.; //degree to radian
	double arpha = 7.2973525693*pow(10,-3); //fine-structure constant
	double mp1 = 938.2720817*pow(10,6); //proton mass[eV/c^2]
	double mp2 = 1.6726219*pow(10,-27); //proton mass[kg]
	double v = pow((2*E/mp2),0.5); //3MeV proton velocity[m/s]
	double h = 6.62607015*pow(10,-34)/(2*M_PI); //Dirac's constant[J/s] 
	double nr; //nuclear radius
	double nf; //nuclear force 

	//graph parameter
	double Xmin=0, Xmax=180;
	double Ymin, Ymax;
	TString funcname,funcname2;
	TString fitfuncname;

	double CS(double x){
		double y;
		y = pow(10,4)*(pow(((Z*e*e)/(16*M_PI*ep0*E)),2))/(pow((sin(r*x/2)),4)); //cm^2/sr
		return y;
	}

	double Mott(double x){
	double y;
		y =  pow(10,4)*(pow(((e*e)/(16*M_PI*ep0*E)),2))/(pow((sin(r*x/2)),4))
		  + pow(10,4)*(pow(((e*e)/(16*M_PI*ep0*E)),2))/(pow((cos(r*x/2)),4));
		  - pow(10,4)*(pow(((e*e)/(16*M_PI*ep0*E)),2))*cos(e*e*log(pow(tan(r*x/2),2))/(4*M_PI*ep0*h*v))/pow((cos(r*x/2)*sin(r*x/2)),2); //cm^2/sr
		return y;
	}


	double NF(double x){
		double y;
		y = (pow(nr,2))*(pow(10,-26))/4; //cm^2/sr
		return y;
	}

	
void Cross(){
	
	double p0,p1,Er0,Er1;

	for(int i=0;i<1000000;i++){

		cout << "\nTarget(H,C,Au) = ";
		cin >> target;

		if(target=="H"){
			Z=1;
			A=1;
			nr=0.87; //fm
			funcname="Mott(x)"; //H核力なし理論値
			funcname2="Mott(x)+NF(x)"; //H核力あり理論値
			//fitfuncname="[0]*Mott(x)"; //H核力なしFitting
			fitfuncname="[0]*Mott(x)+[1]"; //H核力ありFitting
			Ymin=5e-28;
			Ymax=1e-20;
			break;  

		}else if(target=="C"){
			Z=6;
			A=12;
			nr=1.3*pow(A,(1./3.)); //fm
			funcname="CS(x)"; //C核力なし理論値
			funcname2="CS(x)+NF(x)"; //C核力あり理論値
			//fitfuncname="[0]*CS(x)"; //C核力なしFitting  
			fitfuncname="[0]*CS(x)+[1]"; //C核力ありFitting
			//fitfuncname="[0]*(CS(x)+NF(x))";
			Ymin=1e-27;
			Ymax=1e-22;
			break;

		 }else if(target=="Au"){
			Z=79;
			A=197; 
			nr=1.3*pow(A,(1./3.)); //fm
			funcname="CS(x)"; //Au核力なし理論値
			funcname2="CS(x)+NF(x)"; //Au核力あり理論値
			fitfuncname="[0]*CS(x)"; //Au核力なしFitting
			//fitfuncname="[0]*CS(x)+[1]"; //Au核力ありFitting
			Ymin=5e-25;
			Ymax=1e-20;
			break;

		}else{
			cout << "Target name is wrong! Your input → " << target << endl; 
			continue;
		}

	}

	cout << "Input filename = ";
	cin >> filename;              
	cout << "\n";
	



	gROOT->SetStyle("ATLAS");

	//Experimental Value
	TGraphErrors* tg = new TGraphErrors(filename, "%lg %lg %lg");
	tg->SetTitle("Differencial Cross Section vs θ_{CM}");
	tg->GetXaxis()->SetTitle("Scattering Angle [degree]");
	tg->GetYaxis()->SetTitle("Differencial Cross Section [cm^{2}/sr]");
	tg->SetMinimum(Ymin);
	tg->SetMaximum(Ymax);
	tg->GetXaxis()->SetLimits(Xmin, Xmax);
	tg->SetMarkerSize(0.7);
	tg->Draw("APE1");




	//Theoretical Value
	
	//核力なし
	
	TF1* func = new TF1("func", funcname, 0, 180);
	func->SetLineColor(kOrange+7);
	func->Draw("same");
	

	//核力あり
	
	TF1* func2 = new TF1("func2", funcname2, 0, 180); 
	func2->SetLineColor(kMagenta);
	if(target!="Au"){
	func2->Draw("same");
	}

	//核力のみ
	
	TF1* func3 = new TF1("func3", "NF(x)", 0, 180);
	func3->SetLineColor(kGreen-3);
	if(target!="Au"){
	func3->Draw("same");
	}

	//Fitting
	const double FitMin = 0;
	const double FitMax = 180;
	
	TF1* fitfunc = new TF1("fitfunc", fitfuncname, 0, 180); 
	fitfunc->SetParName(0,"p0");
	fitfunc->SetParName(1,"R^2/(4*p0)");
	fitfunc->SetParameter(0,1);
	tg->Fit("fitfunc", "", "", FitMin, FitMax);
	fitfunc->SetLineColor(kAzure+7);
	fitfunc->Draw("same");

	p0=fitfunc->GetParameter(0);
	p1=fitfunc->GetParameter(1);
	Er0=fitfunc->GetParError(0);
	Er1=fitfunc->GetParError(1);

	cout <<  "\np0: " << p0 << " ± " << Er0 << endl;
	if(fitfuncname=="[0]*CS(x)+[1]" || fitfuncname=="[0]*Mott(x)+[1]"){
	  cout << "R^2/4: " << Er1/Er0 << " ± " 
	  	 << pow( (pow((Er1/p0),2) + pow((Er0*p1/(p0*p0)),2) ) ,0.5) << "[cm^2]"<< endl;
	}
	cout << "Chi2/NDF: " << (fitfunc->GetChisquare())/(fitfunc->GetNDF()) << "\n" << endl;




	//TLegend
	TLegend* leg = new TLegend(0.62, 0.78, 0.92, 0.9);
	leg->AddEntry(tg, "Experimental Value", "p");
	leg->AddEntry(fitfunc, "Fitting Curve", "l");
	leg->AddEntry(func, "Theoretical Value", "l");
	if(target!="Au"){
	leg->AddEntry(func2, "Theoretical Value with Nuclear Force", "l");
	leg->AddEntry(func3, "Nuclear Force", "l");
	}
	leg->SetBorderSize(0);
	leg->Draw();

	gPad->SetLogy();

	//統計BOX
	/*gStyle->SetOptFit(0101);
	gStyle->SetStatX(1);
	gStyle->SetStatY(1);
	*/

	return 0;

}
