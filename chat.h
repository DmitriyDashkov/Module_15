#pragma once

#include "string.h"
#include "hashtable.h"
#include <string>
#include <iostream>
using namespace std;
typedef unsigned int uint;

#define SIZE 10



struct AuthData {
    AuthData();
    ~AuthData();
    AuthData(char log[LOGINLENGTH], int* pHash);
    //AuthData& operator = (const AuthData& other);

    char login[LOGINLENGTH];
    int* passHash;
};


class Chat {
private:
    AuthData data[SIZE];
    int data_count;
public:
    Chat();
    HashTable* hTable;
    void reg(char log[LOGINLENGTH], char pass[]);
    bool login(char log[LOGINLENGTH], string pass);
};
