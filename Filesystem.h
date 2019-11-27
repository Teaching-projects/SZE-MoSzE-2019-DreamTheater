#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Directory.h"
#include <list>
#include <vector>
using namespace std;

class FileSystem
{
private:
    list <Directory*> listOfFolders;
    Directory* root;

public:
    FileSystem();
    ~FileSystem();
    string followPath(string, bool);
    void echo(string, string);
    void rm(string);
    void touch(string);
    void mkdir(string);
    void ls();
    bool cd(string);
    bool inputCheck(string , vector<string> );
    Directory* currentDir;
    void start();
    bool hasFile(string);
    bool hasDir(string);
    vector<string> processPath(string);
    
};

#endif // FILESYSTEM_H