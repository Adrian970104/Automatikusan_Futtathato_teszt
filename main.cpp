#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "Leny.h"
using namespace std;

void beolvas(const string &str, vector<Leny *> &lenyek, vector<char> &napok)
{
    ifstream f(str.c_str());
    if (f.fail())
    {
        cout << "Nem letezo fajl!" << endl;
        exit(1);
    }

    // L�nyek l�trehoz�sa
    int n;
    f >> n;
    lenyek.resize(n);
    for (int i = 0; i < n; i++)
    {
        char ch;
        string _nev;
        int _viz;
        f >> _nev >> ch >> _viz;
        switch (ch)
        {
        case 'h':
            lenyek[i] = new Homokjaro(_nev, _viz);
            break;
        case 's':
            lenyek[i] = new Szivacs(_nev, _viz);
            break;
        case 'l':
            lenyek[i] = new Lepegeto(_nev, _viz);
            break;
        }
    }
    // Napok beolvasasa
    char c;
    f >> c;
    while (!f.fail())
    {
        napok.push_back(c);
        f >> c;
    }
}

Leny *verseny(vector<Leny *> &lenyek, vector<char> &napok)
{
    for (unsigned int i = 0; i < napok.size(); i++)
    {
        for (unsigned int j = 0; j < lenyek.size(); j++)
        {
            switch (napok[i])
            {
            case 'n':
                lenyek[j]->napos();
                break;
            case 'f':
                lenyek[j]->felhos();
                break;
            case 'e':
                lenyek[j]->esos();
                break;
            }
        }
    }
    bool b = false;
    int maxtav;
    Leny *nyertes;
    for (unsigned int i = 0; i < lenyek.size(); i++)
    {
        if (!b && lenyek[i]->el)
        {
            maxtav = lenyek[i]->tavolsag;
            nyertes = lenyek[i];
            b = true;
        }
        else if (b && lenyek[i]->el && lenyek[i]->tavolsag > maxtav)
        {
            maxtav = lenyek[i]->tavolsag;
            nyertes = lenyek[i];
        }
    }
    if (b)
    {
        cout << "A nyertes: " << nyertes->nev << ", tavolsaga: " << maxtav << endl;
        return nyertes;
    }
    else
    {
        cout << "Egy leny sem elte tul a versenyt!" << endl;
        return 0;
    }
}

//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    vector<Leny *> l;
    vector<char> n;
    string fajlnev;
    cout << "Add meg a fajl nevet: ";
    cin >> fajlnev;
    beolvas(fajlnev, l, n);
    Leny *nyertes = verseny(l, n);

    for (int i = 0; i < l.size(); i++)
        l[i]->kiir();
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("ures vagy 0 fajl")
{

    vector<Leny *> l;
    vector<char> n;
    beolvas("teszt1.txt", l, n);
    CHECK(l.size() == 0);
    CHECK(n.size() == 0);

    Leny *ny = verseny(l, n);
    CHECK(ny == nullptr);
}

TEST_CASE("csak 1 leny")
{

    vector<Leny *> l;
    vector<char> n;

    beolvas("teszt2.txt", l, n);
    CHECK(l.size() == 1);
    CHECK(n.size() == 5);

    Leny *ny = verseny(l, n);
    CHECK(ny == l[0]);
}

TEST_CASE("tobb leny, nincs nap")
{

    vector<Leny *> l;
    vector<char> n;

    beolvas("teszt3.txt", l, n);
    CHECK(l.size() == 4);
    CHECK(n.size() == 0);

    Leny *ny = verseny(l, n);
    CHECK(ny->tavolsag == 0);
}

TEST_CASE("senki nem eli tul")
{

    vector<Leny *> l;
    vector<char> n;

    beolvas("teszt4.txt", l, n);
    CHECK(l.size() == 4);
    CHECK(n.size() == 10);
    Leny *ny = verseny(l, n);
    CHECK(ny == nullptr);
}

TEST_CASE("verseny")
{

    vector<Leny *> l;
    vector<char> n;

    beolvas("teszt5.txt", l, n);
    CHECK(l.size() == 4);
    CHECK(n.size() == 11);

    Leny *ny = verseny(l, n);
    CHECK(ny == l[0]);
    CHECK(l[0]->viz == 4);
    CHECK(l[1]->viz == 3);
    CHECK(l[2]->viz == 3);
    CHECK(l[3]->viz == 3);

    CHECK(l[0]->tavolsag == 18);
    CHECK(l[1]->tavolsag == 14);
    CHECK(l[2]->tavolsag == 12);
    CHECK(l[3]->tavolsag == 12);
}

#endif
