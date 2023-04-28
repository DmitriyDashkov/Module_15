#include "chat.h"
#include "hash.cpp"

int hfunc(string password)      //хеш-функция
{
    int val{0};
    for(size_t i=0; i<password.length(); i++) {
        val += (password[i]);
    }
    const double A = 0.6;
    const int M = 1000;
    int res = int(M*(A*val-int(A*val)));
    return res;
}

AuthData::AuthData():
    login(""),
    passHash(nullptr)
{

}

AuthData::AuthData(char log[LOGINLENGTH], int* pHash)
{
    strcpy(login, log);
    passHash = pHash;
}

AuthData::~AuthData()
{
    if(passHash)
        delete [] passHash;
}

//AuthData& AuthData::operator = (const AuthData& other)
//{
//    strcpy(login, other.login);
//    if(pass_hash != nullptr)
//        delete [] pass_hash;
//    pass_hash = new int[NAMEPASSWORD];
//    memcpy(pass_hash, other.pass_hash, NAMEPASSWORD);
//    return *this;
//}

Chat::Chat()
{
    data_count = 0;
    hTable = new HashTable;
}



void Chat::reg(char log[LOGINLENGTH], char pass[]) {
    int digest = (hfunc(pass));
    hTable->add(log, digest);
    data_count++;
}

bool Chat::login(char log[LOGINLENGTH], string pass) {

    int hash2 = hfunc(pass);
    for(int i=0; i<SIZE; i++) {
        int index = hTable->hash_func(log, i);
        if(strcmp(log, hTable->array[index].login)==0) {
            int hash1 = hTable->array[index].hPassword;
            if(hash1 == hash2) {
               return true;
            }
        }
    }
    return false;
}
