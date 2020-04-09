//Testy jednostkowe, Ewa Roszczyk, nr. indeksu: 304077
#include "pch.h"
#include "CppUnitTest.h"
#include "../roweryMiejskie/User.cpp"
//#include "../roweryMiejskie/UserBase.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//UserBase base;
User user("a", "b", "c", "d");

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
			user.setCash(50);
			Assert::IsTrue(user.getCash() == 50);
		}

		TEST_METHOD(testRentedBikes)
		{
			user.setRentedBikes(3);
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

	//TEST_CLASS(testUserBase)
	//{
	//	/*TEST_METHOD(testName)
	//	{
	//		base.setUserNames("a", "b", "c", "d");
	//		base.getUserNames().find(0)->second.setName("Jan");
	//		Assert::IsTrue("Jan" == base.getUserNames().find(0)->second.getName());
	//	}*/

	//	/*TEST_METHOD(surname)
	//	{
	//		User user("a", "b", "c", "d");
	//		user.setSurname("Kowalski");
	//		Assert::IsTrue("Kowalski" == user.getSurname());
	//	}

	//	TEST_METHOD(username)
	//	{
	//		User user("a", "b", "c", "d");
	//		user.setUsername("Janek.Kowalski");
	//		Assert::IsTrue("Janek.Kowalski" == user.getUsername());
	//	}

	//	TEST_METHOD(password)
	//	{
	//		User user("a", "b", "c", "d");
	//		user.setPassword("haslo");
	//		Assert::IsTrue("haslo" == user.getPassword());
	//	}

	//	TEST_METHOD(cash)
	//	{
	//		User user("a", "b", "c", "d");
	//		user.setCash(50);
	//		Assert::IsTrue(50 == user.getCash());
	//	}

	//	TEST_METHOD(rentedBikes)
	//	{
	//		User user("a", "b", "c", "d");
	//		user.setRentedBikes(3);
	//		Assert::IsTrue(3 == user.getRentedBikes());
	//	}

	//	TEST_METHOD(rentedBikesId)
	//	{
	//		vector<int> bike;
	//		bike.push_back(123);
	//		User user("a", "b", "c", "d");
	//		user.addRentedBikeId(123);
	//		Assert::IsTrue(bike == user.getRentedBikesId());
	//	}

	//	TEST_METHOD(rentedBikesId2)
	//	{
	//		vector<int> bike;
	//		User user("a", "b", "c", "d");
	//		user.addRentedBikeId(123);
	//		user.removeRentedBikesId();
	//		Assert::IsTrue(bike == user.getRentedBikesId());
	//	}*/
	//};
}
