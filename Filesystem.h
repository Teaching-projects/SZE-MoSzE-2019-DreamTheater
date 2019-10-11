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
    void mkdir(string);
    void ls();
    void cd(string);
    Directory* currentDir;
    void start();
};

#endif // FILESYSTEM_H