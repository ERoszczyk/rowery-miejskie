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
    // self-assignment check
    //zmiana roweru, np w przypadku checi zmiany rowru lub zepsucia poprzedniego, przypisanie nowego roweru
    if (this == &b)
        return *this;

    id = b.id;
    holder = b.holder;
    account = b.account;
    start = b.start;
    price = b.price;
    end = 0;
    time_hold = 0;

    return *this;
}

void Bike::HistoryOfRent() //wpisanie obiektu do historii
{
    /*if (b.id == id)
    {
        string line = b.holder + " | " + to_string(b.state) + " | " + to_string(b.time_hold) + " | " + to_string(b.price);
        if (history.empty())
        {
            string pi = "Bike " + to_string(b.id) + ": " + "USER | STATE | TIME OF RENT | PRICE\n";
            b.history.push_back(pi);
            b.history.push_back(line);
        }
        else
        {
            history.push_back(line);
        }
    }
    else
    {
        b.HistoryOfRent(b);
    }*/
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
        cout << "Unable to open file" ;
#endif
     }
     file.close();

}

void Bike::Stop(BikeDatabase& database, map<int, bool>& states, Client& user) //koniec wypozyczenia, po wys³aniu wiadomosci o checi oddania roweru od uzytkownika lub wypozyczalni
{
    bool endassingnment;
    endassingnment = StandAssignment(database, states);
    if (endassingnment)
    {
        time(&end);
        time_hold = difftime(end, start) / 60;
        cout << "Time of rent " << time_hold << " minutes." << endl;
        Pay(user);
        HistoryOfRent();
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
        /*for (auto it = states.begin(); it != states.end(); ++it)
            if (it->second == id)
            {
                it->second == 0;
            }*/
            //  Obliczanie czasu wypozyczenia, informacja o czasie wypzyczenia oraz wywolanie funkcji do pobrania srodkow
        cout << "Rental time has begun" << endl;
        time(&start);
        //odliczanie czasu od wynajecia 
    }

};

bool Bike::StandAssignment(BikeDatabase& database, map<int, bool>& states)
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

int Bike::FindStand(map<int, bool>& states)
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
