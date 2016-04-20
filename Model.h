//
// Created by manfredi on 19.04.16.
//

#ifndef AK_PROJEKT_MODEL_H
#define AK_PROJEKT_MODEL_H
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <limits>
#include <cstdlib>
using namespace std;


class Model {
    float number;
	unsigned int *int_number;

    public: Model();
    public: Model(float f);
	public: Model(unsigned int i);
    public: ~Model();

	float get_number();
	unsigned int* get_int_number();

    public: unsigned int insert(string str);
	public: string ToString(unsigned int number);

	bool sign();
	unsigned int index();
	unsigned int multiplier();

    public: int expo(int a, int b);
    public: float convert();

    Model* add(Model m);
    float multiply(unsigned int fpu1, unsigned int fpu2);
    float subtract(unsigned int fpu1, unsigned int fpu2);
    float divide(unsigned int fpu1, unsigned int fpu2);


};


#endif //AK_PROJEKT_MODEL_H
