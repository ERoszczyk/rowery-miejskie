#include "Administrator.h"

Administrator::Administrator(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& id)
	:User(userName, userSurname, userUsername, userPassword, id),
	ifAdministrator(true)
{
}

void Administrator::menu(RentalPoint& rental, BikeDatabase& database)
{
	int optionNumber;
	string answer;

	system("CLS");
	cout << "Hello " << getName() << "!" << endl;
	cout << "You're logged in as administrator" << endl;
	cout << "1. Add new rental point" << endl;
	cout << "2. Disactivate rental point" << endl;
	cout << "3. Add bike" << endl;
	cout << "4. Delete bike" << endl;
	cout << "5. Add user" << endl;
	cout << "6. Delete user" << endl;
	cout << "7. Change user's password" << endl;
	cout << "8. Change user's name" << endl;
	cout << "9. Change user's surname" << endl;
	cout << "10. Change user's username" << endl;
	cout << "11. Export users database to file" << endl;
	cout << "12. Import users database from file" << endl;
	cout << "13. Add new administrator" << endl;
	cout << "14. Delete administrator" << endl;
	cout << "15. Log out" << endl;
	cout << "Enter what would you like to do: ";
	cin >> optionNumber;
	switch (optionNumber)
	{
	case 1:
		cout << "This option is not available yet" << endl;
		break;
	case 2:
		cout << "This option is not available yet" << endl;
		break;
	case 3:
		cout << "This option is not available yet" << endl;
		break;
	case 4:
		cout << "This option is not available yet" << endl;
		break;
	case 5:
		cout << "This option is not available yet" << endl;
		break;
	case 6:
		cout << "This option is not available yet" << endl;
		break;
	case 7:
		cout << "This option is not available yet" << endl;
		break;
	case 8:
		cout << "This option is not available yet" << endl;
		break;
	case 9:
		cout << "This option is not available yet" << endl;
		break;
	case 10:
		cout << "This option is not available yet" << endl;
		break;
	case 11:
		cout << "This option is not available yet" << endl;
		break;
	case 12:
		cout << "This option is not available yet" << endl;
		break;
	case 13:
		cout << "This option is not available yet" << endl;
		break;
	case 14:
		cout << "This option is not available yet" << endl;
		break;
	case 15:
		return;
	default:
		menu(rental, database);
	}
	cout << "Would you like to continue? (y/n) ";
	cin >> answer;
	if (answer == "y")
	{
		menu(rental, database);
	}
	else
	{
		cout << "You've been logged out" << endl;
		return;
	}
}
