#include <iostream>
#include "Model.h"
#include "Tests.h"

using namespace std;

int main() {
    Model model;
    unsigned int nr = model.insert("00111110000000000000000000000000");		//0.125
    unsigned int nr2 = model.insert("01000001011100000000000000000000");


    cout << model.convert(nr) << endl;
    cout << model.convert(nr2) << endl;
    //cout << model.add(nr, nr2);

    float f = 0.125;
    unsigned int *number = reinterpret_cast<unsigned int*>(&f);
    cout << model.ToString(*number);

    return 0;
}