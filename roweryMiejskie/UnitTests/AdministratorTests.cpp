//Testy jednostkowe, Ewa Roszczyk
//W tym pliku testowane s¹ metody z klasy UserBase. Ze wzglêdu na to, i¿ z nich korzysta klasa Administrator 
//testy te znajduj¹ siê w pliku o nazwie AdministratorTests, a nie UserBaseTests.
#include "pch.h"
#include "CppUnitTest.h"
#include "../roweryMiejskie/UserDataBase.h"
#include "../roweryMiejskie/User.h"
#include "../roweryMiejskie/Administrator.h"
#include "../roweryMiejskie/RentalPoint.h"
#include "../roweryMiejskie/Bike.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AdministratorTests
{
	TEST_CLASS(AdministratorTest)
	{
		UserDataBase base;
		TEST_METHOD(testAdministratorsName)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewAdministrator("a", "b", "c", "d");
			Assert::IsTrue("a" == base.getUserNames().find(usersAmount)->second->getName());
		}

		TEST_METHOD(testAdministratorsSurname)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewAdministrator("a", "b", "c", "d");
			Assert::IsTrue("b" == base.getUserNames().find(usersAmount)->second->getSurname());
		}

		TEST_METHOD(testAdministratorsUsername)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewAdministrator("a", "b", "c", "d");
			Assert::IsTrue("c" == base.getUserNames().find(usersAmount)->second->getUsername());
		}

		TEST_METHOD(testAdministratorsPassword)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewAdministrator("a", "b", "c", "d");
			Assert::IsTrue("d" == base.getUserNames().find(usersAmount)->second->getPassword());
		}

		TEST_METHOD(testChangeName)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			base.changeNameAsAdministrator("c", "abc");
			Assert::IsTrue("abc" == base.getUserNames().find(usersAmount)->second->getName());
		}

		TEST_METHOD(testChangeSurname)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			base.changeSurnameAsAdministrator("c", "abc");
			Assert::IsTrue("abc" == base.getUserNames().find(usersAmount)->second->getSurname());
		}

		TEST_METHOD(testChangeUsername)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			base.changeUsernameAsAdministrator("c", "abc");
			Assert::IsTrue("abc" == base.getUserNames().find(usersAmount)->second->getUsername());
		}

		TEST_METHOD(testChangePassword)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			base.changePasswordAsAdministrator("c", "abc");
			Assert::IsTrue("abc" == base.getUserNames().find(usersAmount)->second->getPassword());
		}

		TEST_METHOD(testDeleteUser)
		{
			int usersAmount = base.getUserNames().size();
			base.addNewClient("a", "b", "c", "d");
			base.deleteUserAsAdministrator("c");
			Assert::IsTrue(usersAmount == base.getUserNames().size());
		}
	};
}
