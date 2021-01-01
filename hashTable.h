#ifndef HASHTABLE
#define HASHTABLE
#include "course.h"
#include <iostream>
#include <cmath>
#define A=sqrt((5)-1)/2
#define EXPAND_RATE = 10
#define INITIAL_SIZE = 15


template <class T>
struct hash_element
{
    public:
    int key;
    T* data;
    T* next;
    hash_element() :key(0), data(NULL), next(NULL){};
    hash_element(int key, T* data) : key(key) data(data), next(nullptr){};
    hash_element(const hash_element& target ) : key(target.key), data(target.data), next(target.next) {}
    hash_elemnt& operator=(const hash_element &target){
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
    int num_of_courses;// counter - n.
    hash_element<T>** hash_array;
    int hash_function(int key);
    void expand();
public:
    hashTable();
    hashTable(hashTable& target) : 
    original_size(target.original_size),num_of_courses(target.num_of_courses), hash_array(new hash_element[target.original_size])
    {
        hash_element* new_hash_array= new hash_element[target.original_size];
        for(int i=0; i<original_size;i++){
            new_hash_array[i]=target.hash_array[i];
        }
    };
    void insert(T& hash_node, int key);
    T* find(int key);
    void removeCourse(int key);
    ~hashTable();
};

template <class T>
hashTable<T>::hashTable() : original_size(INITIAL_SIZE), num_of_courses(0), hash_array(new hash_element<T>[INITIAL_SIZE]= {NULL}) {}

template <class T>
int hashTable<T>::hash_function(int key)
{
    int hashed=0;
    hashed=m*((A*key)%1);
    return hashed;
}

template <class T>
void hashTable<T>::insert(T& hash_node, int key)
{
    hash_element<T>* hash_node = new hash_element<T>(key, &hash_node);
    hash_node->next = hash_array[hash_function(key)];
    hash_array[hash_function(key)] = hash_node;
    if (num_of_courses >= 10*original_size)
    {
        expand();
    }
}

template<class T>
void hashTable<T>::expand(){
    hash_element<T>** hash_new_array = new hash_element<T>** hash_element[EXPAND_RATE*this.original_size];
    int previous_original_size = this.original_size;//next line we are updating to new size parameters
    original_size=EXPAND_RATE*this.original_size;//updating parameter m
    for(int i=0;i<previous_original_size;i++){
        if(this->hash_array[i]!=NULL){
            hash_element* current=hash_array[i];
            while(current->next!=NULL){
                current->next = hash_new_array[hash_function(current->key)];//if the slot is thaken,
                hash_new_array[hash_function(current->key)]=current;//then we'll insert current and
                //attach to it its next in line, else we are putting NULL next in line so it doesnt matter.
            }
        }
    }
}

template <class T>
T* hashTable<T>::find(int key)
{
    hash_element res = hash_array[hash_function(key)];
    if (res == NULL)
    {
        return NULL;
    }
    if (res->key == key)
    {
        return res->data;
    }
    else 
    {
        while (res->next != NULL)
        {
            if (res->next->key == key)
            {
                return res->next->data;
            }
            res = res->next;
        }
    }
    return NULL;
}

#endif /* HASHTABLE */