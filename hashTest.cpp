#include "hashTable.h"
#include <iostream>

struct intStruct
{
    int key;
    char info;
};

int main(){
    hashTable<intStruct> test_hash;
    intStruct a;
    a.key=1;
    a.info='a';
    intStruct* a_ptr= &a;
    intStruct b;
    a.key=2;
    a.info='b';
    intStruct* b_ptr= &b;
    intStruct c;
    a.key=3;
    a.info='c';
    intStruct* c_ptr= &c;
    intStruct d;
    a.key=4;
    a.info='d';
    intStruct* d_ptr= &d;
    intStruct e;
    a.key=5;
    a.info='e';
    intStruct* e_ptr= &e;
    intStruct f;
    a.key=6;
    a.info='f';
    intStruct* f_ptr= &f;
    intStruct g;
    a.key=7;
    a.info='g';
    intStruct* g_ptr= &g;
    intStruct h;
    a.key=8;
    a.info='h';
    intStruct* h_ptr= &h;
    intStruct i;
    a.key=9;
    a.info='i';
    intStruct* i_ptr= &i;
    intStruct j;
    a.key=10;
    a.info='j';
    intStruct* j_ptr= &j;
    test_hash.insert(a_ptr,1);
    test_hash.insert(b_ptr,1);
    std::cout<<"printing hash with 2 elements"<<std::endl;
    test_hash.print_hash();
    test_hash.insert(c_ptr,1);
    std::cout<<"printing hash with 3 elements size should be 4 now"<<std::endl;
    test_hash.print_hash();
    test_hash.removeElement(2);
    std::cout<<"printing hash with 2 elements size should be 2 now, without b"<<std::endl;
    test_hash.print_hash();
    return 1;
}

