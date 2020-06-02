//Klasa ElectricBike, dziedziczy po Bike
//Olga Krupa,nr indeksu 304048
#include "ElectricBike.h"

using namespace std;

ElectricBike& ElectricBike::operator=(const ElectricBike& b)
{
    if (this == &b)
        return *this;

    id = b.id;
    holder = b.holder;
    account = b.account;
    start = b.start;
    price = b.price;
    end = 0;
    time_hold = 0;
    battery = b.battery;
    batterystate = b.batterystate;
    damage = b.damage;
    return *this;
}

bool ElectricBike::CheckBattery() //rozladowywanie baterii az do wartoœci zera lub przerwania przez funkcjê
{
    while (battery != 0)
    {
        if (actualstate == false)
        {
            return false;
        }
        battery -= 1;
        Sleep(5000);
    }
    return true;
};

void ElectricBike::StartOfRent(BikeDatabase& database, int person, float money, Client& user) //rozpoczecie wypozyczennia
{
    holder = to_string(person);
    account = money;
    if (account < 15)
    {
        int answer;
        cout << "You do not have enough money to rent a bike." << endl;
        database.setBikeState(id, false);
        cout << "Would you like to deposit money? " << endl;
        cout << "1.YES " << endl << "2.NO " << endl;
        cin >> answer;
        switch (answer)
        {
        case 1:
            cout << "Now you can deposit money" << endl;
            user.transferMoney();
            break;

        default:
            cout << "You didn't rent any bikes " << endl;
        }
    }
    else
    {
        int state;
        database.setBikeState(id, true);
        database.setBikeOwner(id, person);
        database.setBikeStand(id, 0);
        end = 0;
        time_hold = 0;
        price = 0;
#if _DEBUG
        cout << "Rental time has begun" << endl;
#endif
        time(&start);
        
        batterystate = async(launch::async, &ElectricBike::CheckBattery, this);
        damage = async(launch::async, &ElectricBike::Breakdown, this);
    }

};



void ElectricBike::Stop(BikeDatabase& database, map<int, bool>& states, Client& user) //koniec wypozyczenia, po wys³aniu wiadomosci o checi oddania roweru
{

    bool endassingnment;
    endassingnment = StandAssignment(database, states);
    if (endassingnment)
    {
        actualstate = false;
        bool koniec = batterystate.get();
        actualstate = true;
        cout << "Battery state " << battery << endl;
        time(&end);
        time_hold = difftime(end, start) / 60;
        cout << "Time of rent " << time_hold << " minutes." << endl;
        Pay(user);
        check_demage = true;
        bool dem = damage.get();
        check_demage = false;
        if (dem || battery != 100)
        {
            if (dem)
            {
                database.breakDown(id);
                HistoryOfRentWithNotification();
                database.setBikeState(id, false);
            }

            if (battery != 100)
            {
                loading = async(launch::async, &ElectricBike::Loading, this, &database);
                HistoryOfRent();
            }
        }

        else
        {
            database.setBikeState(id, false);
            HistoryOfRent();
        }
        database.setBikeOwner(id, 0);
    }
}



void ElectricBike::Pay(Client& user) //pobieranie srodkow w konta
{
    int ftime;
    double mtime = time_hold;
    if (mtime < 21)
    {
        account = account - 5;
        price = 5;
    }
    if (mtime > 20 && mtime < 61)
    {
        account -= 8;
        price = 8;
    }
    if (mtime > 60 && mtime < 121)
    {
        account -= 16;
        price = 16;
    }
    if (mtime > 120 && mtime < 181)
    {
        account -= 24;
        price = 24;
    }
    if (mtime > 180)
    {
        ftime = mtime - 180;
        price = 24 + ((ftime / 60 + 1) * 10);
        account -= price;
    }
    user.transferCash(-price);
};

void ElectricBike::Loading( BikeDatabase* database) //ladowanie baterii
{
    while (battery != 100)
    {
        battery += 1;
        Sleep(5000);
    }
    database->setBikeState(id, false);
};

bool ElectricBike::Breakdown() //losowe zepsucia
{
    srand(time(NULL));
    int val;
    bool bike_demage = false;
    while (true)
    {
        if (check_demage)
        {
            return bike_demage;
        }
        val = rand() % 100;
        if (val < 30)
        {
            cout << "Damage found, return the bike to the nearest free stand" << endl;
            bike_demage = true;
            return bike_demage;
        }
        Sleep(5000);
    }
};

