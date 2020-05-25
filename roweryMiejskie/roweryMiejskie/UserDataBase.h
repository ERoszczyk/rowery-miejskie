//Plik nag³ówkowy klasy UserBase, Ewa Roszczyk, nr. indeksu: 304077
#ifndef UserdDataBase_h
#define UserdDataBase_h

#include <map>

#include "Administrator.h"
#include "Client.h"
#include "ClientPremium.h"
#include "Mechanic.h"

class MainLocation;
class BikeDatabase;


class UserDataBase
{
	std::map<int, User*> userNames;

public:
	UserDataBase();
	void menuStart(MainLocation& rental, BikeDatabase& database);
	void addNewUser(const std::string& userName, const std::string& userSurname, const std::string& userUsername, const std::string& userPassword);
	void addNewAdministrator(const std::string& userName, const std::string& userSurname, const std::string& userUsername, const std::string& userPassword);
	std::map<int, User*> getUserNames();
	bool ifUsernameExists(const std::string& username);
	int getCurrentLoginIndex();
	bool ifUsernameAvailable(const std::string& username);

	// To do odrêbnej klasy
	void createNewUser();
	void createNewUserAsAdministrator();
	void createNewAdministrator();

	void login(MainLocation& rental, BikeDatabase& database);
	void changeUsernameAsAdministrator(const std::string& currentUsername, const std::string& newUsername);
	void changePasswordAsAdministrator(const std::string& username, const std::string& newPassword);
	void changeNameAsAdministrator(const std::string& username, const std::string& newName);
	void changeSurnameAsAdministrator(const std::string& username, const std::string& newSurname);
	void deleteUserAsAdministrator(const std::string& username);
	void premiumActivation(const int& userId, MainLocation& rental, BikeDatabase& database);
	void premiumResignation(const int& userId);
	void exportBaseToFile(const std::string& filename);
};

#endif
