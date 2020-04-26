#include "pch.h"
#include "CppUnitTest.h"
#include "../roweryMiejskie/RentalPoint.cpp"
#include "../roweryMiejskie/userBase.cpp"
#include "../roweryMiejskie/userBase.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UserBaseTests
{
	TEST_CLASS(testUserBase)
	{
		UserBase base;
		TEST_METHOD(testName)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue("a" == base.getUserNames().find(0)->second.getName());
		}

		TEST_METHOD(testSurname)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue("b" == base.getUserNames().find(0)->second.getSurname());
		}

		TEST_METHOD(testUsername)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue("c" == base.getUserNames().find(0)->second.getUsername());
		}

		TEST_METHOD(testPassword)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue("d" == base.getUserNames().find(0)->second.getPassword());
		}

		TEST_METHOD(testCash)
		{
			base.addNewUser("a", "b", "c", "d");
			int activeUser = 0;
			base.setActiveUserId(0);
			base.transferMoney(50);
			Assert::IsTrue(70 == base.getUserNames().find(0)->second.getCash());
		}

		TEST_METHOD(rentedBikesId2)
		{
			vector<int> bike;
			base.addNewUser("a", "b", "c", "d");
			base.getUserNames().find(0)->second.addRentedBikeId(123);
			base.getUserNames().find(0)->second.removeRentedBikesId();
			Assert::IsTrue(bike == base.getUserNames().find(0)->second.getRentedBikesId());
		}

		TEST_METHOD(testGetUserNames)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue(1 == base.getUserNames().size());
		}

		TEST_METHOD(testGetCurrentLoginIndex)
		{
			Assert::IsTrue(0 == base.getCurrentLoginIndex());
		}

		TEST_METHOD(testActiveUserId)
		{
			base.setActiveUserId(1);
			Assert::IsTrue(1 == base.getActiveUserId());
		}

		TEST_METHOD(testIfUsernameAvailable)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue(false == base.ifUsernameAvailable("c"));
		}

		TEST_METHOD(testIfUsernameAvailable2)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue(true == base.ifUsernameAvailable("abc"));
		}

		TEST_METHOD(testIfLogged)
		{
			base.setActiveUserId(1);
			Assert::IsTrue(true == base.ifLogged());
		}

		TEST_METHOD(testIfLogged2)
		{
			Assert::IsTrue(false == base.ifLogged());
		}

		TEST_METHOD(testCheckAccountBalance)
		{
			base.addNewUser("a", "b", "c", "d");
			base.setActiveUserId(0);
			Assert::IsTrue(20 == base.checkAccountBalance());
		}

		TEST_METHOD(testCheckAccountBalance2)
		{
			base.addNewUser("a", "b", "c", "d");
			base.setActiveUserId(0);
			base.transferMoney(2.5);
			Assert::IsTrue(22.5 == base.checkAccountBalance());
		}
	};
}
