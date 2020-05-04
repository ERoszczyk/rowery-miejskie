#include "ElectricBike.h"


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
    zut = b.zut;
    //batterystate = b.batterystate;
    //shared_future<bool> shfut = b.batterystate.share();
    return *this;
}

bool ElectricBike::CheckBattery() {
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

void ElectricBike::StartOfRent(BikeDatabase& database, int person, float money)
{
    holder = to_string(person);
    account = money;
    if (account < 10)
    {
        cout << "You do not have enough money to rent a bike." << endl;
        database.setBikeState(id, false);
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
        cout << "Rental time has begun." << endl;
        time(&start);
        
        batterystate = async(launch::async,&ElectricBike::CheckBattery,this);
        zut = async(launch::async, &ElectricBike::CheckBattery, this);
    }

};



void ElectricBike::Stop(BikeDatabase& database, map<int, bool>& states, Client& user)
{

    bool endassingnment;
    endassingnment = StandAssignment(database, states);
    if (endassingnment)
    {
        actualstate = false;
        bool koniec = zut.get();
        //bool koniec = batterystate.get();
        actualstate = true;
        cout << "Battery state " << battery << endl;
        //koniec bool ret = fut.get();
        time(&end);
        time_hold = difftime(end, start) / 60;
        cout << "Time of rent " << time_hold << " minutes." << endl;
        Pay(user);
        HistoryOfRent();
        if (battery != 100)
        {
            //std::future<void> but = std::async(this->Loading, database);
            std::future<void> but = async(launch::async, &ElectricBike::Loading, this, &database);
        }
        database.setBikeState(id, false);
        database.setBikeOwner(id, 0);
    }
}



void ElectricBike::Pay(Client& user)
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
    user.transferCash(account);
};

void ElectricBike::Loading( BikeDatabase* database) {
    while (battery != 100)
    {
        battery += 1;
        Sleep(5000);
    }
    database->setBikeState(id, false);
};