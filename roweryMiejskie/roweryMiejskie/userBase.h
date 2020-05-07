//Plik nag��wkowy klasy UserBase, Ewa Roszczyk, nr. indeksu: 304077
#ifndef userBase_h
#define userBase_h

//#include <iostream>
#include <map>
//#include <conio.h> -> lepiej do cpp
//#include <vector>  
#include <fstream> //-> lepiej do cpp
#include "Administrator.h"
#include "Client.h"

class MainLocation;
class BikeDatabase;

using namespace std; // Nie wolno (nie powinno si�) wstawia� w plikach nag��wkowych!!

class UserBase  //Mo�e UsersDataBase? 
{
	map<int, User*> userNames;

public:
	UserBase();
	void menuStart(MainLocation& rental, BikeDatabase& database);
	void addNewUser(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword);
	void addNewAdministrator(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword);
	map<int, User*> getUserNames();
	bool ifUsernameExists(const string& username);
	int getCurrentLoginIndex();
	bool ifUsernameAvailable(const string& username);

	// To do odr�bnej klasy
   void createNewUser();
	void createNewUserAsAdministrator();
	void createNewAdministrator();

   void login(MainLocation& rental, BikeDatabase& database, UserBase& base);
	void changeUsernameAsAdministrator(const string& currentUsername, const string& newUsername);
	void changePasswordAsAdministrator(const string& username, const string& newPassword);
	void changeNameAsAdministrator(const string& username, const string& newName);
	void changeSurnameAsAdministrator(const string& username, const string& newSurname);
	void deleteUserAsAdministrator(const string& username);
	void exportBaseToFile(const string& filename);
};

#endif
