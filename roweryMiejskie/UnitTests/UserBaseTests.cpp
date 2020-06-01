//Testy jednostkowe, Ewa Roszczyk
#include "pch.h"
#include "CppUnitTest.h"
#include "../roweryMiejskie/UserDataBase.h"
#include "../roweryMiejskie/User.h"
#include "../roweryMiejskie/Administrator.h"
#include "../roweryMiejskie/RentalPoint.h"
#include "../roweryMiejskie/Bike.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UserBaseTests
{
	TEST_CLASS(UserBaseTest)
	{
		UserDataBase base;
		TEST_METHOD(testName)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue("a" == base.getUserNames().find(2)->second->getName());
		}

		TEST_METHOD(testSurname)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue("b" == base.getUserNames().find(2)->second->getSurname());
		}

		TEST_METHOD(testUsername)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue("c" == base.getUserNames().find(2)->second->getUsername());
		}

		TEST_METHOD(testPassword)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue("d" == base.getUserNames().find(2)->second->getPassword());
		}

		TEST_METHOD(testGetUserNames)
		{
			base.addNewUser("a", "b", "c", "d");
			Assert::IsTrue(3 == base.getUserNames().size());
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

		TEST_METHOD(testIfUsernameExists)
		{
			base.addNewAdministrator("a", "b", "c", "d");
			Assert::IsTrue(true == base.ifUsernameExists("c"));
		}

		TEST_METHOD(testIfUsernameExists2)
		{
			base.addNewAdministrator("a", "b", "c", "d");
			Assert::IsTrue(false == base.ifUsernameExists("abc"));
		}

		TEST_METHOD(testGetCurrentLoginIndex)
		{
			Assert::IsTrue(2 == base.getCurrentLoginIndex());
		}
	};
}
