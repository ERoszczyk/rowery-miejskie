#pragma once
#include "Bike.h"
#include <future>
#include <windows.h>

class ElectricBike : public Bike
{
private:
    //int battery = 100;
    bool actualstate = true;
    shared_future<bool> zut;
    future<bool> batterystate;
    future<void> loading;
public:
    int battery = 100; 
    ElectricBike() {};
    ElectricBike(int id) {
        this->id = id;
    }
    ElectricBike& operator=(const ElectricBike& b);
    void StartOfRent(BikeDatabase& database, int person, const float money);
    void Stop(BikeDatabase& database, map<int, bool>& states, Client& user) ;
    bool CheckBattery();
    void Loading( BikeDatabase* database);
    void Pay(Client& user);
};