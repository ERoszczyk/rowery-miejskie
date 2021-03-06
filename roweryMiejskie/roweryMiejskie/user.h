//Plik nagłówkowy klasy User, Ewa Roszczyk, nr. indeksu: 304077
#ifndef user_h
#define user_h

#include <vector>
#include <string>

class MainLocation;
class BikeDatabase;
class UserDataBase;


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
	virtual void menu(MainLocation& rental, BikeDatabase& database, UserDataBase& base) = 0;
	virtual ~User();
};

#endif