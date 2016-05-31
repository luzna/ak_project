#include "Model.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include </usr/include/boost/test/unit_test.hpp>
#include <iostream>

float f, f2;
Model *model3;
float r;

BOOST_AUTO_TEST_SUITE( Dodawanie )

BOOST_AUTO_TEST_CASE( testDodaj1 )
{
	f = 2.0f; 
	f2 = 3.0f;
	Model model(f); Model model2(f2);
	model3 = model.add(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 5.f );
}

BOOST_AUTO_TEST_CASE( testDodaj2 )
{
	f = 0.2; 
	f2 = 0.7;
	Model model(f); Model model2(f2);
	model3 = model.add(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 0.9f );
}

BOOST_AUTO_TEST_CASE( testDodaj3 )
{
	f = 14.5; 
	f2 = 11.02;
	Model model(f); Model model2(f2);
	model3 = model.add(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 25.52f );
}

BOOST_AUTO_TEST_CASE( testDodaj4 )
{
	f = 112.015; 
	f2 = 0.2;
	Model model(f); Model model2(f2);
	model3 = model.add(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 112.215f );
}

BOOST_AUTO_TEST_CASE( testDodaj5 )
{
	f = -4.0; 
	f2 = 1.0;
	Model model(f); Model model2(f2);
	model3 = model.add(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == -3.0f );
}

BOOST_AUTO_TEST_CASE( testDodaj6 )
{
	f = -10.0; 
	f2 = -5.4;
	Model model(f); Model model2(f2);
	model3 = model.add(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == -15.4f );
}


BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( Odejmowanie )

BOOST_AUTO_TEST_CASE( testOd1 )
{
	f = 5.0; 
	f2 = 3.0;
	Model model(f); Model model2(f2);
	model3 = model.subtract(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 2.0f );
}

BOOST_AUTO_TEST_CASE( testOd2 )
{
	f = 14.2; 
	f2 = 3.0;
	Model model(f); Model model2(f2);
	model3 = model.subtract(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 11.2f );
}

BOOST_AUTO_TEST_CASE( testOd3 )
{
	f = 4.5; 
	f2 = 1;
	Model model(f); Model model2(f2);
	model3 = model.subtract(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 3.5f );
}

BOOST_AUTO_TEST_CASE( testOd4 )
{
	f = 128.41; 
	f2 = 12.0;
	Model model(f); Model model2(f2);
	model3 = model.subtract(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 116.41f );
}

BOOST_AUTO_TEST_CASE( testOd5 )
{
	f = -0.8; 
	f2 = 1.0;
	Model model(f); Model model2(f2);
	model3 = model.subtract(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == -1.8f );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( Mnozenie )

BOOST_AUTO_TEST_CASE( testMn1 )
{
	f = 5.0; 
	f2 = 3.0;
	Model model(f); Model model2(f2);
	model3 = model.multiply(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 15.0f );
}

BOOST_AUTO_TEST_CASE( testMn2 )
{
	f = 2.5; 
	f2 = 12;
	Model model(f); Model model2(f2);
	model3 = model.multiply(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 30.0f );
}

BOOST_AUTO_TEST_CASE( testMn3 )
{
	f = 0.4; 
	f2 = 2;
	Model model(f); Model model2(f2);
	model3 = model.multiply(model2);
	r = *((*model3).get_number());
	//r = round(r * 100.0f) / 100.0f;
	cout << endl << "result: " << r << endl;
	BOOST_CHECK( r == 0.8f );
}

BOOST_AUTO_TEST_CASE( testMn4 )
{
	f = 20; 
	f2 = 40;
	Model model(f); Model model2(f2);
	model3 = model.multiply(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 800.0f );
}

BOOST_AUTO_TEST_CASE( testMn5 )
{
	f = 0.2; 
	f2 = 0.3;
	Model model(f); Model model2(f2);
	model3 = model.multiply(model2);
	r = *((*model3).get_number());
	cout << endl << "result: " << r << endl;
	BOOST_CHECK( r == 0.6f );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE( Dzielenie )

BOOST_AUTO_TEST_CASE( testDz1 )
{
	f = 10.0; 
	f2 = 2.0;
	Model model(f); Model model2(f2);
	model3 = model.divide(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 5.0f );
}

BOOST_AUTO_TEST_CASE( testDz2 )
{
	f = 0.6; 
	f2 = 2.0;
	Model model(f); Model model2(f2);
	model3 = model.divide(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 0.3f );
}

BOOST_AUTO_TEST_CASE( testDz3 )
{
	f = 112.0; 
	f2 = 5.0;
	Model model(f); Model model2(f2);
	model3 = model.divide(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 22.4f );
}

BOOST_AUTO_TEST_CASE( testDz4 )
{
	f = 86.6; 
	f2 = 0.5;
	Model model(f); Model model2(f2);
	model3 = model.divide(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == 173.2f );
}

BOOST_AUTO_TEST_CASE( testDz5 )
{
	f = 0.6; 
	f2 = -0.3;
	Model model(f); Model model2(f2);
	model3 = model.divide(model2);
	r = *((*model3).get_number());
	BOOST_CHECK( r == -2.0f );
}
BOOST_AUTO_TEST_SUITE_END()
