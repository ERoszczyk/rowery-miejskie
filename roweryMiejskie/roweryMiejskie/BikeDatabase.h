// BikeDatabase.h contains declaration of class BikeDatabase and structure Record
// Author: Kinga Kwoka gr.208
#ifndef BikeDatabase_h
#define BikeDatabase_h

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
	bool state = false; //default as free
	int user = 0; //default as no user
	int stand = 0; //default as no stand  (ie.if both 0= out of use)
public:
	Record() {};
	bool getState() const { return state; };
	void setState(const bool newState) { state = newState; };
	int getUser() const { return user; };
	void setUser(const int newUser) { user = newUser; };
	int getStand() const { return stand; };
	void setStand(const int newStand) { stand = newStand; };
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
	void addBike(const Record); //tested
	void addBike(const int bikeId, const Record);

	void addBikes(const int);
	void addBikes(const std::vector<Record>); //tested
	void addBikes(const std::map<int, Record>); //tested in testing operator+

	void removeBike(const int bikeId) { allBikes.erase(bikeId); }
	void removeBikes(const std::vector<int> bikeIds) { for (int bikeId:bikeIds) { removeBike(bikeId); } };

	bool getBikeState(int bikeId) const { return allBikes.at(bikeId).getState(); };
	void setBikeState(const int bikeId, const bool state) { allBikes.at(bikeId).setState(state); };

	int getBikeOwner(int bikeId) const { return allBikes.at(bikeId).getUser(); };  
	void setBikeOwner(const int bikeId, const int userId) { allBikes.at(bikeId).setUser(userId); };

	int getBikeStand(int bikeId) const { return allBikes.at(bikeId).getStand(); };
	void setBikeStand(const int bikeId, const int standId) { allBikes.at(bikeId).setStand(standId); };

	std::map<int, Record> getAllBikes() const { return allBikes; }; // 
	Record getBike(int bikeId) const { return allBikes.at(bikeId); } // 

	void exportToFile(std::string filename = "database.txt"); //tested
	void importFromFile(std::string filename = "database.txt"); //tested
	BikeDatabase operator+(const BikeDatabase& database) const; //tested

	friend
		std::ostream& operator<< (std::ostream& os, BikeDatabase& database);
	friend
		std::istream& operator>> (std::istream& is, BikeDatabase& point); 
};

#endif
