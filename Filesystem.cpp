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
int FileSystem::cd(string t){
if(t==".."){
    currentDir=currentDir->getParent();
    return 1;
}
for(auto& i:currentDir->getSubFolder()){
    if(i->getName()==t){
    currentDir=i;
    return 1;
    }
}
return 0;
}
void FileSystem::start(){
string command;
string completeCommand;
string arg;
do{
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
           if(arg==".."){
                if(currentDir==root){
                cout<<"We are in the root, you can't apply <cd ..> command"<<endl;
           }
           else
               currentDir=currentDir->getParent();
           }
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