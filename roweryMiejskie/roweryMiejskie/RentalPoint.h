// RentalPoint.h contains declaration of class RentalPoint
// Author: Kinga Kwoka gr.208
#ifndef RentalPoint_h
#define RentalPoint_h

//#include "BikeDatabase.h"
#include "Bike.h"
#include "ElectricBike.h"
//#include <string>
#include "Tandem.h"
#include "Mechanic.h"

#include <algorithm>
#ifdef _DEBUG
#endif

class RentalPoint
{
public:
	virtual ~RentalPoint() = 0 {};

	virtual void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user, int bikeType)=0;
	virtual void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user)=0;

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
	virtual std::vector<int> getFreeBikes(BikeDatabase& database, const int bikeType) const = 0;
	virtual std::vector<int> getBrokenBikes() const = 0;
	//virtual int getSpaces() const = 0; 

	friend
		std::ostream& operator<< (std::ostream& os, RentalPoint& point); 
	friend
		std::istream& operator>> (std::istream& is, RentalPoint& point); 

};

class RentalLocation : public RentalPoint
{
protected:
	std::string location = "";	
	int pointId = 1;
	const int size = 10;
	int bikesCount = 0;
	bool active = true;
	std::vector<int> myBikes;
	std::vector<int> bikesFree;
	std::vector<int> brokenBikes;

	std::map<int, Bike*> rentedBikes;
	std::map<int, bool> standStates;

   
	std::vector<std::string> bikeTypes = {"Bike", "Electric Bike", "Tandem"};

public:
	RentalLocation() { defaultStands(); };
	RentalLocation(std::vector<int> bikeIds, BikeDatabase& database); //tested
	RentalLocation(BikeDatabase& database); //tested
	RentalLocation(std::map<int, Record> bikes, BikeDatabase& database);
	~RentalLocation() { bikesCount = 0; myBikes.clear(); };//? =default

	void setPointId(const int id) { pointId = id; }
	int getPointId() const { return pointId; }

    void setLocation(const std::string locationName) { location = locationName; };
	std::string getLocation()const { return location; }

	void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user, int bikeType = 0) override; // mo¿na dodaæ //tested
	void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user); //tested
	void putBackOtherLocation(const int bikeId, const int userId, BikeDatabase& database, Client& user, RentalLocation& otherLocation);

	void takeBroken(const int bikeId, const int techId, BikeDatabase& database, Mechanic& tech);
	void returnFixed(const int bikeId, const int techId, BikeDatabase& database, Mechanic& tech);
	void returnFixedOtherLocation(const int bikeId, const int techId, BikeDatabase& database, Mechanic& tech, RentalLocation& otherLocation);

	void addBike(const int bikeId); 
	void addBike(const int bikeId, BikeDatabase& base); 
	void addBikes(const std::vector<int> bikeIds, BikeDatabase& base);

	void removeBike(const int bikeId, BikeDatabase& base);
	void removeBikes(const std::vector<int> bikeIds, BikeDatabase& base); //tested

	void disactivateLocation(BikeDatabase& base);
	bool isActive()const { return active; }

	void defaultStands(void);
	void takeStand(const int standId);
	void freeStand(const int standId);
	void freeAllStands(void);

	int findFreeStand(void);
	std::vector<int> getFreeStands();

	std::vector<int> getBikes() const { return myBikes; }
	std::vector<int> getFreeBikes(BikeDatabase& base, int bikeType = 0) const;
	std::map<int, Bike*> getRentedBikes() const { return rentedBikes; };
	std::vector<int> getBrokenBikes() const { return brokenBikes; }

	int getSpaces() const { return size - bikesCount; } //done

	std::vector<std::string> getBikeTypes() { return bikeTypes; }
	int determineBikeType(const int bikeId, BikeDatabase& database);
};


class MainLocation : public RentalLocation
{
	std::vector<std::string> locationNames;
	std::map<std::string, RentalLocation> locationObjects;
	BikeDatabase& base;

public:
	MainLocation(std::vector<std::string> names, BikeDatabase& database);
	void rent(const int bikeId, const int userId, BikeDatabase& database, Client& user, int nameId = -1, int bikeType = 0); //tested
	void putBack(const int bikeId, const int userId, BikeDatabase& database, Client& user, int nameId = -1); //tested
	std::vector<std::string> getRentalLocationNames() const { return locationNames; }
	void addBike(const int bikeId, int nameId = -1);
	void removeBike(const int bikeId, int nameId = -1);
	void disactivateLocation(int nameId = -1);
	std::vector<int> getFreeBikes(int nameId = -1, int bikeType = 0) const;
	std::vector<int> getBrokenBikes(int nameId = -1) const;
	void takeBroken(const int bikeId, const int techId, BikeDatabase& database, Mechanic& tech, int nameId = -1);
	void returnFixed(const int bikeId, const int techId, BikeDatabase& database, Mechanic& tech, int nameId = -1);
};

#endif