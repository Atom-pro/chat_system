#ifndef _UDP_CLIENT_
#define _UDP_CLIENT_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "log.h"

class udpClient{
public:
    udpClient(const std::string _srv_ip, const int& _srv_port);
    void initClient();
    int recvData(std::string &outString);
    int sendData(const std::string &inString);
    void addUser(std::string &_friend);
    void delUser(std::string &_friend);
    ~udpClient();
    std::vector<std::string> flist; 

private:
    udpClient(const udpClient&);
private:
    int sock;
    std::string server_ip;
    int server_port;
};

#endif
