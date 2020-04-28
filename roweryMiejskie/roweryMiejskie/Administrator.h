#ifndef Administrator_h
#define Administrator_h

#include "User.h"

class Administrator: public User
{
	bool ifAdministrator;

public:
	Administrator(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& id);
	void menu(RentalPoint& rental, BikeDatabase& database);
};

#endif
