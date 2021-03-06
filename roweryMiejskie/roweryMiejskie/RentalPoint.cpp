// RentalPoint.cpp contains definitions of class Rental Point methods
// and friend operators
// Author: Kinga Kwoka gr.208

#include "RentalPoint.h"


using namespace std;

RentalLocation::RentalLocation(vector<int> bikeIds, BikeDatabase& database)
{
	defaultStands();
	for (int bikeId:bikeIds)
	{
		if (bikesCount < size)
		{
			addBike(bikeId, database);
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
				if (database.isBikeBroken(it->first))
				{
					brokenBikes.push_back(it->first);
				}
				else
				{
					bikesFree.push_back(it->first);
				}				
				int standId = findFreeStand();
				takeStand(standId);
				database.setBikeStand(it->first, standId);
			}
		}
	}
}

RentalLocation::RentalLocation(std::map<int, Record> allBikes, BikeDatabase& database)
{
	defaultStands();
	for (auto it = allBikes.begin(); it != allBikes.end(); ++it)
	{
		if (it->first > 0 && bikesCount < size)
		{
			myBikes.push_back(it->first);
			bikesCount += 1;
			if (database.getBikeState(it->first) == false)
			{
				if (database.isBikeBroken(it->first))
				{
					brokenBikes.push_back(it->first);
				}
				else
				{
					bikesFree.push_back(it->first);
				}
				int standId = findFreeStand();
				takeStand(standId);
				database.setBikeStand(it->first, standId);
			}
		}
	}
}

void RentalLocation::rent(int bikeId, int userId, BikeDatabase& database, Client& user, int bikeType)
{
	if (find(myBikes.begin(), myBikes.end(), bikeId) != myBikes.end() && database.getBikeState(bikeId) == false)
	{
		int standId = database.getBikeStand(bikeId);
		double account = user.getCash();
		Bike *bike = new Bike(bikeId);
		ElectricBike *ebike = new ElectricBike(bikeId);
		Tandem *tbike = new Tandem(bikeId);
		switch (bikeType)
		{
		case(0):
			bike->StartOfRent(database, userId, account, user);
			if (database.getBikeState(bikeId))
			{
				bikesFree.erase(find(bikesFree.begin(), bikesFree.end(), bikeId));
				rentedBikes[bikeId] = bike;
				freeStand(standId);
				bikesCount -= 1;
			}
			break;
		case(1):
			ebike->StartOfRent(database, userId, account, user);
			if (database.getBikeState(bikeId))
			{
				bikesFree.erase(find(bikesFree.begin(), bikesFree.end(), bikeId));
				rentedBikes[bikeId] = ebike;
				freeStand(standId);
				bikesCount -= 1;
			}
			break;
		case(2):
			tbike->StartOfRent(database, userId, account, user);
			if (database.getBikeState(bikeId))
			{
				bikesFree.erase(find(bikesFree.begin(), bikesFree.end(), bikeId));
				rentedBikes[bikeId] = tbike;
				freeStand(standId);
				bikesCount -= 1;

			}
			break;
		}
	
		
	}
	else { cout << "Invalid bike ID (no bikes in this location)"; };
}

void RentalLocation::putBack(int bikeId, int userId, BikeDatabase& database, Client& user)
{
	if (this->getSpaces() > 0) 
	{
		map<int, Record> bikes = database.getAllBikes();
		if (bikes.find(bikeId) != bikes.end())
		{
			
			rentedBikes.at(bikeId)->Stop(database, standStates, user);
			rentedBikes.erase(bikeId);
			
			if (database.getAllBikes().at(bikeId).isBroken())
			{
				brokenBikes.push_back(bikeId);
			}
			else
			{
				bikesFree.push_back(bikeId);
			}
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

void RentalLocation::putBackOtherLocation(int bikeId, int userId, BikeDatabase& database, Client& user, RentalLocation& otherLocation)
{
	int bikeType = otherLocation.determineBikeType(bikeId, database);
	if (otherLocation.getSpaces() > 0)
	{
		
		map<int, Record> bikes = database.getAllBikes();
		if (bikes.find(bikeId) != bikes.end())
		{
			rentedBikes.at(bikeId)->Stop(database, otherLocation.standStates, user);
			if (database.getAllBikes().at(bikeId).isBroken())
			{
				otherLocation.brokenBikes.push_back(bikeId);
			}
			else
			{
				otherLocation.bikesFree.push_back(bikeId);
			}
			otherLocation.myBikes.push_back(bikeId);
			rentedBikes.erase(bikeId);
			int standId = database.getBikeStand(bikeId);
			if (standId != 0)
			{
				otherLocation.takeStand(standId);
			}
		}
		else { cout << "Invalid bike ID"; };
		
	}
	else { cout << "No spaces available"; };

}
void RentalLocation::takeBroken(const int bikeId, const int techId, BikeDatabase& database, Mechanic& tech)
{
	if (find(myBikes.begin(), myBikes.end(), bikeId) != myBikes.end() && database.getBikeState(bikeId) == false)
	{
		int standId = database.getBikeStand(bikeId);
		brokenBikes.erase(find(brokenBikes.begin(), brokenBikes.end(), bikeId));
		database.setBikeOwner(bikeId, techId);
		database.setBikeState(bikeId, 1);
		freeStand(standId);
		bikesCount -= 1;
	}
}
void RentalLocation::returnFixed(const int bikeId, const int techId, BikeDatabase& database, Mechanic& tech)
{
	if (this->getSpaces() > 0)
	{
		map<int, Record> bikes = database.getAllBikes();
		if (bikes.find(bikeId) != bikes.end())
		{
			myBikes.at(bikeId);
			bikesFree.push_back(bikeId);
			database.setBikeOwner(bikeId, 0);
			database.setBikeState(bikeId, 0);
			int standId = findFreeStand();
			database.setBikeStand(bikeId, standId);
			if (standId != 0)
			{
				takeStand(standId);
			}
			database.fix(bikeId);
		}
	}
}
void RentalLocation::returnFixedOtherLocation(const int bikeId, const int techId, BikeDatabase& database, Mechanic& tech, RentalLocation& otherLocation)
{
	if (otherLocation.getSpaces() > 0)
	{
		map<int, Record> bikes = database.getAllBikes();
		if (bikes.find(bikeId) != bikes.end())
		{
			
			//brokenBikes.erase(find(brokenBikes.begin(), brokenBikes.end(), bikeId));
			otherLocation.bikesFree.push_back(bikeId);
			otherLocation.myBikes.push_back(bikeId);
			myBikes.erase(find(myBikes.begin(), myBikes.end(), bikeId));
			int standId = otherLocation.findFreeStand();
			if (standId != 0)
			{
				otherLocation.takeStand(standId);
			}
			database.setBikeOwner(bikeId, 0);
			database.setBikeState(bikeId, 0);
			database.setBikeStand(bikeId, standId);
			database.fix(bikeId);
		}
		else { cout << "Invalid bike ID"; };

	}
	else { cout << "No spaces available"; };
}
void RentalLocation::addBike(int bikeId)
{
	if (bikeId > 0 && bikesCount < size)
	{
		int stand = findFreeStand();
		takeStand(stand);
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
void RentalLocation::addBike(int bikeType, BikeDatabase& base)
{
	if (bikesCount < size)
	{
		int newBikeId = base.addBike();
		int stand = findFreeStand();
		takeStand(stand);
		myBikes.push_back(newBikeId);
		bikesFree.push_back(newBikeId);
		bikesCount += 1;
		base.setBikeStand(newBikeId, stand);
		base.setBikeType(newBikeId, bikeType);
	};
}
void RentalLocation::addBikes(vector<int> bikeIds, BikeDatabase& database)
{
	for (int bikeId:bikeIds)
	{
		if (bikesCount < size)
		{
			addBike(bikeId, database);
		}
		else
		{
#if _DEBUG
			cout << "No spaces available";
#endif
		}
	}
}
void RentalLocation::removeBike(const int bikeId, BikeDatabase& base)
{
	std::map<int, Record> bikes = base.getAllBikes();
	if (bikes.find(bikeId)!=bikes.end())
	{
		if (find(bikesFree.begin(), bikesFree.end(), bikeId) != bikesFree.end())
		{
			int stand = base.getBikeStand(bikeId);
			myBikes.erase(find(myBikes.begin(), myBikes.end(), bikeId));
			bikesFree.erase(find(bikesFree.begin(), bikesFree.end(), bikeId));
			freeStand(stand);
			base.removeBike(bikeId);
			bikesCount -= 1;
		}
		else if (find(brokenBikes.begin(), brokenBikes.end(), bikeId) != brokenBikes.end())
		{
			int stand = base.getBikeStand(bikeId);
			myBikes.erase(find(myBikes.begin(), myBikes.end(), bikeId));
			brokenBikes.erase(find(brokenBikes.begin(), brokenBikes.end(), bikeId));
			freeStand(stand);
			base.removeBike(bikeId);
			bikesCount -= 1;
		}
	}
}

void RentalLocation::removeBikes(vector<int> bikeIds, BikeDatabase& base)
{
	for (int bikeId:bikeIds)
	{
		removeBike(bikeId, base);
	}
}

void RentalLocation::disactivateLocation(BikeDatabase& base)
{
	if (rentedBikes.size() == 0)
	{
		freeAllStands();
		for (int bikeId : bikesFree)
		{
			base.setBikeStand(bikeId, 0);
		}
		myBikes.clear();
		active = false;

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

std::vector<int> RentalLocation::getFreeBikes(BikeDatabase& base, int bikeType ) const
{
	std::vector<int> freeBikesForType;
	for (int bikeId : bikesFree)
	{
		if (base.getAllBikes().at(bikeId).getType() == bikeType)
		{
			freeBikesForType.push_back(bikeId);
		}
	}
	return freeBikesForType;
}
int RentalLocation::determineBikeType(const int bikeId, BikeDatabase& database)
{
	if (rentedBikes.find(bikeId) != rentedBikes.end())
	{
		return database.getAllBikes().at(bikeId).getType();
	}
	
}

ostream& operator<<(ostream& os, RentalPoint& point)
{
	vector<int> myBikes = point.getBikes();
	for (int i = 0; i < myBikes.size(); i++)
	{
		os << myBikes[i] << "\n";
	}
	return os;
}
istream& operator>>(istream& is, RentalPoint& point)
{
	int id;
	while (is >> id)
	{
		point.addBike(id); 
	}
	return is;
}

///////////////////////////////////////////////////////////////////////////////////////////////

MainLocation::MainLocation(std::vector<string> names, BikeDatabase& database) :RentalLocation(database), locationNames(names), base(database)
{
	this->setLocation("Main Location");

	for (string name : names)
	{
		std::map<int, Record> bikes = database.getAllBikes();
		std::map<int, Record> tempBikes;
		for (auto it = bikes.begin(); it != bikes.end(); ++it)
		{
			if (it->second.getStand() == 0 && it->second.getUser() == 0)
			{
				tempBikes.insert(pair<int, Record>(it->first, it->second));
			}
		}
		RentalLocation rental(tempBikes, database);
		locationObjects.insert(pair<string, RentalLocation>(name, rental));
	}
}

void MainLocation::rent(const int bikeId, Client& user, int nameId, int bikeType)
{

	if (nameId == -1)
	{
		RentalLocation::rent(bikeId, user.getId(), base,user, bikeType);
	}
	else
	{
		locationObjects.at(locationNames[nameId]).rent(bikeId, user.getId(), base, user, bikeType);
	}

}

void MainLocation::putBack(const int bikeId, Client& user, int nameId)
{
	if (nameId == -1)
	{
		try
		{
			RentalLocation::putBack(bikeId, user.getId(), base, user);
		}
		catch (std::out_of_range)
		{
			for (string location : locationNames)
			{
				std::map<int, Bike*> bikes = locationObjects.at(location).getRentedBikes();
				if (bikes.find(bikeId) != bikes.end())
				{
					locationObjects.at(location).putBackOtherLocation(bikeId, user.getId(), base, user, *this);
				}
			}
		}
	}
	else
	{
		try
		{
			locationObjects.at(locationNames[nameId]).putBack(bikeId, user.getId(), base, user);
		}
		catch (std::out_of_range)
		{
			for (string location : locationNames)
			{
				std::map<int, Bike*> bikes = locationObjects.at(location).getRentedBikes();
				string key = locationNames[nameId];
				std::map<int, Bike*> thisBikes = this->getRentedBikes();
				if (bikes.find(bikeId) != bikes.end())
				{
					locationObjects.at(location).putBackOtherLocation(bikeId, user.getId(), base, user,locationObjects[key]);
				}
				else if(thisBikes.find(bikeId)!=thisBikes.end())
				{
					this->putBackOtherLocation(bikeId, user.getId(), base, user, locationObjects[key]);
				}
			}
		}
	}

}

void MainLocation::addBike(const int bikeType, int nameId)
{
	if (nameId == -1)
	{
		RentalLocation::addBike(bikeType, this->base);
	}
	else
	{
		locationObjects.at(locationNames[nameId]).addBike(bikeType, this -> base);
	}
}

void MainLocation::removeBike(const int bikeId, int nameId)
{
	if (nameId == -1)
	{
		RentalLocation::removeBike(bikeId, this->base);
	}
	else
	{
		locationObjects.at(locationNames[nameId]).removeBike(bikeId, this->base);
	}
}
void MainLocation::disactivateLocation(int nameId)
{
	if (nameId == -1)
	{
		RentalLocation::disactivateLocation(base);
	}
	else
	{
		locationObjects.at(locationNames[nameId]).disactivateLocation(base);
	}
}
void MainLocation::addLocation(std::string name)
{
	if (find(locationNames.begin(), locationNames.end(), name) == locationNames.end())
	{
		locationNames.push_back(name);
		std::map<int, Record> bikes = base.getAllBikes();
		std::map<int, Record> tempBikes;
		for (auto it = bikes.begin(); it != bikes.end(); ++it)
		{
			if (it->second.getStand() == 0 && it->second.getUser() == 0)
			{
				tempBikes.insert(pair<int, Record>(it->first, it->second));
			}
		}
		RentalLocation rental(tempBikes, base);
		locationObjects.insert(pair<string, RentalLocation>(name, rental));
	}
	else
	{
		cout << "Location already exists.\n";
	}
}

std::vector<int> MainLocation::getFreeBikes(int nameId, int bikeType) const
{
	if (nameId == -1)
	{
		return RentalLocation::getFreeBikes(base, bikeType);
	}
	else
	{
		return locationObjects.at(locationNames[nameId]).getFreeBikes(base, bikeType);
	}
}

std::vector<int> MainLocation::getBrokenBikes(int nameId) const
{
	if (nameId == -1)
	{
		return RentalLocation::getBrokenBikes();
	}
	else
	{
		return locationObjects.at(locationNames[nameId]).getBrokenBikes();
	}
}

void MainLocation::takeBroken(const int bikeId, Mechanic& tech, int nameId)
{
	if (nameId == -1)
	{
		RentalLocation::takeBroken(bikeId, tech.getId(), base, tech);
	}
	else
	{
		locationObjects.at(locationNames[nameId]).takeBroken(bikeId, tech.getId(), base, tech);
	}
}

void MainLocation::returnFixed(const int bikeId, Mechanic& tech, int nameId)
{
	if (nameId == -1)
	{
		try
		{
			RentalLocation::returnFixed(bikeId, tech.getId(), base, tech);
		}
		catch (std::out_of_range)
		{
			for (string location : locationNames)
			{
				std::map<int, Bike*> bikes = locationObjects.at(location).getRentedBikes();
				if (bikes.find(bikeId) != bikes.end())
				{
					locationObjects.at(location).returnFixedOtherLocation(bikeId, tech.getId(), base, tech, *this);
				}
			}
		}
	}
	else
	{
		try
		{
			locationObjects.at(locationNames[nameId]).returnFixed(bikeId, tech.getId(), base, tech);
		}
		catch (std::out_of_range)
		{
			for (string location : locationNames)
			{
				std::vector<int> bikes = locationObjects.at(location).getBikes();
				string key = locationNames[nameId];
				std::vector<int> thisBikes = this->getBikes();
				if (find(bikes.begin(), bikes.end(),bikeId) != bikes.end())
				{
					locationObjects.at(location).returnFixedOtherLocation(bikeId, tech.getId(), base, tech, locationObjects[key]);
					break;
				}
				else if (find(thisBikes.begin(), thisBikes.end(),bikeId) != thisBikes.end())
				{
					this->returnFixedOtherLocation(bikeId, tech.getId(), base, tech, locationObjects[key]);
					break;
				}
			}
		}
	}
}