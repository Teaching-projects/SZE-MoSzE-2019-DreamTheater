#include "Filesystem.h"
#include <sstream>

FileSystem::FileSystem(){
root=new Directory("root",nullptr);
currentDir=root;
}
FileSystem::~FileSystem(){
delete root;
}
void FileSystem::mkdir(string dirName){
    if(currentDir->getSubFolder().empty()){
        //push a new subfolder
        currentDir->makefolder(dirName);
        return;
    }
    //check that the dir is already exits
    for(auto i:currentDir->getSubFolder()){
        if(i->getName()==dirName){
            cout<<"The directory is already exits"<<endl;
            return;
        }
    }
    currentDir->makefolder(dirName);
    return;
}

void FileSystem::ls(){
    if(!currentDir->getSubFolder().empty()){
        //call Directory class function
        currentDir->ls();
        return;
    }
    cout<<""<<endl;
    return;
}
void FileSystem::cd(string a){
if(a==".."){
    if(currentDir->getParent() == nullptr){
        return;
    }
    currentDir=currentDir->getParent();
    return;
}
for(auto& i:currentDir->getSubFolder()){
    if(i->getName()==a){
    currentDir=i;
    return;
    }
}
cout<< "The folder is not exits!"<< endl;
return;
}
void FileSystem::start(){
string command;
string completeCommand;
string arg;
do{
    cout<<"~";
    getline(cin,completeCommand);
    istringstream line(completeCommand);
    command=arg="";
    //sets the strings from line
    line>>command;
    line>>arg;
        if (command=="ls")
        {
         //call FileSystem function
           this->ls();
        }
        else if (command=="cd")
        {
            if(arg=="") cout<<"Enter the name of the folder"<<endl;
            else{
                this->cd(arg);
            }
        }
        else if (command=="mkdir")
        {
            if(arg=="")
                cout<<"The folder must be named!"<<endl;
            else
            {
               this->mkdir(arg);
            }
        }
        else cout<<"Invalid command"<<endl;
    } while (command!="quit");
}