#include "pch.h"
#include "CppUnitTest.h"
#include "../roweryMiejskie/user.cpp"
//#include "../roweryMiejskie/userBase.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

User user("a", "b", "c", "d");
//UserBase base;

namespace UnitTests
{
	TEST_CLASS(testUser)
	{
		TEST_METHOD(testName)
		{
			user.setName("Jan");
			Assert::IsTrue(user.getName() == "Jan");
		}

		TEST_METHOD(testSurname)
		{
			user.setSurname("Kowalski");
			Assert::IsTrue(user.getSurname() == "Kowalski");
		}

		TEST_METHOD(testUsername)
		{
			user.setUsername("Jan.Kowalski");
			Assert::IsTrue(user.getUsername() == "Jan.Kowalski");
		}

		TEST_METHOD(testPassword)
		{
			user.setPassword("haslo");
			Assert::IsTrue(user.getPassword() == "haslo");
		}

		TEST_METHOD(testCash)
		{
			user.transferCash(50);
			Assert::IsTrue(user.getCash() == 70); //70, poniewa¿ 20 u¿ytkownik posiada w momencie za³o¿enia konta
		}

		TEST_METHOD(testRentedBikes)
		{
			user.addRentedBikesAmount(3);
			Assert::IsTrue(user.getRentedBikes() == 3);
		}

		TEST_METHOD(testRentedBikesId)
		{
			vector<int> bikes;
			bikes.push_back(123);
			user.addRentedBikeId(123);
			Assert::IsTrue(user.getRentedBikesId() == bikes);
		}

		TEST_METHOD(testRentedBikesId2)
		{
			vector<int> bikes;
			user.removeRentedBikesId();
			Assert::IsTrue(user.getRentedBikesId() == bikes);
		}
	};
}
