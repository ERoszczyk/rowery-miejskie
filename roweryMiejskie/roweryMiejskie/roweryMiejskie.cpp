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
    RentalLocation point(database);
    UserBase base;
    base.menuStart(point, database);
    base.saveBaseToFile("users.txt");
    database.exportToFile("exporteddatabase.txt");
}