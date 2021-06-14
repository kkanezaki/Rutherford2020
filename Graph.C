void Graph(){

	gROOT->SetStyle("ATLAS");

	TGraph* tg = new TGraph("nazo.txt");

	tg->SetMinimum(0);
	tg->GetXaxis()->SetLimits(0,2000);

	tg->Draw("AP");

	return 0;
}
