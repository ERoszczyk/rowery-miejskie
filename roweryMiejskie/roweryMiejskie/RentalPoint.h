// RentalPoint.h contains declaration of class RentalPoint
// Author: Kinga Kwoka gr.208
#ifndef RentalPoint_h
#define RentalPoint_h

//#include "BikeDatabase.h"
#include "Bike.h"
#include "ElectricBike.h"
#include "Tandem.h"

#include <algorithm>
#ifdef _DEBUG
#endif

class RentalPoint
{
public:
	virtual ~RentalPoint()=0 {};

	virtual void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user, int bikeType)=0;
	virtual void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user, int bikeType)=0;

	virtual void addBike(const int bikeId) = 0;
	virtual void addBike(const int bikeId, BikeDatabase& database) = 0;
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
	//std::map<int, ElectricBike& > rentedElectrics;
	std::map<int, Tandem> rentedTandems;
	std::map<int, bool> standStates;
	std::vector<string> bikeTypes = {"Bike", "Electric Bike", "Tandem"};

public:
	RentalLocation() { defaultStands(); };
	RentalLocation(std::vector<int> bikeIds, BikeDatabase& database); //tested
	RentalLocation(BikeDatabase& database); //tested
	RentalLocation(std::map<int, Record> bikes, BikeDatabase& database);
	~RentalLocation() { bikesCount = 0; myBikes.clear(); };//?

	void setPointId(const int id) { pointId = id; }
	int getPointId() const { return pointId; }

    void setLocation(const string locationName) { location = locationName; };
	string getLocation()const { return location; }

	void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user, int bikeType=0); //tested
	void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user, int bikeType =0); //tested
	void putBackOtherLocation(const int bikeId, const int userId, BikeDatabase& database, Client& user, RentalLocation& otherLocation);

	void addBike(const int bikeId); 
	void addBike(const int bikeId, BikeDatabase& base); 
	void addBikes(const std::vector<int> bikeIds, BikeDatabase& base);

	void removeBike(const int bikeId, BikeDatabase& base);
	void removeBikes(const std::vector<int> bikeIds); //tested

	void disactivateLocation(BikeDatabase& base);

	void defaultStands(void);
	void takeStand(const int standId);
	void freeStand(const int standId);
	void freeAllStands(void);

	int findFreeStand(void);
	std::vector<int> getFreeStands();

	std::vector<int> getBikes() const { return myBikes; }
	std::vector<int> getFreeBikes() const { return bikesFree; }
	std::map<int, Bike> getRentedBikes() const { return rentedBikes; };
	int getSpaces() const { return size - bikesCount; } //done
	std::vector<string> getBikeTypes() { return bikeTypes; }

};


class MainLocation : public RentalLocation
{
	std::vector<string> locationNames;
	std::map<string, RentalLocation> locationObjects;
	BikeDatabase& base;
public:
	MainLocation(std::vector<string>names, BikeDatabase& database);
	void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user, int nameId = -1); //tested
	void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user, int nameId = 1); //tested
	vector<string> getRentalLocationNames() const { return locationNames; }
	void addBike(const int bikeId, int nameId = -1);
	void removeBike(const int bikeId, int nameId = -1);
	void disactivateLocation(int nameId = -1);
	std::vector<int> getFreeBikes(int nameId = 0) const;
};

#endif