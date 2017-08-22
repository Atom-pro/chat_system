#include "data_pool.h"

data_pool::data_pool(int _cap)
    :cap(_cap),
    size(0),
    pool(_cap)
    {
        product_step = 0;
        comsumer_step = 0;
        sem_init(&blank, 0, cap);
        sem_init(&data, 0, 0);
    }

void data_pool::getData(std::string &outString)
{
    sem_wait(&data);
    outString = pool[comsumer_step];
    comsumer_step++;
    comsumer_step %= cap;
    size--;
    sem_post(&blank);
}

void data_pool::putData(const std::string &inString)
{
    sem_wait(&blank);
    pool[product_step] = inString;
    product_step++;
    product_step %= cap;
    size++;
    sem_post(&blank);
}

data_pool::~data_pool()
{
    cap = 0;
    size = 0;
    product_step = 0;
    comsumer_step = 0;
    sem_destroy(&blank);
    sem_destroy(&data);
}
