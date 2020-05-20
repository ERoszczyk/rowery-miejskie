//Plik zawieraj�cy funkcje klasy Administrator, Ewa Roszczyk, nr. indeksu: 304077
#include "Administrator.h"
#include "UserBase.h"
#include "RentalPoint.h"

Administrator::Administrator(const string& userName, const string& userSurname, const string& userUsername, const string& userPassword, const int& id)
	: User(userName, userSurname, userUsername, userPassword, id),
     ifAdministrator(true)
{
}

void Administrator::menu(MainLocation& rental, BikeDatabase& database, UserBase& base)
{
	int optionNumber;
	string answer, filename;

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
		cout << "This option is not available yet" << endl;  //od wypozyczalni
		break;
	case 2:
		disactivateRentalPoint(rental);
		break;
	case 3:
		cout << "This option is not available yet" << endl;  //od wypozyczalni
		break;
	case 4:
		cout << "This option is not available yet" << endl;  //od wypozyczalni
		break;
	case 5:
		base.createNewUserAsAdministrator();
		break;
	case 6:
		deleteUser(base);
		break;
	case 7:
		changeUsersPassword(base);
		break;
	case 8:
		changeUsersName(base);
		break;
	case 9:
		changeUsersSurname(base);
		break;
	case 10:
		changeUsersUsername(base);
		break;
	case 11:
		cout << "Enter file name: " << endl;
		cin >> filename;
		filename.append(".txt");
		base.exportBaseToFile(filename);
		break;
	case 12:
		cout << "This option is not available yet" << endl;
		break;
	case 13:
		base.createNewAdministrator();
		break;
	case 14:
		deleteAdministrator(base);
		break;
	case 15:
		cout << "You've been logged out" << endl;
		return;
	default:
		menu(rental, database, base);
	}
	cout << "Would you like to continue? (y/n) ";
	cin >> answer;
	if (answer == "y")
	{
		menu(rental, database, base);
	}
	else
	{
		cout << "You've been logged out" << endl;
		return;
	}
}

void Administrator::viewRentalPointLocation(MainLocation& rental)
{
	for (int i = 0; i < rental.getRentalLocationNames().size(); i++)
	{
		cout << i + 1 << ". ";
		cout << rental.getRentalLocationNames()[i] << endl;
	}
	cout << rental.getRentalLocationNames().size() + 1 << ". Main location" << endl;
}

void Administrator::disactivateRentalPoint(MainLocation& rental)
{
	int location;
	string answer;
	viewRentalPointLocation(rental);
	cout << "Enter number of location you would like to disactivate: ";
	cin >> location;
	if (location < 1 || location > rental.getRentalLocationNames().size() + 1)
	{
		cout << "Wrong number!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer; 
		if (answer == "y")
			disactivateRentalPoint(rental);
		else
			return;
	}
	else
	{
		if (location == rental.getRentalLocationNames().size() + 1)
			location = -1;
		else
			location -= 1;
		rental.disactivateLocation(location);
	}
}

void Administrator::changeUsersPassword(UserBase& base)
{
	string currentUsername, newPassword = "", answer;
	char character;

	cout << "Enter user's Username: " << endl;
	cin >> currentUsername;
	if (!base.ifUsernameExists(currentUsername))
	{
		cout << "Wrong username!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer;
		if (answer == "y")
			changeUsersPassword(base);
		else
			return;
	}
	else
	{
		cout << "Enter new User's password: " << endl;
		character = _getch();
		while (character != 13)
		{
			newPassword.push_back(character);
			cout << "*";
			character = _getch();
		}
		cout << endl;
		base.changePasswordAsAdministrator(currentUsername, newPassword);
	}
}

void Administrator::changeUsersName(UserBase& base)
{
	string currentUsername, newName, answer;
	cout << "Enter user's Username: " << endl;
	cin >> currentUsername;
	if (!base.ifUsernameExists(currentUsername))
	{
		cout << "Wrong username!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer;
		if (answer == "y")
			changeUsersName(base);
		else
			return;
	}
	else
	{
		cout << "Enter new User's name: " << endl;
		cin >> newName;
		base.changeNameAsAdministrator(currentUsername, newName);
	}
}

void Administrator::changeUsersSurname(UserBase& base)
{
	string currentUsername, newSurname, answer;
	cout << "Enter user's Username: " << endl;
	cin >> currentUsername;
	if (!base.ifUsernameExists(currentUsername))
	{
		cout << "Wrong username!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer;
		if (answer == "y")
			changeUsersSurname(base);
		else
			return;
	}
	else
	{
		cout << "Enter new User's surname: " << endl;
		cin >> newSurname;
		base.changeSurnameAsAdministrator(currentUsername, newSurname);
	}
}

void Administrator::changeUsersUsername(UserBase& base)
{
	string currentUsername, newUsername, answer;
	cout << "Enter current user's Username: " << endl;
	cin >> currentUsername;
	if (!base.ifUsernameExists(currentUsername))
	{
		cout << "Wrong username!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer;
		if (answer == "y")
			changeUsersUsername(base);
		else
			return;
	}
	else
	{
		cout << "Enter new User's username: " << endl;
		cin >> newUsername;
		base.changeUsernameAsAdministrator(currentUsername, newUsername);
	}
}

void Administrator::deleteUser(UserBase& base)
{
	string username, answer;
	cout << "Enter user's Username: " << endl;
	cin >> username;
	if (!base.ifUsernameExists(username))
	{
		cout << "Wrong username!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer;
		if (answer == "y")
			deleteUser(base);
		else
			return;
	}
	else
	{
		base.deleteUserAsAdministrator(username);
	}
}

void Administrator::deleteAdministrator(UserBase& base)
{
	string username, answer;
	cout << "Enter administrator's Username: " << endl;
	cin >> username;
	if (!base.ifUsernameExists(username))
	{
		cout << "Wrong username!" << endl;
		cout << "Would you like to try again? (y/n) ";
		cin >> answer;
		if (answer == "y")
			deleteUser(base);
		else
			return;
	}
	else
	{
		base.deleteUserAsAdministrator(username);
	}
}