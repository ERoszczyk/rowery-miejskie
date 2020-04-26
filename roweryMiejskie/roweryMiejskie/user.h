//Plik nag³ówkowy klasy User, Ewa Roszczyk, nr. indeksu: 304077
#ifndef user_h
#define user_h

#include <iostream>
#include <vector>

using namespace std;

class User
{
	string name;
	string surname;
	string username;
	string password;
	double cash;
	int rentedBikes;
	vector<int> rentedBikesId;

public:
	User(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword);
	void setName(const string& name);
	void setSurname(const string& surname);
	void setUsername(const string& username);
	void setPassword(const string& password);
	void transferCash(const double& cash);
	void addRentedBikesAmount(const int& rentedBikes);
	void removeRentedBikes();
	void addRentedBikeId(const int& BikeId);
	void removeRentedBikesId();
	string getName();
	string getSurname();
	string getUsername();
	string getPassword();
	double getCash();
	int getRentedBikes();
	vector<int> getRentedBikesId();
};

#endif