#include "Filesystem.h"
#include <sstream>
#include <vector>
#include <map>

FileSystem::FileSystem(){
root=new Directory("root",nullptr);
currentDir=root;
}
FileSystem::~FileSystem(){
for(auto& i : listOfFolders){
    delete i;
}
delete root;
}
bool FileSystem::hasDir(string arg){
    for(auto i:currentDir->getSubFolders()){
        if(i->getName()==arg)return true;
    }
    return false;
}
bool FileSystem::hasFile(string arg){
    for(auto i:currentDir->getFiles()){
        if(i->getName()==arg)return true;
    }
    return false;
}
bool FileSystem::checkDocsExits(string docName){
    bool hasD = hasDir(docName);
    bool hasF = hasFile(docName);
    if(hasD || hasF){
        if(hasD){
            cout<<"There is already a folder with this name!"<<endl;
            return true;
        }
        if(hasF){
            cout<<"The file is already exits!"<<endl;
            return true;
        }
    }
    return false;
}

void FileSystem::touch(vector <string> args){
    bool docExits = checkDocsExits(args.front());
    if(!docExits){
        currentDir->makeFile(args.front());
    }
    else {
        return;
    }
}

void FileSystem::rm(vector <string> args){
    if(currentDir->getSubFolders().empty()){  
        cout << "The directory is not exits!"<< endl;
        return;
    }
    if(!currentDir->searchDir(args.front())->getSubFolders().empty()){
        cout << "The directory has content in it!"<< endl;
        return;
    }
    currentDir->remove(currentDir->searchDir(args.front()));
}

void FileSystem::mkdir(vector <string> args){
    bool docExits = checkDocsExits(args.front());
    if(!docExits){
        currentDir->makefolder(args.front());
    }else {
        return;
    }
}

void FileSystem::ls(vector <string> s){
    currentDir->ls();
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
    if(hasDir(args.front())){
        currentDir = currentDir->searchDir(args.front());
        return;
    }
cout<< "The folder is not exits!"<< endl;
return;
}

bool FileSystem::inputCheck(string command, string arg){
    if(arg == "" && command != "ls"){
        cout<<"Invalid argument"<<endl;
        return false;
    }
    vector<string> setOfCommands = {"ls", "cd", "mkdir","touch", "rm"}; 
    for(string i : setOfCommands){
        if(i == command){
            return true;
        }
    }
    cout << "Invalid command!"<< endl;
    return false;
}

void FileSystem::start(){
    vector <string> arg;
    string inputHelper;
    string command;
    do{
        cout<<"Comerick@: "<< currentDir->getName()<< endl;
        cout<<"~";
        getline(cin,inputHelper);
        istringstream line(inputHelper);
        command="";
        arg.clear();
        while(line){
            inputHelper = "";
            line >> inputHelper;
            arg.push_back(inputHelper);
        };
        command = arg.front();
        //clear the vector empty parts because of the istringstream
        arg.erase(arg.begin());
        arg.erase(arg.end());
        //sets the strings from line
        if(inputCheck(command, arg.front())){
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
            else if(command=="touch")
            {
                this->touch(arg);
            }
        }
    } while (command!="quit");
}