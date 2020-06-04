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
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			Assert::IsTrue("a" == base.getUserNames().find(usersAmount)->second->getName());
		}

		TEST_METHOD(testSurname)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			Assert::IsTrue("b" == base.getUserNames().find(usersAmount)->second->getSurname());
		}

		TEST_METHOD(testUsername)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			Assert::IsTrue("c" == base.getUserNames().find(usersAmount)->second->getUsername());
		}

		TEST_METHOD(testPassword)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			Assert::IsTrue("d" == base.getUserNames().find(usersAmount)->second->getPassword());
		}

		TEST_METHOD(testGetUserNames)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			Assert::IsTrue(usersAmount+1 == base.getUserNames().size());
		}


		TEST_METHOD(testIfUsernameAvailable)
		{
			base.addNewClient("a", "b", "c", "d");
			Assert::IsTrue(false == base.ifUsernameAvailable("c"));
		}

		TEST_METHOD(testIfUsernameAvailable2)
		{
			base.addNewClient("a", "b", "c", "d");
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
			int usersAmount = base.getUserNames().size();
			Assert::IsTrue(usersAmount == base.getCurrentLoginIndex());
		}
	};
}
