#include "Bike.h"
//Klasa Bike
//Olga Krupa,nr indeksu 304048

using namespace std;

ostream& operator<<(ostream& os, const Bike& b)
{
    os << b.id << endl;
    os << b.holder << endl;
    os << b.account << endl;
    os << b.price << endl;
    os << b.time_hold << endl;
    os << b.start << endl;
    os << b.end << endl;

    return os;
}

istream& operator>>(istream& is, Bike& b)
{
    is >> b.id >> b.holder >> b.account;
    return is;
}

Bike& Bike::operator=(const Bike& b)
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
    damage = b.damage;

    return *this;
}

void Bike::HistoryOfRentWithNotification() //wpisanie obiektu do historii z informacj¹ o zepsuciu
{
    ofstream file;
    file.open("history.txt", ofstream::app);

    if (file.is_open())
    {
        string line = to_string(id) + " | " + holder + " | " + to_string(state) + " | " + to_string(time_hold) + " | " + to_string(price) + "\n";
        file << line;
        string notification = "While renting a bike by the user " + holder + " of the bike with id " + to_string(id) + " got broken.\n";
        file << notification;
    }
    else
    {
#if _DEBUG
        cout << "Unable to open file" ;
#endif
     }
     file.close();

}

void Bike::HistoryOfRent() //wpisanie obiektu do historii
{
    ofstream file;
    file.open("history.txt", ofstream::app);

    if (file.is_open())
    {
        string line = to_string(id) + " | " + holder + " | " + to_string(state) + " | " + to_string(time_hold) + " | " + to_string(price) + "\n";
        file << line;
    }
    else
    {
#if _DEBUG
        cout << "Unable to open file";
#endif
    }
    file.close();

}

void Bike::Stop(BikeDatabase& database, map<int, bool>& states, Client& user) //koniec wypozyczenia, po wys³aniu wiadomosci o checi oddania roweru
{
    bool endassingnment;
    endassingnment = StandAssignment(database, states);
    if (endassingnment)
    {
        time(&end);
        time_hold = difftime(end, start) / 60;
        cout << "Time of rent " << time_hold << " minutes." << endl;
        Pay(user);
        check_demage = true;
        bool dem = damage.get();
        check_demage = false;
        if (dem)
        {
            database.breakDown(id);
            HistoryOfRentWithNotification();
        }
        else
        {
            HistoryOfRent();
        }
        database.setBikeState(id, false);
        database.setBikeOwner(id, 0);
    }
}

void Bike::Pay(Client& user)
{
    //Pobieranie œrodków z konta u¿ytkownika
    int ftime;
    double mtime = time_hold;
    if (mtime < 21)
    {
        account = account - 1;
        price = 1;
    }
    if (mtime > 20 && mtime < 61)
    {
        account -= 2;
        price = 2;
    }
    if (mtime > 60 && mtime < 121)
    {
        account -= 5;
        price = 5;
    }
    if (mtime > 120 && mtime < 181)
    {
        account -= 10;
        price = 10;
    }
    if (mtime > 180)
    {
        ftime = mtime - 180;
        price = 10 + ((ftime / 60 + 1) * 7);
        account -= price;
    }
    user.transferCash(-price);
};

void Bike::StartOfRent(BikeDatabase& database, int person, float money)
{
    holder = to_string(person);
    account = money;
    //Sprawdzanie konta
    if (account < 10)
    {
        cout << "You do not have enough money to rent a bike." << endl;
        database.setBikeState(id, false);
        //funkcja do dodania œrodków, odes³anie do u¿ytkownika?
    }
    else
    {
        int state;
        //zwalnianie stojaka
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
        damage = async(launch::async, &Bike::Breakdown, this);
        //odliczanie czasu od wynajecia 
    }

};

bool Bike::StandAssignment(BikeDatabase& database, map<int, bool>& states) //przypisanie stojaka
{
    int stateid;
    bool use = false;
    stateid = FindStand(states);
    if (stateid == 0)
    {
        cout << "No available state" << endl;
        return use;
    }
    else
    {
        use = true;
        database.setBikeStand(id, stateid);
        cout << "You returned the bike" << endl;
    }
    return use;
    
};

int Bike::FindStand(map<int, bool>& states) //szukanie wolnego stojaka
{
    int stateid = 0;
    bool available = false;
    std::map<int, bool>::iterator itr;
    for (map<int, bool>::iterator itr = states.begin(); itr != states.end(); ++itr)
    {
        if (itr->second == false)
        {
            stateid = itr->first;
            itr->second = true;
            return stateid;
        }
    }
    return stateid;
};

bool Bike::Breakdown() //losowe zepsucia
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
        if (val < 15)
        {
            cout << endl << "Damage found, return the bike to the nearest free stand" << endl;
            bike_demage = true;
            return bike_demage;
        }
        Sleep(5000);
    }
};
