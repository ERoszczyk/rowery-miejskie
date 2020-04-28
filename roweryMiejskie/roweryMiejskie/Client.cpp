//Plik zawieraj¹cy funkcje klasy Client, Ewa Roszczyk, nr. indeksu: 304077
#include <conio.h>
#include "Client.h"
#include "RentalPoint.h"

Client::Client(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& id)
	: User(userName, userSurname, userUsername, userPassword, id),
	cash(20),
	rentedBikes(0)
{
}

void Client::menu(MainLocation& rental, BikeDatabase& database, UserBase& base)
{
	int optionNumber;
	string answer;

	system("CLS");
	cout << "Hello " << getName() << "!" << endl;
	cout << "1. Rent a bike" << endl;
	cout << "2. View rented bike(s)" << endl;
	cout << "3. Return rented bike(s)" << endl;
	cout << "4. View a list of rental points" << endl; // od wypozyczalni
	cout << "5. Transfer money" << endl;
	cout << "6. Check account balance" << endl;
	cout << "7. Check account history" << endl;
	cout << "8. Change password" << endl;
	cout << "9. Log out" << endl;
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
		for (int i = 0; i < rental.getRentalLocationNames().size(); i++)
		{
			cout << i+1 << ". ";
			cout << rental.getRentalLocationNames()[i] << endl;
		}
        break;
    case 5:
        transferMoney();
        break;
    case 6:
        cout << getCash() << endl;
        break;
    case 7:
        cout << "This option is not available yet" << endl;
        break;
    case 8:
        changePassword();
        break;
    case 9:
		return;
        break;
    default:
        cout << "Wrong number!" << endl;
        break;
    }
    cout << "Would you like to continue? (y/n) ";
    cin >> answer;
    if (answer == "y")
    {
        menu(rental, database, base);
    }
    else
    {
		cout << "You've been logged out" << endl;
        return;
    }
}

void Client::transferCash(const double& usersCash)
{
	cash += usersCash;
}

void Client::addRentedBikesAmount(const int& usersRentedBikes)
{
	rentedBikes += usersRentedBikes;
}

void Client::removeRentedBikes()
{
	rentedBikes = 0;
}

void Client::addRentedBikeId(const int& usersBikeId)
{
	rentedBikesId.push_back(usersBikeId);
}

void Client::removeRentedBikesId()
{
	vector<int> noBikes;
	rentedBikesId = noBikes;
}

double Client::getCash()
{
	return cash;
}

int Client::getRentedBikes()
{
	return rentedBikes;
}

vector<int>Client::getRentedBikesId()
{
	return rentedBikesId;
}

void Client::changePassword()
{
	string currentPassword = "", newPassword = "", answer;
	char character;
	cout << "Enter your current password: " << endl;
	character = _getch();
	while (character != 13)
	{
		currentPassword.push_back(character);
		cout << "*";
		character = _getch();
	}
	cout << endl;
	while (currentPassword != getPassword())
	{
		cout << "Wrong password!" << endl;
		cout << "Do you want to try again? (y/n) ";
		cin >> answer;
		if (answer != "y")
		{
			cout << "You haven't changed your password" << endl;
			return;
		}
		cout << "Enter your current password once more: " << endl;
		currentPassword = "";
		character = _getch();
		while (character != 13)
		{
			currentPassword.push_back(character);
			cout << "*";
			character = _getch();
		}
		cout << endl;
	}
	cout << "Enter new password:" << endl;
	character = _getch();
	while (character != 13)
	{
		newPassword.push_back(character);
		cout << "*";
		character = _getch();
	}
	cout << endl;
	setPassword(newPassword);
}

void Client::rentBike(MainLocation& const rental, BikeDatabase& database)
{
	string loginAnswer, rentAnswer;
	int bikesNumber;
	cout << "How many bikes would you like to rent?" << endl;
	cin >> bikesNumber;
	addRentedBikesAmount(bikesNumber);
	for (int i = 0; i < bikesNumber; i++)
	{
		if (rental.getFreeBikes().size() > i)
		{
			addRentedBikeId(rental.getFreeBikes()[i]);
			rental.rent(rental.getFreeBikes()[i], getId(), database, *this, "another location");
		}
	}
}

void Client::returnBike(MainLocation& rental, BikeDatabase& database)
{
	vector<int> rentedBikesId = getRentedBikesId();
	removeRentedBikes();
	for (int i = 0; i < rentedBikesId.size(); i++)
		rental.putBack(rentedBikesId[i], getId(), database, *this);
	removeRentedBikesId();
}

void Client::transferMoney(double money)
{
	if (money == 0)
	{
		cout << "Enter how much would you like to transer: " << endl;
		cin >> money;
	}
	transferCash(money);
}

void Client::viewRentedBikes()
{
	if (getRentedBikes() == 0)
		cout << "You don't have any rented bikes" << endl;
	else if (getRentedBikes() == 1)
		cout << "You have " << getRentedBikes() << " rented bike:" << endl;
	else
		cout << "You have " << getRentedBikes() << " rented bikes:" << endl;
	vector<int> rentedBikesId = getRentedBikesId();
	if (rentedBikesId.size() > 0)
	{
		for (auto i = rentedBikesId.begin(); i != rentedBikesId.end(); ++i)
		{
			cout << *i << endl;
		}
	}
}
