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
void Directory::echo(string content, File * file){
    file->setContent(content);
}
void Directory::ls(){
    //Loop though the current directory subfolders and list them
    for(auto i:this->getSubFolders()){
        cout<< i->getName() + "\t";
    }
    for(auto i:this->getFiles()){
        cout<< i->getName() + "\t";
    }
    cout << endl;
    return;
}
Directory* Directory::searchDir(string s){
    for(auto& i : subFolders){
        if(i->getName() == s){
            return i;
        }
    }
    return nullptr;
}
File* Directory::searchFile(string s){
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
        return;
    } else {
        cout << "The directory is not exits!"<< endl;
        return;
    }
}
bool Directory::validFileFormat(string s){
    vector <string> validFormats= {"json","xml"};
    s = s.erase(0,s.find('.')+1);
    for(string i : validFormats){
        if(i == s){
            return true;
        }
    }
    return false;
}
File* Directory::makeFile(string s){
    if(validFileFormat(s)){
        //push a new file to the files list
        File * f = new File(s);
        files.push_back(f);
        return f;
    } else {
        cout << "Invalid file format!"<<endl;
        return nullptr;
    }
}
void Directory::makefolder(string s){
    //push a new folder and set the parent to the function caller 
subFolders.push_back(new Directory(s,this));
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
void Directory::setParent(Directory* setParent){
parent = setParent;
}

