#include<vector>

double threshold(double x){
	double y = 100.; //Discriminator threshold(estimated)[mV]
	return y;
}


void THarea(){

	vector<double> x60,x70;
	vector<double> y60,y70;

	TString filename = "volt1.txt";

	gROOT->SetStyle("ATLAS");

	TGraphErrors* tg = new TGraphErrors(filename, "%lg %lg %lg %lg"); //ADCvalue
	//TGraphErrors* tg = new TGraphErrors(filename, "%*lg %lg %lg %*lg %lg %lg"); //energy
	tg->SetTitle(";PHADC_Value;Input Voltage [mV]");
	//tg->SetTitle(";Energy[keV];Voltage[mV]");
	tg->SetMinimum(0);
	tg->SetMaximum(500);	
	tg->GetXaxis()->SetLimits(0, 1500);
	tg->SetMarkerSize(1);
	tg->Draw("AP");
	

	TF1* fitfunc = new TF1("fitfunc", "pol1", 0, 10000);
	fitfunc->SetParameter(0, -50);
	fitfunc->SetParameter(1, 0.3);
	tg->Fit("fitfunc", "", "", 0, 10000);
	fitfunc->SetLineColor(kAzure+1);
	fitfunc->Draw("same");


	TF1* threshold = new TF1("threshold", "threshold(x)", 0, 3000);
	threshold->SetLineColor(kOrange+7);	
	threshold->SetFillStyle(3002);	
	threshold->SetFillColor(kOrange+7);
	threshold->Draw("sameL");


	for(int i=0;i<=10;i++){
		x60.push_back(435.6);
		y60.push_back(i*300);
	}
	TGraph* tv60 = new TGraph(10, x60.data(), y60.data());
	tv60->SetLineColor(kSpring-8);
	tv60->SetLineWidth(3);
	tv60->Draw("Lsame");

	for(int j=0;j<=10;j++){
		x70.push_back(160.1); 
		y70.push_back(300*j);
	}
	TGraph* tv70 = new TGraph(x70.size(), x70.data(), y70.data());
	tv70->SetLineColor(kViolet-3);
	tv70->SetLineWidth(3);
	tv70->Draw("same");
		
	
	TLegend* leg = new TLegend(0.6,0.85,0.92,0.9);
	leg->AddEntry(fitfunc,"Voltage vs PHADC_Value","l");
	leg->AddEntry(threshold,"Estimated Threshold","l");
	leg->AddEntry(tv60,"Theoretical Value at 60#circ","l");
	leg->AddEntry(tv70,"Theoretical Value at 70#circ","l");
	leg->SetBorderSize(0);
	leg->Draw();

	return 0;
}
