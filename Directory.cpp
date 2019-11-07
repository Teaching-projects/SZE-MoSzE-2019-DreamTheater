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
    for(auto i:this->getFile()){
        cout<< i->getName() + "\t";
    }
    cout << endl;
    return;
}
Directory* Directory::searchDir(string s){
    for(auto& i : subFolder){
        if(i->getName() == s){
            return i;
        }
    }
    return nullptr;
}
File* Directory::searchFile(string s){
    for(auto& i : getFile()){
        if(i->getName() == s){
            return i;
        }
    }
    return nullptr;
}
void Directory::remove(string s){
    Directory* searchedDir = searchDir(s);
    cout<< searchedDir->getName()<< endl;
    if(searchedDir != nullptr){
        delete searchedDir;
        subFolder.remove(searchedDir);
    }
    return ;
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
list<File *> Directory::getFile() const{
return files;
}
Directory *Directory::getParent() const{
return parent;
}

bool Directory::noSubfolder(){
    if(getSubFolder().empty()){
        return true;
    }
    return false;
}
bool Directory::noFile(){
    if(getFile().empty()){
        return true;
    }
    return false;
}