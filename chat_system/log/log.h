#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>
#include <string>

#define NORMAL 0
#define NOTICE 1
#define WARNING 2
#define FATAL 3
void print_log(std::string msg, int _level);

#endif
