#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Directory.h"
#include <list>
#include <vector>
using namespace std;

class FileSystem
{
private:
    list <Directory*> Directorys;
    Directory* root;

public:
    FileSystem();
    ~FileSystem();
    void rm(vector <string>);
    void touch(vector <string>);
    void mkdir(vector <string>);
    void ls(vector <string>);
    void cd(vector <string>);
    //void inputCheck(string , string );
    void commandCaller(string, string);
    Directory* currentDir;
    void start();
    
};

#endif // FILESYSTEM_H