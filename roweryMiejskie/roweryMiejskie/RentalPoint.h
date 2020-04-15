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
	std::map<int,Bike> rentedBikes; 
	std::map<int, bool> standStates;
public:
	RentalPoint() {};
	RentalPoint(std::vector<int> bikeIds); //tested
	RentalPoint(BikeDatabase database); //tested
	~RentalPoint() { bikesCount = 0; myBikes.clear(); }; // wyczyœciæ pamiêæ?
	void setPointId(int id) { pointId = id; } //dopiero w mniejszych punktach
	int getPointId() { return pointId; }

	void rent(int bikeId, int userId, BikeDatabase& database, User& user); //tested
	void putBack(int bikeId, int userId, BikeDatabase& database, User& user); //tested

	void addBike(int bikeId); //tested
	void addBikes(std::vector<int> bikeIds); //tested
	void removeBikes(std::vector<int> bikeIds); //tested

	std::vector<int> getBikes() { return myBikes; } 
	std::vector<int> getFreeBikes() { return bikesFree; }
	int getSpaces() { return size - bikesCount; } //done

	friend
		std::ostream& operator<< (std::ostream& os, RentalPoint& point); //prints out  point id and bikes ids 
	friend
		std::istream& operator>> (std::istream& is, RentalPoint& point); // takes point id ???? (could take bike ids, reference if exists in database)

};
