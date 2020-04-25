// BikeTests.cpp contains tests for struct Record and classes Database and Rental Point
// Author: Kinga Kwoka gr.208

#include "pch.h"
#include "CppUnitTest.h"
#include "..\roweryMiejskie\BikeDatabase.cpp"
//#include "..\roweryMiejskie\RentalPoint.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecordClass
{
	TEST_CLASS(RecordTests)
	{
		Record example;
	public:

		TEST_METHOD(TestAll)
		{
			example.setState(true);
			Assert::IsTrue(example.getState());
		};
		TEST_METHOD(TestUser)
		{
			example.setUser(567);
			Assert::AreEqual(example.getUser(), 567);
		};
		TEST_METHOD(TestStand)
		{
			example.setStand(1);
			Assert::AreEqual(example.getStand(), 1);
		};
	};
}

namespace BikeDatabaseTests
{
	TEST_CLASS(TestDatabase)
	{
	public:
		TEST_METHOD(TestConstructor)
		{
			BikeDatabase base(5);
			int size = base.getAllBikes().size();
			Assert::AreEqual(size, 5);
		};
		TEST_METHOD(TestAddBike)
		{
			BikeDatabase base;
			base.addBike();
			int size = base.getAllBikes().size();
			Assert::AreEqual(size, 1);
		};
		TEST_METHOD(TestAddBike2)
		{
			BikeDatabase base(2);
			Record example;
			example.setStand(4);
			base.addBike(example);
			Assert::AreEqual(base.getBikeStand(3), 4);
		}
		TEST_METHOD(TestAddBikes)
		{
			Record example1, example2, example3;
			example1.setStand(45);
			example3.setState(true);
			example3.setUser(789);
			std::vector<Record> records;
			records.push_back(example1);
			records.push_back(example2);
			records.push_back(example3);
			BikeDatabase base;
			base.addBikes(records);
			Assert::AreEqual(base.getBikeStand(1), 45);
			Assert::IsFalse(base.getBikeState(1));
			Assert::IsTrue(base.getBikeState(3));
			Assert::AreEqual(base.getBikeOwner(3), 789);
		}
		TEST_METHOD(TestIndexOutOfRange)
		{
			BikeDatabase base(1);
			try
			{
				base.getBikeState(2); //index out of range
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};
			try
			{
				base.setBikeState(2, true);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};
		}
		TEST_METHOD(TestExportImportFile)
		{
			BikeDatabase base(5), newBase;
			base.setBikeState(4, true);
			base.setBikeOwner(4, 54);
			base.exportToFile();
			newBase.importFromFile();
			Assert::IsTrue(newBase.getBikeState(4));
			Assert::AreEqual(newBase.getBikeOwner(4), 54);

		}
		TEST_METHOD(TestPlusOperator)
		{
			BikeDatabase base(6), newbase(4);
			newbase.setBikeOwner(4, 56);
			newbase.setBikeState(4, 1);
			BikeDatabase added;
			added = base + newbase;
			Assert::IsTrue(added.getBikeState(10));
			Assert::AreEqual(added.getBikeOwner(10), 56);
		}


	};
}

//namespace RentalTests
//{
//	TEST_CLASS(TestRentalPoint)
//	{
//	public:
//		TEST_METHOD(TestConstructor) //Constructor if a bike added is rented
//		{
//			BikeDatabase base(5);
//			base.setBikeState(2, true);
//			RentalPoint point(base);
//			int size = point.getBikes().size();
//			int free = point.getFreeBikes().size();
//			Assert::AreEqual(size, 5);
//			Assert::AreEqual(free, 4);
//
//		};
//		TEST_METHOD(TestConstructor2) //Constructor if database too big
//		{
//			BikeDatabase base(15);
//			RentalPoint point(base);
//			int size = point.getBikes().size();
//			Assert::AreEqual(size, 10);  //10 set as max rental point size
//		};
//		TEST_METHOD(TestConstructor3) //Constructor if too many bikeIds
//		{
//			std::vector<int>bikes = { 1,2,3,4,5,6,7,8,9,10,11,12 };
//			RentalPoint point(bikes);
//			int size = point.getBikes().size();
//			Assert::AreEqual(size, 10);
//		};
//		TEST_METHOD(TestRentalAdd) // Unacceptable Id
//		{
//			RentalPoint point;
//			point.addBike(-3);
//			int size = point.getBikes().size();
//			Assert::AreEqual(size, 0);
//		};
//		TEST_METHOD(TestAddBikes) // Too many bikes
//		{
//			std::vector<int>bikes = { 1,2,3,4,5,6,7,8,9,10,11,12 };
//			RentalPoint point;
//			point.addBikes(bikes);
//			int size = point.getBikes().size();
//			Assert::AreEqual(size, 10);
//		};
//		TEST_METHOD(TestRemoveBikes)//Inexistent bike
//		{
//			std::vector<int>bikes = { 1,2,3 };
//			std::vector<int>otherBikes = { 2,4 };
//			RentalPoint point;
//			point.addBikes(bikes);
//			point.removeBikes(otherBikes);
//			int size = point.getBikes().size();
//			Assert::AreEqual(size, 2);
//		};
//		TEST_METHOD(TestRent)
//		{
//			BikeDatabase base(5);
//			RentalPoint point(base);
//			point.rent(4, 25, base);
//			Assert::IsTrue(base.getBikeState(4));
//			Assert::AreEqual(base.getBikeOwner(4), 25);
//			Assert::AreEqual(base.getBikeStand(4), 0);
//			std::vector<int> free = point.getFreeBikes();
//			Assert::IsTrue(find(free.begin(), free.end(), 4) == free.end());
//
//		};
//		TEST_METHOD(TestPutBack)
//		{
//			BikeDatabase base(5);
//			RentalPoint point(base);
//			point.rent(4, 25, base);
//			point.putBack(4, 25, base);
//			Assert::IsFalse(base.getBikeState(4));
//			Assert::AreEqual(base.getBikeOwner(4), 0);
//			Assert::AreEqual(base.getBikeStand(4), 1);
//			std::vector<int> free = point.getFreeBikes();
//			Assert::IsTrue(find(free.begin(), free.end(), 4) != free.end());
//
//		}
//
//
//	};
//}