#include <iostream>
#include "userBase.h"
#include "BikeDatabase.h"
#include "RentalPoint.h"

using namespace std;

#ifdef _DEBUG
#endif

int main()
{
    BikeDatabase database;
    database.importFromFile();
    vector<string> names{ "another location", "one more location" };
    MainLocation point(names, database);
    UserBase base;
    base.menuStart(point, database);
    database.exportToFile("exporteddatabase.txt");
}