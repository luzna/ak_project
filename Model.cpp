//
// Created by manfredi on 19.04.16.
//


#include "Model.h"

Model::Model(float f) {
    this->number = f;
    this->int_number = reinterpret_cast<unsigned int*>(&number);
}

Model::Model(unsigned int i)
{
	int_number = new unsigned int();
	*(this->int_number) = i;
	this->number = convert();
}

float Model::get_number()
{
	return number;
}

unsigned int* Model::get_int_number()
{
	return int_number;
}

//wpisany ciąg zer i jedynek przekształca w int
unsigned int Model::insert(string str) {
    unsigned int value = bitset<numeric_limits<unsigned int>::digits>(str).to_ulong();
    return value;
}

//w celach testowania poprawnośći wyniku
//wyświetla inta jako string
string Model::ToString(unsigned int number) {
    unsigned int mask;
    string index;
    unsigned int pos;

    for (int i = 31; i >= 0; i--)
    {
        mask = expo(2, i);
        pos = number&mask;

        if (pos)
            index += "1";
        else
            index += "0";
    }

    return index;
}

//potegowanie a^b na intach
int Model::expo(int a, int b) {
    int sum = a;
    if (b == 0)
        return 1;
    for (int i = 1; i<b; i++)
        sum = sum*a;

    return sum;
}

bool Model::sign() {
	unsigned int mask = expo(2, 31);
	bool sign;
	sign = *int_number&mask;
	if (sign)
		sign = 1;
	else sign = 0;

	return sign;
}

unsigned int Model::index() {
	unsigned int mask;
	unsigned int index = 0;
	unsigned int pos;

	for (int i = 30; i >= 23; i--)
	{
		mask = pow(2.0, i);
		pos = *int_number&mask;

		if (pos)
			index |= pos;
	}

	index = index >> 23;
	return index;
}

unsigned int Model::multiplier() {
	unsigned int mask;
	unsigned int mpr = 0;
	unsigned int pos;

	for (int i = 22; i >= 0; i--)
	{
		mask = expo(2, i);
		pos = *int_number&mask;

		if (pos)
			mpr |= pos;
	}
	return mpr;
}

//obliczanie wartości liczby
float Model::convert() {

	float f;
	bool s = sign();
	int i = (int)index();
	unsigned int m = multiplier();

	if (s)
		f = -1;
	else
		f = 1;

	f *= pow(2, i - 127);

	float total = 0;
	int power = -23;
	for (int i = 0; i < 23; i++)
	{
		unsigned int x = m >> i;
		total += (float)(x & 1) * (float)pow(2.0, power);
		power++;
	}
	total += 1;
	f *= total;

	return f;
}

//dodawanie
Model* Model::add(Model m) {

    unsigned int idx1 = index();
    unsigned int idx2 = m.index();
    unsigned int higher_idx;
    int dif = 0;
    unsigned int mpr1 = multiplier();
    unsigned int mpr2 = m.multiplier();
    bool sign1 = sign();
    bool sign2 = m.sign();
	unsigned int mask;

    if (idx1 > idx2)
    {
        higher_idx = idx1;
        dif = higher_idx - idx2;
		
		//denormalizacja
        mpr2 = mpr2 >> dif;
		mask = expo(2, 23 - dif); //jedynka przed przecinkiem
		mpr2 |= mask;
    }
	else if (idx2 > idx1)
    {
        higher_idx = idx2;
        dif = higher_idx - idx1;

		//denormalizacja
        mpr1 = mpr1 >> dif;
		mask = expo(2, 23 - dif); //jedynka przed przecinkiem
		mpr1 |= mask;
    }
	else
	{
		higher_idx = idx2;
		dif = higher_idx - idx1;
	}

    unsigned int add_mpr = mpr1 + mpr2;

	//normalizacja wyniku, jeśli większy od dwóch
	if (dif == 0)
	{
		add_mpr = add_mpr >> 1;
		higher_idx++;
	}

	unsigned int value = 0;

	if (sign1 && sign2)
		value |= 0x80000000;

	value |= higher_idx << 23;
	value |= add_mpr;
    
	Model *result = new Model(value);

    return result;
}

Model::Model() {

}

Model::~Model() {

}









/*float Model::multiply(unsigned int fpu1, unsigned int fpu2) {
    unsigned int idx1 = index(fpu1);
    unsigned int idx2 = index(fpu2);
    unsigned int idx = idx1 + idx2 - 127;

    unsigned int mpr1 = multiplier(fpu1);
    unsigned int mpr2 = multiplier(fpu2);
    unsigned int mpr = mpr1*mpr2;
    mpr = mpr >> 1;

    //cout << ToString(idx1) << endl << ToString(idx2) << endl << ToString(idx) << endl;
    unsigned int sign_a;
    if ((sign(fpu1) && sign(fpu2)) || (!sign(fpu1) && !sign(fpu2)))
        sign_a = 0;
    else sign_a = 1;
    float value = conv(sign_a, idx, mpr);

    //if ((sign(fpu1) && sign(fpu2)) || (!sign(fpu1) && !sign(fpu2)))
    //	value *= -1;

    return value;
}*/























