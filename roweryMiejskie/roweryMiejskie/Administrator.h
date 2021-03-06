//Plik nagłówkowy klasy Administrator, Ewa Roszczyk, nr. indeksu: 304077
#ifndef Administrator_h
#define Administrator_h

#include "User.h"

class Administrator: public User
{
public:
	Administrator(const std::string& userName, const std::string& userSurname, const std::string& userUsername, const std::string& userPassword, const int& id);
	void menu(MainLocation& rental, BikeDatabase& database, UserDataBase& base);
	void viewRentalPointLocation(MainLocation& rental);
	void disactivateRentalPoint(MainLocation& rental);
	void addBike(MainLocation& rental) {}
	void deleteBike(MainLocation& rental) {}
	void changeUsersPassword(UserDataBase& base);
	void changeUsersName(UserDataBase& base);
	void changeUsersSurname(UserDataBase& base);
	void changeUsersUsername(UserDataBase& base);
	void deleteUser(UserDataBase& base);
	void deleteAdministrator(UserDataBase& base);
	void addNewRentalPoint(MainLocation& rental);
	void addBikeToRentalPoint(MainLocation& rental);
	int chooseLocation(MainLocation& rental);
	int chooseBikeType(MainLocation& rental);
	void deleteBikeFromRentalPoint(MainLocation& rental);
};

#endif
