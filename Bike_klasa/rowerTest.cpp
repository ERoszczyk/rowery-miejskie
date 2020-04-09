//Testy klasy Bike
//Olga Krupa,nr indeksu 304048
#include "pch.h"
#include "CppUnitTest.h"
#include "../rower/Bike.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

map<int, int> state = {
	{ 12, 385 },
	{ 38, 1 },
	{ 35, 1 },
	{ 43, 1 },
	{ 41, 415 },
	{ 56, 1 }
};
map<int, char> bikes = {
	{ 124, 'F' },
	{ 385, 'O' },
	{ 354, 'F' },
	{ 432, 'F' },
	{ 415, 'O' },
	{ 567, 'F' }
};
namespace rowerTest
{
	TEST_CLASS(rowerTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Bike ss(123);
			ss.time_hold = 10;
			ss.account = 13;
			ss.Pay();
			float check = 1;
			float i = 13;
			float acc = 12;
			Assert::AreEqual(acc, ss.account);
			Assert::AreEqual(check, ss.price);
			Assert::AreNotEqual(i, ss.account);
		};
		TEST_METHOD(TestMethod2)
		{
			Bike xx(324);
			xx.time_hold = 190;
			xx.account = 27;
			xx.Pay();
			float check = 17;
			float i = 27;
			float acc = 10;
			Assert::AreEqual(acc, xx.account);
			Assert::AreEqual(check, xx.price);
			Assert::AreNotEqual(i, xx.account);

		};
		TEST_METHOD(TestMethod3)
		{
			Bike xx(90);
			xx.time_hold = 270;
			xx.account = 30;
			xx.Pay();
			float check = 24;
			float i = 30;
			float acc = 6;
			Assert::AreEqual(acc, xx.account);
			Assert::AreEqual(check, xx.price);
			Assert::AreNotEqual(i, xx.account);

		};

		TEST_METHOD(TestMethod4)
		{
			Bike aa(90);
			int s1 = 1;
			int s2 = 12;
			int s3 = 38;
			Assert::AreEqual(true, aa.FindStand(state, s3));
			Assert::AreEqual(false, aa.FindStand(state, s1));
			Assert::AreNotEqual(true, aa.FindStand(state, s2));

		};

		TEST_METHOD(TestMethod5)
		{
			Bike bb(80);
			bb.StartOfRent(state, bikes, "xyz", 44);
			bb.time_hold = 15;
			bb.price = 1;
			bb.state = 20;
			bb.HistoryOfRent(bb);

			string tittle = "Bike 80: USER | STATE | TIME OF RENT | PRICE\n";
			string curstate = "xyz | 20 | 15.000000 | 1.000000";
			Assert::AreEqual(tittle, bb.history[0] );
			Assert::AreEqual(curstate, bb.history[1]);

		};
	};
}
