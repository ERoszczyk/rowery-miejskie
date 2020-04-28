//Plik nag³ówkowy klasy UserBase, Ewa Roszczyk, nr. indeksu: 304077
#ifndef userBase_h
#define userBase_h

#include <iostream>
#include <map>
#include <conio.h>
#include <vector>
#include <fstream>
//#include "RentalPoint.h"
#include "Administrator.h"
#include "Client.h"

class MainLocation;
class BikeDatabase;

using namespace std;

class UserBase
{
	map<int, User*> userNames;
	int activeUserId;  //vector? - mozliwa wieksza ilosc zalogowanych osob

public:
	UserBase();
	void menuStart(MainLocation& rental, BikeDatabase& database);
	void addNewUser(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword);
	void setActiveUserId(const int& userId);
	int getActiveUserId();
	map<int, User*> getUserNames();
	int getCurrentLoginIndex();
	bool ifUsernameAvailable(const string& username);
	void createNewUser();
	bool ifLogged();
	void login(MainLocation& rental, BikeDatabase& database);
	void logout();
	/*double checkAccountBalance();
	void changePassword();
	void rentBike(RentalPoint& const rental, BikeDatabase& database);
	void returnBike(RentalPoint& rental, BikeDatabase& database);
	void transferMoney(double money = 0);
	void viewRentedBikes();*/
	void saveBaseToFile(const string& filename);  //aministrator
};

#endif
