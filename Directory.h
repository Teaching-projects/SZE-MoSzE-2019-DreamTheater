#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <iostream>
#include <string>
#include <list>
using namespace std;

class Directory
{

private:
    string name;
    Directory* parent;
    list <Directory*> subFolder;
public:
    Directory(string,Directory*);
    ~Directory();
    string getName() const;
    void ls();
    void makefolder(string);
    list<Directory *> getSubFolder() const;
    Directory *getParent() const;
};

#endif // DIRECTORY_H