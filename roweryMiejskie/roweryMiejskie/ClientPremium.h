//Plik nag³ówkowy klasy ClientPremium, Ewa Roszczyk, nr. indeksu: 304077
#ifndef ClientPremium_h
#define ClientPremium_h
//#include <vector>

#include "Client.h"

class MainLocation;
class BikeDatabase;
class UserDataBase;

class ClientPremium : public Client
{
public:
	ClientPremium(const std::string& userName, const std::string& userSurname, const std::string& userUsername, const std::string& userPassword, const int& id);
	void rentBike(MainLocation& const rental, BikeDatabase& database);
	virtual void menu(MainLocation& rental, BikeDatabase& database, UserDataBase& userBase);
	void premiumResignation(UserDataBase& const userBase);
};

#endif