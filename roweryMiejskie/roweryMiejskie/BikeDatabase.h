// BikeDatabase.h contains declaration of class BikeDatabase and structure Record
// Author: Kinga Kwoka gr.208

#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#ifdef _DEBUG
#endif

struct Record
{
	bool state = false;
	int user = 0; //default as no user
	int stand = 0; //default as no stand  (ie.if both 0= out of use)
public:
	Record() = default;
	bool getState() const { return state; };
	void setState(const bool newState) { state = newState; };
	int getUser() { return user; };
	void setUser(int newUser) { user = newUser; };
	int getStand() { return stand; };
	void setStand(int newStand) { stand = newStand; };
	friend
		std::ostream& operator<< (std::ostream& os, Record& database);
	friend
		std::istream& operator>> (std::istream& os, Record& record);
};

class BikeDatabase
{
	std::map<int,Record> allBikes;
	int idCount = 0;
public:
	BikeDatabase() {};
	BikeDatabase(int newBikes) { addBikes(newBikes); }; //constructs a database of a given size
	BikeDatabase(std::vector<Record> newBikes) { addBikes(newBikes); }; // ie.bikes sorted by production number

	void addBike(void); //tested
	void addBike(Record); //tested

	void addBikes(int);
	void addBikes(std::vector<Record>); //tested
	void addBikes(std::map<int, Record>); //tested in testing operator+

	void removeBike(int bikeId) { allBikes.erase(bikeId); }
	void removeBikes(std::vector<int> bikeIds) { for (int i = 0; i < bikeIds.size(); i++) { removeBike(i); } };

	bool getBikeState(int bikeId) { return allBikes.at(bikeId).getState(); };
	void setBikeState(int bikeId, bool state) { allBikes.at(bikeId).setState(state); };

	int getBikeOwner(int bikeId) { return allBikes.at(bikeId).getUser(); };  
	void setBikeOwner(int bikeId, int userId) { allBikes.at(bikeId).setUser(userId); };

	int getBikeStand(int bikeId) { return allBikes.at(bikeId).getStand(); };
	void setBikeStand(int bikeId, int standId) { allBikes.at(bikeId).setStand(standId); };

	const std::map<int, Record> getAllBikes() { return allBikes; }; // 
	const Record getBike(int bikeId) { return allBikes.at(bikeId); } // 

	void exportToFile(std::string filename = "database.txt"); //tested
	void importFromFile(std::string filename = "database.txt"); //tested
	BikeDatabase operator+(const BikeDatabase& database) const; //tested

	friend
		std::ostream& operator<< (std::ostream& os, BikeDatabase& database);
	friend
		std::istream& operator>> (std::istream& is, BikeDatabase& point); 
};
