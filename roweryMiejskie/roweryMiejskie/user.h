//Plik nag³ówkowy klasy User, Ewa Roszczyk, nr. indeksu: 304077
#include <iostream>
#include <vector>

using namespace std;

class User
{
	string name;
	string surname;
	string username;
	string password;
	double cash;
	int rentedBikes;
	vector<int> rentedBikesId;

public:
	User(string userName, string userSurname, string userUsername, string userPassword);
	void setName(string name);
	void setSurname(string surname);
	void setUsername(string username);
	void setPassword(string password);
	void setCash(double cash);
	void addRentedBikesAmount(int rentedBikes);
	void removeRentedBikes();
	void addRentedBikeId(int BikeId);
	void removeRentedBikesId();
	string getName();
	string getSurname();
	string getUsername();
	string getPassword();
	double getCash();
	int getRentedBikes();
	vector<int> getRentedBikesId();
};