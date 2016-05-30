//
// Created by manfredi on 19.04.16.
//


#include "Model.h"

Model::Model(float f) {
	number = new float();
    *(number) = f;
    int_number = reinterpret_cast<unsigned int*>(number);
}

Model::Model(unsigned int i)
{
	int_number = new unsigned int();
	*(int_number) = i;
	number = reinterpret_cast<float*>(int_number);
}

float* Model::get_number()
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

		if (i == 31 || i == 23)
		{
			index += " ";
		}
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

	if (i == 0 && m == 0)
	{
		f = 0;
	}
	else
	{
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
	}

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

	if (sign1 == sign2)
	{
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
	}
	//jeśli składniki mają różne znaki - odejmowanie
	else if (sign2)
	{
		unsigned int i = *m.get_int_number() & 0x7fffffff;
		Model m2(i);
		return subtract(m2);
	}
	else
	{
		unsigned int i = *m.get_int_number() | 0x80000000;
		Model m2(i);
		return subtract(m2);
	}

    unsigned int add_mpr = mpr1 + mpr2;

	//normalizacja wyniku, jeśli większy od dwóch
	if (dif == 0)
	{
		add_mpr = add_mpr >> 1;
		higher_idx++;
	}
	else if ((add_mpr & 0x00800000) == 0x00800000)
	{
		add_mpr &= 0x007fffff;
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

//odejmowanie
Model* Model::subtract(Model m) {

	unsigned int idx1 = index();
	unsigned int idx2 = m.index();
	unsigned int higher_idx;
	int dif = 0;

	unsigned int higher_mpr;
	unsigned int lower_mpr;
	unsigned int mpr1 = multiplier();
	unsigned int mpr2 = m.multiplier();

	bool sign1 = sign();
	bool sign2 = m.sign();
	bool sign; //znak wyniku
	unsigned int mask;

	if (sign1 == sign2)
	{
		if (idx1 > idx2)
		{
			higher_idx = idx1;
			dif = higher_idx - idx2;
			sign = sign1; //jeśli pierwsza liczba jest większa znak wyniku taki sam jak składników

			//denormalizacja
			mpr2 = mpr2 >> dif;
			mask = expo(2, 23 - dif); //jedynka przed przecinkiem
			mpr2 |= mask;

			higher_mpr = mpr1;
			lower_mpr = mpr2;
		}
		else if (idx2 > idx1)
		{
			higher_idx = idx2;
			dif = higher_idx - idx1;
			sign = !sign1; //jeśli pierwsza liczba jest większa znak wyniku przeciwny do znaku składników

			//denormalizacja
			mpr1 = mpr1 >> dif;
			mask = expo(2, 23 - dif); //jedynka przed przecinkiem
			mpr1 |= mask;

			higher_mpr = mpr2;
			lower_mpr = mpr1;
		}
		else
		{
			higher_idx = idx2;
			dif = higher_idx - idx1;
			
			if (mpr1 > mpr2)
			{
				higher_mpr = mpr1;
				lower_mpr = mpr2;
				sign = sign1; //jeśli pierwsza liczba jest większa znak wyniku taki sam jak składników
			}
			else
			{
				higher_mpr = mpr2;
				lower_mpr = mpr1;
				sign = !sign1; //jeśli pierwsza liczba jest większa znak wyniku przeciwny do znaku składników
			}
		}
	}
	//jeśli składniki mają różne znaki - dodawanie 
	else if (sign2)
	{
		unsigned int i = *m.get_int_number() & 0x7fffffff;
		Model m2(i);
		return add(m2);
	}
	else
	{
		unsigned int i = *m.get_int_number() | 0x80000000;
		Model m2(i);
		return add(m2);
	}

	unsigned int sub_mpr = higher_mpr - lower_mpr;

	//normalizacja wyniku, jeśli mniejszy od 1
	if ((dif == 0 || ((sub_mpr & 0x00800000) == 0x00800000)) && sub_mpr > 0)
	{
		mask = 0x00400000;
		unsigned bit = 0;
		while (bit != mask)
		{
			bit = sub_mpr & mask;
			sub_mpr = sub_mpr << 1;
			higher_idx--;
		}
	}
	else if ((dif == 0 || ((sub_mpr & 0x00800000) == 0x00800000)) && sub_mpr == 0)
	{
		higher_idx = 0;
	}

	unsigned int value = 0;

	if (sign)
		value |= 0x80000000;

	value |= higher_idx << 23;

	sub_mpr &= 0x007fffff; //maskowanie bitów mnożnika powyżej 23
	value |= sub_mpr;

	Model *result = new Model(value);

	return result;
}

Model* Model::multiply(Model m) {

	unsigned int idx1 = index();
	unsigned int idx2 = m.index();
	unsigned int idx = idx1 + idx2 - 127;

	unsigned int mpr1 = multiplier();
	unsigned int mpr2 = m.multiplier();
	unsigned int mpr;

	bool sign1 = sign();
	bool sign2 = m.sign();

	bool sign;
	unsigned int value = 0;

	mpr1 |= 0x00800000; //jedynki przed przecinkiem
	mpr2 |= 0x00800000;
	mpr = (mpr1>>11) * (mpr2>>11); //wynik ma mieć maksymalnie 24 bity
	mpr = mpr >> 1;

	//normalizacja
	if ((mpr & 0x01000000) == 0x01000000)
	{
		mpr = mpr >> 1;
		idx++;
	}

	if (sign1 == sign2)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}

	if (sign)
		value |= 0x80000000;

	value |= idx << 23;
	mpr &= 0x007fffff;
	value |= mpr;

	Model *result = new Model(value);

	return result;
}

Model* Model::divide(Model m)
{
	/*cout << ToString(*int_number) << endl;
	cout << ToString(*m.int_number) << endl;*/

	unsigned int idx1 = index();
	unsigned int idx2 = m.index();
	unsigned int idx = idx1 - idx2 + 127;

	/*cout << endl;
	cout << ToString(idx1 << 23) << endl;
	cout << ToString(idx2 << 23) << endl;
	cout << ToString(idx << 23) << endl;*/

	unsigned int mpr1 = multiplier();
	unsigned int mpr2 = m.multiplier();
	unsigned int mpr;

	bool sign1 = sign();
	bool sign2 = m.sign();

	bool sign;
	unsigned int value = 0;
	unsigned int mask;

	mpr1 |= 0x00800000; //jedynki przed przecinkiem
	mpr2 |= 0x00800000;

	/*cout << endl;
	cout << ToString(mpr1) << endl;
	cout << ToString(mpr2) << endl;*/

	mask = 1;
	int count = 0;
	unsigned bit = mpr2 & mask;
	while (bit != mask)
	{
		bit = mpr2 & mask;

		if (bit != mask)
		{
			mpr2 = mpr2 >> 1;
			count++;
		}
	}

	mpr = mpr1 / mpr2;
	idx += (23 - count);

	/*cout << endl;
	cout << ToString(mpr1) << endl;
	cout << ToString(mpr2) << endl;
	cout << ToString(mpr) << endl;*/

	//normalizacja
	if ((mpr & 0x00800000) != 0x00800000)
	{
		mask = 0x00400000;
		unsigned bit = 0;
		while (bit != mask)
		{
			bit = mpr & mask;
			mpr = mpr << 1;
			idx--;
		}
	}

	//cout << ToString(mpr) << endl;

	if (sign1 == sign2)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}

	if (sign)
		value |= 0x80000000;

	value |= idx << 23;
	mpr &= 0x007fffff;
	value |= mpr;

	/*cout << endl;
	cout << ToString(value) << endl;*/

	Model *result = new Model(value);

	return result;
}

Model::Model() {

}

Model::~Model() {

}























