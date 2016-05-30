#include <iostream>
#include "Model.h"
#include "Tests.h"

using namespace std;

int main() {

	//float* number;
	//number = reinterpret_cast<float*>(11588);

    float f, f2;
    Model *model3;

    int m;
    char sign0;
    do{
        cout << "MENU \n[1] - dodawanie \n[2] - odejmowanie \n[3] - mnozenie \n[4] - dzielenie";
        cin >> m;
        cout << endl;

        switch(m)
        {
            case 1: {
                cout << "Podaj pierwszy skladnik dodawania: ";
                cin >> f;
                Model model(f);
                cout << "Podaj drugi skladnik dodawania: ";
                cin>> f2;
                Model model2(f2);
                model3 = model.add(model2);
                cout << "Wynik dodawania " << f << " + " << f2 << " to " << *((*model3).get_number());
                break;
            }
            case 2: {
                cout << "Podaj odjemna: ";
                cin >> f;
                Model model(f);
                cout << "Podaj odjemnik: ";
                cin>> f2;
                Model model2(f2);
                model3 = model.subtract(model2);
                cout << "Wynik odejmowania " << f << " - " << f2 << " to " << *((*model3).get_number());
                break;
            }
			case 3: {
				cout << "Podaj pierwszy skladnik mnozenia: ";
				cin >> f;
				Model model(f);
				cout << "Podaj drugi skladnik mnozenia: ";
				cin >> f2;
				Model model2(f2);
				model3 = model.multiply(model2);
				cout << "Wynik mnozenia " << f << " * " << f2 << " to " << *((*model3).get_number());
				break;
			}
			case 4: {
				cout << "Podaj dzielna: ";
				cin >> f;
				Model model(f);
				cout << "Podaj dzielnik: ";
				cin >> f2;
				Model model2(f2);
				model3 = model.divide(model2);
				cout << "Wynik dzielenia " << f << " / " << f2 << " to " << *((*model3).get_number());
				break;
			}
            default:break;

        }
        cout << endl << "Czy chcesz zakonczyc program(t/n)?"; cin>>sign0;
        cout << endl;
    }while(sign0 !='t');
    return 0;
}
