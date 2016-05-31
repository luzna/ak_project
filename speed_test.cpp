#include <time.h>
#include "Model.h"
#include <iostream>
using namespace std;

int main()
{

	float f = 10;
	float f2 = 2;
	Model model(f); 
	Model model2(f2);
	Model *model3;
	double time;

	double t[100];

	clock_t start, end;

	for(int i=0; i<100; i++){
		
		/*
		cout.setf(ios::fixed);
		cout << "Czas: "
		<< setprecision(5) << ((double)(end-start)/CLOCKS_PER_SEC)*1000
		<< " milisekund." << "\n\n";*/

		start = clock();
			
			//model3 = model.divide(model2);
			float d = f / f2;

		end = clock();



		time = ((double)(end-start)/CLOCKS_PER_SEC)*1000;
		t[i] = time;

	}
	
	double sum = 0;
	for( int i=0; i<100; i++){
		sum += t[i];
	
	}
	cout << endl << "Srednia: " << sum/100 << endl;
	


	return 0;
} 
