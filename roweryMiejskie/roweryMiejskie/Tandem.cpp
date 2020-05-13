#include "Tandem.h"

using namespace std;

void Tandem::Pay(Client& user)
{
    //Pobieranie œrodków z konta u¿ytkownika
    int ftime;
    double mtime = time_hold;
    if (mtime < 21)
    {
        account = account - 3;
        price = 3;
    }
    if (mtime > 20 && mtime < 61)
    {
        account -= 7;
        price = 7;
    }
    if (mtime > 60 && mtime < 121)
    {
        account -= 15;
        price = 15;
    }
    if (mtime > 120 && mtime < 181)
    {
        account -= 20;
        price = 20;
    }
    if (mtime > 180)
    {
        ftime = mtime - 180;
        price = 20 + ((ftime / 60 + 1) * 8);
        account -= price;
    }
    user.transferCash(-price);
};
