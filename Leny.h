#ifndef LENY_H_INCLUDED
#define LENY_H_INCLUDED
#include <string>
#include <iostream>
#include <algorithm>

class Leny
{

public:
    std::string nev;
    int viz;
    int maxviz = 0;
    bool el = true;
    int tavolsag = 0;

    void kiir()
    {
        std::cout << "~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "A leny neve: " << nev << std::endl;
        std::cout << "Viz: " << viz << std::endl;
        std::cout << "El: " << el << std::endl;
        std::cout << "Tavolsag: " << tavolsag << std::endl;
        std::cout << "Maxviz: " << maxviz << std::endl;
        std::cout << "~~~~~~~~~~~~~~~~" << std::endl;
    }

    Leny(const std::string &str, int v = 0) : nev(str), viz(v) {}

    void lep(int v, int t)
    {
        if (el)
        {
            viz += v;
            if (viz > maxviz)
                viz = maxviz;
            if (viz <= 0)
                el = false;
            else
                tavolsag += t;
        }
    }
    virtual void napos() = 0;
    virtual void felhos() = 0;
    virtual void esos() = 0;
};

class Homokjaro : public Leny
{
public:
    Homokjaro(const std::string &str, int v = 0) : Leny(str, v)
    {
        maxviz = 8;
        if (viz > maxviz)
            viz = maxviz;
    }
    void napos() override { lep(-1, 3); }
    void felhos() override { lep(0, 1); }
    void esos() override { lep(3, 0); }
};

class Szivacs : public Leny
{
public:
    Szivacs(const std::string &str, int v = 0) : Leny(str, v)
    {
        maxviz = 20;
        if (viz > maxviz)
            viz = maxviz;
    }
    void napos() override { lep(-4, 0); }
    void felhos() override { lep(-1, 1); }
    void esos() override { lep(6, 3); }
};

class Lepegeto : public Leny
{
public:
    Lepegeto(const std::string &str, int v = 0) : Leny(str, v)
    {
        maxviz = 12;
        if (viz > maxviz)
            viz = maxviz;
    }
    void napos() override { lep(-2, 1); }
    void felhos() override { lep(-1, 2); }
    void esos() override { lep(3, 1); }
};

#endif // LENY_H_INCLUDED
