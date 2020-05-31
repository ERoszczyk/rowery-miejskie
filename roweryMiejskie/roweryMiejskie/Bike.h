#pragma once
//Klasa Bike
//Olga Krupa,nr indeksu 304048
#ifndef Bike_h
#define Bike_h

#include "BikeDatabase.h"
#include "Client.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <time.h>
#include <conio.h>
#include <sstream>
#include <future>
#include <windows.h>



class Bike {
protected:
    int id;
    std::string holder;
    time_t start, end;
    std::shared_future<bool> damage;

public:

    float account;
    float price;
    double time_hold;
    int state;
    Bike() : account(0) {}; // niezainicjalizowane pola klasy ...
    Bike(int id) {
        this->id = id;
    }
    virtual ~Bike() {};
    Bike& operator=(const Bike& b);
    virtual void StartOfRent(BikeDatabase& database, int person, const float money);
    bool StandAssignment(BikeDatabase& database, std::map<int, bool>& states);
    int FindStand(std::map<int, bool>& states);
    virtual void Pay(Client& user);
    virtual void Stop(BikeDatabase& database, std::map<int, bool>& states, Client& user);
    virtual bool Breakdown();
    void HistoryOfRent();
    void HistoryOfRentWithNotification();

    friend
        std::ostream& operator<< (std::ostream& os, const Bike& b);
    friend
        std::istream& operator>> (std::istream& is, Bike& b);
};

#endif
