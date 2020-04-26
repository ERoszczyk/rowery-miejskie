#include "pch.h"
#include "CppUnitTest.h"
#include "../roweryMiejskie/Bike.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

User userx("a", "b", "c", "d");
//User user("a", "b", "c", "d");
//UserBase base;

namespace BikeTests
{
	TEST_CLASS(testBike)
	{
		TEST_METHOD(TestBike1)
		{
			Bike ss(123);
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
			Bike xx(324);
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
			Bike xx(90);
			xx.time_hold = 270;
			xx.account = 30;
			xx.Pay(userx);
			float check = 24;
			float i = 30;
			float acc = 6;
			Assert::AreEqual(acc, xx.account);
			Assert::AreEqual(check, xx.price);
			Assert::AreNotEqual(i, xx.account);

		};

	};
}