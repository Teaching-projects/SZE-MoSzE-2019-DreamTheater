#ifndef DIRECTORY_H
#define DIRECTORY_H
#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "File.h"

using namespace std;

class Directory
{
private:
    string name;
    Directory* parent;
    list <Directory*> subFolders;
    list <File*> files;
    
public:
    bool noSubfolder();
    bool noFile();
    Directory(string,Directory*);
    ~Directory();
    string getName() const;
    Directory* searchDir(string);
    File* searchFile(string);
    template <typename T>
    void move(T);
    void ls();
    void remove(Directory *);
    void makefolder(string);
    bool validFileFormat(string);
    void makeFile(string);
    void echo(string, string);
    list <Directory *> getSubFolders() const;
    list <File *> getFiles() const;
    Directory* getParent() const;
    void setParent(Directory*);
    void setName(string s){name = s;};

};

#endif // DIRECTORY_H