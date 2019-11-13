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
    void rm(vector <string>);
    void touch(vector <string>);
    void mkdir(vector <string>);
    void ls(vector <string>);
    void cd(vector <string>);
    bool inputCheck(string , string );
    void commandCaller(string, string);
    Directory* currentDir;
    void start();
    bool hasFile(string);
    bool hasDir(string);
    bool checkDocsExits(string);
    
};

#endif // FILESYSTEM_H