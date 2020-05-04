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

using namespace std;

class Bike {
protected:
    int id;
    string holder;
    time_t start, end;

public:

    float account;
    float price;
    double time_hold;
    int state;
    vector <string> history;
    Bike() {};
    Bike(int id) {
        this->id = id;
    }

    virtual Bike& operator=(const Bike& b);
    virtual void StartOfRent(BikeDatabase& database, int person, const float money);
    bool StandAssignment(BikeDatabase& database, map<int, bool>& states);
    int FindStand(map<int, bool>& states);
    virtual void Pay(Client& user);
    virtual void Stop(BikeDatabase& database, map<int, bool>& states, Client& user);
    void HistoryOfRent();

    friend
        ostream& operator<< (ostream& os, const Bike& b);
    friend
        istream& operator>> (istream& is, Bike& b);
};

#endif
