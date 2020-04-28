// RentalPoint.h contains declaration of class RentalPoint
// Author: Kinga Kwoka gr.208
#ifndef RentalPoint_h
#define RentalPoint_h

//#include "BikeDatabase.h"
#include "Bike.h"

#include <algorithm>
#ifdef _DEBUG
#endif

class RentalPoint
{
public:
	virtual ~RentalPoint()=0 {};

	virtual void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user)=0;
	virtual void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user)=0;

	virtual void addBike(const int bikeId) = 0;
	/*virtual void addBikes(const std::vector<int> bikeIds)=0;
	virtual void removeBikes(const std::vector<int> bikeIds)=0;

	virtual void defaultStands(void)=0;
	virtual void takeStand(const int standId)=0;
	virtual void freeStand(const int standId)=0;
	virtual void freeAllStands(void)=0;

	virtual int findFreeStand(void)=0;*/
	virtual std::vector<int> getFreeStands()=0;

	virtual std::vector<int> getBikes() const = 0;
	virtual std::vector<int> getFreeBikes() const = 0;
	//virtual int getSpaces() const = 0; 

	friend
		std::ostream& operator<< (std::ostream& os, RentalPoint& point); 
	friend
		std::istream& operator>> (std::istream& is, RentalPoint& point); 

};

class RentalLocation : public RentalPoint
{
protected:
	string location = "";	
	int pointId = 1;
	const int size = 10;
	int bikesCount = 0;
	std::vector<int> myBikes;
	std::vector<int> bikesFree;
	std::map<int, Bike> rentedBikes;
	std::map<int, bool> standStates;

public:
	RentalLocation() { defaultStands(); };
	RentalLocation(std::vector<int> bikeIds); //tested
	RentalLocation(BikeDatabase& database); //tested
	RentalLocation(std::map<int, Record> bikes, BikeDatabase& database);
	~RentalLocation() { bikesCount = 0; myBikes.clear(); };//?

	void setPointId(const int id) { pointId = id; }
	int getPointId() const { return pointId; }

    void setLocation(const string locationName) { location = locationName; };
	string getLocation()const { return location; }

	void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user); //tested
	void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user); //tested

	void addBike(const int bikeId); //tested
	void addBikes(const std::vector<int> bikeIds); //tested
	void removeBikes(const std::vector<int> bikeIds); //tested

	void defaultStands(void);
	void takeStand(const int standId);
	void freeStand(const int standId);
	void freeAllStands(void);

	int findFreeStand(void);
	std::vector<int> getFreeStands();

	std::vector<int> getBikes() const { return myBikes; }
	std::vector<int> getFreeBikes() const { return bikesFree; }
	int getSpaces() const { return size - bikesCount; } //done


};


class MainLocation : public RentalLocation
{
	std::vector<string> locationNames;
	std::map<string, RentalLocation> locationObjects;
public:
	MainLocation(std::vector<string>names, BikeDatabase& database);
	void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user, string name="Main Location"); //tested
	void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user, string name="Main Location"); //tested
};


#endif