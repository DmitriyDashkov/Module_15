//#include <iostream>
#include "chat.h"
#include "hash.cpp"


int main()
{
    Chat chat;
    chat.reg((char*)"apple", (char*)"12345sdgv");
    chat.reg((char*)"qw", (char*)"12345");
    chat.reg((char*)"qdsvsw", (char*)"1vsdvsddv2345");



    cout << chat.login((char*)"qdsvsw", (char*)"1vsdvsddv2345");


    return 0;
}

