#include "Filesystem.h"
#include <sstream>
#include <vector>
#include <map>

FileSystem::FileSystem(){
root=new Directory("root",nullptr);
currentDir=root;
}
FileSystem::~FileSystem(){
for(auto& i : Directorys){
    delete i;
}
delete root;
}


void FileSystem::touch(vector <string> args){
    if(currentDir->noFile()){
        //push a new file
        currentDir->makeFile(args.front());
        return;
    }
        //check that the file is already exits
    for(auto i:currentDir->getFile()){
        if(i->getName()==args.front()){
            cout<<"The file is already exits"<<endl;
            return;
        }
    }
    currentDir->makeFile(args.front());
}

void FileSystem::rm(vector <string> args){
    if(currentDir->noSubfolder()){  
        cout << "The directory is not exits!"<< endl;
        return;
    }
    if(!currentDir->searchDir(args.front())->getSubFolder().empty()){
        cout << "The directory has content in it!"<< endl;
        return;
    }
    currentDir->remove(args.front());
}

void FileSystem::mkdir(vector <string> args){
    if(currentDir->noSubfolder()){
        //push a new subfolder
        currentDir->makefolder(args.front());
        return;
    }
    //check that the dir is already exits
    for(auto i:currentDir->getSubFolder()){
        if(i->getName()==args.front()){
            cout<<"The directory is already exits"<<endl;
            return;
        }
    }
    currentDir->makefolder(args.front());
    return;
}

void FileSystem::ls(vector <string> s){
    if(!currentDir->noSubfolder()){
        //call Directory class function
        currentDir->ls();
        return;
    }
    cout<<""<<endl;
    return;
}

void FileSystem::cd(vector <string> args){
if(args.front() == ".."){
    if(currentDir->getParent() == nullptr){
        return;
    }
    currentDir=currentDir->getParent();
    return;
}
for(auto& i:currentDir->getSubFolder()){
    if(i->getName()==args.front()){
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
    vector <string> arg;
    string inputHelper;
    string command;
    do{
        cout<<"~";
        getline(cin,inputHelper);
        istringstream line(inputHelper);
        command="";
        line>>command;
        while(line){
            line >> inputHelper;

            cout << endl;
            cout << "The args is: "<< inputHelper;

            arg.push_back(inputHelper);
        };
        //sets the strings from line
        if (command=="ls")
        {
            this->ls(arg);
        }
        else if (command=="cd")
        {
            this->cd(arg);
        }
        else if (command=="mkdir")
        {
            this->mkdir(arg);
        }
        else if (command=="rm")
        {
            this->rm(arg);
        }
        else if (command=="touch")
        {
            this->touch(arg);
        }
        else cout<<"Invalid command"<<endl;
    } while (command!="quit");
}