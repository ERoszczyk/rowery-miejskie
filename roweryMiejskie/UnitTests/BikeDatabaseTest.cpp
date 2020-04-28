// BikeTests.cpp contains tests for struct Record and classes Database and Rental Point
// Author: Kinga Kwoka gr.208

#include "pch.h"
#include "CppUnitTest.h"
#include "..\roweryMiejskie\BikeDatabase.cpp"


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

