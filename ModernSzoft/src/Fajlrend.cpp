#include "Fajlrend.h"
#include <sstream>
    Fajlrend::Fajlrend(){
    gyoker=new Konyvtar("gyoker",nullptr);
    jelenlegidir=gyoker;
    }
    Fajlrend::~Fajlrend(){
    delete gyoker;
    }
    int Fajlrend::mkdir(string s){
        if(jelenlegidir->getAlkonyvtar().empty()){
            jelenlegidir->makefolder(s);
            return 1;
        }
        for(auto i:jelenlegidir->getAlkonyvtar()){
            if(i->getNev()==s){
                cout<<"Ilyen mappa van mar"<<endl;
                return 0;
            }
        }
        jelenlegidir->makefolder(s);
        return 1;
    }
    void Fajlrend::ls(){
    Konyvtar* tmp;
    tmp=jelenlegidir;
    list<string> path;
    while(tmp->getSzulo()!=nullptr){
        path.push_front(tmp->getSzulo()->getNev());
        tmp=tmp->getSzulo();
    }
    for(auto i:jelenlegidir->getAlkonyvtar()){
        for(auto i:path){
            cout<<i;
            cout<<"/";
        }
        jelenlegidir->print();
        i->ls();
        cout<<endl;
    }
    }
    int Fajlrend::cd(string t){
    if(t==".."){
        jelenlegidir=jelenlegidir->getSzulo();
        return 1;
    }
    for(auto& i:jelenlegidir->getAlkonyvtar()){
        if(i->getNev()==t){
        jelenlegidir=i;
        return 1;
        }
    }
    return 0;
    }
    void Fajlrend::start(){
    string parancs;
    string teljesparancs;
    string argumentum;
    do{
       getline(cin,teljesparancs);
       istringstream line(teljesparancs);
       parancs=argumentum="";
       line>>parancs;
       line>>argumentum;

           if (parancs=="ls")
           {
              this->ls();
           }
           else if (parancs=="cd")
           {
               if(argumentum=="") cout<<"Adjon meg egy mappanevet"<<endl;
               else{
                   this->cd(argumentum);
               }
           }
           else if(parancs=="cd.."){
               if(jelenlegidir==gyoker){
                   cout<<"Gyoker mappában van, nem lehet cd funkciot alkalmazni"<<endl;
               }
               else
                   jelenlegidir=jelenlegidir->getSzulo();
           }
           else if (parancs=="mkdir")
           {
               if(argumentum=="")
                   cout<<"A mappat el kell nevezni"<<endl;
               else
               {
                  this->mkdir(argumentum);
               }
           }
           else cout<<"Érvénytelen parancs"<<endl;
       } while (parancs!="quit");
    }
