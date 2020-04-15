// RentalPoint.cpp contains definitions of class Rental Point methods
// and friend operators
// Author: Kinga Kwoka gr.208

#include "RentalPoint.h"


using namespace std;

RentalPoint::RentalPoint(vector<int> bikeIds)
{
	for (int i = 0; i < bikeIds.size(); i++)
	{
		if (bikesCount < size)
		{
			addBike(bikeIds[i]);
		}
		else
		{
#if _DEBUG
			cout << "Too many bikes\n";
#endif
		}
	}
}
RentalPoint::RentalPoint(BikeDatabase database)
{
	map<int, Record> allBikes = database.getAllBikes();
	for (auto it = allBikes.begin(); it != allBikes.end(); ++it)
	{
		if (it->first > 0 && bikesCount<size)
		{
			myBikes.push_back(it->first);
			bikesCount += 1;
			if (database.getBikeState(it->first) == false)
			{
				bikesFree.push_back(it->first);
			}
		}
#if _DEBUG
		cout << "Too many bikes or invalid bike ID\n";
#endif
	}
}


void RentalPoint::rent(int bikeId, int userId, BikeDatabase& database)
{
	if (find(myBikes.begin(), myBikes.end(), bikeId) != myBikes.end() && database.getBikeState(bikeId) == false)
	{
		Bike bike(bikeId);
		//bike.StartOfRent(database, userId, userNames(userId)->second.getCash());
		database.setBikeState(bikeId, true);
		database.setBikeOwner(bikeId, userId);
		database.setBikeStand(bikeId, 0);
		bikesFree.erase(find(bikesFree.begin(), bikesFree.end(), bikeId));
		/*Bike bike;
		bike.rent(bikeId, userId);
		bikesRented.push_back(pair(bikeId, bike));*/  //example for merging with Bike
	}
	else { cout << "Invalid bike ID"; };
}
void RentalPoint::putBack(int bikeId, int userId, BikeDatabase& database)
{
	if (getSpaces() > 0) //add if user id matches the one in the databases
	{
		map<int, Record> bikes = database.getAllBikes();
		if (bikes.find(bikeId) != bikes.end())
		{
			/*auto it = bikesRented.at(bikeId);
			Bike bike = it->second;
			bike.putback(bikeId, userId);*/    //example for merging with Bike
			database.setBikeState(bikeId, false);
			database.setBikeOwner(bikeId, 0);
			database.setBikeStand(bikeId, 1);
			bikesFree.push_back(bikeId);
		}
		else { cout << "Invalid bike ID"; };
	}
	else { cout << "No spaces available"; };
}

void RentalPoint::addBike(int bikeId)
{
	if (bikeId > 0)
	{	
		myBikes.push_back(bikeId);
		bikesFree.push_back(bikeId);
		bikesCount += 1;
	}
	else
	{
#if _DEBUG
		cout << "Bike Id out of range";
#endif
	}
}
void RentalPoint::addBikes(vector<int> bikeIds)
{
	for (int i = 0; i < bikeIds.size(); i++)
	{
		if (bikesCount < size)
		{
			addBike(bikeIds[i]);
		}
		else
		{
#if _DEBUG
			cout << "No spaces available";
#endif
		}
	}
}

void RentalPoint::removeBikes(vector<int> bikeIds)
{
	for (int i = 0; i < bikeIds.size(); i++)
	{
		if (find(myBikes.begin(), myBikes.end(), bikeIds[i]) != myBikes.end())
		{
			myBikes.erase(find(myBikes.begin(), myBikes.end(), bikeIds[i]));
			bikesCount -= 1; 
		}
		else
		{
#if _DEBUG
			cout << "Invalid bike ID";
#endif
		}
	}
}

ostream& operator<<(ostream& os, RentalPoint& point)
{
	os << "ID: " << point.getPointId() << endl;
	vector<int> myBikes = point.getBikes();
	for (int i = 0; i < myBikes.size(); i++)
	{
		os << myBikes[i] << "\n";
	}
	return os;
}
istream& operator>>(istream& is, RentalPoint& point)
{
	is >> point.pointId;
	int id;
	while (is >> id)
	{
		point.addBike(id); 
	}
	return is;
}