#pragma once
#include "Bike.h"

class Tandem : public Bike
{
public:

    Tandem();
    Tandem(int id) {
        this->id = id;
    }
    void Pay(User& user);
};