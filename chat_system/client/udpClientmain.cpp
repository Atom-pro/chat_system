#include "udpClient.h"
#include "dataType.h"
#include "window.h"
#include <signal.h>
using namespace std;
static void Usage(std::string proc)
{
    cout<<"Usage: "<<proc<<"[remote_ip] [remote_port]"<<endl;
}

window win;
string name;
string school;
dataType sendData;
dataType recvData;
udpClient *sig_cli = NULL;


static void* run_header(void *arg)
{
    std::string msg = "Welcome to My chatroom";
    int step = 1;
    while(1){
        win.createHeader();
        int h = 0;
        int w = 0;
        getmaxyx(win.header, h, w);
        win.putStringTowin(win.header, h/2, step++, msg);
        win.refreshMyWindow(win.header);   
        win.clrNumsLines(win.header, h/2, 1);
        step %= w;
        step = (step == 0 ? 1: step);
        usleep(200000);

       // std::string str;
       // win.getStringFowin(win.input, str);    
       // getmaxyx(win.output, h, w);
       // win.putStringTowin(win.output, 1, 1, str);
      // win.refreshMyWindow(win.output);   
    }

}

static void* run_output_friend(void *arg)
{
    udpClient *_cli = (udpClient*)arg;
    int point = 1;
    win.createOutput();
    win.createFriendList();
    for(;;){
        int fpoint = 1;
        win.refreshMyWindow(win.output);
        win.refreshMyWindow(win.friend_list);

        std::string str;
        _cli->recvData(str);
        recvData.stringToValue(str);

        std::string tips = recvData.name;
        tips += "-";
        tips += recvData.school;

        std::string newFriend = tips;
        int h, w;

        if(recvData.cmd == "Quit"){
            _cli->delUser(newFriend);
        }else{
            tips += "#";
            tips += recvData.msg;

            getmaxyx(win.output, h, w);
            win.putStringTowin(win.output, point++, 1, tips);
           _cli->addUser(newFriend);
        }

        getmaxyx(win.friend_list, h, w);
        win.clrNumsLines(win.friend_list, 1, h-1);
        win.createFriendList();
        
        std::vector<std::string>::iterator iter = (_cli->flist).begin();
        for(; iter != (_cli->flist).end(); iter++){
            win.putStringTowin(win.friend_list, fpoint++, 1, *iter);
        }



        win.refreshMyWindow(win.output);
        win.refreshMyWindow(win.friend_list);

        point %= (h-1);
        if(point == 0){
            win.clrNumsLines(win.output, 1, h-1);
            win.createOutput();
            win.refreshMyWindow(win.output);
            win.createOutput();
            win.createOutput();
            point = 1;
        }
        usleep(100000);
    }
}

static void* run_input(void *arg)
{  
    udpClient *_cli = (udpClient*)arg;
    for(;;){
        win.createInput();
        win.refreshMyWindow(win.input);
        std::string tips = "Please Enter: ";
        int h = 0;
        int w = 0;
        getmaxyx(win.output, h, w);
        win.putStringTowin(win.input, 1, 1, tips);
        win.refreshMyWindow(win.input);
        
        std::string str;
        win.getStringFromwin(win.input, str);
        sendData.name = name;
        sendData.school = school;
        sendData.msg = str;
        sendData.cmd = "None";

        string sendString;
        sendData.valueToString(sendString);

        _cli->sendData(sendString);
        win.clrNumsLines(win.input, 1, 1);
        usleep(200000);
    }
}

void sendQuit(int sig)
{
    sendData.name = name;
    sendData.school = school;
    sendData.msg = "None";
    sendData.cmd = "Quit";
    std::string sendString;
    sendData.valueToString(sendString);
    sig_cli->sendData(sendString);
}


int main(int argc, char *argv[])
{
    if(argc != 5){
        Usage(argv[0]);
        exit(1);
    }
    int port = atoi(argv[2]);
    udpClient cli(argv[1], port);

    sig_cli = &cli;

    struct sigaction act;
    act.sa_handler = sendQuit;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(2, &act, NULL);

    name = argv[3];
    school = argv[4];
    cli.initClient();

    pthread_t top;
    pthread_t middle;
    pthread_t buttom;

    pthread_create(&top, NULL, run_header, NULL);
    pthread_create(&middle, NULL, run_output_friend,(void *)&cli );
    pthread_create(&buttom, NULL, run_input, (void*)&cli);

    pthread_join(top, NULL);
    pthread_join(middle, NULL);
    pthread_join(buttom, NULL);

    return 0;
}
