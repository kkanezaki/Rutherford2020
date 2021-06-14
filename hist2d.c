void hist2d(){

	gROOT->SetStyle("ATLAS");

	//const int event_num = 10000;

	//int i = 0;
	//int j = 0;
	//double x[event_num], y[event_num];
	//double Energy_x[event_num], Energy_y[event_num];

	vector<double> x,y;
	vector<double> Energy_x,Energy_y;

	double BV,BV2;	

	ifstream yoko("ch1.txt");
	while(yoko >> BV){
		x.push_back(BV);
	}
	yoko.close();

	ifstream tate("ch2.txt");
	while(tate >> BV2){
		y.push_back(BV2);
	}
	tate.close();

	TH2D* hist = new TH2D("hist","hist",50,0,2000,50,0,2000);
	hist->SetTitle(";PHADCValue_CH1;PHADCValue_CH2");
	//hist->SetTitle(";Energy_CH1 [keV];Energy_CH2 [keV]");

	//To_Calibration
	for(int i = 0; i < x.size(); i++){
		//Energy_x.push_back(x.at(i)/0.6897 + 60.46/0.6897);
		//Energy_y.push_back(y.at(i)/0.4807 - 397.53/0.4807);
		hist->Fill(x.at(i),y.at(i));
		//hist->Fill(Energy_x.at(i),Energy_y.at(i));
	}

    gStyle->SetPadRightMargin(0.15);
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadTopMargin(0.14);
    gStyle->SetPadBottomMargin(0.14);

	hist->Draw("colz");
	const Int_t NRGBs = 5;
	const Int_t NCont = 255;
	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 }; 
	Double_t Red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
	Double_t Green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
	Double_t Blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };

	TColor::CreateGradientColorTable(NRGBs, stops, Red, Green, Blue, NCont);
	gStyle->SetNumberContours(NCont);
	

	return 0;
}
