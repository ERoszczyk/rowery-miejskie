//Plik nag³ówkowy klasy Client, Ewa Roszczyk, nr. indeksu: 304077
#ifndef Client_h
#define Client_h
#include <vector>

#include "User.h"

class MainLocation;
class BikeDatabase;
class UserdDataBase;

class Client :public User
{
	double cash;
	int location;
	int rentedBikes;
	std::vector<int> rentedBikesId;

public:
	Client(const std::string & userName, const std::string & userSurname, const std::string & userUsername, const std::string & userPassword, const int & id);
	virtual void menu(MainLocation& rental, BikeDatabase& database, UserDataBase& base);

	void transferCash(const double& cash);
	void addRentedBikesAmount(const int& rentedBikes);
	void removeRentedBikes();
	void addRentedBikeId(const int& BikeId);
	void removeRentedBikesId();
	double getCash();
	int getRentedBikes();
	int getLocation();
	std::vector<int> getRentedBikesId();
	void changePassword();
	void rentBike(MainLocation& const rental, BikeDatabase& database);
	void returnBike(MainLocation& rental, BikeDatabase& database);
	void transferMoney(double money = 0);
	void viewRentedBikes();
	std::string viewLocation(MainLocation& rental);
	void changeLocation(MainLocation& rental);
	void viewRentalPointLocation(MainLocation& rental);
};

#endif