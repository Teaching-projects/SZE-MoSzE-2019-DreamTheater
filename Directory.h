#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <iostream>
#include <string>
#include <list>

#include "File.h"

using namespace std;

class Directory
{

private:
    string name;
    Directory* parent;
    list <Directory*> subFolder;
    list <File*> files;
public:
    Directory(string,Directory*);
    ~Directory();
    string getName() const;
    void ls();
    void makefolder(string);
    void makeFile(string);
    list <Directory *> getSubFolder() const;
    list <File *> getFiles() const;
    Directory *getParent() const;
};

#endif // DIRECTORY_H