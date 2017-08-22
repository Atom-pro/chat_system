#ifndef _WINDOWS_H_
#define _WINDOWS_H_

#include <iostream>
#include <ncurses.h>

class window{
public:
    window();
    void refreshMyWindow(WINDOW* win);
    void clrNumsLines(WINDOW *win, int begin, int nums);
    void getStringFromwin(WINDOW* win, std::string &outString);
    void putStringTowin(WINDOW* win, int start_y, int start_x, std::string &msg);
    void createHeader();
    void createOutput();
    void createFriendList();
    void createInput();
    ~window();
public:
    WINDOW *header;
    WINDOW *output;
    WINDOW *friend_list;
    WINDOW *input;


};

#endif
