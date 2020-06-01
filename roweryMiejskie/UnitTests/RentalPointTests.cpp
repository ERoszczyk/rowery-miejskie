#include "pch.h"
#include "CppUnitTest.h"
//#include "..\roweryMiejskie\RentalPoint.cpp"
#include "..\roweryMiejskie\RentalPoint.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RentalTests
{
	TEST_CLASS(TestRentalLocation)
	{
	public:
		TEST_METHOD(TestConstructor) //Constructor if a bike added is rented
		{
			BikeDatabase base(5);
			base.setBikeState(2, true);
			RentalLocation point(base);
			int size = point.getBikes().size();
			int free = point.getFreeBikes(base).size();
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
		TEST_METHOD(TestIsActive)
		{
			RentalLocation point;
			Assert::IsTrue(point.isActive());
		}
		TEST_METHOD(TestDisactivate)
		{
			BikeDatabase base;
			RentalLocation point;
			point.disactivateLocation(base);
			Assert::IsFalse(point.isActive());
		}
		TEST_METHOD(TestAddBikeWrongId)
		{
			RentalLocation point;
			point.addBike(-3);
			int size = point.getBikes().size();
			Assert::AreEqual(size, 0);
		};
		TEST_METHOD(TestAddBike)
		{
			BikeDatabase base;
			RentalLocation point;
			point.addBike(0, base);
			int bikesCount = point.getBikes().size();
			int bikeId = point.getBikes()[0];
			Assert::AreEqual(1, bikesCount);
			Assert::AreEqual(1, bikeId);
		}
		TEST_METHOD(TestAddBikes) // Too many bikes
		{
			BikeDatabase base;
			std::vector<int>bikes = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			RentalLocation point;
			point.addBikes(bikes, base);
			int size = point.getBikes().size();
			Assert::AreEqual(size, 10);
		};
		TEST_METHOD(TestRemoveBikes)//Inexistent bike not removed
		{
			std::vector<int>bikes = { 1,2,3 };
			std::vector<int>otherBikes = { 2,4 };
			BikeDatabase base;
			RentalLocation point;
			point.addBikes(bikes, base);
			point.removeBikes(otherBikes, base);
			int size = point.getBikes().size();
			Assert::AreEqual(size, 2);

		};
		TEST_METHOD(TestRent)  //old test
		{
			BikeDatabase base(5);
			RentalLocation point(base);
			Client user("a", "b", "c", "d", 0);
			point.rent(4, 1, base, user);
			Assert::IsTrue(base.getBikeState(4));
			Assert::AreEqual(base.getBikeOwner(4), 1);
			Assert::AreEqual(base.getBikeStand(4), 0);
			std::vector<int> free = point.getFreeBikes(base);
			Assert::IsTrue(find(free.begin(), free.end(), 4) == free.end());

		};
		TEST_METHOD(TestPutBack) //old test, now requires user input for choosing bike stand
		{
			BikeDatabase base(5);
			RentalLocation point(base);
			Client user("a", "b", "c", "d", 0);
			point.rent(4, 1, base, user);
			point.putBack(4, 1, base, user);
			Assert::IsFalse(base.getBikeState(4));
			Assert::AreEqual(base.getBikeOwner(4), 0);
			Assert::AreEqual(base.getBikeStand(4), 4);
			std::vector<int> free = point.getFreeBikes(base);
			Assert::IsTrue(find(free.begin(), free.end(), 4) != free.end());
		}


	};
	TEST_CLASS(TestMainLocation)
	{
		BikeDatabase base;
		std::string one = "one";
		std::string two = "two";
		std::vector<std::string> locationNames = {one, two};
		TEST_METHOD(TestConstructor)
		{
			MainLocation location(locationNames, base);
			Assert::AreEqual(two, location.getRentalLocationNames()[1]);
		}
		TEST_METHOD(TestAddBikeDifferentLocation)
		{
			MainLocation location(locationNames, base);
			location.addBike(0, 1);
			int size = location.getBikes().size();
			Assert::AreEqual(0, size);
		}
		TEST_METHOD(TestRentOtherLocation)
		{
			MainLocation location(locationNames, base);
			Client& user = Client("a", "b", "c", "d", 0);
			location.addBike(123, 0); //to other location
			location.addBike(456); //to main location
			int startSize = location.getBikes().size();
			location.rent(123, 1, base, user, 0);
			int newSize = location.getBikes().size();
			Assert::AreEqual(startSize, newSize);
		}
		TEST_METHOD(TestPutBackOtherLocation)
		{
			MainLocation location(locationNames, base);
			Client& user = Client("a", "b", "c", "d", 0);
			location.addBike(123, 0); //to other location
			location.addBike(456); //to main location
			int startSize = location.getBikes().size();
			location.rent(123, 1, base, user, 0);
			location.putBack(123, 1, base, user, 0);
			int newSize = location.getBikes().size();
			Assert::AreEqual(startSize, newSize);
		}
		TEST_METHOD(TestRentOtherPutBackMain)
		{
			MainLocation location(locationNames, base);
			Client& user = Client("a", "b", "c", "d", 0);
			location.addBike(0, 0); //to other location
			location.addBike(0); //to main location
			location.rent(1, 1, base, user, 0);
			location.putBack(1, 1, base, user);
			int newSize = location.getBikes().size();
			Assert::AreEqual(2, newSize);
		}
	};
}