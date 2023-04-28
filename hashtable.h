#pragma once
#include <string>
#include <string.h>
#define LOGINLENGTH 10  // длина логина
//typedef string Login[LOGINLENGTH]; // тип логин
using namespace std;


class HashTable
{
private:
    enum enPairStatus {
        free,       //свободен
        engaged,    //занят
        deleted     //удален
    };
    struct Pair {               //пара ключ-значение
        char login[LOGINLENGTH];            //логин
        int hPassword;           //хэш пароля
        enPairStatus status;    //состояние ячейки
        Pair():
                login(""),
                hPassword(-1),
                status(enPairStatus::free){}
        Pair(char log[LOGINLENGTH], int pass) :     //конструктор копирования
            hPassword(pass),
            status(enPairStatus::engaged)
            {
                strcpy(login, log);
            }
//        Pair& operator = (const Pair& other) {      //оператор присваивания
//            strcpy(login, other.login);
//            strcpy(password, other.password);
//            status = other.status;
//            return *this;
//        }
    };

public:
    HashTable();
    ~HashTable();
    int hash_func(string fr_name, int offset);
    Pair* array;
    int mem_size;
    int count;
    void add(char log[LOGINLENGTH], int hPass);
    void del(string log);
    bool find(string log);
    void resize();
};
