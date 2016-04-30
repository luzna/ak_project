#include <iostream>
#include "Model.h"
#include "Tests.h"

using namespace std;

int main() {

	float f = 4;
	float f2 = 2;
	Model model(f);
	Model model2(f2);
	Model *model3 = model.subtract(model2);
	cout << (*model3).get_number();
	cin.get();

    return 0;
}