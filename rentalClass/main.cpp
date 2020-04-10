// main.cpp contains the main function.
// This is an example of running the Renttal Point
// Program execution starts and ends here.
// Author: Kinga Kwoka gr.208

#include "BikeDatabase.h"
#include "RentalPoint.h"

#ifdef _DEBUG
#endif

void rent(RentalPoint& point, BikeDatabase& database)
{
	std::cout << "Choose one of our free bikes:\n";
	for (auto& bike : point.getFreeBikes())
	{
		std::cout << bike << "\n";
	}
	int bikeId, userId;
	std::cout << "Enter bike ID: ";
	std::cin >> bikeId;
	std::cout << "Enter your user ID: ";
	std::cin >> userId;
	point.rent(bikeId, userId, database);
}

void putback(RentalPoint& point, BikeDatabase& database)
{
	int bikeId2, userId2;
	std::cout << "Enter bike ID: ";
	std::cin >> bikeId2;
	std::cout << "Enter your user ID: ";
	std::cin >> userId2;
	point.putBack(bikeId2, userId2, database);
}

void run(RentalPoint& point, BikeDatabase& database)
{
	std::cout << "Welcome to the Rental Point.\n For RENT enter 1, for RETURN enter 2\n";
	int action;
	std::cin >> action;
	if (action == 1) { rent(point, database); }
	else if (action == 2) { putback(point, database); }
	else { std::cout << "Invalid choice"; }
}
int main()
{
	// Example of rental point usage
	BikeDatabase database;
	database.importFromFile();
	RentalPoint point(database);
	int i=0;
	while (i<3)
	{
		run(point, database);
		i++;
	}
	database.exportToFile("exporteddatabase.txt");
}