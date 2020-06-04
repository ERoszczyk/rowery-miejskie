//Plik zawieraj¹cy funkcje klasy User, Ewa Roszczyk, nr. indeksu: 304077 
#include "user.h"
#include <iostream>
using namespace std;

User::User(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& userId)
	: name(userName),
	surname(userSurname),
	username(userUsername),
	password(userPassword),
	id(userId)
{
}

void User::setName(const string& usersName)
{
	name = usersName;
}

void User::setSurname(const string& usersSurname)
{
	surname = usersSurname;
}

void User::setUsername(const string& usersUsername)
{
	username = usersUsername;
}

void User::setPassword(const string& usersPassword)
{
	password = usersPassword;
}

string User::getName()
{
	return name;
}

string User::getSurname()
{
	return surname;
}

string User::getUsername()
{
	return username;
}

string User::getPassword()
{
	return password;
}

int User::getId()
{
	return id;
}

User::~User()
{
	delete[] & name;
	delete[] & surname;
	delete[] & username;
	delete[] & password;
	delete[] & id;
}
