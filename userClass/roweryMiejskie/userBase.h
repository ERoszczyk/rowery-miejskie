//Plik nag³ówkowy klasy UserBase, Ewa Roszczyk, nr. indeksu: 304077
#include <iostream>
#include <map>
#include <conio.h>
#include <vector>
#include <fstream>
#include "user.h"

using namespace std;

class UserBase
{
	map<int, User> userNames;
	int activeUserId;  //vector? - mozliwa wieksza ilosc zalogowanych osob

public:
	void setUserNames(string userName, string userSurname, string userUsername, string userPassword);
	void setActiveUserId(int userId);
	map<int, User> getUserNames();
	int getAvctiveUserId();
	UserBase();
	int getCurrentLoginIndex();
	bool ifUsernameAvailable(string username);
	void createNewUser();
	bool ifLogged();
	void login();
	void logout();
	void changePassword();
	void rentBike();
	void returnBike();
	void viewRentedBikes();
	double checkAccountBalance();
	void saveBaseToFile(string filename);
};
