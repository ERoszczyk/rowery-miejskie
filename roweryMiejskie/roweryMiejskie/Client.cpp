//Plik zawierający funkcje klasy Client, Ewa Roszczyk, nr. indeksu: 304077
#include <conio.h>
#include "Client.h"
#include "RentalPoint.h"

Client::Client(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& id)
	: User(userName, userSurname, userUsername, userPassword, id),
	cash(20),
	location(-1),
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
	cout << "4. View location" << endl;
	cout << "5. Change location" << endl;
	cout << "6. View a list of rental points" << endl;
	cout << "7. Transfer money" << endl;
	cout << "8. Check account balance" << endl;
	cout << "9. Check account history" << endl;
	cout << "10. Change password" << endl;
	cout << "11. Log out" << endl;
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
		if (rental.getFreeBikes(location).size() > i)
		{
			addRentedBikeId(rental.getFreeBikes(location)[i]);
			rental.rent(rental.getFreeBikes(location)[i], getId(), database, *this, location);
		}
	}
}

void Client::returnBike(MainLocation& rental, BikeDatabase& database)
{
	vector<int> rentedBikesId = getRentedBikesId();
	removeRentedBikes();
	for (int i = 0; i < rentedBikesId.size(); i++)
		rental.putBack(rentedBikesId[i], getId(), database, *this, location);
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

string Client::viewLocation(MainLocation& rental)
{
	string localization = "Your current location: ";
	if (location == -1)
		localization.append("Main location");
	else
		localization.append(rental.getRentalLocationNames()[location]);
	localization.append(" \n");
	return localization;
}

void Client::changeLocation(MainLocation& rental)
{
	int newLocation;
	string answer;
	cout << viewLocation(rental);
	viewRentalPointLocation(rental);
	cout << "Enter new location number: ";
	cin >> newLocation;
	if (newLocation < 1 || newLocation > rental.getRentalLocationNames().size() + 1)
	{
		cout << "Wrong location number!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer;
		if (answer == "y")
			changeLocation(rental);
		else
			return;
	}
	else if (newLocation == rental.getRentalLocationNames().size() + 1)
		location = -1;
	else
		location = newLocation - 1;
}

void Client::viewRentalPointLocation(MainLocation& rental)
{
	for (int i = 0; i < rental.getRentalLocationNames().size(); i++)
	{
		cout << i + 1 << ". ";
		cout << rental.getRentalLocationNames()[i] << endl;
	}
	cout << rental.getRentalLocationNames().size() + 1 << ". Main location" << endl;
}
