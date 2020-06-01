//Klasa ElectricBike, dziedziczy po Bike
//Olga Krupa,nr indeksu 304048
#pragma once
#include "Bike.h"

class ElectricBike : public Bike
{
private:
    //int battery = 100;
    bool actualstate = true;
    std::shared_future<bool> batterystate;
    std::future<void> loading;
    
public:
    int battery = 100; 
    ElectricBike() {};
    ElectricBike(int id) {
        this->id = id;
    }
    virtual ~ElectricBike() {};
    ElectricBike& operator=(const ElectricBike& b);
    void StartOfRent(BikeDatabase& database, int person, const float money);
    void Stop(BikeDatabase& database, std::map<int, bool>& states, Client& user) ;
    bool CheckBattery();
    void Loading( BikeDatabase* database);
    bool Breakdown();
    void Pay(Client& user);
};