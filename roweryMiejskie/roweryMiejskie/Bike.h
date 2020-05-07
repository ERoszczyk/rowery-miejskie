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

using namespace std; // proszê siê tego pozbyæ - nie wolno w plikach nag³ówkowych!

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
    Bike() : account(0) {}; // niezainicjalizowane pola klasy ...
    Bike(int id) {
        this->id = id;
    }
    // warto (na wszelki wypadek) dodaæ wirtualny destruktor
    virtual Bike& operator=(const Bike& b);  // Jak bêdzie zmieniana funkcja? virtual nie bardzo ma sens
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
