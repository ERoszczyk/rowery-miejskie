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

		TEST_METHOD(TestState)
		{
			example.setState(true);
			Assert::IsTrue(example.getState());
		};
		TEST_METHOD(TestUser)
		{
			example.setUser(567);
			Assert::AreEqual(567, example.getUser());
		};
		TEST_METHOD(TestStand)
		{
			example.setStand(1);
			Assert::AreEqual(1, example.getStand());
		};
	};
}

namespace BikeDatabaseTests
{
	TEST_CLASS(TestDatabase)
	{
	public:
		TEST_METHOD(TestGetAllBikes)
		{
			BikeDatabase base;
			int size = base.getAllBikes().size();
			Assert::AreEqual(0, size);
		};
		TEST_METHOD(TestConstructor)
		{
			BikeDatabase base(5);
			int size = base.getAllBikes().size();
			Assert::AreEqual(5, size);
		};
		TEST_METHOD(TestAddBike)
		{
			BikeDatabase base;

			base.addBike();
			int size = base.getAllBikes().size();
			Assert::AreEqual(1, size);
		};
		TEST_METHOD(TestAddBike2)
		{
			//prepare data
			BikeDatabase base(2);
			Record example;
			example.setStand(4);
			//test
			base.addBike(example);
			Assert::AreEqual(base.getBikeStand(3), 4);
		};
		TEST_METHOD(TestAddBikes)
		{
			//prepare data
			Record example1, example2, example3;
			example1.setStand(45);
			example3.setState(true);
			example3.setUser(789);
			std::vector<Record> records;
			records.push_back(example1);
			records.push_back(example2);
			records.push_back(example3);
			//test
			BikeDatabase base;
			base.addBikes(records);
			Assert::AreEqual(base.getBikeStand(1), 45);
			Assert::IsFalse(base.getBikeState(1));
			Assert::IsTrue(base.getBikeState(3));
			Assert::AreEqual(base.getBikeOwner(3), 789);
		};
		TEST_METHOD(TestRemoveBike)
		{
			BikeDatabase base(2);
			base.removeBike(1);
			int size = base.getAllBikes().size();
			Assert::AreEqual(1,size);
			try
			{
				base.getBikeState(1);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};

		}
		TEST_METHOD(TestRemoveBikes)
		{
			BikeDatabase base(5);
			base.removeBikes({ 2,3 });
			int size = base.getAllBikes().size();
			Assert::AreEqual(3, size);
			try
			{
				base.getBikeState(3);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};

		}
		TEST_METHOD(TestBikeState)
		{
			BikeDatabase base(1);
			base.setBikeState(1, true);
			Assert::IsTrue(base.getBikeState(1));
		}
		TEST_METHOD(TestBikeOwner)
		{
			BikeDatabase base(1);
			base.setBikeOwner(1, 123);
			Assert::AreEqual(123,base.getBikeOwner(1));
		}
		TEST_METHOD(TestBikeStand)
		{
			BikeDatabase base(1);
			base.setBikeStand(1, 1);
			Assert::AreEqual(1, base.getBikeStand(1));
		}

		TEST_METHOD(TestGetBikeStateforOutOfRange)
		{
			BikeDatabase base; //empty
			try
			{
				base.getBikeState(1);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};
		};
		TEST_METHOD(TestSetBikeStateforOutOfRange)
		{
			BikeDatabase base; //empty
			try
			{
				base.setBikeState(1, true);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};
		};
		TEST_METHOD(TestGetBikeOwnerforOutOfRange)
		{
			BikeDatabase base; //empty
			try
			{
				base.getBikeOwner(1);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};
		};
		TEST_METHOD(TestSetBikeOwnerforOutOfRange)
		{
			BikeDatabase base; //empty
			try
			{
				base.setBikeOwner(1, 123);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};
		};
		TEST_METHOD(TestGetBikeStandforOutOfRange)
		{
			BikeDatabase base; //empty
			try
			{
				base.getBikeStand(1);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};
		};
		TEST_METHOD(TestSetBikeStandforOutOfRange)
		{
			BikeDatabase base; //empty
			try
			{
				base.setBikeStand(1, 1);
				Assert::IsTrue(false);
			}
			catch (std::out_of_range)
			{
				Assert::IsTrue(true);
			};
		};
		TEST_METHOD(TestExportImportFile)
		{
			BikeDatabase base(5), newBase;
			base.setBikeState(4, true);
			base.setBikeOwner(4, 54);
			base.exportToFile();
			newBase.importFromFile();
			Assert::IsTrue(newBase.getBikeState(4));
			Assert::AreEqual(newBase.getBikeOwner(4), 54);

		};
		TEST_METHOD(TestPlusOperator)
		{
			BikeDatabase base(6), newbase(4);
			newbase.setBikeOwner(4, 56);
			newbase.setBikeState(4, 1);
			BikeDatabase added;
			added = base + newbase;
			Assert::IsTrue(added.getBikeState(10));
			Assert::AreEqual(added.getBikeOwner(10), 56);
		};


	};
}

