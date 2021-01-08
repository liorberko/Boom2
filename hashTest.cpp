#include "hashTable.h"
#include <iostream>

struct intStruct
{
    int key;
    char info;
    intStruct(int a , char b) : key(a), info(b) {}
};

int main(){
    hashTable<intStruct> test_hash;
    intStruct a(1, 'a');
    intStruct* a_ptr= &a;
    intStruct b (2,'b');
    intStruct* b_ptr= &b;
    intStruct c(3,'c');
    intStruct* c_ptr= &c;
    intStruct d(4,'d');
    intStruct* d_ptr= &d;
    intStruct e(5,'e');
    intStruct* e_ptr= &e;
    intStruct f(6, 'f');
    intStruct* f_ptr= &f;
    intStruct g(7, 'g');
    intStruct* g_ptr= &g;
    intStruct h(8,'h');
    intStruct* h_ptr= &h;
    intStruct i(9,'i');
    intStruct* i_ptr= &i;
    intStruct j(10,'j');
    intStruct* j_ptr= &j;
    test_hash.insert(a_ptr,1);
    test_hash.insert(b_ptr,2);
    std::cout<<"printing hash with 2 elements"<<std::endl;
    test_hash.print_hash();
    test_hash.insert(c_ptr,3);
    test_hash.insert(d_ptr,4);
    std::cout<<"printing hash with 4 elements size should be 4 now"<<std::endl;
    test_hash.print_hash();
    test_hash.removeElement(2);
    test_hash.removeElement(3);
    std::cout<<"printing hash with 2 elements size should be 2 now, without b"<<std::endl;
    test_hash.print_hash();
    return 1;
}

