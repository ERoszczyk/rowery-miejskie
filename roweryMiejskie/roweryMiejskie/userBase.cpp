//Plik zawieraj¹cy funkcje klasy UserBase, Ewa Roszczyk, nr. indeksu: 304077
#include <iostream>
#include "userBase.h"

using namespace std;

UserBase::UserBase()
{
	activeUserId = -1;
}

void UserBase::addNewUser(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword)
{
	userNames.insert({ getCurrentLoginIndex(), User(userName, userSurname, userUsername, userPassword) });
}

void UserBase::setActiveUserId(const int& userId)
{
	activeUserId = userId;
}

int UserBase::getActiveUserId()
{
	return activeUserId;
}

map<int, User> UserBase::getUserNames()
{
	return userNames;
}

int UserBase::getCurrentLoginIndex()
{
	if (userNames.size() == 0)
	{
		return 0;
	}
	else
	{
		int lastIndex = userNames.rbegin()->first;
		return lastIndex + 1;
	}

}

bool UserBase::ifUsernameAvailable(const string& username)
{
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (username == i->second.getUsername())
			return false;
	}
	return true;
}


void UserBase::createNewUser()
{
	string name, surname, username, password = "";
	char character;
	cout << "Enter your first name: " << endl;
	cin >> name;
	cout << "Enter your surname: " << endl;
	cin >> surname;
	cout << "Enter your username: " << endl;
	cin >> username;
	while (!ifUsernameAvailable(username))
	{
		cout << "This username is already taken. Enter another one: " << endl;
		cin >> username;
	}
	cout << "Enter your password: " << endl;
	character = _getch();
	while (character != 13)
	{
		password.push_back(character);
		cout << "*";
		character = _getch();
	}
	cout << endl;
	addNewUser(name, surname, username, password);
}

bool UserBase::ifLogged()
{
	if (activeUserId >= 0)
		return true;
	else
		return false;
}

void UserBase::login()
{
	string username, tryAgainAnswer, password = "";
	char character;
	bool wrongUsername = true;
	if (ifLogged())
		cout << "You're already logged in!" << endl;
	else
	{
		cout << "Enter your username: " << endl;
		cin >> username;
		for (auto i = userNames.begin(); i != userNames.end(); ++i)
		{
			if (username == i->second.getUsername())
			{
				wrongUsername = false;
				cout << "Enter your password: " << endl;
				character = _getch();
				while (character != 13)
				{
					password.push_back(character);
					cout << "*";
					character = _getch();
				}
				cout << endl;
				if (password == i->second.getPassword())
				{
					cout << "Hello " << username << "! " << "You're logged in!" << endl;
					activeUserId = i->first;
					return;
				}
				else
				{
					cout << "Wrong password!" << endl;
					cout << "Do you want to try again? (y/n) ";
					cin >> tryAgainAnswer;
					if (tryAgainAnswer == "y")
						login();
					else
						return;
				}
			}
		}
		if (wrongUsername)
		{
			cout << "Wrong username!" << endl;
			cout << "Do you want to try again? (y/n) ";
			cin >> tryAgainAnswer;
			if (tryAgainAnswer == "y")
				login();
			else
				return;
		}
	}
}

void UserBase::logout()
{
	string answer;
	cout << "Are you sure you want to log out? (y/n) ";
	cin >> answer;
	if (answer == "y")
		activeUserId = -1;
	else
		return;
}

double UserBase::checkAccountBalance()
{
	string answer;
	if (ifLogged())
		return userNames.find(activeUserId)->second.getCash();
	else
	{
		cout << "You're not logged in! Do you want to log in now? (y/n) ";
		cin >> answer;
		if (answer == "y")
		{
			login();
			return userNames.find(activeUserId)->second.getCash();
		}
		else
		{
			cout << "You're not logged in! We cannot check your account!" << endl;
			return -1;
		}
	}
}

void UserBase::changePassword()
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
	while (currentPassword != userNames.find(activeUserId)->second.getPassword())
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
	userNames.find(activeUserId)->second.getPassword() = newPassword;
}

void UserBase::rentBike(RentalPoint& const rental, BikeDatabase& database)
{
	string loginAnswer, rentAnswer;
	int bikesNumber;
	if (activeUserId >= 0)
	{
		cout << "How many bikes would you like to rent?" << endl;
		cin >> bikesNumber;
		userNames.find(activeUserId)->second.addRentedBikesAmount(bikesNumber);
		for (int i = 0; i < bikesNumber; i++)
		{
			if (rental.getFreeBikes().size() > i)
			{
				userNames.find(activeUserId)->second.addRentedBikeId(rental.getFreeBikes()[i]);
				rental.rent(rental.getFreeBikes()[i], getActiveUserId(), database, userNames.find(activeUserId)->second);
			}
		}
	}
	else
	{
		cout << "You're not logged in! Do you want to log in now? (y/n) ";
		cin >> loginAnswer;
		if (loginAnswer == "y")
		{
			login();

		}
		else
		{
			cout << "You're not logged in! We cannot check your account!" << endl;
			return;
		}
	}
}

void UserBase::returnBike(RentalPoint& rental, BikeDatabase& database)
{
	vector<int> rentedBikesId = userNames.find(activeUserId)->second.getRentedBikesId();
	userNames.find(activeUserId)->second.removeRentedBikes();
	for (int i = 0; i < rentedBikesId.size(); i++)
		rental.putBack(rentedBikesId[i], getActiveUserId(), database, userNames.find(activeUserId)->second);
	userNames.find(activeUserId)->second.removeRentedBikesId();
}

void UserBase::transferMoney(double money)
{
	if (money == 0)
	{
		cout << "Enter how much would you like to transer: " << endl;
		cin >> money;
	}
	userNames.find(activeUserId) -> second.transferCash(money);
}

void UserBase::viewRentedBikes()
{
	if (userNames.find(activeUserId)->second.getRentedBikes() == 0)
		cout << "You don't have any rented bikes" << endl;
	else if (userNames.find(activeUserId)->second.getRentedBikes() == 1)
		cout << "You have " << userNames.find(activeUserId)->second.getRentedBikes() << " rented bike:" << endl;
	else
		cout << "You have " << userNames.find(activeUserId)->second.getRentedBikes() << " rented bikes:" << endl;
	vector<int> rentedBikesId = userNames.find(activeUserId)->second.getRentedBikesId();
	if (rentedBikesId.size() > 0)
	{
		for (auto i = rentedBikesId.begin(); i != rentedBikesId.end(); ++i)
		{
			cout << *i << endl;
		}
	}
}

void UserBase::saveBaseToFile(const string& filename)
{
	ofstream file(filename);
	file << "User's ID" << '\t' << "User's name" << '\t' << "User's surname" << '\t' << "User's username" << '\t' << "User's password" << endl;
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		file << i->first << '\t' << i->second.getName() << '\t' << i->second.getSurname() << '\t' << i->second.getUsername() << '\t';
		for (int j = 0; j < i->second.getPassword().length(); j++)
			file << "*";
		file << endl;
	}
	file.close();
}
