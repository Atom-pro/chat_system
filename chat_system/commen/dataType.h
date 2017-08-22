#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#include <iostream>
using namespace std;
#include <string>
#include "jsonApi.h"

#define SIZE 1024

class dataType{
public:
    int stringToValue(string &inString);
    int valueToString(string &outString);
public:
    string name;
    string school;
    string msg;
    string cmd;
};




#endif
