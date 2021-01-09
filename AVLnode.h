#ifndef AVLNODE
#define AVLNODE
#include <iostream>


template <class T, class M>
class AVLnode
{
    public:
    T* info; 
    M key;
    int rank;
    int balance;
    int height;
    AVLnode<T,M>* left_son;
    AVLnode<T,M>* right_son;
    AVLnode<T,M>* parent;
    AVLnode(T* info, M key);
    ~AVLnode() = default;
    AVLnode<T,M>& operator=(const AVLnode<T,M> target);
};

template <class T, class M>
AVLnode<T,M>::AVLnode(T* info, M key): info(info), key(key), rank(1), balance(0), height(0), left_son(nullptr), right_son(nullptr), parent(nullptr) {}

template <class T, class M>
AVLnode<T,M>& AVLnode<T,M>::operator=(const AVLnode<T,M> target)
{
    if (this == &target)
    {
        return *this;
    }
    rank=target.rank;
    info = target.info;
    key = target.key;
    balance = target.balance;
    height = target.height;
    left_son = target.left_son;
    right_son = target.right_son;
    parent = target.parent;
    return *this;
}

#endif /* AVLNODE */