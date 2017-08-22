#ifndef _UDPSERVER_H_
#define _UDPSERVER_H_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <pthread.h>
#include "log.h"
#include "data_pool.h"
#include "dataType.h"

class udpServer{
public:
    udpServer(const std::string _ip, const int &_port);
    void initServer();
    int recvData(std::string &outString);
    int sendData(std::string &inString, struct sockaddr_in &remote, socklen_t &len);
    int brocast();
    ~udpServer();

private:
    void addUser(const struct sockaddr_in &remote);
    void delUser(const struct sockaddr_in &remote);
    udpServer(const udpServer&);
private:
    int sock;
    std::string ip;
    int port;
    std::map<in_addr_t, struct sockaddr_in> user_list;
    data_pool pool;
};

#endif
