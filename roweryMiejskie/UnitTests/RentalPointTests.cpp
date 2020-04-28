#include "pch.h"
#include "CppUnitTest.h"
//#include "..\roweryMiejskie\RentalPoint.cpp"
#include "..\roweryMiejskie\RentalPoint.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RentalTests
{
	TEST_CLASS(TestRentalPoint)
	{
	public:
		TEST_METHOD(TestConstructor) //Constructor if a bike added is rented
		{
			BikeDatabase base(5);
			base.setBikeState(2, true);
			RentalLocation point(base);
			int size = point.getBikes().size();
			int free = point.getFreeBikes().size();
			Assert::AreEqual(size, 5);
			Assert::AreEqual(free, 4);

		};
		TEST_METHOD(TestConstructor2) //Constructor if database too big
		{
			BikeDatabase base(15);
			RentalLocation point(base);
			int size = point.getBikes().size();
			Assert::AreEqual(size, 10);  //10 set as max rental point size
		};
		TEST_METHOD(TestConstructor3) //Constructor if too many bikeIds
		{
			std::vector<int>bikes = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			RentalLocation point(bikes);
			int size = point.getBikes().size();
			Assert::AreEqual(size, 10);
		};
		TEST_METHOD(TestRentalAdd) // Unacceptable Id
		{
			RentalLocation point;
			point.addBike(-3);
			int size = point.getBikes().size();
			Assert::AreEqual(size, 0);
		};
		TEST_METHOD(TestAddBikes) // Too many bikes
		{
			std::vector<int>bikes = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			RentalLocation point;
			point.addBikes(bikes);
			int size = point.getBikes().size();
			Assert::AreEqual(size, 10);
		};
		TEST_METHOD(TestRemoveBikes)//Inexistent bike
		{
			std::vector<int>bikes = { 1,2,3 };
			std::vector<int>otherBikes = { 2,4 };
			RentalLocation point;
			point.addBikes(bikes);
			point.removeBikes(otherBikes);
			int size = point.getBikes().size();
			Assert::AreEqual(size, 2);
		};
		TEST_METHOD(TestRent)  //old test
		{
			BikeDatabase base(5);
			RentalLocation point(base);
			User user("a", "b", "c", "d");
			point.rent(4, 1, base, user);
			Assert::IsTrue(base.getBikeState(4));
			Assert::AreEqual(base.getBikeOwner(4), 1);
			Assert::AreEqual(base.getBikeStand(4), 0);
			std::vector<int> free = point.getFreeBikes();
			Assert::IsTrue(find(free.begin(), free.end(), 4) == free.end());

		};
		//TEST_METHOD(TestPutBack) //old test, now requires user input for choosing bike stand
		//{
		//	BikeDatabase base(5);
		//	RentalPoint point(base);
		//	User user("a", "b", "c", "d");
		//	point.rent(4, 1, base, user);
		//	point.putBack(4, 1, base, user);
		//	Assert::IsFalse(base.getBikeState(4));
		//	Assert::AreEqual(base.getBikeOwner(4), 0);
		//	Assert::AreEqual(base.getBikeStand(4), 1);
		//	std::vector<int> free = point.getFreeBikes();
		//	Assert::IsTrue(find(free.begin(), free.end(), 4) != free.end());

		//}


	};
}