// RentalPoint.h contains declaration of class RentalPoint
// Author: Kinga Kwoka gr.208

//#include "BikeDatabase.h"
#include "Bike.h"

#include <algorithm>
#ifdef _DEBUG
#endif

class RentalPoint
{
	int pointId = 1;
	const int size = 10;
	int bikesCount = 0;
	std::vector<int> myBikes; 
	std::vector<int> bikesFree;
	std::map<int, Bike> rentedBikes; 
	std::map<int, bool> standStates;
public:
	RentalPoint() { defaultStands(); };
	RentalPoint(std::vector<int> bikeIds); //tested
	RentalPoint(BikeDatabase& database); //tested
	~RentalPoint() { bikesCount = 0; myBikes.clear(); }; // wyczyœciæ pamiêæ?
	void setPointId(const int id) { pointId = id; } //dopiero w mniejszych punktach
	int getPointId() const { return pointId; }

	void rent(const int bikeId, const int userId, BikeDatabase& database, User& user); //tested
	void putBack(const int bikeId, const int userId, BikeDatabase& database, User& user); //tested

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

	friend
		std::ostream& operator<< (std::ostream& os, RentalPoint& point); //prints out  point id and bikes ids 
	friend
		std::istream& operator>> (std::istream& is, RentalPoint& point); // takes point id ???? (could take bike ids, reference if exists in database)

};

class RentalLocation : public RentalPoint
{
	string location;
public:
	void setLocation(const string locationName) { location = locationName; };
	string getLocation()const { return location; }
};
