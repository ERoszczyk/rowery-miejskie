// RentalPoint.cpp contains definitions of class Rental Point methods
// and friend operators
// Author: Kinga Kwoka gr.208

#include "RentalPoint.h"


using namespace std;

RentalLocation::RentalLocation(vector<int> bikeIds)
{
	defaultStands();
	for (int bikeId:bikeIds)
	{
		if (bikesCount < size)
		{
			addBike(bikeId);
		}
		else
		{
#if _DEBUG
			cout << "Too many bikes\n";
#endif
		}
	}
}
RentalLocation::RentalLocation(BikeDatabase& database)
{
	defaultStands();
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
				int standId = findFreeStand();
				takeStand(standId);
				database.setBikeStand(it->first, standId);
			}
		}
	}
}

RentalLocation::RentalLocation(std::map<int, Record> bikes, BikeDatabase& database)
{
	defaultStands();
	map<int, Record> allBikes = database.getAllBikes();
	for (auto it = allBikes.begin(); it != allBikes.end(); ++it)
	{
		if (it->first > 0 && bikesCount < size)
		{
			myBikes.push_back(it->first);
			bikesCount += 1;
			if (database.getBikeState(it->first) == false)
			{
				bikesFree.push_back(it->first);
				int standId = findFreeStand();
				takeStand(standId);
				database.setBikeStand(it->first, standId);
			}
		}
	}
}

void RentalLocation::rent(int bikeId, int userId, BikeDatabase& database, User& user)
{
	if (find(myBikes.begin(), myBikes.end(), bikeId) != myBikes.end() && database.getBikeState(bikeId) == false)
	{
		Bike bike(bikeId);
		int standId = database.getBikeStand(bikeId);
		double account = user.getCash();
		bike.StartOfRent(database, userId, account);
		if (database.getBikeState(bikeId))
		{
			bikesFree.erase(find(bikesFree.begin(), bikesFree.end(), bikeId));
			rentedBikes[bikeId] = bike;
			freeStand(standId);
			bikesCount -= 1;
			
		}
	}
	else { cout << "Invalid bike ID"; };
}

void RentalLocation::putBack(int bikeId, int userId, BikeDatabase& database, User& user)
{
	if (this->getSpaces() > 0) 
	{
		cout << "Free stands:" << endl;      //optional or
		for (int standId : getFreeStands())  //to be moved
		{									//?
			cout << standId << endl;		//
		}									//
		map<int, Record> bikes = database.getAllBikes();
		if (bikes.find(bikeId) != bikes.end())
		{
			rentedBikes.at(bikeId).Stop(database, standStates, user);
			bikesFree.push_back(bikeId);
			rentedBikes.erase(bikeId);
			int standId = database.getBikeStand(bikeId);
			if (standId != 0)
			{
				takeStand(standId);
			}
		}
		else { cout << "Invalid bike ID"; };
	}
	else { cout << "No spaces available"; };
}

void RentalLocation::addBike(int bikeId)
{
	if (bikeId > 0)
	{
		takeStand(findFreeStand());
		myBikes.push_back(bikeId);
		bikesFree.push_back(bikeId);
		bikesCount += 1;
		//change bike stand in database
	}
	else
	{
#if _DEBUG
		cout << "Bike Id out of range";
#endif
	}
}
void RentalLocation::addBikes(vector<int> bikeIds)
{
	for (int bikeId:bikeIds)
	{
		if (bikesCount < size)
		{
			addBike(bikeId);
		}
		else
		{
#if _DEBUG
			cout << "No spaces available";
#endif
		}
	}
}

void RentalLocation::removeBikes(vector<int> bikeIds)
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

void RentalLocation::defaultStands(void)
{
	for (int i = 1; i <= size; i++)
	{
		standStates[i];
	}
}

void RentalLocation::takeStand(int standId)
{
	standStates[standId] = true;
}

void RentalLocation::freeStand(int standId)
{
	standStates[standId] = false;
}

void RentalLocation::freeAllStands(void)
{
	for (auto it = standStates.begin(); it != standStates.end(); ++it)
	{
		it->second = false;
	}
}

int RentalLocation::findFreeStand(void)
{
	int i = 1;
	do{
		if (standStates[i] == false)
		{
			return i;
		}
		i++;

	} while (i < size);
}

std::vector<int> RentalLocation::getFreeStands()
{
	std::vector<int> freeStands;
	for (auto it = standStates.begin(); it != standStates.end(); ++it)
	{
		if (it->second == false)
		{
			freeStands.push_back(it->first);
		}
	}
	return freeStands;
}

ostream& operator<<(ostream& os, RentalPoint& point)
{
	//os << "ID: " << point.getPointId() << endl;
	vector<int> myBikes = point.getBikes();
	for (int i = 0; i < myBikes.size(); i++)
	{
		os << myBikes[i] << "\n";
	}
	return os;
}
istream& operator>>(istream& is, RentalPoint& point)
{
	//is >> point.pointId;
	int id;
	while (is >> id)
	{
		point.addBike(id); 
	}
	return is;
}

MainLocation::MainLocation(std::vector<string> names, BikeDatabase& database) :RentalLocation(database), locationNames(names)
{
	this->setLocation("Main Location");
	for (string name : names)
	{
		locationObjects.insert(pair<string, RentalLocation>(name, RentalLocation(database)));
	}
}

void MainLocation::rent(const int bikeId, const int userId, BikeDatabase& database, User& user, string name)
{
	if (name == "Main Location")
	{
		RentalLocation::rent(bikeId, userId, database,user);
	}
	else
	{
		locationObjects.at(name).rent(bikeId, userId, database, user);
	}

}

void MainLocation::putBack(const int bikeId, const int userId, BikeDatabase& database, User& user, string name)
{
	if (name == "Main Location")
	{
		RentalLocation::putBack(bikeId, userId, database, user);
	}
	else
	{
		locationObjects.at(name).putBack(bikeId, userId, database, user);
	}

}
