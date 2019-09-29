#ifndef KONYVTAR_H
#define KONYVTAR_H
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Konyvtar
{

private:
    string nev;
    Konyvtar* szulo;
    list <Konyvtar*> alkonyvtar;
public:
    Konyvtar(string,Konyvtar*);
    ~Konyvtar();
    string getNev() const;
    void print();
    void ls();
    void makefolder(string);
    list<Konyvtar *> getAlkonyvtar() const;
    Konyvtar *getSzulo() const;
};

#endif // KONYVTAR_H
