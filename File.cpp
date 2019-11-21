#include <iostream>
#include "File.h"

using namespace std;


File::File(string fileName){
    name = fileName;
}
File::~File(){}

string File::getName() const {
    return name;
}
string File::getContent() const {
    return content;
}
void File::setContent(string s){
    content = s;
}