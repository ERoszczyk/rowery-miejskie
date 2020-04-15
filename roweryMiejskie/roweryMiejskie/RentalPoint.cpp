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
	}
	standStates.insert({ 1, 0 });
}


void RentalPoint::rent(int bikeId, int userId, BikeDatabase& database, User& user)
{
	if (find(myBikes.begin(), myBikes.end(), bikeId) != myBikes.end() && database.getBikeState(bikeId) == false)
	{
		Bike bike(bikeId);
		float account = user.getCash();
		bike.StartOfRent(database, userId, account);
		if (database.getBikeState(bikeId))
		{
			bikesFree.erase(find(bikesFree.begin(), bikesFree.end(), bikeId));
			rentedBikes[bikeId] = bike;
		}
	}
	else { cout << "Invalid bike ID"; };
}
void RentalPoint::putBack(int bikeId, int userId, BikeDatabase& database, User& user)
{
	if (getSpaces() > 0) //add if user id matches the one in the databases
	{
		map<int, Record> bikes = database.getAllBikes();
		if (bikes.find(bikeId) != bikes.end())
		{
			rentedBikes.at(bikeId).Stop(database, standStates, user);
			bikesFree.push_back(bikeId);
			rentedBikes.erase(bikeId);
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


