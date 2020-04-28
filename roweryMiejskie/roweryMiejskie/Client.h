//Plik nag³ówkowy klasy Client, Ewa Roszczyk, nr. indeksu: 304077
#ifndef Client_h
#define Client_h

//#include <vector>

#include "User.h"
//#include "RentalPoint.h"

class MainLocation;
class BikeDatabase;
class UserBase;

class Client :public User
{
	double cash;
	int rentedBikes;
	vector<int> rentedBikesId;

public:
	Client(const string & userName, const string & userSurname, const string & userUsername, const string & userPassword, const int & id);
	virtual void menu(MainLocation& rental, BikeDatabase& database, UserBase& base);
	
	void transferCash(const double& cash);
	void addRentedBikesAmount(const int& rentedBikes);
	void removeRentedBikes();
	void addRentedBikeId(const int& BikeId);
	void removeRentedBikesId();
	double getCash();
	int getRentedBikes();
	vector<int> getRentedBikesId();

	void changePassword();
	void rentBike(MainLocation& const rental, BikeDatabase& database);
	void returnBike(MainLocation& rental, BikeDatabase& database);
	void transferMoney(double money = 0);
	void viewRentedBikes();
};

#endif