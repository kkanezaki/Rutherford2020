#include <iostream>
#include <string>

using namespace std;

void logger() {
  int n=22316;	
  int j=0;
  string s,s2;
  string filename="target_091513_102214.txt";
  double c[n];
  double d[n];
  double sum=0, ave, sigma, sigma2=0;
  double dial, up, low;
  double index_min,index_width=6;
  TString runname;

  cout << "run name: ";
  cin >> runname;

  cout << "current dial[nA]: ";
  cin >> dial;

  cout << "upper line number: ";
  cin >> up;

  cout << "lower line number: ";
  cin >> low;

  ifstream ifs(filename);
  ifstream ifs2(filename);
  ofstream ofs(runname+".txt");
 
  cout << "\nnumber" << "\t" << "year/month/day/time" << "\t" << "current[nA]" << endl;
 
  //to caliculate average
  for(int i=0;i<n;i++){
 
		  if(i<=6315){
			index_min = 67;
		  }else{
			index_min = 64;
		  }

 
		  if (getline(ifs, s)) {
			  if (up<=i+1 && i<=low-1){
  
				string a=s.substr(1,19);
				string b=s.substr(index_min,index_width);


				c[i]=stod(b);
				d[i]=c[i]*dial;

				j++;
				sum=sum+d[i];
				

				cout << j << "\t" << a << "\t" << d[i] << endl;
				ofs << a << "\t" << d[i] << endl;


			  }
		  }

	    }


	ave=sum/j;
	cout << "\naverage current = " << ave << "[nA]" << endl;	
	

  //to caliculate error(σ)
  for(int i=0;i<n;i++){

		  if(i<=6315){
			index_min = 67;
		  }else{
			index_min = 64;
		  }

 
		  if (getline(ifs2, s2)) {
			  if (up<=i+1 && i+1<=low){
				string a=s2.substr(1,19);
				string b=s2.substr(index_min,index_width);

				c[i]=stod(b);
				d[i]=c[i]*dial;
				sigma2+=pow((d[i]-ave),2)/j;


			  }
		  }

	    }

	sigma=sqrt(sigma2);

	cout << "standard error of current = " << sigma << "[nA]\n" << endl; 

	return 0;

}
