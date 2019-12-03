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

string pop_front(vector<string> &v)
{
    string s = "";
    if (v.size() > 0) {
        s = v.front();
        v.erase(v.begin());
    }
    return s;
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
void FileSystem::echo(string content, string filename){
    bool hasD = hasDir(filename);
    if(hasD){
        cout <<"Invalid filename!"<<endl;
    } else {
        currentDir->echo(content, filename);      
    }
}

void FileSystem::touch(string arg){
    bool hasD = hasDir(arg);
    bool hasF = hasFile(arg);
    if(hasD || hasF){
        if(hasD){
            cout<<"There is already a folder with this name!"<<endl;
            return;
        }
        if(hasF){
            cout<<"The file is already exits!"<<endl;
            return;
        }
    }
    currentDir->makeFile(arg);
    return;
}

void FileSystem::rm(string arg){
    Directory * argPointer = currentDir->searchDir(arg);
    if(currentDir->getSubFolders().empty() || argPointer == nullptr){  
        cout << "The directory is not exits!"<< endl;
        return;
    }
    if(!argPointer->getSubFolders().empty()){
        cout << "The directory has content in it!"<< endl;
        return;
    }
    currentDir->remove(argPointer);
}

void FileSystem::mkdir(string arg){
    if(currentDir->getSubFolders().empty()){
        //push a new subfolder
        currentDir->makefolder(arg);
        return;
    }
    //check that the dir is already exits
    for(auto i:currentDir->getSubFolders()){
        if(i->getName()==arg){
            cout<<"The directory is already exits"<<endl;
            return;
        }
    }
    currentDir->makefolder(arg);
}

void FileSystem::ls(){
    currentDir->ls();
}

bool FileSystem::cd(string dir){
    if(dir == ".."){
        if(currentDir->getParent() == nullptr){
            return false;
        }
        currentDir=currentDir->getParent();
        return true;
    }
    if(hasDir(dir)){
        currentDir = currentDir->searchDir(dir);
        return true;
    }
cout<< "The "<< dir <<" folder is not exits!"<< endl;
return false;
}
vector <string> FileSystem::processPath(string path){
    vector<string> addedPath;
    string temp = "";
    for(auto& i: path){
        if(i != '/'){
            temp += i;
        } else {
            if(temp != ""){
                addedPath.push_back(temp);
                temp = "";
            }
        }
    }
    if (temp != "") addedPath.push_back(temp);
    return addedPath;
}
string FileSystem::followPath(string path, bool needLastArg = false){
    string s = "";
    Directory * start = currentDir;
    if(path == "/"){
        currentDir = root;
        return "/";
    }
    //this decide that path is absolute
    if(path[0] == '/') currentDir = root;
    vector<string> slicedPath = processPath(path); 
    string returnLastArg = slicedPath.back();
    //remove last arg which can be a file or dir
    if(needLastArg) slicedPath.pop_back();
    while(!slicedPath.empty()){
        if(!this->cd(pop_front(slicedPath))){
            currentDir = start;
            cout << "Invalid path!"<<endl;
            return "";
        }
    }
    return returnLastArg;
}

bool FileSystem::inputCheck(string command, vector <string> arg){
    if(arg.empty() && command != "ls"){
        cout<<"Invalid argument"<<endl;
        return false;
    }
    vector<string> setOfCommands = {"ls", "cd", "mkdir","touch", "rm", "echo"}; 
    for(string i : setOfCommands){
        if(i == command){
            return true;
        }
    }
    cout << "Invalid command!"<< endl;
    return false;
}

void FileSystem::start(){
    vector <string> args;
    string inputHelper;
    string command;
    bool completedCommand;
    do{
        cout<<"Comerick@: "<< currentDir->getName()<< endl;
        cout<<"~";
        getline(cin,inputHelper);
        istringstream line(inputHelper);
        command="";
        args.clear();
        while(line){
            inputHelper = "";
            line >> inputHelper;
            args.push_back(inputHelper);
        };
        command = args.front();
        //clear the vector empty parts because of the istringstream
        args.erase(args.begin());
        args.erase(args.end());
        //sets the strings from line
        if(inputCheck(command, args)){
            completedCommand = false;
            if (command=="ls")
            {
                completedCommand = true;
                if(args.size() == 1)followPath(args[0]);
                ls();
            }
            else if (command=="cd" && args.size() == 1)
            {
                completedCommand = true;
                followPath(args[0]);
            }
            else if (command=="mkdir" && args.size() == 1)
            {
                completedCommand = true;
                inputHelper = followPath(args[0], true);
                if(inputHelper != ""){
                    mkdir(inputHelper);
                }
            }
            else if (command=="rm" && args.size() == 1 )
            {
                completedCommand = true;
                inputHelper = followPath(args[0], true);
                if(inputHelper != ""){
                    rm(inputHelper);
                }
            }
            else if(command=="touch" && args.size() == 1)
            {
                completedCommand = true;
                inputHelper = followPath(args[0], true);
                if(inputHelper != ""){
                    touch(inputHelper);
                }
            }
            else if(command=="echo" && args.size() <= 2 ){
                completedCommand = true;
                if(args.size() == 1) {
                    cout << "Need more argument to use this command! Echo sytanx: echo <content> <destination>"<<endl;
                } else {
                    inputHelper = followPath(args[1], true);
                    if(inputHelper != ""){
                        echo(args[0], inputHelper);
                    }
                }
            }
            if(!completedCommand)cout << "Too many arguments!"<< endl;
        }
    } while (command!="quit");
}