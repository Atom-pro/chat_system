#include "udpClient.h"



udpClient::udpClient(const std::string _srv_ip, const int &_srv_port)
    :server_ip(_srv_ip)
    ,server_port(_srv_port)
{}

void udpClient::initClient()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        //print_log("create socket error!", FATAL);        
        exit(1);
    }
}
void udpClient::addUser(std::string &_friend)
{
    std::vector<std::string>::iterator iter = find(flist.begin(), flist.end(), _friend);
    if(iter == flist.end()){
        flist.push_back(_friend);
    }
}

void udpClient::delUser(std::string &_friend)
{
    std::vector<std::string>::iterator iter = find(flist.begin(), flist.end(), _friend);
    if(iter != flist.end()){
        flist.erase(iter);    
    }
}

int udpClient::recvData(std::string &outString)
{
    char buf[1024];//SIZE->1024
    struct sockaddr_in remote;
    socklen_t len = sizeof(remote);
    ssize_t s = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&remote, &len);
    std::cout<<"2222222222222"<<std::endl;
    if(s > 0){
        buf[s] = '\0';
        outString = buf;
    }
    return s;
}

int udpClient::sendData(const std::string &inString)
{
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip.c_str());
    socklen_t len = sizeof(server);
    ssize_t s = sendto(sock, inString.c_str(), inString.size(), 0, (struct sockaddr*)&server, len);
    if(s > 0){
        //print_log()        
    }
    return s;
}

udpClient::~udpClient()
{
   close(sock); 
}
