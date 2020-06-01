//Klasa Tandem, dziedziczy po Bike
//Olga Krupa,nr indeksu 304048
#pragma once
#include "Bike.h"

class Tandem : public Bike
{
public:

    Tandem();
    Tandem(int id) {
        this->id = id;
    }
    void Pay(Client& user);
};