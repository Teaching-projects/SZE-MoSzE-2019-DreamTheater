#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <string>
#include <list>
using namespace std;

class File
{
private:
    string name;
    string content;

public:
    File(string fName);
    ~File();
    string getName() const;
    string getContent() const;
    void setContent(string);
    void setName(string s){name = s;};
};


#endif // FILE_H