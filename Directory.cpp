#include "Directory.h"
#include "File.h"

Directory::Directory(string n,Directory* p){
this->name=n;
this->parent=p;
}
Directory::~Directory(){
    for(auto& i:subFolders){
        delete i;
    }
    for(auto& i: files){
        delete i;
    }
}
string Directory::getName() const{
return name;
}
void Directory::echo(string content, string filename){
    File * file = searchFile(filename);
    if(file == nullptr){
        file = makeFile(filename);
        file->setContent(content);
    } else {
        file->setContent(content);
    }
}
void Directory::ls(){
    //Loop though the current directory subfolders and list them
    for(auto i:getSubFolders()){
        cout<< i->getName() + "\t";
    }
    for(auto k:getFiles()){
        cout<< k->getName() + "\t";
    }
    cout << endl;
    return;
}
Directory* Directory::searchDir(string s) const{
    for(auto& i : subFolders){
        if(i->getName() == s){
            return i;
        }
    }
    return nullptr;
}
File* Directory::searchFile(string s) const{
    for(auto& i : getFiles()){
        if(i->getName() == s){
            return i;
        }
    }
    return nullptr;
}
void Directory::remove(Directory * s){
    if(s != nullptr){
        subFolders.remove(s);
    } else {
        cout << "The directory is not exits!"<< endl;
    }
}
File * Directory::makeFile(string s){
    //push a new file to the files list
    File * f = new File(s);
    files.push_back(f);
return f;
}
void Directory::makefolder(string s){
    //push a new folder and set the parent to the function caller 
subFolders.push_back(new Directory(s,this));
return;
}
list<Directory *> Directory::getSubFolders() const{
return subFolders;
}
list<File *> Directory::getFiles() const{
return files;
}
Directory *Directory::getParent() const{
return parent;
}