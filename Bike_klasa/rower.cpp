//Przykład uzycia klasa Bike
//Olga Krupa,nr indeksu 304048
#include <iostream>
#include "Bike.h"



int main()
{
    map<int, char> bikes = {
    { 124, 'F' },
    { 385, 'O' },
    { 354, 'F' },
    { 432, 'F' },
    { 415, 'O' },
    { 567, 'F' }
    };

    map<int, int> state = {
        { 12, 385 },
        { 38, 1 },
        { 35, 1 },
        { 43, 1 },
        { 41, 415 },
        { 56, 1 }
    }; 

    Bike b(124);
    Bike c(385);
    Bike d(432);
    b.StartOfRent(state, bikes, "ABC", 32);
    c.StartOfRent(state, bikes, "DEF", 76);
    b.Stop(bikes, state);
    b.HistoryOfRent(b);
    b.StartOfRent(state, bikes, "GHI", 12);
    b.Stop(bikes, state);
#ifdef _DEBUG
    b.HistoryOfRent(b);
#endif // DEBUG

    c.Stop(bikes, state);
    b.StartOfRent(state, bikes, "JKL", 21);
    b.Stop(bikes, state);
    b.HistoryOfRent(b);
    b.HistoryOfRent(c);
    d = b;
    d.Stop(bikes, state);
    d.HistoryOfRent(d);
#ifdef _DEBUG
    cout << "History of rent";
    b.FullHistory();
    c.FullHistory();
    d.FullHistory();
#endif // DEBUG



}