//Plik nag³ówkowy klasy Mechanic, Ewa Roszczyk, nr. indeksu: 304077
#ifndef Mechanic_h
#define Mechanic_h
#include <vector>

#include "user.h"

class MainLocation;
class BikeDatabase;
class UserdDataBase;

class Mechanic :public User
{
	double earnedCash;
	int location;
	std::vector<int> takenBikesId;
public:
	Mechanic(const std::string& userName, const std::string& userSurname, const std::string& userUsername, const std::string& userPassword, const int& id);
	virtual void menu(MainLocation& rental, BikeDatabase& database, UserDataBase& base);
	double getCash();
	void setCash(const double& money);
	std::vector<int> getTakenBikesId();
	void getMoney();
	void viewTakenBikes();
	void changePassword();
	std::string viewLocation(MainLocation& rental);
	void changeLocation(MainLocation& rental);
	void viewRentalPointLocation(MainLocation& rental);
	int chooseLocation(MainLocation& rental);
	void takeBrokenBike(MainLocation& rental);
};

#endif
