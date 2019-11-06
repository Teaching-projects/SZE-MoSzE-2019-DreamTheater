#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Directory.h"
#include <list>
using namespace std;

class FileSystem
{
private:
    list <Directory*> Directorys;
    Directory* root;
public:
    FileSystem();
    ~FileSystem();
    void touch(string);
    void mkdir(string);
    void ls();
    void cd(string);
    //void inputCheck(string , string );
    void commandCaller(string, string);
    Directory* currentDir;
    void start();
    
};

#endif // FILESYSTEM_H