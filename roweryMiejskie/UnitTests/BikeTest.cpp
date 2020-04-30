#include "pch.h"
#include "CppUnitTest.h"
//#include "../roweryMiejskie/Bike.cpp"
#include "../roweryMiejskie/ElectricBike.cpp" 
#include "../roweryMiejskie/Tandem.cpp" 


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

Client userx("a", "b", "c", "d", 1);
BikeDatabase database(12);
Bike ss(123);
Bike xx(324);
Bike aa(90);
Tandem tt(90);
ElectricBike x(55);
//User user("a", "b", "c", "d");
//UserBase base;

namespace BikeTests
{
	TEST_CLASS(testBike)
	{
		TEST_METHOD(TestBike1)
		{
			ss.time_hold = 10;
			ss.account = 13;
			ss.Pay(userx);
			float check = 1;
			float i = 13;
			float acc = 12;
			Assert::AreEqual(acc, ss.account);
			Assert::AreEqual(check, ss.price);
			Assert::AreNotEqual(i, ss.account);
		}

		TEST_METHOD(TestBike2)
		{
			xx.time_hold = 190;
			xx.account = 27;
			xx.Pay(userx);
			float check = 17;
			float i = 27;
			float acc = 10;
			Assert::AreEqual(acc, xx.account);
			Assert::AreEqual(check, xx.price);
			Assert::AreNotEqual(i, xx.account);

		};
		TEST_METHOD(TestBike3)
		{
			aa.time_hold = 270;
			aa.account = 30;
			aa.Pay(userx);
			float check = 24;
			float i = 30;
			float acc = 6;
			Assert::AreEqual(acc, aa.account);
			Assert::AreEqual(check, aa.price);
			Assert::AreNotEqual(i, aa.account);

		};

		TEST_METHOD(TestTandemBike)
		{
			tt.time_hold = 200;
			tt.account = 30;
			tt.Pay(userx);
			float check = 28;
			float i = 30;
			float acc = 2;
			Assert::AreEqual(acc, tt.account);
			Assert::AreEqual(check, tt.price);
			Assert::AreNotEqual(i, tt.account);

		};
		TEST_METHOD(TestElectricBike)
		{
			x.time_hold = 170;
			x.account = 30;
			x.Pay(userx);
			float check = 24;
			float i = 30;
			float acc = 6;
			Assert::AreEqual(acc, x.account);
			Assert::AreEqual(check, x.price);
			Assert::AreNotEqual(i, x.account);

		};
		TEST_METHOD(TestElectricBike2)
		{
			//double account = userx.getCash();
			double account = 30;
			int userid = userx.getId();
			float check = 5;
			float acc = 25;
			float i = 30;
			int battery = 99;
			map<int, bool> standStates = {
				{ 12, true },
				{ 38, false },
				{ 35, false },
				{ 43, true },
				{ 41, true },
				{ 56, false }
			};
			x.StartOfRent(database, userid, account);
			x.Stop(database,standStates ,userx);
			Assert::AreEqual(acc, x.account);
			Assert::AreEqual(check, x.price);
			Assert::AreNotEqual(i, x.account);
			Assert::AreEqual(battery, x.battery);

		};

	};
}