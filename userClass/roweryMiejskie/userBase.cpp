//Plik zawieraj¹cy funkcje klasy UserBase, Ewa Roszczyk, nr. indeksu: 304077
#include <iostream>
#include "userBase.h"

using namespace std;

UserBase::UserBase()
{
	activeUserId = -1;
}

void UserBase::setUserNames(string userName, string userSurname, string userUsername, string userPassword)
{
	userNames.insert({ getCurrentLoginIndex(), User(userName, userSurname, userUsername, userPassword) });
}

void UserBase::setActiveUserId(int userId)
{
	activeUserId = userId;
}

map<int, User> UserBase::getUserNames()
{
	return userNames;
}

int UserBase::getAvctiveUserId()
{
	return activeUserId;
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

bool UserBase::ifUsernameAvailable(string username)
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
	userNames.insert({ getCurrentLoginIndex(), User(name, surname, username, password) });
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

bool UserBase::ifLogged()
{
	if (activeUserId >= 0)
		return true;
	else
		return false;
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

void UserBase::rentBike()
{
	string loginAnswer, rentAnswer;
	int bikesNumber;
	if (activeUserId >= 0)
	{
		cout << "How many bikes would you like to rent?" << endl;
		cin >> bikesNumber;
		userNames.find(activeUserId)->second.setRentedBikes(bikesNumber);
		for (int i = 0; i < bikesNumber; i++)
			userNames.find(activeUserId)->second.rentedBikesId.push_back(getFreeBikes()[i]);
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

void UserBase::returnBike()
{
	userNames.find(activeUserId)->second.setRentedBikes(0);
	userNames.find(activeUserId)->second.removeRentedBikesId();
}

void UserBase::viewRentedBikes()
{
	if (userNames.find(activeUserId)->second.getRentedBikes() == 0)
		cout << "You don't have any rented bikes" << endl;
	else if (userNames.find(activeUserId)->second.getRentedBikes() == 1)
		cout << "You have " << userNames.find(activeUserId)->second.getRentedBikes() << " rented bike:" << endl;
	else
		cout << "You have " << userNames.find(activeUserId)->second.getRentedBikes() << " rented bikes:" << endl;
	if (userNames.find(activeUserId)->second.getRentedBikesId().size() > 0)
	{
		for (auto i = userNames.find(activeUserId)->second.getRentedBikesId().begin(); i != userNames.find(activeUserId)->second.getRentedBikesId().end(); ++i)
		{
			cout << *i << endl;
		}
	}
}

void UserBase::saveBaseToFile(string filename)
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
