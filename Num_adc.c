void Num_adc(){

  const int event_num = 15;
  const double Min = 10;
  const double Max = 19;
  int i = 0;
  int j = 0;
  int k = 0;
  double data[event_num];


  ifstream ifs("data.txt");
  while(!ifs.eof()){
	ifs >> data[i];
	i++;
  }
  
  for (int j=0; j < event_num; j++){

 	if ( Min <= data[j] && data[j]<= Max){
	  k++;
	}
 
  			
  }

  cout << "ADCValue " << Min << " ~ " << Max << " Number: " << k << endl;

  return 0;
}
