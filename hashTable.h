#ifndef HASHTABLE
#define HASHTABLE
#include <iostream>
#include <cmath>
#define A ((sqrt(5)-1)/2)
#define EXPAND_RATE 10
#define INITIAL_SIZE 10
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
    void print_hash_element();
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
void hash_element<T>::print_hash_element() 
{
std::cout<< key <<std::endl;
// std::cout<< static_cast<std::string>(*data) <<std::endl;
}

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
    int getSize();
    hash_element<T>* operator[](int i);
    ~hashTable();
    void print_hash();
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
    // hashed = key%original_size;
    double frac = (A*(double)key) - (int)(A*(double)key);
    hashed = (int)(original_size*frac);
    return hashed;
}

template <class T>
void hashTable<T>::insert(T* hash_node, int key)
{
    hash_element<T>* new_hash_node = new hash_element<T>(key, hash_node);
    new_hash_node->next = hash_array[hash_function(key)];
    hash_array[hash_function(key)] = new_hash_node;
    num_of_elements+=1;
    if (num_of_elements >= EXPAND_RATE*original_size)
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
                hash_element<T>* temp = current->next;
                current->next = hash_new_array[hash_function(current->key)];//if the slot is thaken,
                hash_new_array[hash_function(current->key)]=current;//then we'll insert current and
                //attach to it its next in line, else we are putting NULL next in line so it doesnt matter.
                current=temp;      
            }
        }
    }
    delete[](this->hash_array);
    this->hash_array=hash_new_array;
}

template <class T>
void hashTable<T>::reduce()
{
    hash_element<T>** hash_new_array = new hash_element<T>* [(this->original_size)/REDUCE_RATE];
    int previous_original_size = this->original_size;//next line we are updating to new size parameters
    original_size= (this->original_size)/REDUCE_RATE;//updating parameter m
    for (int i=0; i<original_size;i++){
        hash_new_array[i]=NULL;
    }
    for(int i=0;i<previous_original_size;i++){
        if(this->hash_array[i]!=NULL){
            hash_element<T>* current=hash_array[i];
            while(current!=NULL){
                hash_element<T>* temp = current->next;
                current->next = hash_new_array[hash_function(current->key)];//if the slot is thaken,
                hash_new_array[hash_function(current->key)]=current;//then we'll insert current and
                //attach to it its next in line, else we are putting NULL next in line so it doesnt matter.
                current=temp;         
            }
        }
    }
    delete[](this->hash_array);
    this->hash_array=hash_new_array;
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
    num_of_elements-=1;
    if (num_of_elements <= (original_size/REDUCE_RATE))
    {
        reduce();
    }
}

template <class T>
int hashTable<T>::getSize(){
    return original_size;
}

template <class T>
hash_element<T>* hashTable<T>::operator[](int i)
{
    return hash_array[i];
}

template <class T>
void hashTable<T>::print_hash(){
    std::cout<<"printing hash: "<<std::endl;
    std::cout<<"hash size is: "<<std::endl;
    std::cout<<original_size<<std::endl;
    std::cout<<"number of elements inserted is: "<<std::endl;
    std::cout<<num_of_elements<<std::endl;
    std::cout<<"printing elements"<<std::endl;
    for(int i=0; i<original_size; i++){
        std::cout<<"this is the " << i << " row"<<std::endl;
        hash_element<T>* current=hash_array[i];
        while(current!=NULL){
            std::cout<<"this key in the same chain:"<<std::endl;
            current->print_hash_element();
            int hashed_key = hash_function(current->key);
            std::cout<<"my hashed key is: "<<hashed_key<<std::endl;
            current=current->next;      
        }
    }
}

#endif /* HASHTABLE */