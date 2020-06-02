// BikeDatabase.cpp: contains definition of class BikeDatabse methods
// and friend operator for BikeDatabase and Record
// Author: Kinga Kwoka gr.208


#include "BikeDatabase.h"


using namespace std;

int BikeDatabase::addBike()
{
	int newId = 1;
	if (allBikes.size() != 0)
	{
		newId = allBikes.rbegin()->first + 1;
	}
	Record empty;
	allBikes.insert(pair<int, Record>(newId, empty)); 
	return newId;
}
void BikeDatabase::addBike(Record newRecord)
{
	int newId = 1;
	if (allBikes.size() != 0)
	{
		newId = allBikes.rbegin()->first + 1;
	}
	allBikes.insert(pair<int, Record>(newId, newRecord)); 
	idCount++;
}
void BikeDatabase::addBike(int bikeId, Record newRecord)
{
	allBikes.insert(pair<int, Record>(bikeId, newRecord));
}

void BikeDatabase::addBikes(int newBikes)
{
	for (int i = 0; i < newBikes; i++)
	{
		addBike();
	}
}
void BikeDatabase::addBikes(const vector<Record>& newBikes)
{
	for (auto it = newBikes.begin(); it != newBikes.end(); ++it)
	{
		addBike(*it);
	}
}
void BikeDatabase::addBikes(map<int, Record> newBikes)
{
	for (auto it = newBikes.begin(); it != newBikes.end(); ++it)
	{
		addBike(it->second);
	}
};

void BikeDatabase::exportToFile(string filename)
{
	ofstream file1(filename);
	if (file1.is_open())
	{
		file1 << *this; 
	}
	else
	{
#if _DEBUG
		cout << "Unable to open file " << filename;
#endif
	}
	file1.close();
}

void BikeDatabase::importFromFile(string filename)
{
	ifstream file2(filename);
	if (file2.is_open())
	{
		file2 >> *this;
	}
	else
	{
#if _DEBUG
		cout << "Unable to open file" << filename;
#endif
	}
	file2.close();
}

BikeDatabase BikeDatabase::operator+(const BikeDatabase& database) const
{
	BikeDatabase addedDatabases;
	BikeDatabase oldDatabase = *this;
	BikeDatabase newDatabase = database;
	addedDatabases.addBikes(oldDatabase.getAllBikes());
	addedDatabases.addBikes(newDatabase.getAllBikes());
	return addedDatabases;
}

ostream& operator<<(ostream& os, BikeDatabase& database)
{
	map<int, Record> myBikes = database.getAllBikes();
	for (auto it = myBikes.begin(); it != myBikes.end(); ++it)
	{
		os <<it->first<<' '<<  it->second <<'\n';
	}
	return os;
}
istream& operator>> (istream& is, BikeDatabase& database)
{
	int id;
	Record record;
	while (is >> id >> record)
	{
		database.allBikes.insert(pair<int, Record>(id, record));
	}
	return is;
}




ostream& operator<<(ostream& os, Record& record)
{
	os << record.state << ' ' << record.user << ' ' << record.stand << ' ' << record.type << ' ' << record.broken;
	return os;
}
istream& operator>> (istream& is, Record& record)
{
	is >> record.state >> record.user >> record.stand >> record.type >> record.broken;
	return is;
};

