#ifndef FAJLREND_H
#define FAJLREND_H

#include "Konyvtar.h"
#include <list>
using namespace std;
class Fajlrend
{
private:
    list <Konyvtar*> konyvtarak;
    Konyvtar* gyoker;
public:
    Fajlrend();
    ~Fajlrend();
    int mkdir(string);
    void ls();
    int cd(string);
    Konyvtar* jelenlegidir;
    void start();
};

#endif // FAJLREND_H
