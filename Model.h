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


    public: unsigned int insert(string str);
    public: string ToString(unsigned int number);

    public: int expo(int a, int b);
    public: float convert(unsigned int n);

    bool sign(unsigned int number);
    unsigned int index(unsigned int number);
    unsigned int multiplier(unsigned int number);

    float add(unsigned int fpu1, unsigned int fpu2);
    float multiply(unsigned int fpu1, unsigned int fpu2);
    float subtract(unsigned int fpu1, unsigned int fpu2);
    float divide(unsigned int fpu1, unsigned int fpu2);


};


#endif //AK_PROJEKT_MODEL_H
