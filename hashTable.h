#ifndef HASHTABLE
#define HASHTABLE
#include "course.h"
#include "lecture.h"
#include <iostream>
#include <cmath>
#define A (sqrt((5)-1)/2)
#define EXPAND_RATE 10
#define INITIAL_SIZE 15
#define REDUCE_RATE 10 // to divide by


template <class T>
struct hash_element
{
    public:
    int key;
    T* data;
    hash_element* next;
    hash_element() :key(0), data(NULL), next(NULL){}
    hash_element(int key, T* data) : key(key) ,data(data), next(nullptr){}
    hash_element(const hash_element& target ) : key(target.key), data(target.data), next(target.next) {}
    hash_element& operator=(const hash_element &target)
    {
    if(this == &target) return *this;
    key=target.key;
    data=target.data;
    next=target.next;
    return *this;
    }
    ~hash_element() = default;
};

template <class T>
class hashTable
{
private:
    int original_size;//m.
    int num_of_elements;// counter - n.
    hash_element<T>** hash_array;
    int hash_function(int key);
    void expand();
    void reduce();
public:
    hashTable();
    hashTable(hashTable& target) : 
    original_size(target.original_size),num_of_elements(target.num_of_elements), hash_array(new hash_element<T>[target.original_size])
    {
        for(int i=0; i<original_size;i++){
            hash_array[i]=target.hash_array[i];
        }
    };
    void insert(T* hash_node, int key);
    T* find(int key);
    void removeElement(int key);
    ~hashTable();
};

template <class T>
hashTable<T>::~hashTable()
{
    for (int i = 0 ; i < original_size ; i++)
    {
        hash_element<T>* current = hash_array[i];
        while (current != NULL)
        {
            hash_element<T>* to_delete = current;
            current = current->next;
            delete(to_delete);
        }
    }
    delete[] hash_array;
}

template <class T>
hashTable<T>::hashTable() : original_size(INITIAL_SIZE), num_of_elements(0), hash_array(new hash_element<T>*[INITIAL_SIZE]) 
{
    for (int i = 0; i < original_size; i++)
    {
        hash_array[i] = NULL;
    }
}

template <class T>
int hashTable<T>::hash_function(int key)
{
    int hashed=0;
    hashed=original_size*(static_cast<int>(A*key)%1);
    return hashed;
}

template <class T>
void hashTable<T>::insert(T* hash_node, int key)
{
    hash_element<T>* new_hash_node = new hash_element<T>(key, hash_node);
    new_hash_node->next = hash_array[hash_function(key)];
    hash_array[hash_function(key)] = new_hash_node;
    if (num_of_elements >= 10*original_size)
    {
        expand();
    }
}

template<class T>
void hashTable<T>::expand(){
    hash_element<T>** hash_new_array = new hash_element<T>*[EXPAND_RATE*original_size];
    int previous_original_size = original_size;//next line we are updating to new size parameters
    original_size=EXPAND_RATE*original_size;//updating parameter m
    for (int i=0; i<original_size;i++){
        hash_new_array[i]=NULL;
    }
    for(int i=0;i<previous_original_size;i++){
        if(this->hash_array[i]!=NULL){
            hash_element<T>* current=hash_array[i];
            while(current!=NULL){
                current->next = hash_new_array[hash_function(current->key)];//if the slot is thaken,
                hash_new_array[hash_function(current->key)]=current;//then we'll insert current and
                //attach to it its next in line, else we are putting NULL next in line so it doesnt matter.
                current=current->next;      
            }
        }
        delete[](this->hash_array);
        this->hash_array=hash_new_array;
    }
}

template <class T>
void hashTable<T>::reduce()
{
    hash_element<T>** hash_new_array = new hash_element<T>** ((this.original_size)/REDUCE_RATE);
    int previous_original_size = this.original_size;//next line we are updating to new size parameters
    original_size= (this.original_size)/REDUCE_RATE;//updating parameter m
    for (int i=0; i<original_size;i++){
        hash_new_array[i]=NULL;
    }
    for(int i=0;i<previous_original_size;i++){
        if(this->hash_array[i]!=NULL){
            hash_element<T>* current=hash_array[i];
            while(current!=NULL){
                current->next = hash_new_array[hash_function(current->key)];//if the slot is thaken,
                hash_new_array[hash_function(current->key)]=current;//then we'll insert current and
                //attach to it its next in line, else we are putting NULL next in line so it doesnt matter.
                current=current->next;         
            }
        }
        delete[](this->hash_array);
        this->hash_array=hash_new_array;
    }
}

template <class T>
T* hashTable<T>::find(int key)
{
    hash_element<T>* res = hash_array[hash_function(key)];
    if (res == NULL)
    {
        return NULL;
    }
    else 
    {
        while (res != NULL)
        {
            if (res->key == key)
            {
                return res->data;
            }
            res = res->next;
        }
    }
    return NULL;
}

template <class T>
void hashTable<T>::removeElement(int key)
{
    hash_element<T>* res = hash_array[hash_function(key)];
    if (res == NULL)
    {
        return; // Element does not exict.
    }
    if (res->key == key)
    {
        hash_element<T>* to_delete = res;
        hash_array[hash_function(key)] = res->next;
        delete(to_delete);
    }
    else 
    {
        hash_element<T>* next_step = res->next;
        hash_element<T>* prev = res;
        while (res != NULL)
        {
            if (res->key == key)
            {
                prev->next = res->next;
                delete(res);
                break;
            }
            prev = res;
            res = next_step;
            next_step=next_step->next;
        }
    }
    if (num_of_elements <= (original_size/REDUCE_RATE))
    {
        reduce();
    }
}

#endif /* HASHTABLE */