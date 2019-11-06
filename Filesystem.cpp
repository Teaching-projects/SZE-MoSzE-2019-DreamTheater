#include "Filesystem.h"
#include <sstream>
#include <vector>
#include <map>

FileSystem::FileSystem(){
root=new Directory("root",nullptr);
currentDir=root;
}
FileSystem::~FileSystem(){
delete root;
}

void FileSystem::touch(string fileName){
    if(currentDir->getFiles().empty()){
        //push a new file
        currentDir->makeFile(fileName);
        return;
    }
        //check that the file is already exits
    for(auto i:currentDir->getFiles()){
        if(i->getName()==fileName){
            cout<<"The file is already exits"<<endl;
            return;
        }
    }
    currentDir->makeFile(fileName);
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


/*
void FileSystem::inputCheck(string command, string arg){
    if(arg == "" && command != "ls"){
        cout<<"Invalid argument"<<endl;
        return;
    }
    vector<string> setOfCommands = {"ls", "cd", "mkdir","touch"}; 
    for(string i : setOfCommands){
        if(i == command){
            commandCaller(i, arg);
        }
    }
    return;
}*/

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
            this->cd(arg);
        }
        else if (command=="mkdir")
        {
            this->mkdir(arg);
        }
        else if (command=="touch")
        {
            this->touch(arg);
        }
        else cout<<"Invalid command"<<endl;
    } while (command!="quit");
}