#ifndef Client_h
#define Client_h

//#include <vector>

#include "User.h"
//#include "RentalPoint.h"

class RentalPoint;
class BikeDatabase;

class Client :public User
{
	double cash;
	int rentedBikes;
	vector<int> rentedBikesId;

public:
	Client(const string & userName, const string & userSurname, const string & userUsername, const string & userPassword, const int & id);
	virtual void menu(RentalPoint& rental, BikeDatabase& database);
	
	void transferCash(const double& cash);
	void addRentedBikesAmount(const int& rentedBikes);
	void removeRentedBikes();
	void addRentedBikeId(const int& BikeId);
	void removeRentedBikesId();
	double getCash();
	int getRentedBikes();
	vector<int> getRentedBikesId();

	void changePassword();
	void rentBike(RentalPoint& const rental, BikeDatabase& database);
	void returnBike(RentalPoint& rental, BikeDatabase& database);
	void transferMoney(double money = 0);
	void viewRentedBikes();
};

#endif