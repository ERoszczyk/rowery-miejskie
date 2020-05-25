#include <conio.h>
#include "ClientPremium.h"
#include "RentalPoint.h"
#include "UserDataBase.h"

using namespace std;

ClientPremium::ClientPremium(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& id)
	: Client(userName, userSurname, userUsername, userPassword, id)
{
}

void ClientPremium::menu(MainLocation& rental, BikeDatabase& database, UserDataBase& userBase)
{
	int optionNumber;
	string answer;

	system("CLS");
	cout << "Hello " << getName() << "!" << endl;
	cout << "1. Rent a bike(s)" << endl;
	cout << "2. View rented bike(s)" << endl;
	cout << "3. Return rented bike(s)" << endl;
	cout << "4. View location" << endl;
	cout << "5. Change location" << endl;
	cout << "6. View a list of rental points" << endl;
	cout << "7. Transfer money" << endl;
	cout << "8. Check account balance" << endl;
	cout << "9. Check account history" << endl;
	cout << "10. Change password" << endl;
	cout << "11. Resign from premium" << endl;
	cout << "12. Log out" << endl;
	cout << "Enter what would you like to do: ";
	cin >> optionNumber;
	switch (optionNumber)
	{
	case 1:
		rentBike(rental, database);
		break;
	case 2:
		viewRentedBikes();
		break;
	case 3:
		returnBike(rental, database);
		break;
	case 4:
		cout << viewLocation(rental);
		break;
	case 5:
		changeLocation(rental);
		break;
	case 6:
		viewRentalPointLocation(rental);
		break;
	case 7:
		transferMoney();
		break;
	case 8:
		cout << getCash() << endl;
		break;
	case 9:
		cout << "This option is not available yet" << endl;
		break;
	case 10:
		changePassword();
		break;
	case 11:
		cout << "This option is not available yet" << endl;
		//premiumResignation(userBase);
		break;
	case 12:
		cout << "You've been logged out" << endl;
		return;
	default:
		cout << "Wrong number!" << endl;
		break;
	}
	cout << "Would you like to continue? (y/n) ";
	cin >> answer;
	if (answer == "y")
	{
		menu(rental, database, userBase);
	}
	else
	{
		cout << "You've been logged out" << endl;
		return;
	}
}

void ClientPremium::rentBike(MainLocation& const rental, BikeDatabase& database)
{
	string answer;
	int bikesNumber, bikeType;
	cout << "1. Normal bike" << endl;
	cout << "2. Electric bike" << endl;
	cout << "3. Tandem" << endl;
	cout << "Enter bike type you would like to rent (number): ";
	cin >> bikeType;
	if (bikeType >= 1 && bikeType <= 3)
	{
		cout << "How many bikes would you like to rent?" << endl;
		cin >> bikesNumber;
		addRentedBikesAmount(bikesNumber);
		for (int i = 0; i < bikesNumber; i++)
		{
			if (rental.getFreeBikes(getLocation()).size() > i)
			{
				addRentedBikeId(rental.getFreeBikes(getLocation())[i]);
				rental.rent(rental.getFreeBikes(getLocation())[i], getId(), database, *this, getLocation(), bikeType - 1);
			}
		}
	}
	else
	{
		cout << "Wrong number!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer;
		if (answer == "y")
			rentBike(rental, database);
		else
			return;
	}
}

void ClientPremium::premiumResignation(UserDataBase& const userBase)
{
	userBase.premiumResignation(getId());
}
