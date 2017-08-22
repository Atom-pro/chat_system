#include "log.h"

static std::string level[]={
    "[NORMAL] ",
    "[NOTICE] ",
    "[WARNING] ",
    "[FATAL] ",
};


void print_log(std::string msg, int _level)
{
#ifndef DEBUG
    if(_level >= 0 && _level<=3){
        
        std::cout<<"level[_level]"<<msg<<std::endl;
    }
#endif
}
