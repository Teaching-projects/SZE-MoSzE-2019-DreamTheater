#include "Directory.h"
#include "File.h"

Directory::Directory(string n,Directory* p){
this->name=n;
this->parent=p;
}
Directory::~Directory(){
for(auto& i:subFolder){
    delete i;
}
}
string Directory::getName() const{
return name;
}
void Directory::ls(){
    //Loop though the current directory subfolders and list them
    for(auto i:this->getSubFolder()){
        cout<< i->getName() + "\t";
    }
    for(auto i:this->getFiles()){
        cout<< i->getName() + "\t";
    }
    cout << endl;
    return;
}
void Directory::makeFile(string s){
    //push a new file to the files list
return files.push_back(new File(s));
}
void Directory::makefolder(string s){
    //push a new folder and set the parent to the function caller 
return subFolder.push_back(new Directory(s,this));
}
list<Directory *> Directory::getSubFolder() const{
return subFolder;
}
list<File *> Directory::getFiles() const{
return files;
}
Directory *Directory::getParent() const{
return parent;
}