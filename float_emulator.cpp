
#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <limits>
#include <cstdlib>
using namespace std;

int expo(int a, int b)		//potegowanie a^b
{
	int i;
	int sum = a;
	if (b == 0)
		return 1;
	for (i = 1; i<b; i++)
		sum = sum*a;

	return sum;
}

float convert(unsigned int n)
{
	int x = n >> 31;
	int y = x & 1;
	float f = expo(-1, y);
	x = n >> 23;
	y = x & 0xff;
	f *= pow(2, y - 127);
	float total = 0;
	int power = -23;
	for (int i = 0; i < 23; i++)
	{
		x = n << i;
		total += (float)(x & 1) * (float)pow(2.0, power);
		power++;
	}
	total += 1;
	f *= total;
	return f;
}

unsigned int insert(string str)
{
	unsigned int value = bitset<numeric_limits<unsigned int>::digits>(str).to_ulong();
	return value;
}

string ToString(unsigned int number)  //funkcja do testów
{
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



bool sign(unsigned int number)
{
	unsigned int mask = expo(2, 31);
	bool sign;
	sign = number&mask;
	if (sign)
		sign = 1;
	else sign = 0;

	return sign;
}

unsigned int index(unsigned int number)
{
	unsigned int mask;
	unsigned int index = 0;
	unsigned int pos;

	for (int i = 30; i >= 23; i--)
	{
		mask = pow(2.0, i);
		pos = number&mask;

		if (pos)
			index |= pos;
	}

	index = index >> 23;
	return index;
}

unsigned int multiplier(unsigned int number)
{
	unsigned int mask;
	unsigned int mpr = 0;
	unsigned int pos;

	for (int i = 22; i >= 0; i--)
	{
		mask = expo(2, i);
		pos = number&mask;

		if (pos)
			mpr |= pos;
	}
	return mpr;
}

float add(unsigned int fpu1, unsigned int fpu2)
{
	unsigned int idx1 = index(fpu1);
	unsigned int idx2 = index(fpu2);
	unsigned int higher_idx;
	int dif = 0;
	unsigned int mpr1 = multiplier(fpu1);
	unsigned int mpr2 = multiplier(fpu2);
	bool sign1 = sign(fpu1);
	bool sign2 = sign(fpu2);

	if (idx1 > idx2)
	{
		higher_idx = idx1;
		dif = higher_idx - idx2;
		mpr2 = mpr2 << dif;

	}
	else
	{
		higher_idx = idx2;
		dif = higher_idx - idx1;
		mpr1 = mpr1 << dif;
	}

	unsigned int add_mpr = mpr1 + mpr2;
	
	//float value = add_mpr*pow(2, higher_idx - 127);
	string sign;
	if (sign1 || sign2)
		sign = "1";
	else
		sign = "0";

	string Binary = sign + ToString(higher_idx) + ToString(add_mpr);
	int value = insert(Binary);
	float conv_value = convert(value);

	return conv_value;
}

/*float multiply(unsigned int fpu1, unsigned int fpu2)
{
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



int main()
{
	
	unsigned int nr = insert("00111110000000000000000000000000");		//0.125
	unsigned int nr2 = insert("00111110000000000000000000000000");
	float f = 0.125;
	
	//unsigned int *nr = reinterpret_cast<unsigned int*>(&f);
	//cout << ToString(*nr);
	
	//cout << convert(nr);
	

	
	//cout << add(nr, nr2);
	
	system("pause");
	return 0;
}

