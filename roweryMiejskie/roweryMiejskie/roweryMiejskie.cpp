#include <iostream>
#include "userBase.h"
//#include "BikeDatabase.h"
//#include "RentalPoint.h"

using namespace std;

#ifdef _DEBUG
#endif

void optionsToChoose(UserBase& base, RentalPoint& rental, BikeDatabase& database)
{
    int optionNumber;
    string answer;

    system("CLS");
    if (base.ifLogged())
    {
        cout << "Hello " << base.getUserNames().find(base.getActiveUserId())->second.getName() << "!" << endl;
        cout << "1. Rent a bike" << endl;
        cout << "2. View rented bike(s)" << endl;
        cout << "3. Return rented bike(s)" << endl;
        cout << "4. View a list of bike points" << endl; // od wypozyczalni
        cout << "5. Check account balance" << endl;
        cout << "6. Check account history" << endl;
        cout << "7. Change password" << endl;
        cout << "8. Log out" << endl;
        cout << "Enter what would you like to do: ";
        cin >> optionNumber;
        optionNumber += 2;
    }
    else
    {
        cout << "You're not logged in" << endl;
        cout << "1. Log in" << endl;
        cout << "2. Sign up" << endl;
        cout << "Enter what would you like to do: ";
        cin >> optionNumber;
    }
    switch (optionNumber)
    {
    case 1:
        base.login();
        break;
    case 2:
        base.createNewUser();
        break;
    case 3:
        base.rentBike(rental, database);
        break;
    case 4:
        base.viewRentedBikes();
        break;
    case 5:
        base.returnBike(rental, database);
        break;
    case 6:
        cout << "This option is not available yet" << endl;
        break;
    case 7:
        cout << base.checkAccountBalance() << endl;
        break;
    case 8:
        cout << "This option is not available yet" << endl;
        break;
    case 9:
        base.changePassword();
        break;
    case 10:
        base.logout();
        break;
    default:
        cout << "Wrong number!" << endl;
        break;
    }
    cout << "Would you like to continue? (y/n) ";
    cin >> answer;
    if (answer == "y")
        optionsToChoose(base, rental, database);
    else
    {
        if (base.ifLogged())
            cout << "You've been logged out" << endl;
        return;
    }
}

int main()
{
    BikeDatabase database;
    database.importFromFile();
    RentalPoint point(database);
    UserBase base;
    optionsToChoose(base, point, database);
    base.saveBaseToFile("users.txt");
    database.exportToFile("exporteddatabase.txt");
}