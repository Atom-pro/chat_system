#ifndef _DATA_POOL_H_
#define _DATA_POOL_H_

#include <iostream>
#include <vector>
#include <string>
#include <semaphore.h>

class data_pool{
public:
    data_pool(int _cap);
    void getData(std::string &outString);
    void putData(const std::string &inString);
    ~data_pool();
private:
    data_pool(const data_pool&);
private:
    int cap;
    int size;
    int product_step;
    int comsumer_step;
    sem_t blank;
    sem_t data;
    std::vector<std::string> pool;
};


#endif
