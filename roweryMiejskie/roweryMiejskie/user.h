//Plik nag³ówkowy klasy User, Ewa Roszczyk, nr. indeksu: 304077
#ifndef user_h
#define user_h

#include <iostream>
#include <vector>

class MainLocation;
class BikeDatabase;

using namespace std;

class User
{
	string name;
	string surname;
	string username;
	string password;
	int id;

public:
	User(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& userId);
	void setName(const string& name);
	void setSurname(const string& surname);
	void setUsername(const string& username);
	void setPassword(const string& password);
	string getName();
	string getSurname();
	string getUsername();
	string getPassword();
	int getId();

	virtual void menu(MainLocation& rental, BikeDatabase& database) = 0;
};

#endif