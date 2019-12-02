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
    string s = v.front();
    if (v.size() > 0) {
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
    bool hasF = hasFile(filename);
    bool hasD = hasDir(filename);
    if(hasD){
        cout <<"Invalid filename!"<<endl;
        return;
    } else {
        if(hasF){
            currentDir->echo(content, filename);
        }else {
            currentDir->makeFile(filename);
            currentDir->echo(content, filename);
        }
        return;
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
    if(currentDir->getSubFolders().empty()){  
        cout << "The directory is not exits!"<< endl;
        return;
    }
    if(!currentDir->searchDir(arg)->getSubFolders().empty()){
        cout << "The directory has content in it!"<< endl;
        return;
    }
    currentDir->remove(currentDir->searchDir(arg));
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
    return;
}

void FileSystem::ls(){
    if(!currentDir->getSubFolders().empty()){
        //call Directory class function
        currentDir->ls();
        return;
    }
    cout<<""<<endl;
    return;
}

bool FileSystem::cd(string folder){
    if(folder == ".."){
        if(currentDir->getParent() == nullptr){
            return false;
        }
        currentDir = currentDir->getParent();
        return true;
    }
    if(hasDir(folder)){
        currentDir = currentDir->searchDir(folder);
        return true;
    }
cout<< "The "<< folder <<" folder is not exits!"<< endl;
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
string FileSystem::followPath(string path, bool needLastArg = false, bool startFromCurrentDir = false){
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
    if(startFromCurrentDir == true) {currentDir = start;}
    return returnLastArg;
}

bool FileSystem::loadFile(string command){
    File* loadedFile = currentDir->searchFile(command);
    string line, lineHelper = "";
    bool exit = true;
    if(loadedFile != nullptr){
        cout << loadedFile->getContent() << '\r' << flush;
        do{
            getline(cin,line);
            lineHelper = line;
            if(line.erase(0,line.size()-4) == "exit"){
                exit = false;
                lineHelper = lineHelper.substr(0, lineHelper.size()-4);
            }  
        } while(exit);
        loadedFile->setContent(lineHelper);        
        return true;
    }
    return false;
}

bool FileSystem::inputCheck(string command, vector <string> arg, bool isloaded){
    if(isloaded) return true;
    if(arg.empty() && command != "ls"){
        cout<<"Invalid argument"<<endl;
        return false;
    }
    vector<string> setOfCommands = {"ls", "cd", "mkdir","touch", "rm", "echo", "mv"}; 
    for(string i : setOfCommands){
        if(i == command){
            return true;
        }
    }
    cout << "Invalid command!"<< endl;
    return false;
}
template<typename T>
list<T*> deleteFromList(list<T*> items, T* target){
    typename list<T*>::iterator i = items.begin();
    while (i != items.end())
    {
        if (*i ==  target)
        {
            items.erase(i++);  // alternatively, i = items.erase(i), delete and increase its value after;
        }
        else
        {
            ++i;
        }
    }
    return items;
}
void FileSystem::mv(string movedPath, string destinationPath){
    Directory * startFromHere = currentDir;
    string moved, destination;
    Directory * movedPointerDir = nullptr;
    File * movedPointerFile = nullptr;
    Directory * movedToPointer = nullptr;

    moved = followPath(movedPath, true);
    //decide if folder or file 
    if(hasDir(moved)){
        movedPointerDir = currentDir->searchDir(moved);
        //delete from list
        currentDir->setSubFolders(deleteFromList(currentDir->getSubFolders(),movedPointerDir));
    } else if(hasFile(moved)){
        movedPointerFile = currentDir->searchFile(moved);
        //delete from list
        currentDir->setFiles(deleteFromList(currentDir->getFiles(),movedPointerFile));
    } else {
        cout << "The folder or file that you want to move is not exits!"<<endl;
        currentDir = startFromHere;
        return;
    }
    currentDir = startFromHere;
    destination = followPath(destinationPath, true);
    movedToPointer = currentDir->searchDir(destination);
    if(movedPointerDir != nullptr){
        //cannot move the folder with the same name to the subfolders
        if(movedToPointer != nullptr && movedToPointer->searchDir(moved) == nullptr){
            movedPointerDir->setParent(movedToPointer);
            movedToPointer->addFolder(movedPointerDir);
        } else if(!hasDir(moved)){
            //if destination is invalid move to currentDir
            cout<< "Set the name of the folder from " << moved << " to: ";
            getline(cin,moved);
            movedPointerDir->setName(moved);
            movedPointerDir->setParent(currentDir);
            currentDir->addFolder(movedPointerDir);
        } else {
            //set back the deleted folder
            followPath(movedPath, true);
            currentDir->addFolder(movedPointerDir);
            cout << "The folder is already exits at the destination!"<<endl;
        }
    } else if(movedPointerFile != nullptr) {
        //cannot move the file with the same name to the files list
        if(movedToPointer != nullptr && movedToPointer->searchFile(moved) == nullptr){
            movedToPointer->addFile(movedPointerFile);
        } else if(!hasFile(moved)){
            //if destination is invalid move to currentDir
            cout<< "Set the name of the file from " << moved << " to: ";
            getline(cin,moved);
            //valid the fileformat
            if(!currentDir->validFileFormat(moved)){
                cout << "Invalid file format!"<<endl;
                return;
            }
            movedPointerFile->setName(moved);
            currentDir->addFile(movedPointerFile);
        } else {
            //set back deleted file
            followPath(movedPath, true);
            currentDir->addFolder(movedPointerDir);
            cout << "The file is already exits at the destination!"<<endl;
        }
    }
    currentDir = startFromHere;
}

void FileSystem::start(){
    vector <string> args;
    string inputHelper;
    string command;
    bool completedCommand;
    bool fileLoaded;
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
        fileLoaded = loadFile(command);
        if(inputCheck(command, args, fileLoaded)){
            (fileLoaded) ? completedCommand = true : completedCommand = false;
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
            else if(command=="mv" && args.size() <= 2)
            {
                if(args.size() == 1) {
                cout << "Need more argument to use this command! mv sytanx: mv <path to a file/directory> <destination>"<<endl;
                } else{
                    completedCommand = true;
                    inputHelper = followPath(args[0], true, true);
                    if(inputHelper != ""){
                        //add back the poped last string
                        inputHelper = followPath(args[1], true, true);
                        if(inputHelper != ""){
                            mv(args[0], args[1]);
                        }
                    }
                }
            }
            if(!completedCommand)cout << "Too many arguments!"<< endl;
        }
    } while (command!="quit");
}