//Plik zawieraj¹cy funkcje klasy UserBase, Ewa Roszczyk, nr. indeksu: 304077
#include <iostream>
#include <conio.h>
#include <fstream>

#include "UserDataBase.h"

using namespace std;

UserDataBase::UserDataBase()
{
	userNames.insert({0, new Administrator("Administrator", "Przykladowy", "admin", "haslo", 0)});
	userNames.insert({1, new Client("Uzytkownik", "Przykladowy", "user", "haslo", 1) });
	userNames.insert({ 2, new ClientPremium("Uzytkownik", "Premium", "premium", "haslo", 2) });
	userNames.insert({ 3, new Mechanic("Mechanik", "Przykladowy", "mechanik", "haslo", 3) });
}

// To (tzn. menu i obs³ugê wejœcia/wyjœcia lepiej odseparowaæ logiki przechowywania uzytkowników 

void UserDataBase::menuStart(MainLocation& rental, BikeDatabase& database)
{
	int optionNumber;
	string answer;

	system("CLS");
	cout << "You're not logged in" << endl;
	cout << "1. Log in" << endl;
	cout << "2. Sign up" << endl;
	cout << "Enter what would you like to do: ";
	cin >> optionNumber;

	switch (optionNumber)
	{
	case 1:
		login(rental, database);
		break;
	case 2:
		createNewUser();
		break;
	default:
		cout << "Wrong number!" << endl;
		break;
	}
	cout << "Would you like to continue? (y/n) ";
	cin >> answer;
	if (answer == "y")
		menuStart(rental, database);
	else
		return;
}

void UserDataBase::addNewUser(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword)
{
	int id = getCurrentLoginIndex();
	userNames.insert({ id, new Client(userName, userSurname, userUsername, userPassword, id) });
}

void UserDataBase::addNewAdministrator(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword)
{
	int id = getCurrentLoginIndex();
	userNames.insert({ id, new Administrator(userName, userSurname, userUsername, userPassword, id) });
}

map<int, User*> UserDataBase::getUserNames()
{
	return userNames;
}

bool UserDataBase::ifUsernameExists(const string& username)
{
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (username == i->second->getUsername())
			return true;
	}
	return false;
}

int UserDataBase::getCurrentLoginIndex()
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

bool UserDataBase::ifUsernameAvailable(const string& username)
{
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (username == i->second->getUsername())
			return false;
	}
	return true;
}


void UserDataBase::createNewUser()
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

void UserDataBase::createNewUserAsAdministrator()
{
	string name, surname, username, password = "";
	char character;
	cout << "Enter user's first name: " << endl;
	cin >> name;
	cout << "Enter user's surname: " << endl;
	cin >> surname;
	cout << "Enter user's username: " << endl;
	cin >> username;
	while (!ifUsernameAvailable(username))
	{
		cout << "This username is already taken. Enter another one: " << endl;
		cin >> username;
	}
	cout << "Enter user's password: " << endl;
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

void UserDataBase::createNewAdministrator()
{
	string name, surname, username, password = "";
	char character;
	cout << "Enter administrator's first name: " << endl;
	cin >> name;
	cout << "Enter administrator's surname: " << endl;
	cin >> surname;
	cout << "Enter administrator's username: " << endl;
	cin >> username;
	while (!ifUsernameAvailable(username))
	{
		cout << "This username is already taken. Enter another one: " << endl;
		cin >> username;
	}
	cout << "Enter administrator's password: " << endl;
	character = _getch();
	while (character != 13)
	{
		password.push_back(character);
		cout << "*";
		character = _getch();
	}
	cout << endl;
	addNewAdministrator(name, surname, username, password);
}

void UserDataBase::login(MainLocation& rental, BikeDatabase& database)
{
	string username, tryAgainAnswer, password = "";
	char character;
	bool wrongUsername = true;
	cout << "Enter your username: " << endl;
	cin >> username;
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (username == i->second->getUsername())
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
			if (password == i->second->getPassword())
			{
				cout << "Hello " << username << "! " << "You're logged in!" << endl;
				//activeUserId = i->first;
				i->second->menu(rental, database, *this);
				return;
			}
			else
			{
				cout << "Wrong password!" << endl;
				cout << "Do you want to try again? (y/n) ";
				cin >> tryAgainAnswer;
				if (tryAgainAnswer == "y")
					login(rental, database);
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
			login(rental, database);
		else
			return;
	}
}

void UserDataBase::changeUsernameAsAdministrator(const string& currentUsername, const string& newUsername)
{
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (currentUsername == i->second->getUsername())
		{
			i->second->setUsername(newUsername);
		}
	}
}

void UserDataBase::changePasswordAsAdministrator(const string& username, const string& newPassword)
{
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (username == i->second->getUsername())
		{
			i->second->setPassword(newPassword);
		}
	}
}

void UserDataBase::changeNameAsAdministrator(const string& username, const string& newName)
{
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (username == i->second->getUsername())
		{
			i->second->setName(newName);
		}
	}
}

void UserDataBase::changeSurnameAsAdministrator(const string& username, const string& newSurname)
{
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (username == i->second->getUsername())
		{
			i->second->setSurname(newSurname);
		}
	}
}

void UserDataBase::deleteUserAsAdministrator(const string& username)
{
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		if (username == i->second->getUsername())
		{
			auto it = userNames.find(i->second->getId());
			userNames.erase(it);
			break;
		}
	}
}

void UserDataBase::premiumActivation(const int& userId, MainLocation& rental, BikeDatabase& database)
{
	userNames.find(userId)->second = static_cast<ClientPremium*>(userNames.find(userId)->second);
	//userNames.find(userId)->second->menu(rental, database, *this);
}

void UserDataBase::premiumResignation(const int& userId)
{
	userNames.find(userId)->second = static_cast<Client*>(userNames.find(userId)->second);
}

void UserDataBase::exportBaseToFile(const string& filename)
{
	ofstream file(filename);
	file << "User's ID" << '\t' << "User's name" << '\t' << "User's surname" << '\t' << "User's username" << '\t' << "User's password" << endl;
	for (auto i = userNames.begin(); i != userNames.end(); ++i)
	{
		file << i->first << '\t' << i->second->getName() << '\t' << i->second->getSurname() << '\t' << i->second->getUsername() << '\t';
		for (int j = 0; j < i->second->getPassword().length(); j++)
			file << "*";
		file << endl;
	}
	file.close();
}
