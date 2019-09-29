#include "Konyvtar.h"

    Konyvtar::Konyvtar(string s,Konyvtar*sz){
    this->nev=s;
    this->szulo=sz;
    }
    Konyvtar::~Konyvtar(){
    for(auto& i:alkonyvtar){
        delete i;
    }
    }
    string Konyvtar::getNev() const{
    return nev;
    }
    void Konyvtar::print(){
    return this->getNev()<<"/";
    }
    void Konyvtar::ls(){
    return this->print();
    }
    void Konyvtar::makefolder(string s){
    return alkonyvtar.push_back(new Konyvtar(s,this));
    }
    list<Konyvtar *> Konyvtar::getAlkonyvtar() const{
    return alkonyvtar;
    }
    Konyvtar *Konyvtar::getSzulo() const{
    return szulo;
    }
