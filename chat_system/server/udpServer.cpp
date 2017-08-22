#include "udpServer.h"


udpServer::udpServer(const std::string _ip, const int &_port)
    :ip(_ip)
    ,port(_port)
    ,pool(1024)
{}

void udpServer::initServer()
{
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        print_log("create socket error!", FATAL);        
        exit(1);
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip.c_str());

    if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
        print_log("bind socket error!", FATAL);
        exit(2);
    }
}

void udpServer::delUser(const struct sockaddr_in &remote)
{
    std::map<in_addr_t, struct sockaddr_in>::iterator iter = user_list.find(remote.sin_addr.s_addr);
    if(iter == user_list.end()){
        user_list.erase(iter->first);
    }
}

void udpServer::addUser(const struct sockaddr_in &remote)
{
    user_list.insert(std::pair<in_addr_t, struct sockaddr_in>(remote.sin_addr.s_addr, remote));
}

int udpServer::recvData(std::string &outString)
{
    char buf[1024];//SIZE->1024
    struct sockaddr_in remote;
    socklen_t len = sizeof(remote);

    ssize_t s = recvfrom(sock, buf, sizeof(buf),0, (struct sockaddr*)&remote, &len);
    if(s > 0){
        buf[s] = '\0';

        outString = buf;
        pool.putData(outString);
        dataType data;
        data.stringToValue(outString);
        if(data.cmd == "Quit"){
            delUser(remote);        
        }else{
            addUser(remote);
        }

    }
    return s;
}

int udpServer::sendData(std::string &inString, struct sockaddr_in &remote, socklen_t &len)
{
    ssize_t s = sendto(sock, inString.c_str(), inString.size(), 0, (struct sockaddr*)&remote, len);
    if(s > 0){
        //print_log()        
    }
    return s;
}

int udpServer::brocast()
{
    std::string msg;
    pool.getData(msg);
    std::map<in_addr_t, struct sockaddr_in>::iterator iter = user_list.begin();
    socklen_t len = 0;
    for(; iter != user_list.end(); iter++){
        len = sizeof(iter->second);
        sendData(msg, iter->second, len);
    }

}

udpServer::~udpServer()
{
   close(sock); 
}
