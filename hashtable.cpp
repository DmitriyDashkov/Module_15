#include "hashtable.h"
#include "hash.cpp"

HashTable::HashTable()
{
    count = 0;
    mem_size = 8;
    array = new Pair[mem_size];
}

HashTable::~HashTable()
{
    delete [] array;
}

int HashTable::hash_func(string log, int offset)
{
    int sum=0;
    size_t i=0;
    for(; i<log.length(); i++) {
        sum += log[i];
    }
    //квадратичные пробы
    return (sum % mem_size + offset*offset) % mem_size;
}

void HashTable::add(char log[LOGINLENGTH], int hPass)
{
    int index = -1;
    int i = 0;
    for(; i<mem_size; i++){
        index = hash_func(log, i);
        if(array[index].status != enPairStatus::engaged) {
            //найдена пустая ячейка, занимаем ее
            break;
        }
    }
    if(i>=mem_size) {
        resize();               //увеличиваем размер
        add(log, hPass);        //добавляем новый элемент, ставший причиной увеличения
    }
    else {                      //кладем в свободную ячейку пару
        array[index] = Pair(log, hPass);
        count++;
    }
}

bool HashTable::find(string log)
{
    for(int i =0;i < mem_size; i++) {
            int index = hash_func(log, i);
            if( array[index].status == enPairStatus::engaged &&
              (array[index].login == log) ) {
                return true;
            } else if(array[index].status == enPairStatus::free) {
                return false;
            }
        }
        return false;
}

void HashTable::del(string login)
{
    int index = -1, i = 0;
        // берем пробы по всем i от 0 до размера массива
        for(;i < mem_size; i++) {
            index = hash_func(login, i);
            if( array[index].status == enPairStatus::engaged &&
              (array[index].login == login) ) {
                array[index].status = enPairStatus::deleted;
                count--;
                return;
            } else if(array[index].status == enPairStatus::free) {
                return;
            }
        }
}

void HashTable::resize()
{
    Pair* save = array;                 //запоминаем старый массив
    int save_ms = mem_size;
    mem_size *= 2;                      //увеличиваем массив в 2 раза
    count = 0;                          //обнуляем кол-во элементов
    array = new Pair[mem_size];       //выделяем новую память
    for(int i=0; i<save_ms; i++) {
        Pair& oldPair = save[i];
        if(oldPair.status==enPairStatus::engaged) {
            add(oldPair.login, oldPair.hPassword);
        }
    }
    delete [] save;
}
