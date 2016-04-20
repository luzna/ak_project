#include <iostream>
#include "Model.h"
#include "Tests.h"

using namespace std;

int main() {

	float f = 1.125;
	float f2 = 4.5;
	Model model(f);
	Model model2(f2);
	Model *model3 = model.add(model2);
	cout << (*model3).get_number();
	cin.get();

    return 0;
}