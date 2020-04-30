//Testy jednostkowe, Ewa Roszczyk
#include "pch.h"
#include "CppUnitTest.h"
#include "../roweryMiejskie/Client.h"
#include "../roweryMiejskie/Client.cpp"
#include "../roweryMiejskie/User.cpp"
#include "../roweryMiejskie/Administrator.cpp"
#include "../roweryMiejskie/RentalPoint.cpp"
#include "../roweryMiejskie/UserBase.cpp"
#include "../roweryMiejskie/Bike.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

Client user("a", "b", "c", "d", 0);

namespace ClientTest
{
	TEST_CLASS(ClientTest)
	{
	public:

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
			Assert::IsTrue(user.getCash() == 70); //20 użytkownik posiada w momencie założenia konta
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
