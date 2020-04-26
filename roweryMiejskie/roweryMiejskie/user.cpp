//Plik zawieraj¹cy funkcje klasy User, Ewa Roszczyk, nr. indeksu: 304077
#include "user.h"
#include <iostream>
using namespace std;

User::User(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword)
	: name(userName),
	surname(userSurname),
	username(userUsername),
	password(userPassword),
	cash(20),
	rentedBikes(0)
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

void User::transferCash(const double& usersCash)
{
	cash += usersCash;
}

void User::addRentedBikesAmount(const int& usersRentedBikes)
{
	rentedBikes += usersRentedBikes;
}

void User::removeRentedBikes()
{
	rentedBikes = 0;
}

void User::addRentedBikeId(const int& usersBikeId)
{
	rentedBikesId.push_back(usersBikeId);
}

void User::removeRentedBikesId()
{
	vector<int> noBikes;
	rentedBikesId = noBikes;
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

double User::getCash()
{
	return cash;
}

int User::getRentedBikes()
{
	return rentedBikes;
}

vector<int>User::getRentedBikesId()
{
	return rentedBikesId;
}
