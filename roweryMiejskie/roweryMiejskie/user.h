//Plik nag³ówkowy klasy User, Ewa Roszczyk, nr. indeksu: 304077
#ifndef user_h
#define user_h

//#include <iostream>
#include <vector>
#include <string>

class MainLocation;
class BikeDatabase;
class UserBase;

// using namespace std;  Nie wolno (nie powinno siê) wstawiaæ w plikach nag³ówkowych!!

class User
{
	std::string name;
	std::string surname;
	std::string username;
	std::string password;
	int id;

public:
	User(const std::string& userName, const std::string& userSurname, const std::string& userUsername, const std::string& userPassword, const int& userId);
	void setName(const std::string& name);
	void setSurname(const std::string& surname);
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	std::string getName();
	std::string getSurname();
	std::string getUsername();
	std::string getPassword();
	int getId();
	virtual void menu(MainLocation& rental, BikeDatabase& database, UserBase& base) = 0;

   //na wszelki wypadek lepiej dodaæ wirtualny destruktor
};

#endif