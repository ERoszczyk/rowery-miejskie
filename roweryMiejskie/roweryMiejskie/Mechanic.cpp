//Plik zawieraj¹cy funkcje klasy Mechanic, Ewa Roszczyk, nr. indeksu: 304077
#include <iostream>
#include <conio.h>
#include "Mechanic.h"
#include "RentalPoint.h"

using namespace std;

Mechanic::Mechanic(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& id)
	: User(userName, userSurname, userUsername, userPassword, id),
	earnedCash(0),
    location(-1)
{
}

void Mechanic::menu(MainLocation& rental, BikeDatabase& database, UserDataBase& base)
{
	int optionNumber;
	string answer;

	system("CLS");
	cout << "Hello " << getName() << "!" << endl;
	cout << "1. Get bike(s) to repair it(them)" << endl;
	cout << "2. View taken bike(s)" << endl;
	cout << "3. Return repaired bike(s)" << endl;
	cout << "4. View location" << endl;
	cout << "5. Change location" << endl;
	cout << "6. View a list of rental points" << endl;
	cout << "7. Get money" << endl;
	cout << "8. Check account balance" << endl;
	cout << "9. Check account history" << endl;
	cout << "10. Change password" << endl;
	cout << "11. Log out" << endl;
	cout << "Enter what would you like to do: ";
	cin >> optionNumber;
    switch (optionNumber)
    {
    case 1:
        cout << "This option is not available yet" << endl; //od wypo¿yczalni
        break;
    case 2:
        viewTakenBikes();
        break;
    case 3:
        cout << "This option is not available yet" << endl; //od wypo¿yczalni
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
        getMoney();
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

double Mechanic::getCash()
{
    return earnedCash;
}

void Mechanic::setCash(const double& money)
{
    earnedCash += money;
}

vector<int>Mechanic::getTakenBikesId()
{
    return takenBikesId;
}

void Mechanic::getMoney()
{
    double money;
    string answer;

    cout << "How much money would you like to get?" << endl;
    cin >> money;
    if (money < 0)
        cout << "Wrong number!" << endl;
    else if (money <= earnedCash)
    {
        setCash(-money);
        cout << "You got " << money << endl;
        return;
    }
    else
    {
        cout << "You have only " << earnedCash << endl;
        cout << "Would you like to try again? (y/n) ";
        cin >> answer;
    }
    if (answer == "y")
        getMoney();
}

void Mechanic::viewTakenBikes()
{
    if (getTakenBikesId().size() == 0)
        cout << "You don't have any rented bikes" << endl;
    else if (getTakenBikesId().size() == 1)
        cout << "You have " << getTakenBikesId().size() << " rented bike:" << endl;
    else
        cout << "You have " << getTakenBikesId().size() << " rented bikes:" << endl;
    vector<int> takenBikesId = getTakenBikesId();
    if (takenBikesId.size() > 0)
    {
        for (auto i = takenBikesId.begin(); i != takenBikesId.end(); ++i)
        {
            cout << *i << endl;
        }
    }
}

void Mechanic::changePassword()
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

string Mechanic::viewLocation(MainLocation& rental)
{
    string localization = "Your current location: ";
    if (location == -1)
        localization.append("Main location");
    else
        localization.append(rental.getRentalLocationNames()[location]);
    localization.append(" \n");
    return localization;
}

void Mechanic::changeLocation(MainLocation& rental)
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

void Mechanic::viewRentalPointLocation(MainLocation& rental)
{
    for (int i = 0; i < rental.getRentalLocationNames().size(); i++)
    {
        cout << i + 1 << ". ";
        cout << rental.getRentalLocationNames()[i] << endl;
    }
    cout << rental.getRentalLocationNames().size() + 1 << ". Main location" << endl;
}
